#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QStringList>
#include <BTCSet.h>
#include "qcustomplot.h"

struct _timeseries
{
    QString filename;
    QString name;
    CTimeSeriesSet Data;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap<QString, _timeseries> BTCs;
    QCustomPlot *plot;
    bool PlotData(CBTC& BTC);
    bool AddData(CBTC& BTC);
    double minx=1e12;
    double maxx=-1e12;
    double miny=1e12;
    double maxy=-1e12;

    QVector<QColor> colours = {QColor("cyan"), QColor("magenta"), QColor("red"),
                          QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
                          QColor("green"), QColor("darkGreen"), QColor("yellow"),
                          QColor("blue")};
    bool showlegend = true;


private slots:
    bool On_Add_Data_File();
    bool On_Show_Data();
    bool On_Add_Data();
    bool On_Legend_Clicked();
    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void removeSelectedGraph();
    void removeAllGraphs();
    void mousePress();
    void mouseWheel();
    void selectionChanged();
    void turnSelectedtoSymbols();
    void Deselect();

};



#endif // MAINWINDOW_H

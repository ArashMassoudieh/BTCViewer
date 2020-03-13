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
private slots:
    bool On_Add_Data_File();
    bool On_Show_Data();
    bool On_Add_Data();

};

#endif // MAINWINDOW_H

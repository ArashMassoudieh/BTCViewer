#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "qdebug.h"
#include "qfileinfo.h"
#include "qaction.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plot = new QCustomPlot(ui->centralWidget);
    plot->setObjectName(QStringLiteral("customPlot"));
    ui->treeWidget->setColumnCount(1);
    ui->horizontalLayout->addWidget(plot);
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(2);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
    plot->setSizePolicy(sizePolicy2);
    connect(ui->actionAdd_Data_File,SIGNAL(triggered()),this, SLOT(On_Add_Data_File()));
    connect(ui->Show_Graph, SIGNAL(clicked()),this, SLOT(On_Show_Data()));
    connect(ui->Add_Graph, SIGNAL(clicked()),this, SLOT(On_Add_Data()));
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    connect(ui->actionLegend, SIGNAL(triggered()), this, SLOT(On_Legend_Clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::On_Add_Data_File()
{
    QString filename =  QFileDialog::getOpenFileName(
              this,
              "Open Time Series",
              QDir::currentPath(),
              "All files (*.*)");

        if( !filename.isNull() )
        {
          qDebug() << "selected file path : " << filename.toUtf8();
          QFileInfo f(filename);
          CBTCSet Data(filename.toStdString(),true);

          if (Data.file_not_found || Data.nvars==0)
          {
              qDebug() << "File format is not correct!";
              return false;
          }

          BTCs[f.fileName()].name = f.fileName();
          BTCs[f.fileName()].filename = filename;
          BTCs[f.fileName()].Data = Data;
          qDebug() << "Data was loaded successfully.";
          QTreeWidgetItem *treeitem = new QTreeWidgetItem(ui->treeWidget);
          treeitem->setText(0,f.fileName());
          ui->treeWidget->addTopLevelItem(treeitem);
          for (int i=0; i<Data.nvars; i++)
          {   QTreeWidgetItem *treechlditem = new QTreeWidgetItem(treeitem);
              treechlditem->setText(0,QString::fromStdString(Data.names[i]));
              treeitem->addChild(treechlditem);
          }
          return  true;
        }
        else
        {
            qDebug() << "File " + filename + "was not found!";
            return  false;
        }
}

bool MainWindow::On_Show_Data()
{
    if (ui->treeWidget->selectedItems().size()==0) return false;
    QTreeWidgetItem* selected_item = ui->treeWidget->selectedItems()[0];
    if (selected_item!=nullptr)
    {
        if (selected_item->parent()==nullptr) return false;
        QString DataSet = selected_item->parent()->text(0);
        QString DataColumn = selected_item->text(0);
        qDebug() << DataSet << ", " << DataColumn;
        PlotData(BTCs[DataSet].Data[DataColumn.toStdString()]);
    }
    return true;
}

bool MainWindow::On_Add_Data()
{
    if (ui->treeWidget->selectedItems().size()==0) return false;
    QTreeWidgetItem* selected_item = ui->treeWidget->selectedItems()[0];
    if (selected_item!=nullptr)
    {
        if (selected_item->parent()==nullptr) return false;
        QString DataSet = selected_item->parent()->text(0);
        QString DataColumn = selected_item->text(0);
        qDebug() << DataSet << ", " << DataColumn;
        AddData(BTCs[DataSet].Data[DataColumn.toStdString()]);
    }
    return true;
}

bool MainWindow::PlotData(CBTC& BTC)
{
    minx=1e12;
    maxx=-1e12;
    miny=1e12;
    maxy=-1e12;
    maxx = max(BTC.t[0],maxx);
    maxy = max(BTC.maxC(),maxy);
    minx = min(BTC.t[BTC.n-1],minx);
    miny = min(BTC.minC(),miny);
    plot->legend->setVisible(showlegend);
    plot->clearGraphs();
    QVector<double> x, y; // initialize with entries 0..100
    for (int i=0; i<BTC.n; ++i)
    {
      x.push_back(BTC.t[i]);
      y.push_back(BTC.C[i]);
    }
    // create graph and assign data to it:
    plot->addGraph();
    plot->graph(0)->setName(QString::fromStdString(BTC.name));
    plot->graph(0)->setData(x, y);
    plot->graph(0)->setPen(QPen(colours[plot->graphCount()%10]));
    // give the axes some labels:
    plot->xAxis->setLabel("t");
    plot->yAxis->setLabel("value");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(BTC.t[0], BTC.t[BTC.n-1]);
    plot->yAxis->setRange(BTC.minC()-0.001, BTC.maxC()+0.001);
    plot->replot();

    return true;

}

bool MainWindow::AddData(CBTC& BTC)
{
    plot->legend->setVisible(showlegend);
    maxx = max(BTC.t[0],maxx);
    maxy = max(BTC.maxC(),maxy);
    minx = min(BTC.t[BTC.n-1],minx);
    miny = min(BTC.minC(),miny);
    qDebug() << maxx << "," << minx << "," << miny << "," << maxy;
    QVector<double> x, y; // initialize with entries 0..100
    for (int i=0; i<BTC.n; ++i)
    {
      x.push_back(BTC.t[i]);
      y.push_back(BTC.C[i]);
    }
    // create graph and assign data to it:
    plot->addGraph();
    plot->graph(plot->graphCount()-1)->setName(QString::fromStdString(BTC.name));
    plot->graph(plot->graphCount()-1)->setData(x, y);
    plot->graph(plot->graphCount()-1)->setPen(QPen(colours[plot->graphCount()%10]));
    // give the axes some labels:
    plot->xAxis->setLabel("t");
    plot->yAxis->setLabel("value");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(minx, maxx);
    plot->yAxis->setRange(miny, maxy);
    plot->replot();

    return true;

}

bool MainWindow::On_Legend_Clicked()
{
    showlegend = !showlegend;
    plot->legend->setVisible(showlegend);
    return true;
}


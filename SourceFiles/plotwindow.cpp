#include <QWidget>
#include <QLayout>
#include <QDebug>
#include <QVector>
#include <QFrame>
#include <QScrollArea>
#include <QFont>
#include <QPalette>
#include <QTextEdit>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>

#include "plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) : QWidget(parent)
{
    //this->setObjectName(QString::fromUtf8("TaskTracker - Plot"));
    this->setWindowTitle(QString::fromUtf8("TaskTracker - Plot"));
    this->resize(1330, 300);

    QVector<QTime> x(10); // initialize with entries 0..100
    QVector<double> x1(10), y1(10); // initialize with entries 0..100

    QTime n(14,0,0);
    x[0] = n;
    x1[0] = QTime(0,0,0).secsTo(x[0]);
    y1[0] = 0;


    for (int i=1; i<10; ++i)
    {
      x[i] = x[i-1].addSecs(60);
      x1[i] = QTime(0,0,0).secsTo(x[i]);
      y1[i] = i*i;
    }

    customPlot = new QCustomPlot(this);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    customPlot->xAxis->setTicker(timeTicker);
    timeTicker->setTimeFormat("%h:%m");
    customPlot->xAxis->setRange(QTime(0,0,0).secsTo(x[0]), QTime(0,0,0).secsTo(x[9]));


    customPlot->addGraph();
    customPlot->graph(0)->setData(x1,y1);



    //customPlot->xAxis->setRange(0,10);
    customPlot->yAxis->setRange(0,200);
    QHBoxLayout* plotLayout = new QHBoxLayout;
    plotLayout->addWidget(customPlot);

    this->setLayout(plotLayout);



}

void PlotWindow::plotRectangle(const QString& start, const QString& end, const QString& taskName)
{

}



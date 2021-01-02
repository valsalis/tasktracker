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

/*
 * void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(548, 420);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        verticalLayout->addWidget(customPlot);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi
*/

PlotWindow::PlotWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(QString::fromUtf8("TaskTracker - Plot"));
    this->resize(1330, 800);



    /*QVector<QTime> x(10); // initialize with entries 0..100
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
    */


}

void PlotWindow::createPlot()
{
    customPlot = new QCustomPlot(this);

    double now = QDateTime::currentDateTime().toTime_t();
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:
    for (int gi=0; gi<5; ++gi)
    {
      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(0, 0, 255, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(255/4.0*gi,160,50,150)));
      // generate random walk data:
      QVector<double> time(250), value(250);
      for (int i=0; i<250; ++i)
      {
        time[i] = now + 24*3600*i;
        if (i == 0)
          value[i] = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
        else
          value[i] = qFabs(value[i-1])*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
      }
      customPlot->graph()->setData(time, value);
    }

    // Single Plot Example
    customPlot->addGraph();
    QPen pen;
    pen.setColor(QColor(0, 0, 0, 200));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setBrush(QBrush(QColor(255,0,0,255)));
    // generate random walk data:
    QVector<double> time(250), value(250);
    for (int i=0; i<250; ++i)
    {
      time[i] = now + 24*3600*i;
      if ((i > 0) && (i < 100))
        value[i] = 0;
      else if ((i >= 100) && (i < 200))
        value[i] = 50;
      else
        value[i] = 0;
    }
    customPlot->graph()->setData(time, value);

    // configure bottom axis to show date instead of number:
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    customPlot->xAxis->setTicker(dateTicker);
    // configure left axis text labels:
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(10, "a bit\nlow");
    textTicker->addTick(50, "quite\nhigh");
    customPlot->yAxis->setTicker(textTicker);
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Random wobbly lines value");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, now+24*3600*249);
    customPlot->yAxis->setRange(0, 60);
    // show legend with slightly transparent background brush:
    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));

    QHBoxLayout* plotLayout = new QHBoxLayout;
    plotLayout->addWidget(customPlot);

    this->setLayout(plotLayout);
}


void PlotWindow::plotRectangle(const QString& start, const QString& end, const QString& taskName)
{

}



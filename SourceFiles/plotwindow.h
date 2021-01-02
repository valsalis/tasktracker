#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QVector>

#include <qcustomplot.h>

struct taskData
{
    QString taskDescription;
    double startTime;
    double stopTime;
    bool ticked;

    void setTaskDescription(QString description) { taskDescription = description; }
    void setStartTime(double start) { startTime = start; }
    void setStopTime(double stop) { stopTime = stop; }
    void setTicked(double tick) { ticked = tick; }
};

class PlotWindow : public QWidget
{
    Q_OBJECT
public:
    PlotWindow(QWidget *parent = nullptr);
    virtual ~PlotWindow() {}

    QCustomPlot* customPlot;

    void createPlot();
    void calculateRoundMinMaxTime(QVector<taskData*> vectorTaskData);


    const int numberPlotPoints = 2000;
    double timeMin = 24*60*60;
    double timeMax = 0;

    QVector<taskData*> vectorTaskData;
};


#endif // PLOTWINDOW_H

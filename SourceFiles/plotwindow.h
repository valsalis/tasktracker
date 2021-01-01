#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QVector>

#include <qcustomplot.h>

class PlotWindow : public QWidget
{
    Q_OBJECT
public:
    PlotWindow(QWidget *parent = nullptr);
    virtual ~PlotWindow() {}

    QCustomPlot* customPlot;

    void plotRectangle(const QString& start, const QString& end, const QString& taskName);

    const int numberPlotPoints = 2000;

};

#endif // PLOTWINDOW_H

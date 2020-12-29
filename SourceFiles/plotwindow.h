#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

#include <qcustomplot.h>

class PlotWindow : public QWidget
{
    Q_OBJECT
public:
    PlotWindow(QWidget *parent = nullptr);
    virtual ~PlotWindow() {}

    QCustomPlot* customPlot;


};

#endif // PLOTWINDOW_H

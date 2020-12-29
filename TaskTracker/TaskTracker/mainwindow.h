#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QCalendarWidget>

#include "analogclock.h"
#include "task.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() {}

    void setPushButtonStyle(QPushButton* pushButton);
    void setButtonTabOrder();

private slots:
    void buttonStartStopClicked();
    void buttonClearTimeClicked();
    void buttonAddTaskClicked();
    void buttonImportTasksClicked();
    void buttonExportTasksClicked();
    void buttonPlotClicked();
    void setSelectionFrame();

public slots:
    void timerFunction();

private:
    AnalogClock* analogClock;
    QCalendarWidget* calendar;
    QVBoxLayout* layoutClockCalendar;
    QHBoxLayout* buttonLayout1;
    QHBoxLayout* buttonLayout2;
    QVBoxLayout* layoutLeft;
    QVBoxLayout* layoutRight;

    QPushButton* buttonAddTask;
    QPushButton* buttonClearTime;
    QPushButton* buttonStartStop;
    QPushButton* buttonImportTasks;
    QPushButton* buttonExportTasks;
    QPushButton* buttonPlot;

    Task* taskProva;
    int taskIndex {10};
    QVector<Task*> vectorTask;

};

#endif // MAINWINDOW_H

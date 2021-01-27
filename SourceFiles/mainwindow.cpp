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

#include "mainwindow.h"
#include "plotwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->resize(1380, 300);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(timerFunction()));
    timer->start(1000);

    analogClock = new AnalogClock(this);
    calendar = new QCalendarWidget(this);
    setCalendarStyle(calendar);

    layoutClockCalendar = new QVBoxLayout;
    layoutClockCalendar->addWidget(analogClock);
    layoutClockCalendar->addWidget(calendar);

    buttonAddTask = new QPushButton("ADD TASK");
    setPushButtonStyle(buttonAddTask);
    buttonClearTime = new QPushButton("CLEAR TIME");
    setPushButtonStyle(buttonClearTime);
    buttonStartStop = new QPushButton("START / STOP");
    setPushButtonStyle(buttonStartStop);
    buttonImportTasks = new QPushButton("IMPORT");
    setPushButtonStyle(buttonImportTasks);
    buttonExportTasks = new QPushButton("EXPORT");
    setPushButtonStyle(buttonExportTasks);
    buttonPlot = new QPushButton("PLOT");
    setPushButtonStyle(buttonPlot);

    buttonLayout1 = new QHBoxLayout;
    buttonLayout1->addWidget(buttonAddTask);
    buttonLayout1->addWidget(buttonClearTime);
    buttonLayout1->addWidget(buttonStartStop);
    buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(buttonImportTasks);
    buttonLayout2->addWidget(buttonExportTasks);
    buttonLayout2->addWidget(buttonPlot);

    layoutLeft = new QVBoxLayout;
    layoutLeft->addLayout(buttonLayout1);
    layoutLeft->addLayout(buttonLayout2);
    layoutLeft->addLayout(layoutClockCalendar);

    vectorTask.reserve(taskIndex);

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget* scrollAreaWidgetContents = new QWidget;

    layoutRight = new QVBoxLayout(scrollAreaWidgetContents);

    for(int i = 0; i < taskIndex; i++)
    {
        vectorTask.push_back(new Task(this));
        layoutRight->addWidget(vectorTask[i]);
        connect(vectorTask[i], SIGNAL(newSelectedTask()), this, SLOT(setSelectionFrame()));
    }
    // Initialisation to address activeIndex and previousActiveIndex
    vectorTask[0]->setPurpleFrame(vectorTask[0]);
    //qDebug() << "vectorTask->size() = " << vectorTask.size();

    scrollArea->setWidget(scrollAreaWidgetContents);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(layoutLeft);
    mainLayout->addWidget(scrollArea);

    connect(buttonStartStop, SIGNAL(pressed()), this, SLOT(buttonStartStopClicked()));
    connect(buttonAddTask, SIGNAL(pressed()), this, SLOT(buttonAddTaskClicked()));
    connect(buttonClearTime, SIGNAL(pressed()), this, SLOT(buttonClearTimeClicked()));
    connect(buttonExportTasks, SIGNAL(pressed()), this, SLOT(buttonExportTasksClicked()));
    connect(buttonImportTasks, SIGNAL(pressed()), this, SLOT(buttonImportTasksClicked()));
    connect(buttonPlot, SIGNAL(pressed()), this, SLOT(buttonPlotClicked()));

    this->setLayout(mainLayout);

    setButtonTabOrder();
}

void MainWindow::setSelectionFrame()
{
    //qDebug() << "got here in setSelectionFrame";
    if(Task::activeIndex != Task::previousActiveIndex)
    {
        vectorTask[Task::activeIndex]->setPurpleFrame(vectorTask[Task::activeIndex]);
        vectorTask[Task::previousActiveIndex]->setNoFrame(vectorTask[Task::previousActiveIndex]);
    }
    Task::previousActiveIndex = Task::activeIndex;
}

void MainWindow::buttonStartStopClicked()
{
    //qDebug() << "got here in buttonStartStopClicked";
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    switch(vectorTask[Task::activeIndex]->getTaskState())
    {
        case notStarted:
            vectorTask[Task::activeIndex]->timerLabel1->setText(time_text);
            vectorTask[Task::activeIndex]->timerLabel2->setText(time_text);
            vectorTask[Task::activeIndex]->setTaskState(started);
            break;
        case started:
            vectorTask[Task::activeIndex]->setTaskState(stopped);
            break;
        case stopped:
            vectorTask[Task::activeIndex]->setTaskState(continued);
            break;
        case continued:
            vectorTask[Task::activeIndex]->setTaskState(stopped);
            break;
    }
}

void MainWindow::buttonAddTaskClicked()
{
    //qDebug() << "got here in buttonAddTaskClicked";
    vectorTask.push_back(new Task(this));
    setTabOrder(vectorTask[Task::tasksNumber-1],vectorTask[Task::tasksNumber-2]);
    layoutRight->addWidget(vectorTask[Task::tasksNumber-1]);
    connect(vectorTask[Task::tasksNumber-1], SIGNAL(newSelectedTask()), this, SLOT(setSelectionFrame()));
}

void MainWindow::buttonClearTimeClicked()
{
    //qDebug() << "got here in buttonClearTimeClicked";
    QString time_text_zero = QTime(0,0,0,0).toString("hh : mm : ss");
    vectorTask[Task::activeIndex]->timerLabel1->setText(time_text_zero);
    vectorTask[Task::activeIndex]->timerLabel2->setText(time_text_zero);
    vectorTask[Task::activeIndex]->setTaskState(notStarted);
}

void MainWindow::setPushButtonStyle(QPushButton* pushButton)
{
    pushButton->setFont(QFont("Comic Sans MS",12,QFont::Bold));
    pushButton->setAutoFillBackground(true);
    pushButton->setFlat(true);
    pushButton->setStyleSheet("color: rgb(127, 0, 127); background-color: rgba(0, 127, 127, 120)");
}

void MainWindow::setButtonTabOrder()
{
    setTabOrder(analogClock,calendar);
    setTabOrder(calendar,buttonAddTask);
    setTabOrder(buttonAddTask,buttonClearTime);
    setTabOrder(buttonClearTime,buttonStartStop);
    setTabOrder(buttonStartStop,buttonImportTasks);
    setTabOrder(buttonImportTasks,buttonExportTasks);
    setTabOrder(buttonExportTasks,buttonPlot);
}

void MainWindow::timerFunction()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    if (vectorTask[Task::activeIndex]->getTaskState() == started || vectorTask[Task::activeIndex]->getTaskState() == continued)
    {
        vectorTask[Task::activeIndex]->timerLabel2->setText(time_text);
    }
}

void MainWindow::buttonExportTasksClicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save Tasks",".csv");
    QString file_path;
    // qDebug() << "file_path = " << file_path;
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this,"Export","File NOT saved");
        return;
    }
    QTextStream out(&file);
    QString tasks = "Tasks";
    QString startTime = "Start Time";
    out << "Tasks" << "," << "Start Time" << "," << "Finish Time" << "," << "Ticked" << '\n';
    for(int i = 0; i < Task::tasksNumber; ++i)
    {
        if(vectorTask[i]->lineEdit->text() != "")
        {
            out << vectorTask[i]->lineEdit->text() << ","
                << vectorTask[i]->timerLabel1->text() << ","
                << vectorTask[i]->timerLabel2->text() << ","
                << vectorTask[i]->getCheckBoxState() << '\n';
        }
    }
    file.flush();
    file.close();
}

void MainWindow::buttonImportTasksClicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    if (file.open(QFile::ReadOnly))
    {
        int lineindex = 0;                     // file line counter
        QTextStream in(&file);                 // read to text stream

        while (!in.atEnd())
        {
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
            if(lineindex > 0)
            {
                vectorTask[lineindex-1]->lineEdit->setText(lineToken.at(0));
                vectorTask[lineindex-1]->timerLabel1->setText(lineToken.at(1));
                vectorTask[lineindex-1]->timerLabel2->setText(lineToken.at(2));
                //vectorTask[lineindex-1]->setCheckBoxState(QVariant(lineToken.at(3)).toBool());
            }
            lineindex++;
        }
        file.close();
    }
}

void MainWindow::buttonPlotClicked()
{
    //qDebug() << "got in buttonPlotClicked()";
    PlotWindow* plotWindow = new PlotWindow;

    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    if (file.open(QFile::ReadOnly))
    {
        int lineindex = 0;                     // file line counter
        QTextStream in(&file);                 // read to text stream

        while (!in.atEnd())
        {
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
            if(lineindex > 0)
            {
                plotWindow->vectorTaskData.push_back(new taskData);
                plotWindow->vectorTaskData[lineindex-1]->setTaskDescription(lineToken.at(0));
                plotWindow->vectorTaskData[lineindex-1]->setStartTime(QTime(0,0,0).secsTo(QTime::fromString(lineToken.at(1),"HH:mm:ss")));
                //qDebug() << "lineToken.at(1) = " << lineToken.at(1);
                //qDebug() << "QTime::fromString(lineToken.at(1),HH:mm:ss) = " << QTime::fromString(lineToken.at(1),"HH:mm:ss");
                //qDebug() << "QTime(0,0,0).secsTo(QTime::fromString(lineToken.at(1),HH:mm:ss)) = " << QTime(0,0,0).secsTo(QTime::fromString(lineToken.at(1),"HH:mm:ss"));
                plotWindow->vectorTaskData[lineindex-1]->setStopTime(QTime(0,0,0).secsTo(QTime::fromString(lineToken.at(2),"HH:mm:ss")));
                plotWindow->vectorTaskData[lineindex-1]->setTicked(QVariant(lineToken.at(3)).toBool());
                //qDebug() << plotWindow->vectorTaskData[lineindex-1]->taskDescription;
                //qDebug() << plotWindow->vectorTaskData[lineindex-1]->startTime;
                //qDebug() << plotWindow->vectorTaskData[lineindex-1]->stopTime;
                //qDebug() << plotWindow->vectorTaskData[lineindex-1]->ticked;
            }
            lineindex++;
        }
        file.close();
    }

    plotWindow->createPlot();
    plotWindow->show();
}

void MainWindow::setCalendarStyle(QCalendarWidget* calendar)
{
    calendar->setStyleSheet("QTableView{selection-background-color: purple}");
    // Hack: change calendar title colors
    QWidget *calendarNavBar = calendar->findChild<QWidget *>("qt_calendar_navigationbar");
    if (calendarNavBar)
    {
        QPalette pal = calendarNavBar->palette();
        pal.setColor(calendarNavBar->backgroundRole(), QColor(0, 127, 127, 91));
        pal.setColor(calendarNavBar->foregroundRole(), QColor(127, 0, 127));
        pal.setColor(QPalette::Text, QColor(127, 0, 127));
        calendarNavBar->setPalette(pal);
    }

    QTextCharFormat format;
    format.setForeground(QColor(127, 0, 127));
    format.setBackground(QColor(0, 127, 127, 31));
    format.setFontWeight(QFont::Bold);
    QTextCharFormat formatWeekendDays;
    formatWeekendDays.setForeground(QColor(0, 127, 127));
    formatWeekendDays.setFontWeight(QFont::Bold);
    calendar->setWeekdayTextFormat(Qt::Saturday, formatWeekendDays);
    calendar->setWeekdayTextFormat(Qt::Sunday, formatWeekendDays);
    calendar->setHeaderTextFormat(format);
    QToolButton *prevMonth = findChild<QToolButton*>("qt_calendar_prevmonth");
    QToolButton *nextMonth = findChild<QToolButton*>("qt_calendar_nextmonth");
    prevMonth->setIcon(QIcon(":images/arrow_left.png"));
    nextMonth->setIcon(QIcon(":images/arrow_right.png"));

    calendar->setFixedSize(420,420);
}

#ifndef Task_H
#define Task_H

#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QFont>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QPalette>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCheckBox>

#include "settimewindow.h"

/* Before clicking on START/STOP button, the state is notStarted, then after the first click
 * the state changes to started, and the timers appear and the second one increase the time
 * every second. The second click on START/STOP button stops the second timer and brings the
 * state to stopped. The third click brings the state to continued and the second timer
 * resumes counting. The fourth click brings the state back to stopped. Subsequent clicks will
 * bring the state from stopped to continued or from continued to stopped.
 */
enum state
{   notStarted = 0,
    started = 1,
    stopped = 2,
    continued = 3
};

class Task : public QFrame
{
    Q_OBJECT
public:
    Task(QWidget* parent = nullptr);
    QLabel* timerLabel1;
    QLabel* timerLabel2;
    QLineEdit* lineEdit;
    QCheckBox* checkBox;

    void setLabelStyle(QLabel* label, QFont* font, QString labelName);
    void setLineEditStyle(QLineEdit* lineEdit, QFont* font, QString lineEditName);
    void setFontStyle(QFont* font);
    void setPaletteFrameColor(QPalette* palette, QColor color);
    void setFrame(Task* task, QPalette* palette);
    void setPurpleFrame(Task* task);
    void setNoFrame(Task* Task);

    bool eventFilter(QObject *o, QEvent *e);

    static int activeIndex;
    static int previousActiveIndex;
    static int tasksNumber;

    int getIdentifier() const { return _taskIdentifier; }
    void setIdentifier(int id) { _taskIdentifier = id; }

    state getTaskState() const { return _taskState;  }
    void setTaskState(state state) { _taskState = state; }

    bool getCheckBoxState() const { return _checkBoxState; }
    void setCheckBoxState(bool state) { _checkBoxState = state; }

    void openSetTimeWindow();

    SetTimeWindow* setTimeWindow;

    bool changeTimerLabel1 = false;
    bool changeTimerLabel2 = false;

public slots:
    void toggleCheckBoxState() { if(_checkBoxState) {setCheckBoxState(false);} else {setCheckBoxState(true);} };
    void changeTime(QTime time);

signals:
    void newSelectedTask();
    void taskStartedByPressingReturnEnter();

private:
    int _taskIdentifier;
    state _taskState = notStarted;
    bool _checkBoxState;
};

#endif // Task_H

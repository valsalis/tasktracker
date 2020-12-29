#include "task.h"

int Task::tasksNumber {0};
int Task::activeIndex {0};
int Task::previousActiveIndex {0};

Task::Task(QWidget* parent) : QFrame(parent)
{
    this->setIdentifier(tasksNumber);
    tasksNumber++;
    setNoFrame(this);

    QHBoxLayout* taskLayout = new QHBoxLayout();

    QFont* fontTask = new QFont();
    setFontStyle(fontTask);

    timerLabel1 = new QLabel;
    timerLabel1->installEventFilter(this);
    setLabelStyle(timerLabel1, fontTask, QString::fromUtf8("labelStartTime"));

    timerLabel2 = new QLabel;
    timerLabel2->installEventFilter(this);
    setLabelStyle(timerLabel2, fontTask, QString::fromUtf8("labelStopTime"));

    lineEdit = new QLineEdit;
    lineEdit->installEventFilter(this);
    setLineEditStyle(lineEdit, fontTask, QString::fromUtf8("lineEdit"));

    taskLayout->addWidget(lineEdit);
    taskLayout->addWidget(timerLabel1);
    taskLayout->addWidget(timerLabel2);

    this->setLayout(taskLayout);
}

void Task::setLabelStyle(QLabel* label, QFont* font, QString labelName)
{
    label->setObjectName(labelName);
    label->setEnabled(false);
    label->setMinimumSize(QSize(160, 30));
    label->setMaximumSize(QSize(160, 30));
    label->setFont(*font);
    label->setFrameShape(QFrame::WinPanel);
    label->setAlignment(Qt::AlignCenter);

    QPalette paletteLabel;
    QPalette* pPaletteLabel = &paletteLabel;
    QColor grey = QColor(100, 100, 100, 255);
    setPaletteFrameColor(pPaletteLabel, grey);

    label->setPalette(paletteLabel);
}

void Task::setLineEditStyle(QLineEdit* lineEdit, QFont* font, QString lineEditName)
{
    lineEdit->setObjectName(lineEditName);
    lineEdit->setMinimumSize(QSize(500, 30));
    lineEdit->setMaximumSize(QSize(1000, 30));
    lineEdit->setFont(*font);
}

void Task::setFontStyle(QFont* font)
{
    font->setPointSize(14);
    font->setBold(true);
    font->setWeight(75);
}

void Task::setPaletteFrameColor(QPalette* palette, QColor color)
{
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette->setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(color);
    brush1.setStyle(Qt::SolidPattern);
    palette->setBrush(QPalette::Active, QPalette::Light, brush1);
    QBrush brush2(color);
    brush2.setStyle(Qt::SolidPattern);
    palette->setBrush(QPalette::Active, QPalette::Dark, brush2);
    palette->setBrush(QPalette::Active, QPalette::Text, brush);
    palette->setBrush(QPalette::Active, QPalette::ButtonText, brush);
    QBrush brush3(QColor(0, 0, 0, 128));
    brush3.setStyle(Qt::SolidPattern);
    palette->setBrush(QPalette::Active, QPalette::PlaceholderText, brush3);
    palette->setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette->setBrush(QPalette::Inactive, QPalette::Light, brush1);
    palette->setBrush(QPalette::Inactive, QPalette::Dark, brush2);
    palette->setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette->setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette->setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
    palette->setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
    palette->setBrush(QPalette::Disabled, QPalette::Light, brush1);
    palette->setBrush(QPalette::Disabled, QPalette::Dark, brush2);
    palette->setBrush(QPalette::Disabled, QPalette::Text, brush2);
    palette->setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
    palette->setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
}

void Task::setFrame(Task* task, QPalette* palette)
{
    task->setPalette(*palette);
    task->setAutoFillBackground(false);
    task->setFrameShape(QFrame::Panel);
    task->setFrameShadow(QFrame::Sunken);
    task->setLineWidth(8);
    task->setMidLineWidth(0);
}

void Task::setPurpleFrame(Task* task)
{
    QPalette palettePurpleFrame;
    QPalette* pPalettePurpleFrame = &palettePurpleFrame;
    QColor purple = QColor(127, 0, 127, 255);
    setPaletteFrameColor(pPalettePurpleFrame, purple);
    setFrame(task, pPalettePurpleFrame);
}

void Task::setNoFrame(Task* Task)
{
    QPalette paletteNoFrame;
    QColor lightGrey = QColor(240, 240, 240, 255);
    QBrush brush(lightGrey);
    brush.setStyle(Qt::SolidPattern);
    paletteNoFrame.setBrush(QPalette::Active, QPalette::WindowText, brush);
    paletteNoFrame.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

    Task->setPalette(paletteNoFrame);
    Task->setAutoFillBackground(false);
    Task->setFrameShape(QFrame::Panel);
    Task->setFrameShadow(QFrame::Plain);
    Task->setLineWidth(8);
    Task->setMidLineWidth(0);
}

bool Task::eventFilter(QObject* o, QEvent* e)
{
    //qDebug() << "got in Task::eventFilter. taskIdentifier = " << this->getIdentifier();

    if((o == timerLabel1 || o == timerLabel2 || o == lineEdit) && e->type() == QMouseEvent::MouseButtonPress)
    {
        Task::activeIndex = this->getIdentifier();
        emit newSelectedTask();
    }

    if(o == lineEdit && e->type() == QKeyEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
        if(keyEvent->key() == Qt::Key_Tab && Task::activeIndex < (Task::tasksNumber - 1))
        {
            Task::activeIndex++;
        }
        if(keyEvent->key() == Qt::Key_Backtab && Task::activeIndex > 0  )
        {
            Task::activeIndex--;
        }
        emit newSelectedTask();
    }
    return QObject::eventFilter(o,e);
}

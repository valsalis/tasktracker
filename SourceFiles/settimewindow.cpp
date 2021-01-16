#include "settimewindow.h"
#include "task.h"

SetTimeWindow::SetTimeWindow(QWidget *parent) : QDialog(parent)
{
    this->resize(200, 60);
    this->setWindowTitle(QString::fromUtf8("Time"));
    timeLabel1 = new QLineEdit;
    timeLabel2 = new QLineEdit;
    timeLabel3 = new QLineEdit;
    timeLabel4 = new QLineEdit;

    QPushButton* buttonSetTime = new QPushButton("Set Time");

    QLabel* label1 = new QLabel;
    label1->setText(":");

    QFont* fontTask = new QFont();
    setFontStyle(fontTask);

    setLineEditStyle(timeLabel1, fontTask, QString::fromUtf8("labelTime1"));
    setLineEditStyle(timeLabel2, fontTask, QString::fromUtf8("labelTime2"));
    setLineEditStyle(timeLabel3, fontTask, QString::fromUtf8("labelTime3"));
    setLineEditStyle(timeLabel4, fontTask, QString::fromUtf8("labelTime4"));

    QHBoxLayout* setTimeWindowLayout = new QHBoxLayout();

    setTimeWindowLayout->addWidget(timeLabel1);
    setTimeWindowLayout->addWidget(timeLabel2);
    setTimeWindowLayout->addWidget(label1);
    setTimeWindowLayout->addWidget(timeLabel3);
    setTimeWindowLayout->addWidget(timeLabel4);
    setTimeWindowLayout->addWidget(buttonSetTime);

    connect(buttonSetTime, SIGNAL(pressed()), this, SLOT(buttonSetTimeClicked()));
    connect(this, &QDialog::finished,[=] {emit newSetTime(newTime);});

    this->setLayout(setTimeWindowLayout);
}

void SetTimeWindow::setLineEditStyle(QLineEdit* lineEdit, QFont* font, QString lineEditName)
{
    lineEdit->setObjectName(lineEditName);
    lineEdit->setMinimumSize(QSize(10, 30));
    lineEdit->setMaximumSize(QSize(25, 30));
    lineEdit->setFont(*font);
}

void SetTimeWindow::setFontStyle(QFont* font)
{
    font->setPointSize(14);
    font->setBold(true);
    font->setWeight(75);
}

void SetTimeWindow::setPaletteFrameColor(QPalette* palette, QColor color)
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

void SetTimeWindow::buttonSetTimeClicked()
{
    //qDebug() << "got here in buttonStartStopClicked";
    int time_hours = 0;
    time_hours = time_hours + (timeLabel1->text()).toInt()*10;
    time_hours = time_hours + (timeLabel2->text()).toInt();

    int time_minutes = 0;
    time_minutes = time_minutes + (timeLabel3->text()).toInt()*10;
    time_minutes = time_minutes + (timeLabel4->text()).toInt();

    int total_time_seconds = time_hours*3600 + time_minutes*60;

    newTime = QTime(0,0,0,0).addSecs(total_time_seconds);
}

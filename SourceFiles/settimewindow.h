#ifndef SETTIMEWINDOW_H
#define SETTIMEWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPalette>
#include <QPushButton>
#include <QDebug>
#include <QTime>

class SetTimeWindow : public QDialog
{
    Q_OBJECT
public:
    SetTimeWindow(QWidget *parent = nullptr);
    virtual ~SetTimeWindow() {}
    void setLineEditStyle(QLineEdit* lineEdit, QFont* font, QString lineEditName);
    void setFontStyle(QFont* font);
    void setPaletteFrameColor(QPalette* palette, QColor color);
    QTime newTime;
signals:
void newSetTime(QTime time);

private slots:
    void buttonSetTimeClicked();
private:
    QLineEdit* timeLabel1;
    QLineEdit* timeLabel2;
    QLineEdit* timeLabel3;
    QLineEdit* timeLabel4;
};

#endif // SETTIMEWINDOW_H

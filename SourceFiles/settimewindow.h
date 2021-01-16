#ifndef SETTIMEWINDOW_H
#define SETTIMEWINDOW_H

#include <QDialog>
#include <QWidget>

class SetTimeWindow : public QDialog
{
    Q_OBJECT
public:
    SetTimeWindow(QWidget *parent = nullptr);
    virtual ~SetTimeWindow() {}

private:
    int x;

};

#endif // SETTIMEWINDOW_H

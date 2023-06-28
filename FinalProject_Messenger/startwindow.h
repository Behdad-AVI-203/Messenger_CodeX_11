#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "group.h"
namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_actionCreat_Group_triggered();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H

#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "group.h"
#include <QString>
namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    void SetTokenFromUserName(QString token);
    QString GetTokenFromUserName();

private slots:
    void on_actionCreat_Group_triggered();

private:
    Ui::StartWindow *ui;
    QString Token;
};

#endif // STARTWINDOW_H

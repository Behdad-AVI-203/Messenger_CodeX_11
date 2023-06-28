#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include <dialog_create_group.h>
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
    void SetUsernameFromUserName(QString username);
    QString GetTokenFromUserName();
    QString GetUsernameFromUserName();


private slots:
    void on_actionCreat_Group_triggered();

    void on_pushButton_entermessage_2_clicked();

private:
    Ui::StartWindow *ui;
    QString Token;
    QString Username;
};

#endif // STARTWINDOW_H

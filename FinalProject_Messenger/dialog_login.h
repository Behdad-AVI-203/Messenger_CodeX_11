#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
#include"user.h"

extern QVector<User> U;

namespace Ui {
class Dialog_Login;
}

class Dialog_Login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Login(QWidget *parent = nullptr);
    ~Dialog_Login();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_cancel_clicked();
    void on_checkBox_setecho_clicked(bool checked);
private:
    Ui::Dialog_Login *ui;
};

#endif // DIALOG_LOGIN_H

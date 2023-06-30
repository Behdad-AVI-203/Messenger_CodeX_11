#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
<<<<<<< HEAD
#include"user.h"

extern QVector<User> U;

=======
#include <QString>
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc
namespace Ui {
class Dialog_Login;
}

class Dialog_Login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Login(QWidget *parent = nullptr);
    ~Dialog_Login();
    void SetUsernameFromLoginWindow(QString username);

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_cancel_clicked();



    void on_checkBox_setecho_clicked(bool checked);

private:
    Ui::Dialog_Login *ui;
    QString Username;
};

#endif // DIALOG_LOGIN_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"all_include.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_signup_clicked();

    void on_pushButton_login_clicked();

    void on_actionLogout_triggered();

private:
    Ui::MainWindow *ui;
};

class user{
private:
    QString firstname;
    QString lastname;
    QString username;
    QString password;
public:
    user(QString firstname,QString lastname,QString username,QString password){
    this->firstname=firstname;
    this->lastname=lastname;
    this->username=username;
    this->password=password;
    }

};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialog_signup.h"
#include "dialog_login.h"
#include"dialog_logout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_signup_clicked()
{
    Dialog_signup* window=new Dialog_signup(this);
    window->show();

}


void MainWindow::on_pushButton_login_clicked()
{
    Dialog_Login* window = new Dialog_Login(this);
    window->show();
}


void MainWindow::on_actionLogout_triggered()
{
    Dialog_Logout* window=new Dialog_Logout(this);
    window->show();
}


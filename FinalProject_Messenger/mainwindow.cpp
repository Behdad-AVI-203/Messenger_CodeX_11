#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialog_signup.h"
#include "dialog_login.h"

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


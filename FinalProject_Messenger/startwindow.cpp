#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::SetTokenFromUserName(QString token)
{
    Token = token;
}

QString StartWindow::GetTokenFromUserName()
{
    return Token;
}

void StartWindow::on_actionCreat_Group_triggered()
{
    dialog_create_group* window = new dialog_create_group();
    window->show();
}


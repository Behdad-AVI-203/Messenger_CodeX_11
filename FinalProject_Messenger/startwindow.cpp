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
    Group* newGroup = new Group();

    newGroup->CreatedGroup("title",Token,"ali");

}


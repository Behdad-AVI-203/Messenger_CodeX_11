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

void StartWindow::SetUsernameFromUserName(QString username)
{
    Username = username;
}

QString StartWindow::GetTokenFromUserName()
{
    return Token;
}

QString StartWindow::GetUsernameFromUserName()
{
    return Username;
}

void StartWindow::on_actionCreat_Group_triggered()
{
    dialog_create_group* window = new dialog_create_group();
    window->SetCreateGroupToken(Token);
    window->show();
}


void StartWindow::on_pushButton_entermessage_2_clicked()
{
    Group* G = new Group();qDebug()<<"skfksj;sdf";
    G->AddMessageToGroupWithGroupName(Username,ui->lineEdit_message_2->text(),ui->lineEdit_searchgroupe->text());

}


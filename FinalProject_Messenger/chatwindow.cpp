#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "sendtocontact.h"
ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::SetChatWindowToken(string token)
{
    this->token = token;
}

string ChatWindow::GetChatWindowToken()
{
    return token;
}

void ChatWindow::on_SendMessageToUserButton_clicked()
{
    SendToContact* window = new SendToContact();
    window->SetChatWindowToken(token);
    window->show();
}


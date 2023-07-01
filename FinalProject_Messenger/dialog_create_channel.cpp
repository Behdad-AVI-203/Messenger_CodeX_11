#include "dialog_create_channel.h"
#include "ui_dialog_create_channel.h"

Dialog_Create_Channel::Dialog_Create_Channel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Create_Channel)
{
    ui->setupUi(this);
}

Dialog_Create_Channel::~Dialog_Create_Channel()
{
    delete ui;
}

void Dialog_Create_Channel::SetTokenFromChannel(QString token)
{
    Token = token;
}

void Dialog_Create_Channel::SetCreateChannelToken(QString token)
{
    Token = token;
}

void Dialog_Create_Channel::on_pushButton_create_clicked()
{
    Channel* C = new Channel();
    C->CreateNewChannel(Token,ui->lineEdit_channeltitle->text(),ui->lineEdit_channelname->text());
    close();
}


void Dialog_Create_Channel::on_pushButton_cancel_clicked()
{
    this->close();
}


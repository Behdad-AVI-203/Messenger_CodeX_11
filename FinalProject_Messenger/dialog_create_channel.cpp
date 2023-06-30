#include "dialog_create_channel.h"
#include "ui_dialog_create_channel.h"

dialog_create_Channel::dialog_create_Channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_create_Channel)
{
    ui->setupUi(this);
}

dialog_create_Channel::~dialog_create_Channel()
{
    delete ui;
}

void dialog_create_Channel::SetTokenFromChannel(QString token)
{
    Token = token;
}

void dialog_create_Channel::SetCreateChannelToken(QString token)
{
    Token = token;
}

void dialog_create_Channel::on_CreatedButton_clicked()
{
    Channel* C = new Channel();
    C->CreateNewChannel(Token,ui->ChannelTitleLineEdit->text(),ui->ChannelNameLineEdit->text());
    close();
}


#include "dialog_create_channel.h"
#include "ui_dialog_create_channel.h"
#include "all_include.h"
#include"dialog_login.h"

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

void Dialog_Create_Channel::on_pushButton_create_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "createchannel?token=" + U[0].GetToken() +
    + "&channel_name=" +ui->lineEdit_channelname->text()+"&channel_title="+ui->lineEdit_channeltitle->text();
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();
        if(jsonObject.value("code").toString() == "200")
        {
            QMessageBox::information(this,"Creat Cannel",jsonObject.value("message").toString());
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"Creat Channel",jsonObject.value("message").toString());
        }
    }
}


void Dialog_Create_Channel::on_pushButton_cancel_clicked()
{
    this->close();
}


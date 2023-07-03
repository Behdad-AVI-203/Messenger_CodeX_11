#include "dialog_join_channel.h"
#include "ui_dialog_join_channel.h"
#include"dialog_login.h"
#include "all_include.h"


Dialog_Join_Channel::Dialog_Join_Channel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Join_Channel)
{
    ui->setupUi(this);
}

Dialog_Join_Channel::~Dialog_Join_Channel()
{
    delete ui;
}

void Dialog_Join_Channel::on_pushButton_join_clicked()
{
    QString Exception;
    QString urlString = "http://api.barafardayebehtar.ml:8080/joinchannel?token=";
    urlString+=U[0].GetToken()+"&channel_name="+ui->lineEdit_channelname->text();
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished
    try{
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.value("code").toString() == "200")
            {
                QMessageBox::information(this,"Join Channel",jsonObject.value("message").toString());
                this->close();
            }
            else
            {
                QMessageBox::warning(this,"Join Channel",jsonObject.value("message").toString());
                Exception = jsonObject.value("message").toString();
            }
        }
        else
        {
            throw std::invalid_argument("invalid Argument");
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::information(this,"Exception",e.what());
    }
}


void Dialog_Join_Channel::on_pushButton_cancel_clicked()
{
    this->close();
}


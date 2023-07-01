#include "dialog_join_channel.h"
#include "ui_dialog_join_channel.h"
#include "channel.h"

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

void Dialog_Join_Channel::SetJoinChannelToken(QString token)
{
    Token = token;
}

QString Dialog_Join_Channel::GetJoinChannelToken()
{
    return Token;
}

void Dialog_Join_Channel::on_pushButton_join_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/joinchannel?token=";
    urlString+=Token+"&channel_name="+ui->lineEdit_channelname->text();
    qDebug()<<"url = "<<urlString<<"\n";

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
            QMessageBox::information(this,"respons by server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "404")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "204")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "401")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
    }
    close();
}


void Dialog_Join_Channel::on_pushButton_cancel_clicked()
{
    this->close();
}


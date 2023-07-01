#include "dialog_join_channel.h"
#include "ui_dialog_join_channel.h"
#include "channel.h"
dialog_join_Channel::dialog_join_Channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_join_Channel)
{
    ui->setupUi(this);
}

dialog_join_Channel::~dialog_join_Channel()
{
    delete ui;
}

void dialog_join_Channel::SetJoinChannelToken(QString token)
{
    Token = token;
}

QString dialog_join_Channel::GetJoinChannelToken()
{
    return Token;
}

void dialog_join_Channel::on_JoinButton_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/joinchannel?token=";
    urlString+=Token+"&channel_name="+ui->ChannelNameLineEdit->text();
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


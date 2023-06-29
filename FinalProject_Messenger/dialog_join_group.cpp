#include "dialog_join_group.h"
#include "ui_dialog_join_group.h"

dialog_Join_Group::dialog_Join_Group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_Join_Group)
{
    ui->setupUi(this);
}

dialog_Join_Group::~dialog_Join_Group()
{
    delete ui;
}

void dialog_Join_Group::SetJoinGroupToken(QString token)
{
    Token = token;
}

QString dialog_Join_Group::GetJoinGroupToken()
{
    return Token;
}



void dialog_Join_Group::on_JoinBuuton_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/joingroup?token=";
    urlString+=Token+"&group_name="+ui->NameGroupLineEdit->text();
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
            QMessageBox::information(this,"respons by server","Creat group successfully");
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


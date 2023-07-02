#include "dialog_join_group.h"
#include "ui_dialog_join_group.h"
#include"dialog_login.h"


Dialog_Join_Group::Dialog_Join_Group(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Join_Group)
{
    ui->setupUi(this);
}

Dialog_Join_Group::~Dialog_Join_Group()
{
    delete ui;
}

void Dialog_Join_Group::SetJoinGroupToken(QString token)
{
    Token = token;
}

QString Dialog_Join_Group::GetJoinGroupToken()
{
    return Token;
}

void Dialog_Join_Group::on_pushButton_join_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/joingroup?token=";
    urlString+=U[0].GetToken()+"&group_name="+ui->lineEdit_groupname->text();
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
            QMessageBox::information(this,"Join Group",jsonObject.value("message").toString());
        }
        else
        {
            QMessageBox::warning(this,"Join Group",jsonObject.value("message").toString());
        }

    }
    close();
}


void Dialog_Join_Group::on_pushButton_cancel_clicked()
{
    this->close();
}


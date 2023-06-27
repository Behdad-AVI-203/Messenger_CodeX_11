#include "dialog_login.h"
#include "ui_dialog_login.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <thread>
#include <iostream>
#include <string>
using namespace std;

dialog_login::dialog_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_login)
{
    ui->setupUi(this);
}

dialog_login::~dialog_login()
{
    delete ui;
}

void dialog_login::on_OKBuuton_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "login?" + "username=" + ui->UsernameLineEdit->text()
    + "&password=" +ui->PasswordLineEdit->text();

    QUrl url(urlString);

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        QString returnMessage = jsonObject.value("message").toString();
        QString returnCode = jsonObject.value("code").toString();

        if(returnCode == "200")
        {
            QString returnToken = jsonObject.value("token").toString();
            QMessageBox::information(this,"Response sent by the server",data);
            QString temp = returnToken;
            qDebug()<<"token = "<<returnToken<<"\n";
        }
        if(returnCode == "404")
        {
            QMessageBox::warning(this,"Response sent by the server","Your request was not successful and the requested information was not found");
        }
        if(returnCode == "204")
        {
            QMessageBox::warning(this,"Response sent by the server","Your request was not successful and due to the duplicate information, it is not possible to make a request to the server.");
        }
        if(returnCode == "401")
        {
            QMessageBox::warning(this,"Response sent by the server","Your request was not successful and the information you provided to the server is incorrect");
        }
//        else
//        {
//            QMessageBox::information(this,"Error to Connect","Unable to connect to the server at this time, please try again later (thanks)");
//        }

    }


}




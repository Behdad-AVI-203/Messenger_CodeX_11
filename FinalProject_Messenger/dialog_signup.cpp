#include "dialog_signup.h"
#include "ui_dialog_signup.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include<QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QMessageBox>
#include<thread>
#include"mainwindow.h"

Dialog_signup::Dialog_signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_signup)
{
    ui->setupUi(this);
}

Dialog_signup::~Dialog_signup()
{
    delete ui;
}

void Dialog_signup::on_checkBox_echomode_clicked(bool checked)
{
    if(checked){
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
    else{
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
}


void Dialog_signup::on_buttonBox_rejected()
{
    this->close();
}


void Dialog_signup::on_buttonBox_accepted()
{
    QString temp_url="http://api.barafardayebehtar.ml:8080/signup?";
    temp_url+="username="+ui->lineEdit_username->text()+"&"+"password="+ui->lineEdit_password->text()+"&"+"firstname="+ui->lineEdit_firstname->text()+"&"+"lastname="+ui->lineEdit_lastname->text();
    QUrl url(temp_url); // The API endpoint to request
    QNetworkAccessManager manager;

    QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request

    QEventLoop loop;
            connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec(); // Block until the request is finished
            if (reply->error() == QNetworkReply::NoError) {
                // If the request was successful, read the response
                QByteArray data = reply->readAll();
                QMessageBox::information(this,"response",data);

                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();

                QString message = jsonObj.value("message").toString();
                QString code = jsonObj.value("code").toString();

                qDebug()<<"message:"<<message<<", code: "<<code;
            } else {
                // If there was an error, display the error message
                qDebug() << "Error:" << reply->errorString();
            }

            // Cleanup the reply object and exit the application
            reply->deleteLater();
}




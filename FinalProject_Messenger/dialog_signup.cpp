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
    ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
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

void Dialog_signup::on_pushButton_signup_clicked()
{
    if(!ui->lineEdit_username->text().isEmpty()&&!ui->lineEdit_password->text().isEmpty()){
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
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                    QJsonObject jsonObj = jsonDoc.object();

                    if(jsonObj["code"].toString()=="200"){

                        QMessageBox::information(this,"SignUp",jsonObj["message"].toString());
                        this->close();
                    }
                    else{
                        QMessageBox::warning(this,"SignUp",jsonObj["message"].toString());
                    }

                }
                else {
                   QMessageBox::warning(this,"SignUp","You are not connected");
                }

                // Cleanup the reply object and exit the application
                reply->deleteLater();
    }
}


void Dialog_signup::on_pushButton_cancel_clicked()
{
    this->close();
}


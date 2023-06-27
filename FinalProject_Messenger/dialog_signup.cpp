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

void Dialog_signup::on_pushButton_ok_clicked()
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

                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();

                QString code=jsonObj.value("code").toString();

                if(code== "200"){
                    QMessageBox::information(this,"response","Your account has been successfully created");

                }
                else if(code== "204"){
                    QMessageBox::critical(this,"response","You have already created an account with this username");
                }


            } else {
                // If there was an error, display the error message
                QMessageBox::warning(this,"Erorr","Your attempt was unsuccessful.Pleas Try again");
            }

            // Cleanup the reply object and exit the application
            reply->deleteLater();
}


void Dialog_signup::on_pushButton_cancel_clicked()
{
      this->close();
}


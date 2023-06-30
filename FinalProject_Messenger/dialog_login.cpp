#include "dialog_login.h"
#include "ui_dialog_login.h"
#include "dialog_login.h"
#include "ui_dialog_login.h"
#include"startwindow.h"
#include "user.h"
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

QVector<User> U;

Dialog_Login::Dialog_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Login)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
}

Dialog_Login::~Dialog_Login()
{
    delete ui;
}

void Dialog_Login::SetUsernameFromLoginWindow(QString username)
{
    Username = username;
}

void Dialog_Login::on_pushButton_login_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "login?" + "username=" + ui->lineEdit_username->text()
    + "&password=" +ui->lineEdit_password->text();

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

        if(jsonObject["code"].toString() == "200")
        {
<<<<<<< HEAD
            QMessageBox::information(this,"Response sent by the server",jsonObject["message"].toString());

            User temp(ui->lineEdit_username->text(),ui->lineEdit_password->text(),jsonObject["token"].toString());
            U.push_back(temp);
            //qDebug() << U[0].GetToken();
=======
            QString loginToken = jsonObject.value("token").toString();
            QMessageBox::information(this,"Response sent by the server",jsonObject.value("message").toString());
            User temp(ui->lineEdit_username->text(),ui->lineEdit_password->text(),jsonObject.value("token").toString());
            user.push_back(temp);
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc
            this->close();

            QString tempToken; //if token is null , read token from file;
            if(loginToken!="") {
                QFile file("Token.txt");
                file.open(QIODevice::Append);
                QTextStream outFile(&file);
                outFile<<loginToken;
                file.close();
            }
            else
            {
                QFile file("Token.txt");
                file.open(QIODevice::ReadOnly|QIODevice::Text);
                QTextStream inFile(&file);
                tempToken = inFile.readAll();
                file.close();
                loginToken = tempToken;
                qDebug()<<"loginToken = "<<loginToken<<"\n";
            }

            StartWindow* startwindow = new StartWindow();
            startwindow->SetTokenFromUserName(loginToken);
            startwindow->SetUsernameFromUserName(ui->lineEdit_username->text());
            startwindow->show();
        }
        if(jsonObject["code"].toString() == "404")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject["message"].toString());
        }
        if(jsonObject["code"].toString() == "204")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject["message"].toString());
        }
        if(jsonObject["code"].toString() == "401")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject["message"].toString());
        }

    }

}


void Dialog_Login::on_pushButton_cancel_clicked()
{
     this->close();
}

void Dialog_Login::on_checkBox_setecho_clicked(bool checked)
{
    if(checked){
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
    else{
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
}


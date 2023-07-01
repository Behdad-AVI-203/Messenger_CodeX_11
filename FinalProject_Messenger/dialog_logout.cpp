#include "dialog_logout.h"
#include "ui_dialog_logout.h"
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QJsonDocument>
#include<QJsonObject>
#include<QMessageBox>

Dialog_Logout::Dialog_Logout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Logout)
{
    ui->setupUi(this);
}

Dialog_Logout::~Dialog_Logout()
{
    delete ui;
}

void Dialog_Logout::on_pushButton_2_clicked()
{
    this->close();
}


void Dialog_Logout::on_pushButton_logout_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "logout?" + "username=" + ui->lineEdit_username->text()
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
            QMessageBox::information(this,"LogOut",jsonObject["message"].toString());
             this->close();

        }
            else{
             QMessageBox::warning(this,"LogOut",jsonObject["message"].toString());
}
    }
}


void Dialog_Logout::on_checkBox_setecho_clicked(bool checked)
{
    if(checked){
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
    else{
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
}


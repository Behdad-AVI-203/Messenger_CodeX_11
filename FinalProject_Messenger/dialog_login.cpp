#include "dialog_login.h"
#include "ui_dialog_login.h"
#include "dialog_login.h"
#include "ui_dialog_login.h"
#include"startwindow.h"
#include "user.h"
#include "all_include.h"

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

void Dialog_Login::on_pushButton_login_clicked()
{
    if(!ui->lineEdit_username->text().isEmpty()&&!ui->lineEdit_password->text().isEmpty()){
        QString urlString = "http://api.barafardayebehtar.ml:8080/";
        urlString = urlString + "login?" + "username=" + ui->lineEdit_username->text()
        + "&password=" +ui->lineEdit_password->text();
        QUrl url(urlString);
        QNetworkAccessManager manager;
        QNetworkReply* reply = manager.get(QNetworkRequest(url));
        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();
        if(reply->error()==QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject["code"].toString() == "200")
            {
                if(jsonObject["token"].toString()!=""){
                QMessageBox::information(this,"LogIn",jsonObject["message"].toString());
                User temp(ui->lineEdit_username->text(),ui->lineEdit_password->text(),jsonObject["token"].toString());
                U.push_back(temp);
                this->close();
                StartWindow* startwindow = new StartWindow(this);
                startwindow->show();
                }
                else{
                    QMessageBox::warning(this,"LogIn","You have not Logged out of the program.\nPlease logout from the program first");
                }
            }
            else
            {
                QMessageBox::warning(this,"LogIn",jsonObject["message"].toString());
            }
        }
        else{
            QMessageBox::warning(this,"LogIn","You are not connected");
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


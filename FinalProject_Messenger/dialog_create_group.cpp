#include "dialog_create_group.h"
#include "ui_dialog_create_group.h"
#include"dialog_login.h"
#include "all_include.h"
#include"dialog_login.h"


Dialog_Create_Group::Dialog_Create_Group(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Create_Group)
{
    ui->setupUi(this);
}

Dialog_Create_Group::~Dialog_Create_Group()
{
    delete ui;
}

void Dialog_Create_Group::on_pushButton_create_clicked()
{
        QString urlString = "http://api.barafardayebehtar.ml:8080/";
        urlString = urlString + "creategroup?token=" + U[0].GetToken() +
        + "&group_name=" +ui->lineEdit_groupname->text()+"&group_title="+ui->lineEdit_grouptitle->text();
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
                QMessageBox::information(this,"Creat Group",jsonObject.value("message").toString());
                this->close();
            }
            else
            {
                QMessageBox::warning(this,"Creat Group",jsonObject.value("message").toString());
            }
        }
}

void Dialog_Create_Group::on_pushButton_cancel_clicked()
{
    this->close();
}


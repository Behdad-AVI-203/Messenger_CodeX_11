#include "startwindow.h"
#include "ui_startwindow.h"
#include"startwindow.h"
#include"dialog_login.h"
#include"user.h"
#include"contact.h"
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
#include<thread>
#include<QListWidgetItem>
#include<QListWidget>
#include <QListView>
#include <QStringListModel>
#include <QMessageBox>
#include<QGridLayout>
#include<QTextCursor>
#include<QTimer>
#include<QDir>

//QVector<User> U;
QString contactname;

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    ui->textEdit_groupmessages->setReadOnly(true);
    ui->textEdit_channelmessages->setReadOnly(true);
    ui->textEdit_conversation->setReadOnly(true);
    ui->pushButton_entermessage_contact->setEnabled(false);
    ui->pushButton_entermessage_group->setEnabled(false);
    ui->pushButton_entermessage_channel->setEnabled(false);
    connect(this, SIGNAL(ContactSignal()),this, SLOT(show_conversation()));
    connect(timer,SIGNAL(timeout()),this,SLOT(refreshlistview()));
    connect(timer,SIGNAL(timeout()),this,SLOT(show_conversation()));
    timer->start(3000);
    QObject::connect(this, &QWidget::destroyed, []() {
        qDebug() << "Window was closed";
    });
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_actionLogout_triggered()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "logout?" + "username=" + U[0].GetUserName()
    + "&password=" +U[0].GetPassword();

    QUrl url(urlString);
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(refreshlistview()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(show_conversation()));
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            QMessageBox::information(this,"LogOut",jsonObject["message"].toString());

            QDir folder("User");
             if (folder.exists()) {
                 folder.removeRecursively();
             }
             contactname.clear();
             this->close();

        }
            else{
             QMessageBox::warning(this,"LogOut",jsonObject["message"].toString());
}
    }

}


void StartWindow::refreshlistview()
{

    QString urlString_user = "http://api.barafardayebehtar.ml:8080/";
        urlString_user =urlString_user + "getuserlist?" + "token=" + U[0].GetToken();

        QUrl url_user(urlString_user);
        QNetworkAccessManager manager_user;
        QNetworkReply* reply_user = manager_user.get(QNetworkRequest(url_user));

        QEventLoop loop_user;
        connect(reply_user, &QNetworkReply::finished, &loop_user, &QEventLoop::quit);
        loop_user.exec(); // Block until the request is finished

        if(reply_user->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
        {
            QByteArray data_user = reply_user->readAll();
            QJsonDocument jsonDocument_user = QJsonDocument::fromJson(data_user);
            QJsonObject jsonObject_user = jsonDocument_user.object();
            if(jsonObject_user["code"].toString()=="200"){
                int v=0;
                U[0].ClearContacts();
                ui->listWidget_contacts->clear();
                while(jsonObject_user.contains("block "+QString::number(v))){

                    QListWidgetItem* item_contact = new QListWidgetItem(jsonObject_user["block "+QString::number(v)].toObject()["src"].toString());

                            ui->listWidget_contacts->addItem(item_contact);

                        Contact temp(jsonObject_user["block "+QString::number(v)].toObject()["src"].toString());
                        U[0].SetUserContacts(jsonObject_user["block "+QString::number(v)].toObject()["src"].toString(),temp);
                         v++;
                    }

                }
            else{
                QMessageBox::warning(this,"Contacts",jsonObject_user["message"].toString());
            }

        }
        else{

        }

        QString urlString_group = "http://api.barafardayebehtar.ml:8080/";
            urlString_group = urlString_group + "getgrouplist?" + "token=" + U[0].GetToken();

            QUrl url_group(urlString_group);
            QNetworkAccessManager manager_group;
            QNetworkReply* reply_group = manager_group.get(QNetworkRequest(url_group));

            QEventLoop loop_group;
            connect(reply_group, &QNetworkReply::finished, &loop_group, &QEventLoop::quit);
            loop_group.exec(); // Block until the request is finished

            if(reply_group->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
            {
                QByteArray data_group = reply_group->readAll();
                QJsonDocument jsonDocument_group = QJsonDocument::fromJson(data_group);
                QJsonObject jsonObject_group = jsonDocument_group.object();
                if(jsonObject_group["code"].toString()=="200"){
                    int j=0;
                    U[0].ClearGroups();
                    ui->listWidget_groups->clear();
                    while(jsonObject_group.contains("block "+QString::number(j))){

                        QListWidgetItem* item_group = new QListWidgetItem(jsonObject_group["block "+QString::number(j)].toObject()["group_name"].toString());

                                ui->listWidget_groups->addItem(item_group);

                            j++;

                    }
                }
                else{
                QMessageBox::warning(this,"Groups",jsonObject_group["message"].toString());
            }
                }
            else{

            }
            QString urlString_channel = "http://api.barafardayebehtar.ml:8080/";
                urlString_channel = urlString_channel + "getchannellist?" + "token=" + U[0].GetToken();

                QUrl url_channel(urlString_channel);
                QNetworkAccessManager manager_channel;
                QNetworkReply* reply_channel = manager_channel.get(QNetworkRequest(url_channel));

                QEventLoop loop_channel;
                connect(reply_channel, &QNetworkReply::finished, &loop_channel, &QEventLoop::quit);
                loop_channel.exec(); // Block until the request is finished

                if(reply_channel->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
                {
                    QByteArray data_channel = reply_channel->readAll();
                    QJsonDocument jsonDocument_channel = QJsonDocument::fromJson(data_channel);
                    QJsonObject jsonObject_channel = jsonDocument_channel.object();
                    if(jsonObject_channel["code"].toString()=="200"){
                        int i=0;
                        U[0].ClearChannels();
                        ui->listWidget_channels->clear();
                        while(jsonObject_channel.contains("block "+QString::number(i))){

                            QListWidgetItem* item_channel = new QListWidgetItem(jsonObject_channel["block "+QString::number(i)].toObject()["channel_name"].toString());

                                    ui->listWidget_channels->addItem(item_channel);

                                i++;

                        }
                    }
                    else{
                        QMessageBox::warning(this,"Channels",jsonObject_channel["message"].toString());
                    }
                    }
                else{

                }
}

void StartWindow::on_pushButton_searchuser_clicked()
{

    contactname=ui->lineEdit_searchuser->text();
    if(!ui->lineEdit_searchuser->text().isEmpty()){
    show_conversation();
    }
}


void StartWindow::show_conversation(){

    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getuserchats?" + "token=" + U[0].GetToken()
    + "&dst=" +contactname;

    QUrl url(urlString);

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
        ui->textEdit_conversation->clear();

        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            int i=0;
            U[0].GetContact(contactname).ClearConversation();
            while(jsonObject.contains("block "+QString::number(i))){
                ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["src"].toString()+" :");
                QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                        jsonObject["block "+QString::number(i)].toObject()["date"].toString();
                ui->textEdit_conversation->append(message);           
                ui->textEdit_conversation->append("");
                U[0].GetContact(contactname).SetConversation(jsonObject["block "+QString::number(i)].toObject()["src"].toString(),message);
                i++;
            }
            ui->pushButton_entermessage_contact->setEnabled(true);
        }
      else{
            QMessageBox::warning(this,"PrivetChat",jsonObject["message"].toString());
}

    }
    else{

    }
}


void StartWindow::on_pushButton_entermessage_contact_clicked()
{
    if(!ui->lineEdit_messageuser->text().isEmpty()){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "sendmessageuser?" + "token=" + U[0].GetToken()
    + "&dst=" +contactname+"&body="+ui->lineEdit_messageuser->text();

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
        if(jsonObject["code"].toString()=="200"){
            ui->lineEdit_messageuser->clear();
            show_conversation();
        }
        else{
        QMessageBox::warning(this,"EnterMessage",jsonObject["message"].toString());
}

    }
    else{

    }
    }
}


void StartWindow::on_listWidget_contacts_itemClicked(QListWidgetItem *item)
{
    const QString text = item->text();
    contactname=text;
    show_conversation();
}


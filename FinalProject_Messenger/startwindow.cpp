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
#include"group.h"
#include"channel.h"
#include"dialog_create_channel.h"
#include"dialog_create_group.h"
#include"dialog_join_channel.h"
#include"dialog_join_group.h"
#include <ReadUserFromFile.h>
#include<QFile>

//QVector<User> U;
QString contactname;
QString groupname;
QString channelname;

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
    connect(timer,SIGNAL(timeout()),this,SLOT(show_groupmessage()));
    connect(timer,SIGNAL(timeout()),this,SLOT(show_channelmessage()));
    timer->start(3000);
    QObject::connect(this, &QWidget::destroyed, []() {
        qDebug() << "Window was closed";
    });
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::SetTokenFromUserName(QString token)
{
    Token = token;
}

void StartWindow::SetUsernameFromUserName(QString username)
{
    Username = username;
}

void StartWindow::SetPasswordFromUserName(QString password)
{
    Password = password;
}

QString StartWindow::GetTokenFromUserName()
{
    return Token;
}

QString StartWindow::GetUsernameFromUserName()
{
    return Username;
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
        disconnect(timer,SIGNAL(timeout()),this,SLOT(show_groupmessage()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(show_channelmessage()));
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
            QMap<QString, QJsonDocument> Users=ReadUserFromFile();
            ui->listWidget_contacts->clear();
            QMap<QString, QJsonDocument>::ConstIterator userit;
            for(userit = Users.constBegin(); userit != Users.constEnd(); ++userit){

                QListWidgetItem* item_user = new QListWidgetItem(userit.key());

                ui->listWidget_contacts->addItem(item_user);
                }

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
    if(contactname!=""){
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
                QString filePath="User/Contacts/"+contactname+".json";
                QJsonObject fileObjectToWrite=jsonObject;
                QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                QFile fileToWrite(filePath);
                if(fileToWrite.open(QIODevice::WriteOnly)){
                    fileToWrite.write(fileDocumentToWrite.toJson());
                    fileToWrite.close();
                }
            }
            ui->pushButton_entermessage_contact->setEnabled(true);
        }
      else{
            QMessageBox::warning(this,"PrivetChat",jsonObject["message"].toString());
}

    }
    else{
        QMap<QString, QJsonDocument> Users=ReadUserFromFile();
        ui->textEdit_conversation->clear();
        QJsonObject messages = Users[contactname].object();
        //qDebug()<<mess;
        int i1=0;
        while(messages.contains("block "+QString::number(i1))){
            ui->textEdit_conversation->append(messages["block "+QString::number(i1)].toObject()["src"].toString()+" :");
            QString message=messages["block "+QString::number(i1)].toObject()["body"].toString()+"       "+
                    messages["block "+QString::number(i1)].toObject()["date"].toString();
            ui->textEdit_conversation->append(message);
            ui->textEdit_conversation->append("");
            i1++;
            }
        ui->pushButton_entermessage_contact->setEnabled(true);

    }
    }

}
void StartWindow::show_groupmessage(){
    if(groupname!=""){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getgroupchats?" + "token=" + U[0].GetToken()
    + "&dst=" +groupname;
qDebug()<<groupname;
    QUrl url(urlString);

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
        ui->textEdit_groupmessages->clear();

        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            int j=0;
qDebug()<<jsonObject;
            while(jsonObject.contains("block "+QString::number(j))){
                ui->textEdit_groupmessages->append(jsonObject["block "+QString::number(j)].toObject()["src"].toString()+" :");
                QString message=jsonObject["block "+QString::number(j)].toObject()["body"].toString()+"       "+
                        jsonObject["block "+QString::number(j)].toObject()["date"].toString();
                ui->textEdit_groupmessages->append(message);
                ui->textEdit_groupmessages->append("");

                j++;
                QString filePath="User/Groups/"+groupname+".json";
                QJsonObject fileObjectToWrite=jsonObject;
                QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                QFile fileToWrite(filePath);
                if(fileToWrite.open(QIODevice::WriteOnly)){
                    fileToWrite.write(fileDocumentToWrite.toJson());
                    fileToWrite.close();
                }
            }
            ui->pushButton_entermessage_group->setEnabled(true);
        }
      else{
            QMessageBox::warning(this,"GroupChat",jsonObject["message"].toString());
}

    }
    /*else{
        QMap<QString, QJsonDocument> Users=ReadUserFromFile();
        ui->textEdit_conversation->clear();
        QJsonObject messages = Users[contactname].object();
        //qDebug()<<mess;
        int i1=0;
        while(messages.contains("block "+QString::number(i1))){
            ui->textEdit_conversation->append(messages["block "+QString::number(i1)].toObject()["src"].toString()+" :");
            QString message=messages["block "+QString::number(i1)].toObject()["body"].toString()+"       "+
                    messages["block "+QString::number(i1)].toObject()["date"].toString();
            ui->textEdit_conversation->append(message);
            ui->textEdit_conversation->append("");
            i1++;
            }
        ui->pushButton_entermessage_contact->setEnabled(true);

    }*/
    }
}
void StartWindow::show_channelmessage(){
    if(channelname!=""){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getchannelchats?" + "token=" + U[0].GetToken()
    + "&dst=" +channelname;
    QUrl url(urlString);

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
        ui->textEdit_channelmessages->clear();

        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            int j=0;

            while(jsonObject.contains("block "+QString::number(j))){
                QString message=jsonObject["block "+QString::number(j)].toObject()["body"].toString()+"       "+
                        jsonObject["block "+QString::number(j)].toObject()["date"].toString();
                ui->textEdit_channelmessages->append(message);
                ui->textEdit_channelmessages->append("");

                j++;
                QString filePath="User/Groups/"+channelname+".json";
                QJsonObject fileObjectToWrite=jsonObject;
                QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                QFile fileToWrite(filePath);
                if(fileToWrite.open(QIODevice::WriteOnly)){
                    fileToWrite.write(fileDocumentToWrite.toJson());
                    fileToWrite.close();
                }
            }
            ui->pushButton_entermessage_channel->setEnabled(true);
        }
      else{
            QMessageBox::warning(this,"GroupChat",jsonObject["message"].toString());
}

    }
    /*else{
        QMap<QString, QJsonDocument> Users=ReadUserFromFile();
        ui->textEdit_conversation->clear();
        QJsonObject messages = Users[contactname].object();
        //qDebug()<<mess;
        int i1=0;
        while(messages.contains("block "+QString::number(i1))){
            ui->textEdit_conversation->append(messages["block "+QString::number(i1)].toObject()["src"].toString()+" :");
            QString message=messages["block "+QString::number(i1)].toObject()["body"].toString()+"       "+
                    messages["block "+QString::number(i1)].toObject()["date"].toString();
            ui->textEdit_conversation->append(message);
            ui->textEdit_conversation->append("");
            i1++;
            }
        ui->pushButton_entermessage_contact->setEnabled(true);

    }*/
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
}


void StartWindow::on_actionCreat_Group_triggered()
{
    Dialog_Create_Group* window = new Dialog_Create_Group();
    window->SetCreateGroupToken(Token);
    window->show();
}


void StartWindow::on_actionCreat_Channel_triggered()
{
    Dialog_Create_Channel* window = new Dialog_Create_Channel();
    window->SetTokenFromChannel(Token);
    window->show();
}


void StartWindow::on_actionJoin_Group_triggered()
{
    Dialog_Join_Group* window = new Dialog_Join_Group();
    window->SetJoinGroupToken(Token);
    window->show();
}


void StartWindow::on_actionJoin_Channel_triggered()
{
    Dialog_Join_Channel* C = new Dialog_Join_Channel();
    C->SetJoinChannelToken(Token);
    C->show();
}


void StartWindow::on_pushButton_entermessage_group_clicked()
{
    if(!ui->lineEdit_messagegroup->text().isEmpty()){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "sendmessagegroup?" + "token=" + U[0].GetToken()
    + "&dst=" +groupname+"&body="+ui->lineEdit_messagegroup->text();

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
            ui->lineEdit_messagegroup->clear();
        }
        else{
        QMessageBox::warning(this,"EnterMessage",jsonObject["message"].toString());
}

    }
    else{

    }
    }
}


void StartWindow::on_pushButton_entermessage_channel_clicked()
{

    if(!ui->lineEdit_messagechannel->text().isEmpty()){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "sendmessagechannel?" + "token=" + U[0].GetToken()
    + "&dst=" +channelname+"&body="+ui->lineEdit_messagechannel->text();

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
            ui->lineEdit_messagechannel->clear();
        }
        else{
        QMessageBox::warning(this,"EnterMessage",jsonObject["message"].toString());
}

    }
    else{

    }
    }
}


void StartWindow::on_listWidget_groups_itemClicked(QListWidgetItem *item)
{
    const QString text = item->text();
    groupname=text;
    show_conversation();
}


void StartWindow::on_listWidget_channels_itemClicked(QListWidgetItem *item)
{
    const QString text = item->text();
    channelname=text;
}


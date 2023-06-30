#include "startwindow.h"
#include "ui_startwindow.h"
<<<<<<< HEAD
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
#include <QListView>
#include <QStringListModel>
#include <QMessageBox>
#include<QGridLayout>
#include<QTextCursor>
#include<QTimer>
#include<QDir>

//QVector<User> U;
=======
#include "dialog_join_channel.h"
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    //ui->textEdit_groups->setEnabled(false);
   // ui->textEdit_channels->setEnabled(false);
    //ui->textEdit_contacts->setEnabled(false);
    ui->textEdit_groupmessages->setEnabled(false);
    ui->textEdit_channelmessages->setEnabled(false);
    ui->textEdit_conversation->setEnabled(false);
    ui->pushButton_entermessage_contact->setEnabled(false);    //qDebug() << U[0].GetToken();
    ui->pushButton_entermessage_group->setEnabled(false);
    ui->pushButton_entermessage_channel->setEnabled(false);
    connect(this, SIGNAL(ContactSignal(QString)),this, SLOT(show_conversation(QString)));
    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    timer->start(5000);
    //refresh();
}

StartWindow::~StartWindow()
{
    delete ui;
}

<<<<<<< HEAD
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
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            QMessageBox::information(this,"Response sent by the server",jsonObject["message"].toString());

            QDir folder("User");
             if (folder.exists()) {
                 folder.removeRecursively();
             }
             this->close();
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
=======
void StartWindow::SetTokenFromUserName(QString token)
{
    Token = token;
}

void StartWindow::SetUsernameFromUserName(QString username)
{
    Username = username;
}

QString StartWindow::GetTokenFromUserName()
{
    return Token;
}

QString StartWindow::GetUsernameFromUserName()
{
    return Username;
}

void StartWindow::on_actionCreat_Group_triggered()
{
    dialog_create_group* window = new dialog_create_group();
    window->SetCreateGroupToken(Token);
    window->show();
}


void StartWindow::on_pushButton_entermessage_2_clicked()
{
    Group* G = new Group();
    G->SetTokenOfUsernameGroup(Token);
    G->AddMessageToGroupWithGroupName(Username,ui->lineEdit_message_2->text(),ui->lineEdit_searchgroupe->text());
}


void StartWindow::on_actionJoin_Group_triggered()
{
    dialog_Join_Group* window = new dialog_Join_Group();
    window->SetJoinGroupToken(Token);
    window->show();
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc

}


<<<<<<< HEAD
void StartWindow::on_actionRefresh_triggered()
{
    QString urlString_user = "http://api.barafardayebehtar.ml:8080/";
        urlString_user =urlString_user + "getuserlist?" + "token=" + U[0].GetToken();
        //qDebug() << U[0].GetToken();
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
            if(jsonObject_user["message"].toString()=="200"){
                int v=0;
                while(true){
                    if(!jsonObject_user["block"+QString::number(v)].isNull()){
                        contact_items<<jsonObject_user["block "+QString::number(v)].toObject()["username"].toString();
                        contact_model->setStringList(contact_items); // set the items in the model
                        ui->listView_contacts->setModel(contact_model);
                        Contact temp(jsonObject_user["block "+QString::number(v)].toObject()["username"].toString());
                        U[0].SetUserContacts(jsonObject_user["block "+QString::number(v)].toObject()["username"].toString(),temp);
                        v++;
                    }
                    else{
                        break;
                    }
                }
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
                if(jsonObject_group["message"].toString()=="200"){
                    int j=0;
                    while(true){
                        if(!jsonObject_group["block"+QString::number(j)].isNull()){
                            group_items<<jsonObject_group["block "+QString::number(j)].toObject()["group_name"].toString();
                            group_model->setStringList(group_items); // set the items in the model
                            ui->listView_groups->setModel(group_model);
                            j++;
                        }
                        else{
                            break;
                        }
                    }
                }
                else{
                //ui->textEdit_groups->setText(jsonObject_group["message"].toString());
            }
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
                    if(jsonObject_channel["message"].toString()=="200"){
                        int i=0;
                        while(true){
                            if(!jsonObject_channel["block"+QString::number(i)].isNull()){
                                channel_items<<jsonObject_channel["block "+QString::number(i)].toObject()["channel_name"].toString();
                                channel_model->setStringList(channel_items); // set the items in the model
                                ui->listView_channels->setModel(channel_model);
                                i++;
                            }
                            else{
                                break;
                            }
                        }
                    }
                    }
}

//void StartWindow::refresh(){

//}

void StartWindow::on_pushButton_entermessage_clicked()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "sendmessageuser?" + "token=" + U[0].GetToken()
    + "&dst=" +ui->lineEdit_searchuser->text()+"&body="+ui->lineEdit_messageuser->text();

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


void StartWindow::on_pushButton_searchuser_clicked()
{
        QString urlString = "http://api.barafardayebehtar.ml:8080/";
        urlString = urlString + "getuserchats?" + "token=" + U[0].GetToken()
        + "&dst=" +ui->lineEdit_searchuser->text();

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
                int i=0;
                while(!jsonObject["block "+QString::number(i)].isNull()){
                    if(jsonObject["block "+QString::number(i)].toObject()["src"].toString()==jsonObject["block "+QString::number(i)].toObject()["dst"].toString()){
                        ui->textEdit_conversation->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Set text alignment to left-to-right
                        ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["body"].toString());
                        QTextCursor cursor = ui->textEdit_conversation->textCursor();
                        cursor.movePosition(QTextCursor::End);
                        cursor.movePosition(QTextCursor::NextBlock);
                        cursor.movePosition(QTextCursor::StartOfBlock);
                    }
                    else{
                        ui->textEdit_conversation->setAlignment(Qt::AlignRight | Qt::AlignTop);
                        ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["body"].toString());
                        QTextCursor cursor = ui->textEdit_conversation->textCursor();
                        cursor.movePosition(QTextCursor::End);
                        cursor.movePosition(QTextCursor::NextBlock);
                        cursor.movePosition(QTextCursor::StartOfBlock);
                    }
                }

                ui->pushButton_entermessage_contact->setEnabled(true);
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
void StartWindow::refresh_conversation(QString name){
    while(true){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getuserchats?" + "token=" + U[0].GetToken()
    + "&dst=" +name;

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
            int i=0;
            while(!jsonObject["block "+QString::number(i)].isNull()){
                if(jsonObject["block "+QString::number(i)].toObject()["src"].toString()==jsonObject["block "+QString::number(i)].toObject()["dst"].toString()){
                    ui->textEdit_conversation->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Set text alignment to left-to-right
                    ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["body"].toString());
                    QTextCursor cursor = ui->textEdit_conversation->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    cursor.movePosition(QTextCursor::NextBlock);
                    cursor.movePosition(QTextCursor::StartOfBlock);
                }
                else{
                    ui->textEdit_conversation->setAlignment(Qt::AlignRight | Qt::AlignTop);
                    ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["body"].toString());
                    QTextCursor cursor = ui->textEdit_conversation->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    cursor.movePosition(QTextCursor::NextBlock);
                    cursor.movePosition(QTextCursor::StartOfBlock);
                }
            }
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
    }


void StartWindow::on_listView_contacts_clicked(const QModelIndex &index)
{
    QString itemText = index.data(Qt::DisplayRole).toString(); // get the text of the clicked item
    emit ContactSignal(itemText);
}

void StartWindow::show_conversation(QString name){
    while(true){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getuserchats?" + "token=" + U[0].GetToken()
    + "&dst=" +name;

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
            int i=0;
            while(!jsonObject["block "+QString::number(i)].isNull()){
                if(jsonObject["block "+QString::number(i)].toObject()["src"].toString()!=U[0].GetUserName()){
                    ui->textEdit_conversation->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Set text alignment to left-to-right
                    ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["body"].toString());
                    QTextCursor cursor = ui->textEdit_conversation->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    cursor.movePosition(QTextCursor::NextBlock);
                    cursor.movePosition(QTextCursor::StartOfBlock);
                }
                else{
                    ui->textEdit_conversation->setAlignment(Qt::AlignRight | Qt::AlignTop);
                    ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["body"].toString());
                    QTextCursor cursor = ui->textEdit_conversation->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    cursor.movePosition(QTextCursor::NextBlock);
                    cursor.movePosition(QTextCursor::StartOfBlock);
                }
            }
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
=======




void StartWindow::on_textEdit_groupmessages_textChanged()
{
    ui->textEdit_groups->setText("Sdlks;sl;d;sld;sdlkl");
}


void StartWindow::on_textEdit_groups_selectionChanged()
{
    ui->textEdit_groups->setText("Sdlks;sl;d;sld;sdlkl");
}


void StartWindow::on_textEdit_groupmessages_selectionChanged()
{
    //http://api.barafardayebehtar.ml:8080/getgroupchats?token=7a3c48
//    f7c7939b7269d01443a431825f&dst=ap&date=20001121081415

    QString GroupName[10];
    int index = 0;

    QString urlString = "http://api.barafardayebehtar.ml:8080/getgrouplist?token=";
    urlString +=Token;

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject.value("code").toString() == "200")
        {
            QString blocks = "block ";
            int Conuter = 0;
            QMessageBox::information(this,"respons by server",jsonObject.value("message").toString());
            for(int i=0;i<10;i++)
            {

                blocks += QString::fromUtf8(to_string(i));
                if(jsonObject.value(blocks).toString()!="")
                {
                    GroupName[i].append(jsonObject.value(blocks).toString());
                }
                else
                {
                    break;
                }
                Conuter++;
            }
        }
        if(jsonObject.value("code").toString() == "404")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "204")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "401")
        {
            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }


    }

    // بهداد زذه باید جابه جا کنم

    ui->textEdit_groupmessages->setText(GroupName[0]);
}


void StartWindow::on_actionCreat_Channel_triggered()
{
    dialog_create_Channel* window = new dialog_create_Channel();
    window->SetTokenFromChannel(Token);
    window->show();
}


void StartWindow::on_actionJoin_Channel_triggered()
{
    dialog_join_Channel* C = new dialog_join_Channel();
    C->SetJoinChannelToken(Token);
    C->show();
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc
}


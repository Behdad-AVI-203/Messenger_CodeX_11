#include "startwindow.h"
#include "ui_startwindow.h"
#include"startwindow.h"
#include"dialog_login.h"
#include"user.h"
#include"dialog_create_channel.h"
#include"dialog_create_group.h"
#include"dialog_join_channel.h"
#include"dialog_join_group.h"
#include "all_include.h"
#include <QTextEdit>


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
    connect(timer,SIGNAL(timeout()),this,SLOT(contactsrefreshlistview()));
    connect(timer,SIGNAL(timeout()),this,SLOT(groupsrefreshlistview()));
    connect(timer,SIGNAL(timeout()),this,SLOT(channelsrefreshlistview()));
    connect(timer,SIGNAL(timeout()),this,SLOT(show_conversation()));
    connect(timer,SIGNAL(timeout()),this,SLOT(show_groupmessage()));
    connect(timer,SIGNAL(timeout()),this,SLOT(show_channelmessage()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ReadGroupList()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ReadChannelListt()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ReadUserLIST()));
    timer->start(3000);
    QObject::connect(this, &QWidget::destroyed, []() {

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
        disconnect(timer,SIGNAL(timeout()),this,SLOT(contactsrefreshlistview()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(groupsrefreshlistview()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(channelsrefreshlistview()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(show_conversation()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(show_groupmessage()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(show_channelmessage()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(ReadGroupList()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(ReadChannelListt()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(ReadUserLIST()));
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
             this->close();
        }
        else{
            QMessageBox::warning(this,"LogOut",jsonObject["message"].toString());
        }
    }
}

void StartWindow::contactsrefreshlistview()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString =urlString + "getuserlist?" + "token=" + U[0].GetToken();
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
        if(jsonObject["code"].toString()=="200"){
            int v=0;
            ui->listWidget_contacts->clear();
            while(jsonObject.contains("block "+QString::number(v))){
                QListWidgetItem* item = new QListWidgetItem(jsonObject["block "+QString::number(v)].toObject()["src"].toString());
                ui->listWidget_contacts->addItem(item);
                v++;
            }
        }
        else{
            QMessageBox::warning(this,"Contacts",jsonObject["message"].toString());
        }
    }
    else{
        ui->listWidget_contacts->clear();
        QString folderPath = "User/Contacts";
        QDir directory(folderPath);
        QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
        QString temp;
        foreach (QString fileName, jsonFiles) {
        temp = fileName;
        temp = temp.remove(".json");
        QListWidgetItem* item = new QListWidgetItem(temp);
        ui->listWidget_contacts->addItem(item);
        }
    }
}

void StartWindow::groupsrefreshlistview(){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getgrouplist?" + "token=" + U[0].GetToken();
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
            int j=0;
            ui->listWidget_groups->clear();
            while(jsonObject.contains("block "+QString::number(j))){
            QListWidgetItem* item = new QListWidgetItem(jsonObject["block "+QString::number(j)].toObject()["group_name"].toString());
            ui->listWidget_groups->addItem(item);
            j++;
            }
        }
        else{
            QMessageBox::warning(this,"Groups",jsonObject["message"].toString());
        }
    }
    else{
        ui->listWidget_groups->clear();
        QString folderPath = "User/Groups";
        QDir directory(folderPath);
        QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
        QString temp;
        foreach (QString fileName, jsonFiles) {
            temp = fileName;
            temp = temp.remove(".json");
            QListWidgetItem* item = new QListWidgetItem(temp);
            ui->listWidget_groups->addItem(item);
        }
    }
}

void StartWindow::channelsrefreshlistview(){
    QString urlString = "http://api.barafardayebehtar.ml:8080/";
    urlString = urlString + "getchannellist?" + "token=" + U[0].GetToken();
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
            int i=0;
            ui->listWidget_channels->clear();
            while(jsonObject.contains("block "+QString::number(i))){
                QListWidgetItem* item = new QListWidgetItem(jsonObject["block "+QString::number(i)].toObject()["channel_name"].toString());
                ui->listWidget_channels->addItem(item);
                i++;
            }
        }
        else{
              QMessageBox::warning(this,"Channels",jsonObject["message"].toString());
        }
     }
     else{
         ui->listWidget_channels->clear();
         QString folderPath = "User/Channels";
         QDir directory(folderPath);
         QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
         QString temp;
         foreach (QString fileName, jsonFiles) {
             temp = fileName;
             temp = temp.remove(".json");
             QListWidgetItem* item = new QListWidgetItem(temp);
             ui->listWidget_channels->addItem(item);
         }
    }
}

void StartWindow::on_pushButton_searchuser_clicked()
{
    if(!ui->lineEdit_searchuser->text().isEmpty()){
        contactname=ui->lineEdit_searchuser->text();
        ui->label_contactname->setText(contactname);
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
            while(jsonObject.contains("block "+QString::number(i))){
                ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["src"].toString()+" :");
                QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                jsonObject["block "+QString::number(i)].toObject()["date"].toString();
                ui->textEdit_conversation->append(message);
                ui->textEdit_conversation->append("");
                i++;
            }
        }
        else{
            QMessageBox::warning(this,"PrivetChat",jsonObject["message"].toString());
        }
    }
    else{
        QString folderPath = "User/Contacts";
        QDir directory(folderPath);
        QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
        QString temp;
        foreach (QString fileName, jsonFiles) {
            temp = fileName;
            temp = temp.remove(".json");
            if(temp==contactname){
            QFile file(directory.absoluteFilePath(fileName));
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Could not open file:" << fileName;
                continue;
            }
            QByteArray jsonData = file.readAll();
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "Error parsing JSON file:" << fileName << "-" << parseError.errorString();
                continue;
            }
            ui->textEdit_conversation->clear();
            QJsonObject jsonObj = jsonDoc.object();
            int index = 0;
            while (jsonObj.contains("block " + QString::number(index))) {
                QJsonValue blockValue = jsonObj.value("block " + QString::number(index));
                if (blockValue.isObject()) {
                    QJsonObject blockObj = blockValue.toObject();
                    ui->textEdit_conversation->append(blockObj["src"].toString()+" :");
                    QString offmessage=blockObj["body"].toString()+"       "+
                    blockObj["date"].toString();
                    ui->textEdit_conversation->append(offmessage);
                    ui->textEdit_conversation->append("");
                }
                index++;
            }
            }
        }
    }
    }
}
void StartWindow::show_groupmessage(){
    if(groupname!=""){
        QString urlString = "http://api.barafardayebehtar.ml:8080/";
        urlString = urlString + "getgroupchats?" + "token=" + U[0].GetToken()
        + "&dst=" +groupname;
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
                while(jsonObject.contains("block "+QString::number(j))){
                    ui->textEdit_groupmessages->append(jsonObject["block "+QString::number(j)].toObject()["src"].toString()+" :");
                    QString message=jsonObject["block "+QString::number(j)].toObject()["body"].toString()+"       "+
                    jsonObject["block "+QString::number(j)].toObject()["date"].toString();
                    ui->textEdit_groupmessages->append(message);
                    ui->textEdit_groupmessages->append("");
                    j++;
                }
            }
            else{
                QMessageBox::warning(this,"GroupChat",jsonObject["message"].toString());
            }
        }
        else{
            QString folderPath = "User/Groups";
            QDir directory(folderPath);
            QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
            QString temp;
            foreach (QString fileName, jsonFiles) {
                temp = fileName;
                temp = temp.remove(".json");
                if(temp==groupname){
                QFile file(directory.absoluteFilePath(fileName));
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    continue;
                }
                QByteArray jsonData = file.readAll();
                QJsonParseError parseError;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
                if (parseError.error != QJsonParseError::NoError) {
                    continue;
                }
                ui->textEdit_groupmessages->clear();
                QJsonObject jsonObj = jsonDoc.object();
                int index = 0;
                while (jsonObj.contains("block " + QString::number(index))) {
                    QJsonValue blockValue = jsonObj.value("block " + QString::number(index));
                    if (blockValue.isObject()) {
                        QJsonObject blockObj = blockValue.toObject();
                        ui->textEdit_groupmessages->append(blockObj["src"].toString()+" :");
                        QString offmessage=blockObj["body"].toString()+"       "+
                        blockObj["date"].toString();
                        ui->textEdit_groupmessages->append(offmessage);
                        ui->textEdit_groupmessages->append("");
                    }
                    index++;
                }
                }
             }
        }
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
                }
            }
            else{
                QMessageBox::warning(this,"GroupChat",jsonObject["message"].toString());
            }
        }
        else{
            QString folderPath = "User/Channels";
            QDir directory(folderPath);
            QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
            QString temp;
            foreach (QString fileName, jsonFiles) {
                temp = fileName;
                temp = temp.remove(".json");
                if(temp==channelname){
                    QFile file(directory.absoluteFilePath(fileName));
                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        continue;
                    }
                    QByteArray jsonData = file.readAll();
                    QJsonParseError parseError;
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
                    if (parseError.error != QJsonParseError::NoError) {
                        continue;
                    }
                    ui->textEdit_channelmessages->clear();
                    QJsonObject jsonObj = jsonDoc.object();
                    int index = 0;
                    while (jsonObj.contains("block " + QString::number(index))) {
                        QJsonValue blockValue = jsonObj.value("block " + QString::number(index));
                        if (blockValue.isObject()) {
                            QJsonObject blockObj = blockValue.toObject();
                            QString offmessage=blockObj["body"].toString()+"       "+
                            blockObj["date"].toString();
                            ui->textEdit_channelmessages->append(offmessage);
                            ui->textEdit_channelmessages->append("");
                        }
                        index++;
                    }
                }
            }
        }
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
    ui->label_contactname->setText(contactname);
    show_conversation();
}

void StartWindow::on_actionCreat_Group_triggered()
{
    Dialog_Create_Group* window = new Dialog_Create_Group(this);
    window->show();
}

void StartWindow::on_actionCreat_Channel_triggered()
{
    Dialog_Create_Channel* window = new Dialog_Create_Channel(this);
    window->show();
}

void StartWindow::on_actionJoin_Group_triggered()
{
    Dialog_Join_Group* window = new Dialog_Join_Group(this);
    window->show();
}

void StartWindow::on_actionJoin_Channel_triggered()
{
    Dialog_Join_Channel* C = new Dialog_Join_Channel(this);
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
    ui->label_groupname->setText(groupname);
    show_groupmessage();
}

void StartWindow::on_listWidget_channels_itemClicked(QListWidgetItem *item)
{
    const QString text = item->text();
    channelname=text;
    ui->label_channelname->setText(channelname);
    show_channelmessage();
}

void StartWindow::ReadUserLIST()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getuserlist?token=" + U[0].GetToken();
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    try {
    if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if (jsonObject.value("code").toString() == "200")
            {
                QStringList keys = jsonObject.keys();
                for (const auto& key : keys) {
                    if (key == "code" || key == "message") {
                    }
                    else {
                        if (key.startsWith("block")) {
                            QJsonValue blocksValue = jsonObject.value(key);
                            if (blocksValue.isObject())
                            {
                                QJsonObject blockObject = blocksValue.toObject();
                                ReadUseristWithDestination(blockObject.value("src").toString());
                            }
                        }
                    }
                }
            }
        }
        else
        {
             throw std::invalid_argument("The server is unable to respond");
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::information(this,"Exception",e.what());
    }
}

void StartWindow::ReadUseristWithDestination(QString name)
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getuserchats?token=";
    urlString += U[0].GetToken() + "&dst=" + name + "&date=20001121081415";
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    try{
        if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject["code"].toString() == "200")
            {
                int i=0;
                while(jsonObject.contains("block "+QString::number(i))){
                    QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                    jsonObject["block "+QString::number(i)].toObject()["date"].toString();
                    i++;
                    QString filePath="User/Contacts/"+name+".json";
                    QJsonObject fileObjectToWrite=jsonObject;
                    QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                    QFile fileToWrite(filePath);
                    if(fileToWrite.open(QIODevice::WriteOnly)){
                        fileToWrite.write(fileDocumentToWrite.toJson());
                        fileToWrite.close();
                    }
                }
            }
        }
        else
        {
             throw std::invalid_argument("The server is unable to respond");
        }
    }
    catch(const std::exception& e)
    {
         QMessageBox::information(this,"Exception",e.what());
    }
}

void StartWindow::ReadGroupList()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getgrouplist?token=" + U[0].GetToken();
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    try{
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if (jsonObject.value("code").toString() == "200")
            {
                QStringList keys = jsonObject.keys();
                for (const auto& key : keys) {
                    if (key == "code" || key == "message") {
                    }
                    else {
                        if (key.startsWith("block")) {
                            QJsonValue blocksValue = jsonObject.value(key);
                            if (blocksValue.isObject())
                            {
                                QJsonObject blockObject = blocksValue.toObject();
                                ReadGroupListWithDestination(blockObject.value("group_name").toString());
                            }
                        }
                    }
                }
            }
        }
        else
        {
             throw std::invalid_argument("The server is unable to respond");
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::information(this,"Exception",e.what());
    }
}

void StartWindow::ReadGroupListWithDestination(QString name)
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getgroupchats?token=";
    urlString += U[0].GetToken() + "&dst=" + name + "&date=20001121081415";
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished
    try{
        if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject["code"].toString() == "200")
            {
                int i=0;
                while(jsonObject.contains("block "+QString::number(i))){
                    QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                    jsonObject["block "+QString::number(i)].toObject()["date"].toString();
                    i++;
                    QString filePath="User/Groups/"+name+".json";
                    QJsonObject fileObjectToWrite=jsonObject;
                    QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                    QFile fileToWrite(filePath);
                    if(fileToWrite.open(QIODevice::WriteOnly)){
                        fileToWrite.write(fileDocumentToWrite.toJson());
                        fileToWrite.close();
                    }
                }
            }
        }
        else
        {
            throw std::invalid_argument("The server is unable to respond");
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::information(this,"Exception",e.what());
    }
}

void StartWindow::ReadChannelListt()
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getchannellist?token=" + U[0].GetToken();
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    try{
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if (jsonObject.value("code").toString() == "200")
            {
                QStringList keys = jsonObject.keys();
                for (const auto& key : keys) {
                    if (key == "code" || key == "message") {
                    }
                    else {
                        if (key.startsWith("block")) {
                            QJsonValue blocksValue = jsonObject.value(key);
                            if (blocksValue.isObject())
                            {
                                QJsonObject blockObject = blocksValue.toObject();
                                ReadChannelListWithDestination(blockObject.value("channel_name").toString());
                            }
                        }
                    }
                }
            }
        }
        else
        {
            throw std::invalid_argument("The server is unable to respond");
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::information(this,"Exception",e.what());
    }
}

void StartWindow::ReadChannelListWithDestination(QString name)
{

    QString urlString = "http://api.barafardayebehtar.ml:8080/getchannelchats?token=";
    urlString += U[0].GetToken() + "&dst=" + name + "&date=20001121081415";
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));
    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished
    try{
        if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
        {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject["code"].toString() == "200")
            {
                int i=0;
                while(jsonObject.contains("block "+QString::number(i))){
                    QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                    jsonObject["block "+QString::number(i)].toObject()["date"].toString();
                    i++;
                    QString filePath="User/Channels/"+name+".json";
                    QJsonObject fileObjectToWrite=jsonObject;
                    QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                    QFile fileToWrite(filePath);
                    if(fileToWrite.open(QIODevice::WriteOnly)){
                        fileToWrite.write(fileDocumentToWrite.toJson());
                        fileToWrite.close();
                    }
                }
            }
        }
        else
        {
            throw std::invalid_argument("The server is unable to respond");
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::information(this,"Exception",e.what());
    }
}







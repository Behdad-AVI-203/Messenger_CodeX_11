#include <ReadFirst.h>
#include <qjsonarray.h>
#include <QStandardPaths>
void ReadGroupListWithDestination(QString dst, QString token)
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getgroupchats?token=";
    urlString += token + "&dst=" + dst + "&date=20001121081415";

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
//        ui->textEdit_conversation->clear();

        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            int i=0;
//            U[0].GetContact(contactname).ClearConversation();
            while(jsonObject.contains("block "+QString::number(i))){
//                ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["src"].toString()+" :");
                QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                        jsonObject["block "+QString::number(i)].toObject()["date"].toString();
//                ui->textEdit_conversation->append(message);
//                ui->textEdit_conversation->append("");
//                U[0].GetContact(contactname).SetConversation(jsonObject["block "+QString::number(i)].toObject()["src"].toString(),message);
                i++;
                QString filePath="User/Groups/"+dst+".json";
                QJsonObject fileObjectToWrite=jsonObject;
                QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                QFile fileToWrite(filePath);
                if(fileToWrite.open(QIODevice::WriteOnly)){
                    fileToWrite.write(fileDocumentToWrite.toJson());
                    fileToWrite.close();
                }
            }
//            ui->pushButton_entermessage_contact->setEnabled(true);
        }
}
}

void ReadGroupList(QString token)
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getgrouplist?token=" + token;

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if (jsonObject.value("code").toString() == "200")
        {
            qDebug() << "Message: " << jsonObject.value("message").toString();

            QStringList keys = jsonObject.keys();
            for (const auto& key : keys) {
                if (key == "code" || key == "message") {
                    qDebug() << key << ":" << jsonObject.value(key).toString();
                }
                else {
                    if (key.startsWith("block")) {
                        QJsonValue blocksValue = jsonObject.value(key);
                        if (blocksValue.isObject())
                        {
                            QJsonObject blockObject = blocksValue.toObject();
                            qDebug() << "Group Name:" << blockObject.value("group_name").toString();
                            ReadGroupListWithDestination(blockObject.value("group_name").toString(),token);
                    }
                }
            }
        }
    }
}

}




void ReadChannelListt(QString token)
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getchannellist?token=" + token;

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if (jsonObject.value("code").toString() == "200")
        {
            qDebug() << "Message: " << jsonObject.value("message").toString();

            QStringList keys = jsonObject.keys();
            for (const auto& key : keys) {
                if (key == "code" || key == "message") {
                    qDebug() << key << ":" << jsonObject.value(key).toString();
                }
                else {
                    if (key.startsWith("block")) {
                        QJsonValue blocksValue = jsonObject.value(key);
                        if (blocksValue.isObject())
                        {
                            QJsonObject blockObject = blocksValue.toObject();
                            qDebug() << "channel Name:" << blockObject.value("channel_name").toString();
                            ReadChannelListWithDestination(blockObject.value("channel_name").toString(),token);
                    }
                }
            }
        }
    }
}
}





void ReadChannelListWithDestination(QString dst, QString token)
{

    QString urlString = "http://api.barafardayebehtar.ml:8080/getchannelchats?token=";
    urlString += token + "&dst=" + dst + "&date=20001121081415";

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
//        ui->textEdit_conversation->clear();

        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            int i=0;
//            U[0].GetContact(contactname).ClearConversation();
            while(jsonObject.contains("block "+QString::number(i))){
//                ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["src"].toString()+" :");
                QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                        jsonObject["block "+QString::number(i)].toObject()["date"].toString();
//                ui->textEdit_conversation->append(message);
//                ui->textEdit_conversation->append("");
//                U[0].GetContact(contactname).SetConversation(jsonObject["block "+QString::number(i)].toObject()["src"].toString(),message);
                i++;
                QString filePath="User/Channels/"+dst+".json";
                QJsonObject fileObjectToWrite=jsonObject;
                QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                QFile fileToWrite(filePath);
                if(fileToWrite.open(QIODevice::WriteOnly)){
                    fileToWrite.write(fileDocumentToWrite.toJson());
                    fileToWrite.close();
                }
            }
//            ui->pushButton_entermessage_contact->setEnabled(true);
        }
}
}





void ReadUserLIST(QString token)
{

    QString urlString = "http://api.barafardayebehtar.ml:8080/getuserlist?token=" + token;

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if (jsonObject.value("code").toString() == "200")
        {
            qDebug() << "Message: " << jsonObject.value("message").toString();

            QStringList keys = jsonObject.keys();
            for (const auto& key : keys) {
                if (key == "code" || key == "message") {
                    qDebug() << key << ":" << jsonObject.value(key).toString();
                }
                else {
                    if (key.startsWith("block")) {
                        QJsonValue blocksValue = jsonObject.value(key);
                        if (blocksValue.isObject())
                        {
                            QJsonObject blockObject = blocksValue.toObject();
                            qDebug() << "user Name:" << blockObject.value("src").toString();
                            ReadUseristWithDestination(blockObject.value("src").toString(),token);
                    }
                }
            }
        }
    }
}
}




void ReadUseristWithDestination(QString dst, QString token)
{
    QString urlString = "http://api.barafardayebehtar.ml:8080/getuserchats?token=";
    urlString += token + "&dst=" + dst + "&date=20001121081415";

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error()==QNetworkReply::NoError)//This condition checks whether there is a problem on the server side
    {
//        ui->textEdit_conversation->clear();

        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject["code"].toString() == "200")
        {
            int i=0;
//            U[0].GetContact(contactname).ClearConversation();
            while(jsonObject.contains("block "+QString::number(i))){
//                ui->textEdit_conversation->append(jsonObject["block "+QString::number(i)].toObject()["src"].toString()+" :");
                QString message=jsonObject["block "+QString::number(i)].toObject()["body"].toString()+"       "+
                        jsonObject["block "+QString::number(i)].toObject()["date"].toString();
//                ui->textEdit_conversation->append(message);
//                ui->textEdit_conversation->append("");
//                U[0].GetContact(contactname).SetConversation(jsonObject["block "+QString::number(i)].toObject()["src"].toString(),message);
                i++;
                QString filePath="User/Contacts/"+dst+".json";
                QJsonObject fileObjectToWrite=jsonObject;
                QJsonDocument fileDocumentToWrite(fileObjectToWrite);
                QFile fileToWrite(filePath);
                if(fileToWrite.open(QIODevice::WriteOnly)){
                    fileToWrite.write(fileDocumentToWrite.toJson());
                    fileToWrite.close();
                }
            }
//            ui->pushButton_entermessage_contact->setEnabled(true);
        }
}
}

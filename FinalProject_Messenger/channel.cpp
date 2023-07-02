#include "channel.h"
#include"dialog_login.h"


Channel::Channel()
{

}

void Channel::SetAdminAndIsAdmin(QString admin, bool isadmin)
{
    Admin = admin;
    IsAdmin = isadmin;
}

void Channel::CreateNewChannel(QString token, QString title, QString channelName)
{
    Count = 0;
    SetAdminAndIsAdmin(token,true);
    ChannelName = channelName;
    Title = title;
    //initiolize attribute of class

        //http://api.barafardayebehtar.ml:8080/createchannel?token=7a3c48
//        f7c7939b7269d01443a431825f&channel_name=mychannel&channel_title
//        =Channel1
        QString urlString = "http://api.barafardayebehtar.ml:8080/createchannel?token=";
        urlString += U[0].GetToken() + "&channel_name=" + channelName + "&channel_title=" + title;

        QNetworkAccessManager manager;

        QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

        QEventLoop loop;
        QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec(); // Block until the request is finished

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();

            QJsonDocument JsonDocument = QJsonDocument::fromJson(data);

            QJsonObject JsonObject = JsonDocument.object();

            if(JsonObject.value("code").toString() == "200")
            {
    //            QMessageBox::information(this,"respons by server",jsonObject.value("message").toString());
                QLabel* label = new QLabel(JsonObject.value("message").toString());
                label->setFixedSize(400,100);
                label->show();
                QTimer::singleShot(1000, [=]() {
                    label->deleteLater();
                });

                //Working with files (saved format: Jason format)/////////////
                {
                    QJsonObject FileObject;
                    FileObject.insert("ChannelName", channelName);
                    FileObject.insert("Title", title);

                    QJsonDocument FileDocument(FileObject);
                    QByteArray WriteData = FileDocument.toJson(QJsonDocument::Indented);

                    QString filePath = "User/Channels/" + channelName + ".txt";
                    QDir directory("User/Channels");

                    if (!directory.exists())
                    {
                        if (directory.mkpath("."))
                        {
                            qDebug() << "Folder User/Channels created successfully!";
                        }
                    }

                    QFile outFile(filePath);
                    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QTextStream text(&outFile);
                        text << WriteData;
                        outFile.close();
                        qDebug() << "Data written to file: " << filePath;
                    }

                }
            }
            if(JsonObject.value("code").toString() == "404")
            {
                QLabel* label = new QLabel(JsonObject.value("message").toString());
                label->setFixedSize(400,100);
                label->show();
                QTimer::singleShot(1000, [=]() {
                    label->deleteLater();
                });
    //            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
            }
            if(JsonObject.value("code").toString() == "204")
            {
                QLabel* label = new QLabel(JsonObject.value("message").toString());
                label->setFixedSize(400,100);
                label->show();
                QTimer::singleShot(1000, [=]() {
                    label->deleteLater();
                });
    //            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
            }
            if(JsonObject.value("code").toString() == "401")
            {
                QLabel* label = new QLabel(JsonObject.value("message").toString());
                label->setFixedSize(400,100);
                label->show();
                QTimer::singleShot(1000, [=]() {
                    label->deleteLater();
                });
            }

        }

}


void Channel::AddMessageToChannelWithChannelName(QString token, QString channelName, QString message)
{
//http://api.barafardayebehtar.ml:8080/sendmessagechannel?token=7
//a3c48f7c7939b7269d01443a431825f&dst=mychannel&body=hello%20all

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyyMMddhhmmss");

    qDebug() << formattedDateTime;
    QString urlString = "http://api.barafardayebehtar.ml:8080/sendmessagechannel?token=";
    urlString = urlString + Token + "&dst=" + channelName + "&body=" + message;

    qDebug()<<"URL : "<<urlString<<"\n";

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument JsonDocument = QJsonDocument::fromJson(data);

        QJsonObject JsonObject = JsonDocument.object();

        if(JsonObject.value("code").toString()=="200")
        {
            {
                QJsonObject FileObject = GetChannelsChatsWithToken(Count,Token,channelName);
                Count++;
                QJsonDocument FileDocument (FileObject);

                 QString filePath = "User/Channels/" + channelName + ".txt";

                 QByteArray WriteData = FileDocument.toJson(QJsonDocument::Indented);

                 QFile outFile(filePath);
                 if (outFile.open(QIODevice::Append | QIODevice::Text))
                 {
                     QTextStream text(&outFile);
                     text << WriteData;
                     outFile.close();
                     qDebug() << "Data written to file: " << filePath;

                 }

            }
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
        }
        if(JsonObject.value("code").toString() == "404")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
        }
        if(JsonObject.value("code").toString() == "204")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
        }
        if(JsonObject.value("code").toString() == "401")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
        }
    }
}


void Channel::SetChannelTokenWithAdmin(QString token)
{
    Token = token;
}

QJsonObject Channel::GetChannelsChatsWithToken(int block, QString token, QString channelname)
{
//http://api.barafardayebehtar.ml:8080/getchannelchats?token=7a3c
//48f7c7939b7269d01443a431825f&dst=aplab&date=20001121081415
    int temp = block;
    QString urlString = "http://api.barafardayebehtar.ml:8080/getchannelchats?token=";
    urlString += token + "&dst=" + channelname  ;

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument JsonDocument = QJsonDocument::fromJson(data);

        QJsonObject JsonObject = JsonDocument.object();

        if(JsonObject.value("code").toString()=="200")
        {
            QJsonObject Block = JsonObject.value("block " +  QString::number(temp)).toObject();
            return Block;
        }
    }


}


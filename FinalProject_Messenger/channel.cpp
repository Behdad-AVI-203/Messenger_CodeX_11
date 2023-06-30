#include "channel.h"

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
    SetAdminAndIsAdmin(token,true);
    ChannelName = channelName;
    Title = title;
    //initiolize attribute of class

    QString directoryName = "AllChannels";
        QDir directory(directoryName);//current directory
        if (!directory.exists()) {
            if (directory.mkpath(directoryName)) {
                qDebug() << "Folder" << directoryName << "created successfully!";

                QString filePath = "AllChannels/" + channelName + ".txt";
                QFile outFile(filePath);
                outFile.open(QIODevice::Text | QIODevice::Append | QIODevice::WriteOnly);
                QString text ="channelName : "+channelName+"\n"+"title : "+title+"\n";
                   QTextStream outStream(&outFile);
                   outStream << text;
                   outFile.close();

            } else {
                qDebug() << "Error creating folder" << directoryName;
            }
        } else {
            QString filePath = "User/Channels" + channelName + ".txt";
            QFile outFile(filePath);
            outFile.open(QIODevice::Text | QIODevice::Append | QIODevice::WriteOnly);
            QString text ="channelName : "+channelName+"\n"+"title : "+title+"\n";
            QTextStream outStream(&outFile);
            outStream << text;
            outFile.close();

            qDebug() << "Folder" << directoryName << "already exists.";
        }

        //http://api.barafardayebehtar.ml:8080/createchannel?token=7a3c48
//        f7c7939b7269d01443a431825f&channel_name=mychannel&channel_title
//        =Channel1
        QString urlString = "http://api.barafardayebehtar.ml:8080/createchannel?token=";
        urlString += token + "&channel_name=" + channelName + "&channel_title=" + title;

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

void Channel::AddMessageToChannelWithChannelName(QString message, QString channelName, QString username)
{
//http://api.barafardayebehtar.ml:8080/sendmessagechannel?token=7
//a3c48f7c7939b7269d01443a431825f&dst=mychannel&body=hello%20all
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


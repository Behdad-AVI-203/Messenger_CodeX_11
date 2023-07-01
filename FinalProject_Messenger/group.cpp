#include "group.h"
#include <QLabel>
#include <QTimer>
#include <QJsonArray>

Group::Group()
{

}

Group::Group(QString title, QString token, QString groupname)
{
    Title = title;
    Token = token;
    GroupName = groupname;
}

void Group::SetGroup(QString title, QString token, QString groupname)
{
    Title = title;
    Token = token;
    GroupName = groupname;
}

void Group::CreatedNewGroup( QString title,  QString token,  QString groupname)
{
    Count = 0;
    Token = token;
    Title = title;
    GroupName = groupname;

    //Working with files (saved format: Jason format)/////////////
    {
        QJsonObject FileObject;
        FileObject.insert("GroupName", groupname);
        FileObject.insert("Title", title);

        QJsonDocument FileDocument(FileObject);
        QByteArray WriteData = FileDocument.toJson(QJsonDocument::Indented);

        QString filePath = "User/Groups/" + groupname + ".txt";
        QDir directory("User/Groups");

        if (!directory.exists())
        {
            if (directory.mkpath("."))
            {
                qDebug() << "Folder User/Groups created successfully!";
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

void Group::AddMessageToGroupWithGroupName(QString username, QString message,QString groupname)
{
    //http://api.barafardayebehtar.ml:8080/sendmessagegroup?token=7a3
    //c48f7c7939b7269d01443a431825f&dst=ap&body=hello%20all

    QString urlString = "http://api.barafardayebehtar.ml:8080/sendmessagegroup?token=";
    urlString += Token+"&dst="+groupname+"&body="+message;
    qDebug()<<"Token = "<<Token<<"\n";
    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject.value("code").toString() == "200")
        {
            GetBlocks(Token,groupname);
//            QMessageBox::information(this,"respons by server",jsonObject.value("message").toString());
            //-------------------------------------------------------------------------------
            int number = 0;
            //read all message in file (json format)
            {
                QString filePath = "User/Groups/";

                    QFile file(filePath);
                    if (!file.open(QIODevice::ReadOnly))
                    {
                        qDebug() << "Failed to open the file.";
                    }

                    QByteArray jsonData = file.readAll();
                    file.close();

                    QJsonParseError error;
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);
                    if (error.error != QJsonParseError::NoError)
                    {
                        qDebug() << "Failed to parse JSON:" << error.errorString();
                    }

                    if (!jsonDoc.isArray())
                    {
                        qDebug() << "Invalid JSON format: not an array.";
                    }

                    QJsonArray jsonArray = jsonDoc.array();
                    int counter = 1;
                    int index = 0;
                    for (QJsonValueRef value : jsonArray)
                    {

                        if (value.isObject())
                        {
                            QJsonObject jsonObj = value.toObject();
                            jsonObj["block " + QString::number(index)] = counter++;
                            index++;
                            qDebug() << jsonObj;
                        }
                    }
                     qDebug()<<"INDEX : "<<index;
            }
            //-------------------------------------------------------------------------------

            //-------------------------------------------------------------------------------
            // stored message in file(json format)
            {
//                Count = GetBlocks();
                QJsonObject FileObject = GetGroupsChatsWithToken(Count,Token,groupname);
//                Count++;
                QJsonDocument FileDocument (FileObject);

                 QString filePath = "User/Groups/" + groupname + ".txt";

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

            //-------------------------------------------------------------------------------
            QLabel* label = new QLabel(jsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(1000, [=]() {
                label->deleteLater();
            });
        }
        if(jsonObject.value("code").toString() == "404")
        {
            QLabel* label = new QLabel(jsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(1000, [=]() {
                label->deleteLater();
            });
//            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "204")
        {
            QLabel* label = new QLabel(jsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(1000, [=]() {
                label->deleteLater();
            });
//            QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
        }
        if(jsonObject.value("code").toString() == "401")
        {
            QLabel* label = new QLabel(jsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(1000, [=]() {
                label->deleteLater();
            });
        }
    }

}

void Group::CheckMembershipInTheGroup(QString token, QString groupname)
{
    QString urlString = "";///////////////////////////////
}

void Group::MembershipInSpecialGroup(QString token, QString groupname)
{
    //http://api.barafardayebehtar.ml:8080/joingroup?token=7a3c48f7c7
    //939b7269d01443a431825f&group_name=ap
}

void Group::SetTokenOfUsernameGroup(QString token)
{
    Token = token;
}

int Group::GetBlocks(QString token, QString groupname)
{
    QDate currentDate = QDate::currentDate();

    QTime currentTime = QTime::currentTime();

    qDebug()<<"Date : "<<currentDate.toString()+ " " + currentTime.toString()<<"\n";

    int Number = 0;
//http://api.barafardayebehtar.ml:8080/getgroupchats?token=7a3c48
//f7c7939b7269d01443a431825f&dst=ap&date=20001121081415
    QString urlString = "http://api.barafardayebehtar.ml:8080/getgroupchats?token=";
    urlString += token + "&dst=" + groupname  ;

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
            for(int i=0;i<150;i++)
            {
                QJsonObject block = JsonObject.value("block " + QString::number(i)).toObject();
                if(block.value("body").toString()!="")
                {
                    Number ++;
                }
                else
                {
                    break;
                }
            }

        }
        qDebug()<<"Number : "<<Number<<"\n";
        return Number;


    }

}

QJsonObject Group::GetGroupsChatsWithToken(int block ,QString token, QString groupname)
{
    int temp = block;
    QString urlString = "http://api.barafardayebehtar.ml:8080/getgroupchats?token=";
    urlString += token + "&dst=" + groupname  ;

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

void Group::SetCountGroup(int count)
{
    Count = count;
}





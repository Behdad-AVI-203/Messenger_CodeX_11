#ifndef CHANNEL_H
#define CHANNEL_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <fstream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <thread>
#include <QEventLoop>
#include <QObject>
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QTimer>

using namespace std;


class Channel
{
public:
    Channel();
    void SetAdminAndIsAdmin(QString admin,bool isaAdmin);
    void SendChannelMessageByAdmin(QString channelName, bool isadmin, QString message);
    void CreateNewChannel(QString token,QString title, QString channelName);
    void AddMessageToChannel(QString message,QString channelName,QString username);

protected:
    QString Token;
    QString Title;
    QString ChannelName;
    QString Admin;
    bool IsAdmin;

};

#endif // CHANNEL_H

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include<QFile>
using namespace std;
#include "group.h"
#include "channel.h"
#include "contact.h"

class User
{
public:
    User();
    User(QString username,QString password,QString token);
    //void SetUser(string username,string password,string lastname,string firstname,string token);
    void SetUserToken(QString token);
    void SetUserContacts(QString contact,Contact temp);
    void SetUserGroups(QString grname,Group temp);
    void SetUserChannels(QString chname,Channel temp);
    QString GetUserName();
    QString GetPassword();
    QString GetToken();
    Contact GetContact(QString contact);
    bool IsContactExist(QString name);

protected:
    QString UserName;
    QString Password;
    QString Token;
    QMap<QString ,Contact> Contacts;
    QMap<QString,Group> Groups;
    QMap<QString,Channel> Channels;
};

#endif // USER_H

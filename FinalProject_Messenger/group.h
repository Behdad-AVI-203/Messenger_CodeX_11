#ifndef GROUP_H
#define GROUP_H
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
#include <QThread>
#include <QDialog>
#include <QMessageBox>


using namespace std;

class Group
{
public:
    Group();
    Group(QString title,QString token,QString groupname);
    void SetGroup(QString title,QString token,QString groupname);
    void CreatedNewGroup(QString title,QString token,QString groupname);
    void AddMessageToGroupWithGroupName(QString username, QString message,QString groupname);
    void CheckMembershipInTheGroup(QString token,QString groupname);
    void MembershipInSpecialGroup(QString token,QString groupname);
    void SetTokenOfUsernameGroup(QString token);
    int GetBlocks(QString token,QString groupname);
    QJsonObject GetGroupsChatsWithToken(int block ,QString token, QString groupname);
    void SetCountGroup(int count);

protected:
    QString Title;
    QString Token;
    QString GroupName;
    int Count;
};

#endif // GROUP_H

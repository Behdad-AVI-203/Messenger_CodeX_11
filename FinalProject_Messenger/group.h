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
#include <QMessageBox>
#include <thread>
#include <QEventLoop>
#include <QObject>
#include <QDialog>



using namespace std;

class Group
{
public:
    Group();
    Group(QString title,QString token,QString groupname);
    void SetGroup(QString title,QString token,QString groupname);
    void CreatedGroup(QString title,QString token,QString groupname);
    void AddMessageToGroupWithGroupName(QString username, QString message,QString groupname);
    void CheckMembershipInTheGroup(QString token,QString groupname);
    void MembershipInSpecialGroup(QString token,QString groupname);
protected:
    QString Title;
    QString Token;
    QString GroupName;
};

#endif // GROUP_H

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
using namespace std;

class Group
{
public:
    Group();
    Group(QString title,QString token,QString groupname);
    void SetGroup(QString title,QString token,QString groupname);
    void CreatedGroup(QString title,QString token,QString groupname);
    void AddMessageToGroupWithGroupName(QString username, QString message,QString groupname);

protected:
    QString Title;
    QString Token;
    QString GroupName;
};

#endif // GROUP_H

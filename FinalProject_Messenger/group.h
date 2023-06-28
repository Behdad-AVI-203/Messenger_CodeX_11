#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QFile>
#include <QDir>
#include <QString>
using namespace std;

class Group
{
public:
    Group();
    Group(QString title,QString token,QString groupname);
    void SetGroup(QString title,QString token,QString groupname);
    void CreatedGroup(QString title,QString token,QString groupname);


protected:
    QString Title;
    QString Token;
    QString GroupName;
};

#endif // GROUP_H

#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <string>
#include <QVector>
#include <fstream>
#include <map>
#include <QDebug>
using namespace std;
#include "group.h"
#include "channel.h"



class Contact
{
public:
    Contact(QString contactname);
    void SetConversation(QString type,QString message);
protected:
    QString ContactName;
    QMultiMap <QString,QString> Conversation;
};


#endif // CONTACT_H

#ifndef USER_H
#define USER_H

#include"all_include.h"

class User
{
public:
    User();
    User(QString username,QString password,QString token);
    QString GetUserName();
    QString GetPassword();
    QString GetToken();
protected:
    QString UserName;
    QString Password;
    QString Token;
};

#endif // USER_H

#include "user.h"
#include"dialog_login.h"

//QVector<User> U;

User::User()
{
    //defualt constructor
}

User::User(QString username, QString password, QString token)
{
    Token = token;
    UserName = username;
    Password = password;
    QDir().mkdir("User");
    QString filePath = "User/user.json";
    QJsonObject obj;
        obj["username"] = username;
        obj["password"] = password;
        obj["token"] = token;
        QJsonDocument doc(obj);
        QFile file(filePath);
        file.open(QFile::WriteOnly | QFile::Text);
        file.write(doc.toJson());
        file.close();
    QDir().mkdir("User/Contacts");
    QDir().mkdir("User/Groups");
    QDir().mkdir("User/Channels");
}
QString User::GetUserName(){
    return UserName;
}
QString User::GetPassword(){
    return Password;
}
QString User::GetToken(){
    return Token;
}


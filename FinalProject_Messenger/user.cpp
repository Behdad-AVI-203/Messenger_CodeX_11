#include "user.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include<QFile>

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
    QString filePath = "User/"+username+".json";
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

/*void User::SetUser(string username, string password, string lastname, string firstname, string token)
{
    // initialize attribute
    Token = token;
    UserName = username;
    Password = password;
    LastName = lastname;
    FirstName =  firstname;
}
*/

void User::SetUserToken(QString token)
{
    Token = token;
}

void User::SetUserContacts(QString contact,Contact temp){
    Contacts.insert(contact,temp);
}
void User::SetUserGroups(QString grname,Group temp){
    Groups.insert(grname,temp);
}
void User::SetUserChannels(QString chname,Channel temp){
    Channels.insert(chname,temp);
}


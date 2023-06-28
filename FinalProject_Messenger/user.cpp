#include "user.h"
#include <QDir>

User::User()
{
    //defualt constructor
}

User::User(string username, string password, string lastname, string firstname, string token)
{
    // initialize attribute
    Token = token;
    UserName = username;
    Password = password;
    LastName = lastname;
    FirstName =  firstname;
    QDir* Dir = new QDir();
//    qDebug()<<"DIR = "<<Dir->currentPath().append(".txt");
    string filePath = "D:/FinalProject2/Messenger_CodeX_11/build-FinalProject_Messenger-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/Users/";
    filePath.append(username.append(".txt"));
    ofstream outFile(filePath,ios::app);
    if(outFile.is_open())
    {
        qDebug()<<"File created successfully\n";
        outFile<<username<<' '<<password;
    }
    else
    {
        qDebug()<<"File created not successfully\n";
    }
}

void User::SetUser(string username, string password, string lastname, string firstname, string token)
{
    // initialize attribute
    Token = token;
    UserName = username;
    Password = password;
    LastName = lastname;
    FirstName =  firstname;
}

void User::SetUserContactMessage(string dst, string username)
{
    SetUserNameUSER(username);
    Contact *C = new Contact();
    C->SetContactMessage(dst,UserName);
    Contacts.insert(make_pair(Token,*C));
}

void User::SetUserNameUSER(string username)
{
    UserName = username;
}

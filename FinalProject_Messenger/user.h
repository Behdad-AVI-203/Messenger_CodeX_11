#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;
#include "group.h"
#include "channel.h"
#include "contact.h"

class User : public Group, public Channel ,public Contact
{
public:
    User();
    User(string username,string password,string lastname,string firstname,string token);
    void SetUser(string username,string password,string lastname,string firstname,string token);
    void SetUserContactMessage(string dst,string username);
    void SetUserNameUSER(string username);


protected:
    string UserName;
    string Password;
    string LastName;
    string FirstName;
    string Token;
    map<string ,Contact> Contacts;
    vector<Group> Groups;
    vector<Channel>Channels;
};

#endif // USER_H

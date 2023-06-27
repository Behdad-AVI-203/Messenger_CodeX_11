#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class User
{
public:
    User();
protected:
    string UserName;
    string Password;
    string LastName;
    string FirstName;
    string Token;
};

#endif // USER_H

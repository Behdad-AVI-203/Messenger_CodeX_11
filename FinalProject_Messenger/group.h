#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QString>
using namespace std;

class Group
{
public:
    Group();
    Group(string title,string token,string groupname);
    void SetGroup(string title,string token,string groupname);

protected:
    QString Title;
    QString Token;
    QString GroupName;
};

#endif // GROUP_H

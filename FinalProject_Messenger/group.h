#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Group
{
public:
    Group();
    Group(string title,string token,string groupname);
    void SetGroup(string title,string token,string groupname);

protected:
    string Title;
    string Token;
    string GroupName;
};

#endif // GROUP_H

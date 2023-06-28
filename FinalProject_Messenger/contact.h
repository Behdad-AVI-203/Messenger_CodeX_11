#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <QDebug>
using namespace std;
#include "group.h"
#include "channel.h"



class Contact
{
public:
    Contact();
    void SetContactMessage(string message,string username);
    string Messages;
//    friend ofstream& operator<<(ostream& COUT,const Contact& C)
//    {
//        COUT<<"Messages :\n"<<C.Messages<<"\nfrom "<<C.
//    }
};


#endif // CONTACT_H

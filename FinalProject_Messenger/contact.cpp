#include "contact.h"

Contact::Contact()
{

}

void Contact::SetContactMessage(string message,string username)
{
    qDebug()<<"message = "<<QString::fromStdString(message)<<" , Username = "<<QString::fromStdString(username)<<"\n";
    Messages = message ;
    string filePath = username;
    ofstream outFile(filePath.append(".txt"),ios::app);
    outFile<<"from User : "<<username<<"\nMessages : "<<Messages<<"\n";
    outFile.close();
}

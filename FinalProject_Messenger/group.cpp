#include "group.h"

Group::Group()
{

}

Group::Group(QString title, QString token, QString groupname)
{
    Title = title;
    Token = token;
    GroupName = groupname;
}

void Group::SetGroup(QString title, QString token, QString groupname)
{
    Title = title;
    Token = token;
    GroupName = groupname;
}

void Group::CreatedGroup(QString title, QString token, QString groupname)
{
    Token = token;
    Title = title;
    GroupName = groupname;
    QString currentPath = QDir::currentPath();
    QString folderPath = "AllGroups";
    QDir directory(currentPath);
    bool exist = directory.exists(folderPath);
    if(!exist)
    {
        bool created = directory.mkdir(folderPath);
        if(created == true)
            //created successfully
            qDebug()<<"Folder created successfully\n";
        else
        {
            qDebug()<<"Failed to create successfully\n";
        }
    }
    else
    {
        qDebug()<<"Folder exist\n";
    }


}

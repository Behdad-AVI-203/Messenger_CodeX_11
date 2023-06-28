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

void Group::CreatedGroup( QString title,  QString token,  QString groupname)
{
    Token = token;
    Title = title;
    GroupName = groupname;

    QDir directory("AllGroups");
        QString filePath = "AllGroups/" + groupname + ".txt";
        QFile outFile(filePath);

        outFile.open(QIODevice::Text | QIODevice::WriteOnly);
        outFile.write("sdkjsdlksdks;dhadkadjfhaldf");
        outFile.close();

}



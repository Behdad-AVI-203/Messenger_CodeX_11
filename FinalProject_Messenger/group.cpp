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

    QString directoryName = "AllGroups";
        QDir directory(directoryName);

        if (!directory.exists()) {
            if (directory.mkpath(directoryName)) {
                qDebug() << "Folder" << directoryName << "created successfully.";
            } else {
                qDebug() << "Error creating folder" << directoryName;
            }
        } else {
            qDebug() << "Folder" << directoryName << "already exists.";
        }
        QString filePath = "AllGroups/" + groupname + ".txt";
        QFile outFile(filePath);
        outFile.open(QIODevice::Text | QIODevice::Append | QIODevice::WriteOnly);
        QString text = "token : "+token +"\n"+"groupname : "+groupname+"\n"+"title : "+title+"\n";
           QTextStream outStream(&outFile);
           outStream << text;
           outFile.close();
}

void Group::AddMessageToGroupWithGroupName(QString message)
{

}



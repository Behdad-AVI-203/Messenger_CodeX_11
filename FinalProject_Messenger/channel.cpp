#include "channel.h"

Channel::Channel()
{

}

void Channel::SetAdminAndIsAdmin(QString admin, bool isadmin)
{
    Admin = admin;
    IsAdmin = isadmin;
}

void Channel::CreateNewChannel(QString username, QString title, QString channelName)
{
    SetAdminAndIsAdmin(username,true);
    ChannelName = channelName;
    Title = title;
    //initiolize attribute of class

    QString directoryName = "AllChannels";
        QDir directory(directoryName);//current directory
        if (!directory.exists()) {
            if (directory.mkpath(directoryName)) {
                qDebug() << "Folder" << directoryName << "created successfully.";

                QString filePath = "AllGroups/" + channelName + ".txt";
                QFile outFile(filePath);
                outFile.open(QIODevice::Text | QIODevice::Append | QIODevice::WriteOnly);
                QString text ="groupname : "+channelName+"\n"+"title : "+title+"\n";
                   QTextStream outStream(&outFile);
                   outStream << text;
                   outFile.close();

            } else {
                qDebug() << "Error creating folder" << directoryName;
            }
        } else {
            QString filePath = "AllGroups/" + channelName + ".txt";
            QFile outFile(filePath);
            outFile.open(QIODevice::Text | QIODevice::Append | QIODevice::WriteOnly);
            QString text ="groupname : "+channelName+"\n"+"title : "+title+"\n";
            QTextStream outStream(&outFile);
            outStream << text;
            outFile.close();

            qDebug() << "Folder" << directoryName << "already exists.";
        }



}


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

void Group::AddMessageToGroupWithGroupName(QString username, QString message,QString groupname)
{
    QString cuuerntPath = QDir::currentPath();
    QString filePath = cuuerntPath +"/AllGroups/" + groupname + ".txt";
    QFile outFile(filePath);
    qDebug()<<"file path = "<<filePath<<"\n";
    outFile.open(QIODevice::Text | QIODevice::Append);
    QString text = "username : " + username + "\n" + "message : " + message +"\n";
    QTextStream outStream(&outFile);
    outStream << text;
    outFile.close();

}

void Group::CheckMembershipInTheGroup(QString token, QString groupname)
{
    QString urlString = "";///////////////////////////////
}

void Group::MembershipInSpecialGroup(QString token, QString groupname)
{
    //http://api.barafardayebehtar.ml:8080/joingroup?token=7a3c48f7c7
    //939b7269d01443a431825f&group_name=ap


}





#include "mainwindow.h"
#include"startwindow.h"
#include"user.h"
#include"dialog_login.h"
#include "all_include.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir folder("User");

    if(!folder.isEmpty()){
        QFile file("User/user.json");
        file.open(QIODevice::ReadOnly);
        QByteArray b = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(b);
        QJsonObject jsonObject = doc.object();
        User temp(jsonObject["username"].toString(),jsonObject["password"].toString(),jsonObject["token"].toString());
        U.push_back(temp);
        file.close();
        StartWindow s;
        s.show();
        return a.exec();
    }
    MainWindow* w=new MainWindow();
    w->show();
    return a.exec();
}

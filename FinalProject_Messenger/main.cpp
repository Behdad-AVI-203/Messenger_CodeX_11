#include "mainwindow.h"
#include"startwindow.h"
#include<QDir>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir folder("User");
    if(!folder.isEmpty()){
        StartWindow s;
        s.show();
        return a.exec();
    }
    MainWindow w;
    w.show();
    return a.exec();
}

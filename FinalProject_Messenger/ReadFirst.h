#ifndef READFIRST_H
#define READFIRST_H
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <fstream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <thread>
#include <QEventLoop>
#include <QObject>
#include <QDialog>
#include <QMessageBox>


void ReadGroupList(QString token);
void ReadGroupListWithDestination(QString dst, QString token);

void ReadChannelListt(QString token);
void ReadChannelListWithDestination(QString dst, QString token);

void ReadUserLIST(QString token);
void ReadUseristWithDestination(QString dst, QString token);




#endif // READFIRST_H

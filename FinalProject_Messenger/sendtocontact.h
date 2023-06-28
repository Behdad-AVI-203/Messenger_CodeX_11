#ifndef SENDTOCONTACT_H
#define SENDTOCONTACT_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include<QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QMessageBox>
#include<thread>
#include <QWidget>
#include <iostream>
#include <fstream>
using namespace std;


namespace Ui {
class SendToContact;
}

class SendToContact : public QWidget
{
    Q_OBJECT

public:
    explicit SendToContact(QWidget *parent = nullptr);
    ~SendToContact();
    void SetChatWindowToken(string token);
    string GetChatWindowToken();

private slots:


    void on_SendButton_clicked();

private:
    string token;
    Ui::SendToContact *ui;
};

#endif // SENDTOCONTACT_H

#ifndef DIALOG_CREATE_GROUP_H
#define DIALOG_CREATE_GROUP_H

#include "group.h"
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include<QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QMessageBox>
#include<thread>

namespace Ui {
class Dialog_Create_Group;
}

class Dialog_Create_Group : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Create_Group(QWidget *parent = nullptr);
    ~Dialog_Create_Group();
    void SetCreateGroupToken(QString token);
    QString GetCreateGroupToken();

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_Create_Group *ui;
    QString Token;
};

#endif // DIALOG_CREATE_GROUP_H

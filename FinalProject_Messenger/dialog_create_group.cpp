#include "dialog_create_group.h"
#include "ui_dialog_create_group.h"

Dialog_Create_Group::Dialog_Create_Group(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Create_Group)
{
    ui->setupUi(this);
}

Dialog_Create_Group::~Dialog_Create_Group()
{
    delete ui;
}

void Dialog_Create_Group::SetCreateGroupToken(QString token)
{
    Token = token;
}

QString Dialog_Create_Group::GetCreateGroupToken()
{
    return Token;
}


void Dialog_Create_Group::on_pushButton_create_clicked()
{
    //http://api.barafardayebehtar.ml:8080/creategroup?token=7a3c48f7
//    c7939b7269d01443a431825f&group_name=G1&group_title=Group1
        QString urlString = "http://api.barafardayebehtar.ml:8080/";
        urlString = urlString + "creategroup?token=" + Token +
        + "&group_name=" +ui->lineEdit_groupname->text()+"&group_title="+ui->lineEdit_grouptitle->text();

        QNetworkAccessManager manager;

        QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec(); // Block until the request is finished

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();

            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

            QJsonObject jsonObject = jsonDocument.object();

            if(jsonObject.value("code").toString() == "200")
            {
                QMessageBox::information(this,"respons by server","Creat group successfully");
            }
            if(jsonObject.value("code").toString() == "404")
            {
                QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
            }
            if(jsonObject.value("code").toString() == "204")
            {
                QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
            }
            if(jsonObject.value("code").toString() == "401")
            {
                QMessageBox::warning(this,"Response sent by the server",jsonObject.value("message").toString());
            }

        }

        Group* newGroup = new Group();
        newGroup->CreatedNewGroup(ui->lineEdit_grouptitle->text(),Token,ui->lineEdit_groupname->text());
        close();
}


void Dialog_Create_Group::on_pushButton_cancel_clicked()
{
    this->close();
}


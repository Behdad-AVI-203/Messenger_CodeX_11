#include "dialog_create_group.h"
#include "ui_dialog_create_group.h"

dialog_create_group::dialog_create_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_create_group)
{
    ui->setupUi(this);
}

dialog_create_group::~dialog_create_group()
{
    delete ui;
}

void dialog_create_group::SetCreateGroupToken(QString token)
{
    Token = token;
}

QString dialog_create_group::GetCreateGroupToken()
{
    return Token;
}

void dialog_create_group::on_pushButton_clicked()
{
    //http://api.barafardayebehtar.ml:8080/creategroup?token=7a3c48f7
//    c7939b7269d01443a431825f&group_name=G1&group_title=Group1
        QString urlString = "http://api.barafardayebehtar.ml:8080/";
        urlString = urlString + "creategroup?token=" + Token +
        + "&group_name=" +ui->NameLineEdit->text()+"&group_title="+ui->TitleLineEdit->text();

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
        newGroup->CreatedGroup(ui->TitleLineEdit->text(),Token,ui->NameLineEdit->text());
        close();
}


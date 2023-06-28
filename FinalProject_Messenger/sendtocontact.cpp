#include "sendtocontact.h"
#include "ui_sendtocontact.h"

SendToContact::SendToContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendToContact)
{
    ui->setupUi(this);
}

SendToContact::~SendToContact()
{
    delete ui;
}

void SendToContact::SetChatWindowToken(string token)
{
    this->token = token;
}

string SendToContact::GetChatWindowToken()
{
    return token;
}




void SendToContact::on_SendButton_clicked()
{
    QString temp = "http://api.barafardayebehtar.ml:8080/sendmessageuser?";
    temp+= "token="+QString::fromStdString(token)+"&dst=" + ui->UsernameContactLineEdit->text();
    QUrl url(temp);

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();

        QString message = jsonObject.value("message").toString();
        QString code = jsonObject.value("code").toString();

        QString returnMessage = jsonObject.value("message").toString();
        QString returnCode = jsonObject.value("code").toString();
        QString returnToken = jsonObject.value("token").toString();

        if(returnCode == "200")
        {
            QMessageBox::information(this,"Response sent by the server",data);
            QString temp = returnToken;
            qDebug()<<"token = "<<returnToken<<"\n";
        }
        if(returnCode == "404")
        {
            QMessageBox::warning(this,"Response sent by the server","Your request was not successful and the requested information was not found");
        }
        if(returnCode == "204")
        {
            QMessageBox::warning(this,"Response sent by the server","Your request was not successful and due to the duplicate information, it is not possible to make a request to the server.");
        }
        if(returnCode == "401")
        {
            QMessageBox::warning(this,"Response sent by the server","Your request was not successful and the information you provided to the server is incorrect");
        }
    }


    qDebug()<<"Token = "<<QString::fromStdString(token)<<"\n";
}


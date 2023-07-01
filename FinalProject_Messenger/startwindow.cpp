#include "startwindow.h"
#include "ui_startwindow.h"
#include "dialog_join_channel.h"
#include <QThread>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
//    zQThread* thread1 = new QThread();
//        QObject::connect(thread1, &QThread::started, [](){
//            function1();
//        });
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::SetTokenFromUserName(QString token)
{
    Token = token;
}

void StartWindow::SetUsernameFromUserName(QString username)
{
    Username = username;
}

void StartWindow::SetPasswordFromUserName(QString password)
{
    Password = password;
}

QString StartWindow::GetTokenFromUserName()
{
    return Token;
}

QString StartWindow::GetUsernameFromUserName()
{
    return Username;
}

void StartWindow::on_actionCreat_Group_triggered()
{
    dialog_create_group* window = new dialog_create_group();
    window->SetCreateGroupToken(Token);
    window->show();
}


void StartWindow::on_pushButton_entermessage_2_clicked()
{
    Group* G = new Group();
    G->SetTokenOfUsernameGroup(Token);
    G->AddMessageToGroupWithGroupName(Username,ui->lineEdit_message_2->text(),ui->lineEdit_searchgroupe->text());
}


void StartWindow::on_actionJoin_Group_triggered()
{
    dialog_Join_Group* window = new dialog_Join_Group();
    window->SetJoinGroupToken(Token);
    window->show();

}








void StartWindow::on_actionCreat_Channel_triggered()
{
    dialog_create_Channel* window = new dialog_create_Channel();
    window->SetTokenFromChannel(Token);
    window->show();
}


void StartWindow::on_actionJoin_Channel_triggered()
{
    dialog_join_Channel* C = new dialog_join_Channel();
    C->SetJoinChannelToken(Token);
    C->show();
}


void StartWindow::on_pushButton_entermessage_3_clicked()
{
    Channel* C = new Channel();
    C->SetChannelTokenWithAdmin(Token);
    C->AddMessageToChannelWithChannelName(Token,ui->lineEdit_searchchannel->text(),ui->lineEdit_message_3->text());
}


void StartWindow::on_actionLogout_triggered()
{
//http://api.barafardayebehtar.ml:8080/logout?username=sara&passw
//ord=1234
    QString urlString = "http://api.barafardayebehtar.ml:8080/logout?username=";
    urlString +=  Username + "&password=" + Password;

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument JsonDocument = QJsonDocument::fromJson(data);

        QJsonObject JsonObject = JsonDocument.object();

        if(JsonObject.value("code").toString()=="200")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
            close();
        }
        if(JsonObject.value("code").toString() == "404")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
        }
        if(JsonObject.value("code").toString() == "204")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(1000, [=]() {
                label->deleteLater();
            });
        }
        if(JsonObject.value("code").toString() == "401")
        {
            QLabel* label = new QLabel(JsonObject.value("message").toString());
            label->setFixedSize(400,100);
            label->show();
            QTimer::singleShot(2000, [=]() {
                label->deleteLater();
            });
        }

    }

}


void StartWindow::on_textEdit_channels_2_selectionChanged()
{
    ui->textEdit_channels_2->setText("Salam");
}


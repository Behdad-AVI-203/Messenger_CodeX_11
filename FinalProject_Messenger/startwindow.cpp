#include "startwindow.h"
#include "ui_startwindow.h"
#include "dialog_join_channel.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
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






void StartWindow::on_textEdit_groupmessages_textChanged()
{
    ui->textEdit_groups->setText("Sdlks;sl;d;sld;sdlkl");
}


void StartWindow::on_textEdit_groups_selectionChanged()
{
    ui->textEdit_groups->setText("Sdlks;sl;d;sld;sdlkl");
}


void StartWindow::on_textEdit_groupmessages_selectionChanged()
{
    //http://api.barafardayebehtar.ml:8080/getgroupchats?token=7a3c48
//    f7c7939b7269d01443a431825f&dst=ap&date=20001121081415

    QString GroupName[10];
    int index = 0;

    QString urlString = "http://api.barafardayebehtar.ml:8080/getgrouplist?token=";
    urlString +=Token;

    QNetworkAccessManager manager;

    QNetworkReply* reply = manager.get(QNetworkRequest(urlString));

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        QJsonObject jsonObject = jsonDocument.object();

        if(jsonObject.value("code").toString() == "200")
        {
            QString blocks = "block ";
            int Conuter = 0;
            QMessageBox::information(this,"respons by server",jsonObject.value("message").toString());
            for(int i=0;i<10;i++)
            {

                blocks += QString::fromUtf8(to_string(i));
                if(jsonObject.value(blocks).toString()!="")
                {
                    GroupName[i].append(jsonObject.value(blocks).toString());
                }
                else
                {
                    break;
                }
                Conuter++;
            }
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

    // بهداد زذه باید جابه جا کنم

    ui->textEdit_groupmessages->setText(GroupName[0]);
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


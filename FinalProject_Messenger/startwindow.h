#ifndef STARTWINDOW_H
#define STARTWINDOW_H
<<<<<<< HEAD
#include <QListWidgetItem>

#include <QMessageBox>
#include<QTimer>
=======
#include <dialog_create_group.h>
>>>>>>> FixChannel
#include <QMainWindow>
#include "group.h"
#include "dialog_join_group.h"
#include "dialog_create_channel.h"
#include <QString>
#include <QTextCharFormat>
#include <QStringListModel>
#include <QListView>
#include <QListWidgetItem>
#include <QTimer>
#include <QTextEdit>

extern QString contactname;

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
<<<<<<< HEAD
    //void refresh();
    void refresh_conversation(QString name);

private slots:
    void on_actionLogout_triggered();

    void refreshlistview();

    void on_pushButton_searchuser_clicked();

    void show_conversation();
    void on_pushButton_entermessage_contact_clicked();

    void on_listWidget_contacts_itemClicked(QListWidgetItem *item);

signals:
    void ContactSignal();

private:
    Ui::StartWindow *ui;
    QTimer* timer = new QTimer(this);
=======
    void SetTokenFromUserName(QString token);
    void SetUsernameFromUserName(QString username);
    void SetPasswordFromUserName(QString password);
    QString GetTokenFromUserName();
    QString GetUsernameFromUserName();


private slots:
    void on_actionCreat_Group_triggered();

    void on_pushButton_entermessage_2_clicked();

    void on_actionJoin_Group_triggered();

    void on_actionCreat_Channel_triggered();

    void on_actionJoin_Channel_triggered();

    void on_pushButton_entermessage_3_clicked();

    void on_actionLogout_triggered();

    void on_textEdit_channels_2_selectionChanged();

private:
    Ui::StartWindow *ui;
    QString Token;
    QString Username;
    QString Password;
>>>>>>> FixChannel
};

#endif // STARTWINDOW_H

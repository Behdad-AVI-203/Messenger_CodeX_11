#ifndef STARTWINDOW_H
#define STARTWINDOW_H
<<<<<<< HEAD
#include <QListView>
#include <QStringListModel>
#include <QMessageBox>
#include<QTimer>
=======
#include <dialog_create_group.h>
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc
#include <QMainWindow>
#include "group.h"
#include "dialog_join_group.h"
#include "dialog_create_channel.h"
#include <QString>
#include <QTextCharFormat>

//QString contactname;

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

    void on_actionRefresh_triggered();

    void on_pushButton_entermessage_clicked();

    void on_pushButton_searchuser_clicked();

    void on_listView_contacts_clicked(const QModelIndex &index);

    void show_conversation(QString name);
signals:
    void ContactSignal(QString name);

private:
    Ui::StartWindow *ui;
    QStringListModel* contact_model = new QStringListModel(this);
    QStringList contact_items;
    QStringListModel* group_model = new QStringListModel(this);
    QStringList group_items;
    QStringListModel* channel_model = new QStringListModel(this);
    QStringList channel_items;
    QTimer* timer = new QTimer(this);
=======
    void SetTokenFromUserName(QString token);
    void SetUsernameFromUserName(QString username);
    QString GetTokenFromUserName();
    QString GetUsernameFromUserName();


private slots:
    void on_actionCreat_Group_triggered();

    void on_pushButton_entermessage_2_clicked();

    void on_actionJoin_Group_triggered();

    void on_textEdit_groupmessages_textChanged();

    void on_textEdit_groups_selectionChanged();

    void on_textEdit_groupmessages_selectionChanged();

    void on_actionCreat_Channel_triggered();

    void on_actionJoin_Channel_triggered();

private:
    Ui::StartWindow *ui;
    QString Token;
    QString Username;
>>>>>>> ea1a81db0fc2fc1cc6c26e8f740bab25ad81f3fc
};

#endif // STARTWINDOW_H

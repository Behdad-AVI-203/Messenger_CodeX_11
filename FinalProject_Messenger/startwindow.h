#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include"all_include.h"

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
    void refresh_conversation(QString name);
    void ReadGroupListWithDestination(QString name);
    void ReadChannelListWithDestination(QString name);
    void ReadUseristWithDestination(QString name);
private slots:
    void on_actionLogout_triggered();
    void contactsrefreshlistview();
    void groupsrefreshlistview();
    void channelsrefreshlistview();
    void on_pushButton_searchuser_clicked();
    void show_conversation();
    void show_groupmessage();
    void show_channelmessage();
    void on_pushButton_entermessage_contact_clicked();
    void on_listWidget_contacts_itemClicked(QListWidgetItem *item);
    void on_actionCreat_Group_triggered();
    void on_actionCreat_Channel_triggered();
    void on_actionJoin_Group_triggered();
    void on_actionJoin_Channel_triggered();
    void on_pushButton_entermessage_group_clicked();
    void on_pushButton_entermessage_channel_clicked();
    void on_listWidget_groups_itemClicked(QListWidgetItem *item);
    void on_listWidget_channels_itemClicked(QListWidgetItem *item);
    void ReadGroupList();
    void ReadChannelListt();
    void ReadUserLIST();
private:
    Ui::StartWindow *ui;
    QTimer* timer = new QTimer(this);
};

#endif // STARTWINDOW_H

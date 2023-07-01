#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include <QListWidgetItem>

#include <QMessageBox>
#include<QTimer>
#include <QMainWindow>

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
    //void refresh();
    void refresh_conversation(QString name);
    void SetTokenFromUserName(QString token);
    void SetUsernameFromUserName(QString username);
    void SetPasswordFromUserName(QString password);
    QString GetTokenFromUserName();
    QString GetUsernameFromUserName();

private slots:
    void on_actionLogout_triggered();

    void refreshlistview();

    void on_pushButton_searchuser_clicked();

    void show_conversation();
    void on_pushButton_entermessage_contact_clicked();

    void on_listWidget_contacts_itemClicked(QListWidgetItem *item);

    void on_actionCreat_Group_triggered();

    void on_actionCreat_Channel_triggered();

    void on_actionJoin_Group_triggered();

    void on_actionJoin_Channel_triggered();

    void on_pushButton_entermessage_group_clicked();

    void on_pushButton_entermessage_channel_clicked();

signals:
    void ContactSignal();

private:
    Ui::StartWindow *ui;
    QTimer* timer = new QTimer(this);
    QString Token;
    QString Username;
    QString Password;
};

#endif // STARTWINDOW_H

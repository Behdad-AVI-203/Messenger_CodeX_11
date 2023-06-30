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
};

#endif // STARTWINDOW_H

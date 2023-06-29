#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include <QListView>
#include <QStringListModel>
#include <QMessageBox>
#include<QTimer>
#include <QMainWindow>

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
};

#endif // STARTWINDOW_H

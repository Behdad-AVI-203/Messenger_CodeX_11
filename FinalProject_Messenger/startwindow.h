#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

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

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H

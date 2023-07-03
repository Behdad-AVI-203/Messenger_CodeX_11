#ifndef DIALOG_LOGOUT_H
#define DIALOG_LOGOUT_H

#include <QDialog>

namespace Ui {
class Dialog_Logout;
}

class Dialog_Logout : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Logout(QWidget *parent = nullptr);
    ~Dialog_Logout();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_logout_clicked();
    void on_checkBox_setecho_clicked(bool checked);
private:
    Ui::Dialog_Logout *ui;
};

#endif // DIALOG_LOGOUT_H

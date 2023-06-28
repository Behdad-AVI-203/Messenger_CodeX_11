#ifndef DIALOG_SIGNUP_H
#define DIALOG_SIGNUP_H

#include <QDialog>

namespace Ui {
class Dialog_signup;
}

class Dialog_signup : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_signup(QWidget *parent = nullptr);
    ~Dialog_signup();

private slots:
    void on_checkBox_echomode_clicked(bool checked);

    void on_pushButton_signup_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_signup *ui;
};

#endif // DIALOG_SIGNUP_H

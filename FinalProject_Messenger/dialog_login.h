#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QWidget>

namespace Ui {
class dialog_login;
}

class dialog_login : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_login(QWidget *parent = nullptr);
    ~dialog_login();

private slots:
    void on_OKBuuton_clicked();

private:
    Ui::dialog_login *ui;
};

#endif // DIALOG_LOGIN_H

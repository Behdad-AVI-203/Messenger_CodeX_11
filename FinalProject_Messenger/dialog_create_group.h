#ifndef DIALOG_CREATE_GROUP_H
#define DIALOG_CREATE_GROUP_H
#include "group.h"
#include <QWidget>
#include <QString>
namespace Ui {
class dialog_create_group;
}

class dialog_create_group : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_create_group(QWidget *parent = nullptr);
    ~dialog_create_group();
    void SetCreateGroupToken(QString token);
    QString GetCreateGroupToken();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialog_create_group *ui;
    QString Token;
};

#endif // DIALOG_CREATE_GROUP_H

#ifndef DIALOG_JOIN_GROUP_H
#define DIALOG_JOIN_GROUP_H

#include <QWidget>
#include "group.h"

namespace Ui {
class dialog_Join_Group;
}

class dialog_Join_Group : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_Join_Group(QWidget *parent = nullptr);
    ~dialog_Join_Group();
    void SetJoinGroupToken(QString token);
    QString GetJoinGroupToken();

private slots:


    void on_JoinBuuton_clicked();

private:
    Ui::dialog_Join_Group *ui;
    QString Token;

};

#endif // DIALOG_JOIN_GROUP_H

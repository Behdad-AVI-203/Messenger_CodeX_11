#ifndef DIALOG_JOIN_GROUP_H
#define DIALOG_JOIN_GROUP_H

#include <QDialog>
#include"all_include.h"

namespace Ui {
class Dialog_Join_Group;
}

class Dialog_Join_Group : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Join_Group(QWidget *parent = nullptr);
    ~Dialog_Join_Group();
private slots:
    void on_pushButton_join_clicked();
    void on_pushButton_cancel_clicked();
private:
    Ui::Dialog_Join_Group *ui;
};

#endif // DIALOG_JOIN_GROUP_H

#ifndef DIALOG_CREATE_GROUP_H
#define DIALOG_CREATE_GROUP_H

#include"all_include.h"

namespace Ui {
class Dialog_Create_Group;
}

class Dialog_Create_Group : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Create_Group(QWidget *parent = nullptr);
    ~Dialog_Create_Group();
private slots:
    void on_pushButton_create_clicked();
    void on_pushButton_cancel_clicked();
private:
    Ui::Dialog_Create_Group *ui;
};

#endif // DIALOG_CREATE_GROUP_H

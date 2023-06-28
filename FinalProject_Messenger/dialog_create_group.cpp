#include "dialog_create_group.h"
#include "ui_dialog_create_group.h"

dialog_create_group::dialog_create_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_create_group)
{
    ui->setupUi(this);
}

dialog_create_group::~dialog_create_group()
{
    delete ui;
}

void dialog_create_group::SetCreateGroupToken(QString token)
{
    Token = token;
}

QString dialog_create_group::GetCreateGroupToken()
{
    return Token;
}

void dialog_create_group::on_pushButton_clicked()
{
        Group* newGroup = new Group();
        newGroup->CreatedGroup(ui->TitleLineEdit->text(),ui->NameLineEdit->text(),Token);

}


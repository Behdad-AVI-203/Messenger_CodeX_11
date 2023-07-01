#ifndef DIALOG_CREATE_CHANNEL_H
#define DIALOG_CREATE_CHANNEL_H

#include <QDialog>
#include "channel.h"

namespace Ui {
class Dialog_Create_Channel;
}

class Dialog_Create_Channel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Create_Channel(QWidget *parent = nullptr);
    ~Dialog_Create_Channel();
    void SetTokenFromChannel(QString channel);
    void SetCreateChannelToken(QString token);

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_Create_Channel *ui;
    QString Token;

};

#endif // DIALOG_CREATE_CHANNEL_H

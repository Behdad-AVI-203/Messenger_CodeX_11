#ifndef DIALOG_CREATE_CHANNEL_H
#define DIALOG_CREATE_CHANNEL_H

#include <QWidget>
#include "channel.h"


namespace Ui {
class dialog_create_Channel;
}

class dialog_create_Channel : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_create_Channel(QWidget *parent = nullptr);
    ~dialog_create_Channel();
    void SetTokenFromChannel(QString channel);
    void SetCreateChannelToken(QString token);


private slots:
    void on_CreatedButton_clicked();

private:
    Ui::dialog_create_Channel *ui;
    QString Token;
};

#endif // DIALOG_CREATE_CHANNEL_H

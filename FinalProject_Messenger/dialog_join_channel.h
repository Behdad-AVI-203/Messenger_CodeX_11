#ifndef DIALOG_JOIN_CHANNEL_H
#define DIALOG_JOIN_CHANNEL_H

#include <QDialog>
#include <QString>

namespace Ui {
class Dialog_Join_Channel;
}

class Dialog_Join_Channel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Join_Channel(QWidget *parent = nullptr);
    ~Dialog_Join_Channel();
    void SetJoinChannelToken(QString token);
    QString GetJoinChannelToken();

private slots:
    void on_pushButton_join_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_Join_Channel *ui;
    QString Token;
};

#endif // DIALOG_JOIN_CHANNEL_H

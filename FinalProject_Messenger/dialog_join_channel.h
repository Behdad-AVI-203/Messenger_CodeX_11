#ifndef DIALOG_JOIN_CHANNEL_H
#define DIALOG_JOIN_CHANNEL_H

#include <QWidget>
#include <QString>

namespace Ui {
class dialog_join_Channel;
}

class dialog_join_Channel : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_join_Channel(QWidget *parent = nullptr);
    ~dialog_join_Channel();

private slots:
    void on_JoinButton_clicked();

private:
    Ui::dialog_join_Channel *ui;
};

#endif // DIALOG_JOIN_CHANNEL_H

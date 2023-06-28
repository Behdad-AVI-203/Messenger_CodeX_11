#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <iostream>>
#include <fstream>
using namespace std;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    void SetChatWindowToken(string token);
    string GetChatWindowToken();

private slots:
    void on_SendMessageToUserButton_clicked();

private:
    string token;
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H

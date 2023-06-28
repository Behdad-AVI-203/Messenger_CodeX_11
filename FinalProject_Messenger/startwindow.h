#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    //void refresh();
private slots:
    void on_actionLogout_triggered();

    void on_actionRefresh_triggered();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H

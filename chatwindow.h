#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <conn.h>
#include <QSystemTrayIcon>
#include "joindialog.h"
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();

public slots :
    void Send();
    void Join();
    void Out();
    void printGotData();
private:
    Conn *c;
    std::string Cookie,Nickname;
    Ui::ChatWindow *ui;
    QSystemTrayIcon *tray;
    JoinDialog *d;
    bool joined;
    void SendRaw(std::string);
};

#endif // CHATWINDOW_H

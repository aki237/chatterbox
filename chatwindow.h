#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <conn.h>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QMediaPlayer>
#include "message.h"
#include "joindialog.h"
namespace Ui {
class ChatWindow;
}

typedef struct {
    std::string Channel;
    std::string From;
    std::string Message;
    std::string Type;
} messageStruct;

typedef std::vector<messageStruct> Chats;

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
    void ChangeChat();
    void printGotData();
private:
    Conn *c;
    bool firstUL;
    std::map <std::string,Chats> chats;
    QMediaPlayer* alert;
    std::string Cookie,Nickname;
    Ui::ChatWindow *ui;
    QSystemTrayIcon *tray;
    JoinDialog *d;
    bool joined;
    void SendRaw(std::string);

};

#endif // CHATWINDOW_H

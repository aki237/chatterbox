#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "message.h"
#include <iostream>

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow) {

    joined  = false;
    tray = new QSystemTrayIcon();
    d = new JoinDialog(this);
    d->show ();
    ui->setupUi(this);
    c = new Conn(this);
    SendRaw ("LIST USERS");
}

void ChatWindow::printGotData() {
    Message m(c->Read());
    m.Print();
    if (m.GetType ()== "cookie"){
        if (!joined) {
            Cookie = m.GetContent ();
            std::cout << Cookie << std::endl;
            joined = true;
        } else {
            std::cout << "chatwindow.cpp : 24 - Already Joined with the nickname=\"" << Nickname << "\"" << std::endl;
        }
        c->Send ("LIST USERS");
    }
    if (m.GetType () == "userlist") {
        while(ui->chatters->count ()>0) {
          ui->chatters->takeItem(0);
        }
        auto members = m.GetMembers ()->GetMemberList ();
        for(int i = 0; i < int(members.size ()) ; i++ ) {
            QString temp = QString::fromStdString ((members.at (i)));
            ui->chatters->addItem (temp);
        }
    }

    if (m.GetType ()== "error") {
        if (m.GetContent () == "Username already Taken") {
            d->dui->error->setText(QString::fromStdString ("<center><b>" + m.GetContent () + "</b></center>"));
            d->show ();
            c->Send ("LIST USERS");
        }
        // tray->showMessage ("chttrBx - Error",m.GetContent (),QSystemTrayIcon::Critical,10000);
    }
    if (m.GetType () == "message") {
        QString qm = QString::fromStdString ((m.GetFrom () + " says " + m.GetContent ()));
        QLabel *templ = new QLabel(qm);
        QListWidgetItem *tempwi = new QListWidgetItem();
        ui->chatView->addItem (tempwi);
        ui->chatView->setItemWidget (tempwi, templ);
    }
}

void ChatWindow::Send () {
    // Check which view we are in and send broadcast or Private based on that....
    SendRaw("BROADCAST WITH " + Cookie + " " + ui->textBox->text().toStdString ());
    ui->textBox->setText ("");
}

void ChatWindow::SendRaw (std::string msg) {
    c->Send (msg);
    std::cout << msg << std::endl;
}

void ChatWindow::Join() {
    std::string nickname = d->dui->nickname->text().toStdString ();
    std::string password = d->dui->password->text().toStdString ();
    std::cout << "Accepted Join :\nNickname : "<< nickname << std::endl;
    std::cout << "Password : " << password << std::endl;
    c->Send ("JOIN " + nickname + " " + password);
}

void ChatWindow::Out() {
    this->destroy (true,true);
    std::cout << "Reject clicked" << std::endl;
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

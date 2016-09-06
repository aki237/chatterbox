#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "message.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QFontDatabase>
#include <iostream>

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow) {

    joined  = false;
    QFontDatabase::addApplicationFont("qrc:///res/font.ttf");
    firstUL = true;
    tray = new QSystemTrayIcon();
    d = new JoinDialog(this);
    d->show ();
    ui->setupUi(this);
    c = new Conn(this);
    alert = new QMediaPlayer;
    alert->setMedia (QUrl("qrc:///res/alert.mp3"));
    alert->setVolume (100);
    SendRaw ("LIST USERS");
}

void ChatWindow::printGotData() {
    Message m(c->Read());
    alert->stop ();
    if (m.GetType ()== "cookie"){
        if (!joined) {
            Cookie = m.GetContent ();
            joined = true;
        } else {
            return;
        }
        c->Send ("LIST USERS");
    }
    if (m.GetType () == "userlist") {
        auto members = m.GetMembers ()->GetMemberList ();
        std::string previous = "*ChatPi*";
        if (ui->chatters->selectedItems ().size () > 0) {
            previous = ui->chatters->selectedItems ().at (0)->text().toStdString ();
        }

        ui->chatters->clear ();

        for(int i = 0; i < int(members.size ()) ; i++ ) {
            QString temp = QString::fromStdString ((members.at (i)));
            ui->chatters->addItem (temp);
            if (members.at (i) == previous) {
                ui->chatters->item (i)->setSelected (true);
            }
        }
        if (ui->chatters->selectedItems ().size () < 1) {
            ui->chatters->item (0)->setSelected (true);
        }
        ChangeChat ();
    }

    if (m.GetType ()== "error") {
        if (m.GetContent () == "Username already Taken") {
            d->dui->error->setText(QString::fromStdString ("<center><b>" + m.GetContent () + "</b></center>"));
            d->show ();
            c->Send ("LIST USERS");
            return;
        }
        QString qm = QString::fromStdString ("<center><b><font color=\"#FF0000\">"
                                             + m.GetFrom () + " throws " + m.GetContent ()+
                                             "</font></b></center>");
        QLabel *templ = new QLabel(qm);
        QListWidgetItem *tempwi = new QListWidgetItem();
        ui->chatView->addItem (tempwi);
        ui->chatView->scrollToBottom ();
        ui->chatView->setItemWidget (tempwi, templ);
        if (m.GetFrom () != Nickname) {
            alert->play ();
        }
    }
    if (m.GetType () == "message") {
        messageStruct mS;
        mS.Channel = m.GetChannel ();
        mS.From = m.GetFrom ();
        mS.Message = m.GetContent ();
        mS.Type = m.GetType ();
        if (m.GetChannel() == "broadcast") {
            chats["*ChatPi*"].push_back(mS);
        } else {
            chats[m.GetFrom()].push_back(mS);
        }
        if (ui->chatters->selectedItems ().size () < 1) {
            return;
        }
        std::string active_chat = ui->chatters->selectedItems ().at (0)->text ().toStdString ();
        if ((active_chat == m.GetFrom () && m.GetChannel () != "broadcast")||
                ("broadcast" == m.GetChannel () && active_chat == "*ChatPi*")) {
            QString qm = QString::fromStdString (("<b>" + m.GetFrom () + "</b>"+ " says " + m.GetContent ()));
            QLabel *templ = new QLabel(qm);
            QListWidgetItem *tempwi = new QListWidgetItem();
            ui->chatView->addItem (tempwi);
            ui->chatView->scrollToBottom ();
            ui->chatView->setItemWidget (tempwi, templ);
        } else {
            int l = ui->chatters->count ();
            QColor bgclor(255,0,0,255);
            for(int i = 0; i < l; i++) {
                if (m.GetChannel ()==  "broadcast" && ui->chatters->item (i)->text () == "*ChatPi*") {
                    ui->chatters->item (i)->setBackgroundColor (bgclor);
                }
                if (m.GetChannel ()==  "private" && ui->chatters->item (i)->text ().toStdString ()== m.GetFrom ()) {
                    ui->chatters->item (i)->setBackgroundColor (bgclor);
                }
            }
        }

        if (m.GetFrom () != Nickname) {
            alert->play ();
        }
    }
}

void ChatWindow::Send () {
    if (ui->textBox->text().trimmed ().toStdString () == "") {
        return;
    }
    std::string current_chat = "*ChatPi*",sendmessage = "";
    if (ui->chatters->selectedItems ().size () > 0) {
        current_chat = ui->chatters->selectedItems ().at (0)->text ().toStdString ();
    }

    if (current_chat == "*ChatPi*") {
        sendmessage = "BROADCAST WITH " + Cookie + " " + ui->textBox->text().toStdString ();
    } else {
        sendmessage = "MSG WITH " + Cookie + " TO " + current_chat + " " + ui->textBox->text().toStdString ();
        messageStruct mS;
        mS.Channel = "private";
        mS.From = Nickname;
        mS.Message = ui->textBox->text().toStdString ();
        mS.Type = "message";
        chats[current_chat].push_back(mS);
        QString qm = QString::fromStdString (("<b>" + mS.From + "</b>"+ " says " + mS.Message));
        QLabel *templ = new QLabel(qm);
        QListWidgetItem *tempwi = new QListWidgetItem();
        ui->chatView->addItem (tempwi);
        ui->chatView->scrollToBottom ();
        ui->chatView->setItemWidget (tempwi, templ);
    }

    if (-1 == c->Send(sendmessage)){
        QString qm = QString::fromStdString (("<center><b><font color=\"#FF0000\">Lost Connection : Quit the app and restart</font></b></center>"));
        QLabel *templ = new QLabel(qm);
        QListWidgetItem *tempwi = new QListWidgetItem();
        ui->chatView->addItem (tempwi);
        ui->chatView->scrollToBottom ();
        ui->chatView->setItemWidget (tempwi, templ);
        return;
    }
    ui->textBox->setText ("");
}

void ChatWindow::ChangeChat() {
    std::string current_chat = "*ChatPi*";
    if (ui->chatters->selectedItems ().size () > 0) {
        current_chat = ui->chatters->selectedItems ().at (0)->text ().toStdString ();
        QColor bgclor(0,0,0,0);
        ui->chatters->selectedItems ().at (0)->setBackgroundColor (bgclor);
    } else {
        std::cout << "Chat is 0" << std::endl;
        return;
    }
    ui->chatView->clear ();
    messageStruct m;
    for(int i = 0 ; i < int(chats[current_chat].size()) ; i++) {
        m = chats[current_chat].at(i);
        QString qm = QString::fromStdString (("<b>" + m.From + "</b>"+ " says " + m.Message));
        QLabel *templ = new QLabel(qm);
        QListWidgetItem *tempwi = new QListWidgetItem();
        ui->chatView->addItem (tempwi);
        ui->chatView->scrollToBottom ();
        ui->chatView->setItemWidget (tempwi, templ);
    }
}

void ChatWindow::SendRaw (std::string msg) {
    c->Send (msg);
}

void ChatWindow::Join() {
    std::string nickname = d->dui->nickname->text().toStdString ();
    std::string password = d->dui->password->text().toStdString ();
    Nickname = nickname;
    if (c->Send ("JOIN " + nickname + " " + password) == -1){
        d->dui->error->setText(QString::fromStdString ("<center><b>Chat Server isn't running</b></center>"));
        d->show ();
    }
}

void ChatWindow::Out() {
    this->destroy (true,true);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

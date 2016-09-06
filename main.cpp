#include "chatwindow.h"
#include <QApplication>
#include <QIcon>
#include <iostream>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/res/icon.png"));
    ChatWindow w;
    w.show();
    qDebug() << "Showed window!!" ;
    return a.exec();
}

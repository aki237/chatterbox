#include "chatwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon (QIcon("/home/aki237/Pictures/al.png"));
    ChatWindow w;
    w.show();
    qDebug() << "Showed window!!" ;
    return a.exec();
}

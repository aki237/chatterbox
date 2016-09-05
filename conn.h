#ifndef CONN_H
#define CONN_H
#include <QObject>
#include <QTcpSocket>

class Conn : public QObject {
    Q_OBJECT
public:
    explicit Conn(QObject *parent=0);
    std::string Read();
    int Send(std::string);

private:
    QTcpSocket *socket;
    std::string Recieve();
};

#endif // CONN_H

#include "conn.h"
#include "message.h"
#include <iostream>

Conn::Conn(QObject *parent) : QObject(parent){
  socket = new QTcpSocket(this);
  socket->connectToHost("10.9.10.9", 6672);

  if(socket->waitForConnected(3000)){
    qDebug() << "Connected to chatPi Server!!";
  } else {
    qDebug() << "conn.cpp - Error : Check whether the server is up and running";
  }

  connect(socket, SIGNAL(readyRead()), parent, SLOT(printGotData()));
  //connect(parent, SLOT(printGotData), this )
}

int Conn::Send(std::string message) {
  return socket->write((message+"\n").c_str ());
}

std::string Conn::Read(){
  return socket->readAll ().toStdString ();
}

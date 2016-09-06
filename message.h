#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <QXmlStreamReader>
#include "members.h"

class Message
{
public:
    Message(std::string msg);
    ~Message();
    std::string GetFrom();
    std::string GetType();
    std::string GetContent();
    std::string GetChannel();
    Members* GetMembers();
    void Print();
private:
    std::string Channel;
    std::string From;
    std::string Type;
    std::string Content;
    Members* members;
    QXmlStreamReader xml;
    void processMESSAGE();
};

#endif // MESSAGE_H

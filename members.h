#ifndef MEMBERS_H
#define MEMBERS_H
#include <iostream>
#include <vector>
#include <QXmlStreamReader>


class Members
{
public:
    Members(std::string msg);
    ~Members();
    void Print();
    std::vector<std::string> GetMemberList();
private:
    std::vector<std::string> memberlist;
    QXmlStreamReader xml;
    void processMEMBERS();
};

#endif // MEMBERS_H

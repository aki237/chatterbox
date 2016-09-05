#include "members.h"

Members::Members(std::string msg) {
    xml.addData(msg.c_str ());
    if (xml.readNextStartElement () && xml.name() == "MEMBERS") {
        processMEMBERS();
    }
}

void Members::processMEMBERS() {
    if (!xml.isStartElement () || xml.name() != "MEMBERS")
        return ;
    while (xml.readNextStartElement ()){
        if (xml.name() == "MEMBER") {
            auto temp = xml.readElementText ().toStdString ();
            memberlist.push_back (temp);
        }
    }
    if (xml.tokenType() == QXmlStreamReader::Invalid)
           xml.readNext();
}

void Members::Print() {
    int i = 0;
    for (;i < int(memberlist.size()) ; i++) {
        std::cout << "Member : " << memberlist.at (i)<< std::endl;
    }
}

std::vector<std::string> Members::GetMemberList() {
    return memberlist;
}

Members::~Members() {

}

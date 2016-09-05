#include "joindialog.h"

JoinDialog::JoinDialog(QObject *p_parent) : dui(new Ui::Dialog)
{
    parent = p_parent;
    this->setWindowTitle ("Join chatPi network");
    this->setModal (true);
    dui->setupUi (this);
    dui->nickname->setValidator (new QRegExpValidator(QRegExp("[0-9,A-Z,a-z]{1,20}")));
    dui->password->setValidator (new QRegExpValidator(QRegExp("[0-9,A-Z,a-z]{1,20}")));
    connect(this, SIGNAL(accepted()), parent, SLOT(Join()));
    connect(this, SIGNAL(rejected()), parent, SLOT(Out()));
}

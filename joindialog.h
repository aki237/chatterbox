#ifndef JOINDIALOG_H
#define JOINDIALOG_H
#include <QDialog>
#include "ui_dialog.h"


namespace Ui {
class Dialog;
}

class JoinDialog : public QDialog
{
public:
    Ui::Dialog *dui;
    JoinDialog(QObject *p_parent=0);
private :
    QObject *parent;
};

#endif // JOINDIALOG_H

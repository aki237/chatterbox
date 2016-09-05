#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T19:05:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatterbox
TEMPLATE = app


SOURCES += main.cpp\
        chatwindow.cpp \
    conn.cpp \
    message.cpp \
    joindialog.cpp \
    members.cpp

HEADERS  += chatwindow.h \
    conn.h \
    message.h \
    joindialog.h \
    members.h

FORMS    += chatwindow.ui \
    dialog.ui

DISTFILES += \
    .gitignore

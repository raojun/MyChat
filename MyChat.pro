#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T19:21:59
#
#-------------------------------------------------

QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChat
TEMPLATE = app


SOURCES += main.cpp\
        chat.cpp \
    login.cpp \
    index.cpp

HEADERS  += chat.h \
    connection.h \
    login.h \
    index.h

FORMS    += chat.ui \
    login.ui \
    index.ui

RESOURCES += \
    AllSource.qrc

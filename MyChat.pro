#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T19:21:59
#
#-------------------------------------------------

QT       += core gui
QT       += core sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChat
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    index.cpp \
    chat.cpp

HEADERS  += \
    connection.h \
    login.h \
    index.h \
    chat.h

FORMS    += \
    login.ui \
    index.ui \
    chat.ui

RESOURCES += \
    AllSource.qrc

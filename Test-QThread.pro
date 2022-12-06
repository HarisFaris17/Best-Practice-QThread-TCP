#-------------------------------------------------
#
# Project created by QtCreator 2022-12-05T16:54:55
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test-QThread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserver.cpp

HEADERS  += mainwindow.h \
    tcpserver.h

FORMS    += mainwindow.ui

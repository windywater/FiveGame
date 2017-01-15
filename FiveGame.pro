#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T11:01:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FiveGame
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Panel.cpp \
    Controller.cpp \
    Network.cpp \
    QiziWidget.cpp

HEADERS  += MainWindow.h \
    Panel.h \
    Controller.h \
    Common.h \
    Network.h \
    QiziWidget.h

FORMS    += MainWindow.ui

RESOURCES += \
    FiveGame.qrc

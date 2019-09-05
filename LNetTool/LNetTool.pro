#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T21:55:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LNetTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

    CONFIG(debug, debug|release) {
    LIBS += -LF:\work\qt\qt5\LQtTool\bin -lLQtToold
    } else {
    LIBS += -LF:\work\qt\qt5\LQtTool\bin -lLQtTool
    }

    INCLUDEPATH += F:\work\qt\qt5\LQtTool\include

    DEPENDPATH += F:\work\qt\qt5\LQtTool\include

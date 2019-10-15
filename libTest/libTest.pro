#-------------------------------------------------
#
# Project created by QtCreator 2019-09-28T22:17:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CustomMainWidget.cpp

HEADERS  += mainwindow.h \
    CustomMainWidget.h

FORMS    += mainwindow.ui \
    CustomMainWidget.ui

LIBS += -L$$PWD/../LStdTool/bin/ -lLStdToold

INCLUDEPATH += $$PWD/../LStdTool/include
DEPENDPATH += $$PWD/../LStdTool/include

LIBS += -L$$PWD/../LQtTool/bin/ -lLQtToold

INCLUDEPATH += $$PWD/../LQtTool/include
DEPENDPATH += $$PWD/../LQtTool/include

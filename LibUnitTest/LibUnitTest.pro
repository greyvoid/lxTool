#-------------------------------------------------
#
# Project created by QtCreator 2019-10-08T09:41:20
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_libunittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_libunittesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

LIBS += -L$$PWD/../LStdTool/bin/ -lLStdToold

INCLUDEPATH += $$PWD/../LStdTool/include
DEPENDPATH += $$PWD/../LStdTool/include

LIBS += -L$$PWD/../LQtTool/bin/ -lLQtToold

INCLUDEPATH += $$PWD/../LQtTool/include
DEPENDPATH += $$PWD/../LQtTool/include

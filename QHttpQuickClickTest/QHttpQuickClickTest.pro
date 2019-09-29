#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T20:19:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QHttpQuickClickTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    HttpClient.cpp

HEADERS  += mainwindow.h \
    HttpClient.h \
    xgutility.h

FORMS    += mainwindow.ui

LIBS += -L$$PWD/../../../../../thirdparty/openssl/lib/ -llibeay32 -lssleay32

INCLUDEPATH += $$PWD/../../../../../thirdparty/openssl/inc32
DEPENDPATH += $$PWD/../../../../../thirdparty/openssl/inc32

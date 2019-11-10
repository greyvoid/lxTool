#-------------------------------------------------
#
# Project created by QtCreator 2019-11-04T15:23:29
#
#-------------------------------------------------

QT       += core gui multimedia axcontainer xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VersionTool
TEMPLATE = app

DESTDIR = $$PWD/bin

VERSION = 0.1.0
QMAKE_TARGET_PRODUCT = VersionTool
QMAKE_TARGET_COMPANY = Lx
QMAKE_TARGET_DESCRIPTION = --VersionTool
QMAKE_TARGET_COPYRIGHT = Lx

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH += $$PWD/../LQtTool/include
DEPENDPATH += $$PWD/../LQtTool/include

#可行 注意stdTool已经链接到qtTool里面了
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LQtTool/bin/ -lLQtToold

#mingw
win32: LIBS += -L'C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x86' -lVersion
INCLUDEPATH += C:/Program Files (x86)/Windows Kits/8.1/Include/um
DEPENDPATH += C:/Program Files (x86)/Windows Kits/8.1/Include/um
INCLUDEPATH += C:/Program Files (x86)/Windows Kits/8.1/Include/shared
DEPENDPATH += C:/Program Files (x86)/Windows Kits/8.1/Include/shared
INCLUDEPATH += C:/Program Files (x86)/Windows Kits/8.1/Include/winrt
DEPENDPATH += C:/Program Files (x86)/Windows Kits/8.1/Include/winrt

#msvc


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

#LIBS += -L$$PWD/../LStdTool/bin/ -lLStdToold

INCLUDEPATH += $$PWD/../LStdTool/include
DEPENDPATH += $$PWD/../LStdTool/include

#不行啊
#Debug:LIBS += -L$$PWD/../LQtTool/bin/ -lLQtToold
#Release:LIBS += -L$$PWD/../LQtTool/bin/ -lLQtTool

#Debug:LIBS += -L$$PWD/../LStdTool/bin/ -lLStdToold
#Release:LIBS += -L$$PWD/../LStdTool/bin/ -lLStdTool

INCLUDEPATH += $$PWD/../LQtTool/include
DEPENDPATH += $$PWD/../LQtTool/include

#可行 注意stdTool已经链接到qtTool里面了
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LQtTool/bin/ -lLQtToold


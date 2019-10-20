CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(LQtPlugin)
TEMPLATE    = lib


RESOURCES   = icons.qrc
LIBS        += -L. 

QT       += multimedia
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

DESTDIR = $$PWD/../bin

# 引入widgets源码
include($$PWD/../LQtTool/src/widgets/widgets.pri)
INCLUDEPATH += $$PWD/../LQtTool/src/widgets

#######如果需要引入下面文件，说明设计出了问题#########
#include($$PWD/../LStdTool/LStdTool.pri)

#widgets源码对应的包含
#INCLUDEPATH += $$PWD/../LQtTool/src
#INCLUDEPATH += $$PWD/../LStdTool/src

#DEPENDPATH += $$PWD/../LQtTool/src
#DEPENDPATH += $$PWD/../LStdTool/src

HEADERS += \
    LProgressIndicatorPlugin.h

SOURCES += \
    LProgressIndicatorPlugin.cpp

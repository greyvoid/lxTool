
TARGET = LStdTool
TEMPLATE = lib

DESTDIR = $$PWD/bin

#为什么qmake.conf里的内容会优先加载?
DEFINES += L_STD_TOOL
contains(DEFINES,L_STD_TOOL){
    message("11")
}else{
    message("22")

}

CONFIG(debug, debug|release){

    # DEBUG base name add 'd' suffix
    TARGET = $$join(TARGET,,,d)
}

win32{
    system(.\copy_head.bat)
}

include(LStdTool.pri)

HEADERS += \
    src/LStdTool.h \
    src/def/common.h \
    src/def/func.h \
    src/def/type.h \
    src/global/gfunc.h \
    src/global/Util2.h \
    src/patterns/CSingleton.h \
    src/template/Utility.h

SOURCES += \
    src/global/gfunc.cpp \
    src/patterns/CSingleton.cpp \
    src/template/Utility.cpp

#此文件用于同一构建树中项目的依赖，如果不是同一构建树则不需要，本例QtTool依赖StdTool
DISTFILES += \
    .qmake.conf

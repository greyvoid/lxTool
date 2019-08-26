
TARGET = LStdTool
TEMPLATE = lib

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
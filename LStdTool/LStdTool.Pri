include(../common.pri)
# std模块
HEADERS += \
    $$PWD/src/crypto/Base64.h \
    $$PWD/src/crypto/LAes.h \
    $$PWD/src/crypto/LAesEx.h \
    $$PWD/src/crypto/LEncrypt.h \
    $$PWD/src/crypto/LMd5.h \
    $$PWD/src/datastructure/LBuffer.h \
    $$PWD/src/def/common.h \
    $$PWD/src/def/func.h \
    $$PWD/src/def/platform.h \
    $$PWD/src/def/type.h \
    $$PWD/src/global/bin.h \
    $$PWD/src/patterns/Singleton.h \
    $$PWD/src/template/Utility.h \
    $$PWD/src/LStdTool.h \
    $$PWD/src/LStd.h

SOURCES += \
    $$PWD/src/crypto/Base64.cpp \
    $$PWD/src/crypto/LAes.cpp \
    $$PWD/src/crypto/LAesEx.cpp \
    $$PWD/src/crypto/LEncrypt.cpp \
    $$PWD/src/crypto/LMd5.cpp \
    $$PWD/src/datastructure/LBuffer.cc \
    $$PWD/src/global/bin.c \
    $$PWD/src/patterns/Singleton.cpp \
    $$PWD/src/template/Utility.cpp \
    $$PWD/src/LStd.cpp

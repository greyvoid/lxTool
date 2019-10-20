
include($$PWD/widgets/widgets.pri)

SOURCES +=\
    $$PWD/message/LMessageListenner.cpp \
    $$PWD/message/LNotificationCenter.cpp \
    $$PWD/message/LNotifier.cpp \
    $$PWD/delegate/LDelegateSpinbox.cpp \
    $$PWD/network/LHttpClient.cpp \
    $$PWD/network/LHttpDownload.cpp \
    $$PWD/network/LTcpConnection.cpp \
    $$PWD/network/LTcpServer.cpp \
    $$PWD/network/LTcpThread.cpp \
    $$PWD/network/LTcpClient.cpp \
    $$PWD/LQtFunc.cpp \
    $$PWD/styles/LIconStyle.cpp \
    $$PWD/util/L9GridImageUtil.cpp \
    $$PWD/styles/bronzestyle.cpp \
    $$PWD/util/LFileOperateUtil.cpp \
    $$PWD/core/LVersion.cpp \
    $$PWD/util/LXmlOperateUtil.cpp \
    $$PWD/util/LRegExpUtil.cpp \
    $$PWD/util/LCharacterEncodingUtil.cpp

HEADERS  += \
    $$PWD/message/LMessageListenner.h \
    $$PWD/message/LNotificationCenter.h \
    $$PWD/message/LNotifier.h \
    $$PWD/delegate/LDelegateSpinbox.h \
    $$PWD/network/LHttpClient.h \
    $$PWD/network/LHttpDownload.h \
    $$PWD/network/LTcpConnection.h \
    $$PWD/network/LTcpServer.h \
    $$PWD/network/LTcpThread.h \
    $$PWD/network/LTcpClient.h \
    $$PWD/network/LNetDef.h \
    $$PWD/LQtFunc.h \
    $$PWD/LQtDefine.h \
    $$PWD/styles/LIconStyle.h \
    $$PWD/util/L9GridImageUtil.h \
    $$PWD/styles/bronzestyle.h \
    $$PWD/util/LFileOperateUtil.h \
    $$PWD/core/LVersion.h \
    $$PWD/util/LXmlOperateUtil.h \
    $$PWD/util/LRegExpUtil.h \
    $$PWD/util/LCharacterEncodingUtil.h


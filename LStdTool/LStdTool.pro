
TARGET = LStdTool
TEMPLATE = lib

DESTDIR = $$PWD/bin

contains(DEFINES,L_STD_TOOL){
    message("true")
}else{
    message("false")

}

CONFIG(debug, debug|release){

    # DEBUG base name add 'd' suffix
    TARGET = $$join(TARGET,,,d)
}

system(.\copy_head.bat)

win32{
#1-在项目构建前执行命令
#    system(.\copy_head.bat)
#优化后的表达式如下，这样此命令只会在构建前执
#!build_pass:system(.\copy_head.bat)

#2-在链接前后执行，(只有在源码修改导致重新链接成目标文件时才会执
#在链接执行前执行命令cmd
#QMAKE_PRE_LINK += .\copy_head.bat
#在链接执行后执行命令cmd
#QMAKE_POST_LINK += .\copy_head.bat

#3-在构建前后插入命 使用的QMake变量是QMAKE_EXTRA_TARGETS和PRE_TARGETDEPENS变量
#eg:
# 构造自定义生成目标对象
#mybuild.target=pre_build_cmds
#win32{
#mybuild.commands=$$PWD/UpdatePluginLib.cmd
#}else{
#}
# 加入到自定义目标对象列表#QMAKE_EXTRA_TARGETS += mybuild

# 加入到构建依赖列表最前面，会最先被执行，这里必须写目标对象名称，不能是mybuild
#PRE_TARGETDEPS += pre_build_cmds
}

include(LStdTool.pri)

HEADERS += \
    src/LStdTool.h \
    src/def/common.h \
    src/def/func.h \
    src/def/type.h \
    src/global/gfunc.h \
    src/global/Util2.h \
    src/template/Utility.h \
    src/patterns/Singleton.h \
    src/global/bin.h

SOURCES += \
    src/global/gfunc.cpp \
    src/patterns/CSingleton.cpp \
    src/template/Utility.cpp \
    src/global/bin.c

#此文件用于同一构建树中项目的依赖，如果不是同一构建树则不需要，本例QtTool依赖StdTool
#验证结果证明，去掉qmake.conf太垃圾， 因为里面的内容最先执行，打乱次序
#如果要用只能在里定义
#DISTFILES += \
#    .qmake.conf
#即使注释掉也会隐式执 qmake.conf

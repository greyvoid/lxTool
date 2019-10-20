#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T20:34:18
#
#-------------------------------------------------

QT       += core gui multimedia axcontainer xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# target name, not include suffix name
TARGET = LQtTool

TEMPLATE = lib
#app - create a app makefile --defult
#lib - create a lib makefile
#vcapp - create a app of Visual Studio project
#vclib - create a lib of Visual Studio project

CONFIG += c++11

#预处理程序定义
DEFINES += L_QT_TOOL

# 指明编译的目标文件的输出路径
#工程的所在目录
DESTDIR = $$PWD/bin
#DESTDIR = ../bin #编译的所在目录

CONFIG(debug, debug|release){

    # DEBUG base name add 'd' suffix
    TARGET = $$join(TARGET,,,d)
}


# 要执行copy_head.bat需要清除项目重新构建
# 定义输出路径
#{不可换行
win32{
system(.\copy_head.bat)
    #CONFIG += debug_and_release #一万个草泥马
CONFIG(debug, debug|release) {
            #target_path = ./build_/dist
            #TARGET = LQtTool
        } else {
            #target_path = ./build_/debug
            #TARGET = LQtToold
        }
        #MOC_DIR = $$target_path/moc
        #RCC_DIR = $$target_path/rcc
        #OBJECTS_DIR = $$target_path/obj
        #DEFINES  += WIN32   #vc6,nmake不会主动包含WIN32 需要手动定add
        #system(xcopy *.h ..\include /s)

    #src_dir = $$HEADERS
    #dst_dir = $$PWD\\..\\include\\
    #dst_dir = $$DESTDIR

    #和上面的语句之间需要留一个空行，否则会出error
    #src_dir ~= s,/,\\,g
    #dst_dir ~= s,/,\\,g
    #system(xcopy $$src_dir $$dst_dir /y /s)
}


#contains(QMAKE_COMPILER, gcc) { #由于使用mingw应该用sh
#    message("qmake compiler is gcc")
#}

#contains(QMAKE_COMPILER, msvc) {
#    message("qmake compiler is msvc")
#    }

#contains(DEFINES,USE_QT4){
#    message("use qt4")
#}else{
#    message("use qt5")
#}

# 头文件搜索路径INCLUDEPATH:

#qmake将会退exit
#count( DEFINES, 5 ) {        CONFIG += debug    }error( "qmake exit" )

#
#exists( /local/qt/qmake/main.cpp ) {        SOURCES += main.cpp    }message( "local/qt/qmake/main.cpp exists_" )
#!exists( main.cpp ) { error( "no main.cpp file found" ) }

#
#isEmpty( CONFIG ) {        CONFIG += qt warn_on debug    }message( "CONFIG_ is empty" )

#
#system( ls /bin ) {        SOURCES += bin/main.cpp        HEADERS += bin/main.h    }

#
#infile( filename, var, val )

#本库头文件包含路径
INCLUDEPATH += $$PWD\src
#依赖库的头文件包含路径
#INCLUDEPATH += $$PWD\..\LStdTool\include
INCLUDEPATH += $$PWD\..\LStdTool\src

#程序编译时依赖的相关路径
DEPENDPATH += $$PWD\src
#程序编译时依赖的相关路径
#DEPENDPATH += $$PWD\..\LStdTool\include
DEPENDPATH += $$PWD\..\LStdTool\src

#modules
include($$PWD/../LStdTool/LStdTool.pri)
include(LQtTool.pri)

#contains(DEFINES,L_STD_TOOL){
#    message("包含了stdTool")
#}else {
#    CONFIG(debug, debug|release){
#    LIBS += -L$$PWD\..\LStdTool\bin -lLStdToold
#    } else {
#    LIBS += -L$$PWD\..\LStdTool\bin -lLStdTool
#    }

#    INCLUDEPATH += $$PWD\..\LStdTool\include

#    DEPENDPATH += $$PWD\..\LStdTool\include
#}

#此文件用于同一构建树中项目的依赖，如果不是同一构建树则不需要，本例QtTool依赖StdTool
#假如你所有的应用程序都必须和一个特定的库连接，你可以把这个信息添加到相应的qmake.conf文件中。
#验证结果证明，去掉qmake.conf， 太垃圾， 因为里面的内容最先执行，打乱次序
#DISTFILES += \
#    .qmake.conf
#即使注释掉也会隐式执行.qmake.conf
DISTFILES += \
    $$files(conf/*.conf)



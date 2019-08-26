#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T20:34:18
#
#-------------------------------------------------

QT       += core gui multimedia axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# target name, not include suffix name
TARGET = LQtTool

TEMPLATE = lib
#app - create a app makefile --defult
#lib - create a lib makefile
#vcapp - create a app of Visual Studio project
#vclib - create a lib of Visual Studio project

CONFIG += c++11
DEFINES += L_QT_TOOL

# 指明编译的目标文件的输出路径
#DESTDIR = $$PWD/../bin
DESTDIR = ../bin

CONFIG(debug, debug|release){

    # DEBUG base name add 'd' suffix
    TARGET = $$join(TARGET,,,d)
}

include(LQtTool.pri)


# 定义输出路径
win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
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
        system(.\copy_head.bat)
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

DISTFILES += \
    .qmake.conf



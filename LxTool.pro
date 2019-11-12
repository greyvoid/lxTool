TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = LQtTool \
    LQtPlugin \
    libTest \
    LibUnitTest \
    VesionTool
# 依赖关系
libTest.depends = LQtTool
LibUnitTest.depends = LQtTool

#QMAKESPEC环境变量
#举例来说，如果你在Windows下使用Microsoft Visual Studio，然后你需要把QMAKESPEC环境变量设置为win32-msvc。
#如果你在Solaris上使用gcc，你需要把QMAKESPEC环境变量设置为solaris-g++。
#在qt/mkspecs中的每一个目录里面，都有一个包含了平台和编译器特定信息的qmake.conf文件。这些设置适用于你要使用qmake的任何项目，请不要修改它，除非你是一个专家。
#例如，假如你所有的应用程序都必须和一个特定的库连接，你可以把这个信息添加到相应平台的qmake.conf文件中。
#验证结果证明，.qmake.conf里面的内容总是最先执行,即使注释掉也会隐式执行.qmake.conf
# This file allows us to define "top-level" variables, like $${ROOT_SOURCE}
# and $${ROOT_BUILD} which are the relative paths to source & build respectively.
# These top-level variables are used in sub-project .pro files when determining
# paths to the compiled libraries and other "project" path dependent stuff.
OTHER_FILES += \
    .qmake.conf

#if(contains(DEFINES,PLATFORM_WINDOWS)){
#    SUBDIRS += test_tool\
#}



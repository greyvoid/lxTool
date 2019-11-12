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



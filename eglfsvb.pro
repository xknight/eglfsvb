TARGET = qeglfsvb

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QEglFSIntegrationPlugin
#load(qt_plugin)
TEMPLATE = lib
CONFIG += qt plugin
target.path = $$[QT_INSTALL_PLUGINS]/platforms
INSTALLS += target

HEADERS += \
    $$PWD/qeglfspageflipper.h \
    $$PWD/qeglfsvbintegration.h \
    $$PWD/qeglfsvbscreen.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/qeglfspageflipper.cpp \
    $$PWD/qeglfsvbintegration.cpp \
    $$PWD/qeglfsvbscreen.cpp

include(../eglfs/eglfs.pri)

TARGET = qeglfsvb

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QEglFSIntegrationPlugin
load(qt_plugin)

CONFIG += link_pkgconfig
PKGCONFIG += libudev mtdev glib-2.0

HEADERS += \
    $$PWD/qeglfsvbpageflipper.h \
    $$PWD/qeglfsvbintegration.h \
    $$PWD/qeglfsvbscreen.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/qeglfsvbpageflipper.cpp \
    $$PWD/qeglfsvbintegration.cpp \
    $$PWD/qeglfsvbscreen.cpp

include(../eglfs/eglfs.pri)

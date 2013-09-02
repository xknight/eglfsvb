TARGET = qeglfsvb

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QEglFSIntegrationPlugin
load(qt_plugin)

CONFIG += link_pkgconfig
PKGCONFIG += libudev mtdev glib-2.0

HEADERS += \
    $$PWD/qeglfsvbcontext.h \
    $$PWD/qeglfsvbintegration.h \
    $$PWD/qeglfsvbpageflipper.h \
    $$PWD/qeglfsvbscreen.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/qeglfsvbcontext.cpp \
    $$PWD/qeglfsvbintegration.cpp \
    $$PWD/qeglfsvbpageflipper.cpp \
    $$PWD/qeglfsvbscreen.cpp

DEFINES += QT_NO_CURSOR QT_EGLFSVB_ENABLE_ROTATION

include($$PWD/../eglfs/eglfs.pri)

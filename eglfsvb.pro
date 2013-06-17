TARGET = qeglfsvb

LIBS_PRIVATE += $$QT_LIBS_GLIB

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QEglFSIntegrationPlugin
load(qt_plugin)

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

# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = QT-demo
DESTDIR = ../../build/Win32/Debug
QT += core gui opengl qaxserver qaxcontainer
CONFIG += debug qaxserver console
DEFINES += QT_LARGEFILE_SUPPORT QT_DLL QT_OPENGL_LIB QAXSERVER
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
LIBS += -lopengl32 \
    -lglu32 \
    -lQAxServerd
PRECOMPILED_HEADER = StdAfx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(QT-demo.pri)

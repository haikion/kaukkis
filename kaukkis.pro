#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T23:16:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x
maemo5: QMAKE_CXX = g++-4.6
maemo5: QMAKE_CC = gcc-4.6
maemo5: LIBS += -B /usr/binutils2.22/bin
maemo5: QMAKE_CXXFLAGS += -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -O2 -fomit-frame-pointer -ffast-math

INCLUDEPATH += src
TARGET = kaukkis
TEMPLATE = app

release: DESTDIR = build/release
debug:   DESTDIR = build/debug
maemo5: DESTDIR = build/maemo5
OBJECTS_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
RCC_DIR = $$DESTDIR
UI_DIR = $$DESTDIR



SOURCES += src/main.cpp\
    src/remote.cpp \
    src/buttondialog.cpp \
    src/button.cpp \
    src/theme.cpp \
    src/mainwindow.cpp \
    src/newbuttondialog.cpp \
    src/plugindialog.cpp \
    src/mobileview.cpp \
    src/themedialog.cpp

HEADERS  += \
    src/theme.h \
    src/remote.h \
    src/iremoteoutput.h \
    src/buttontheme.h \
    src/buttondialog.h \
    src/buttonaction.h \
    src/button.h \
    src/mainwindow.h \
    src/buttontype.h \
    src/newbuttondialog.h \
    src/plugindialog.h \
    src/mobileview.h \
    src/themedialog.h

FORMS    += \
    src/mainwindow.ui \
    src/newbuttondialog.ui \
    src/buttondialog.ui \
    src/plugindialog.ui \
    src/themedialog.ui

DISTFILES +=

RESOURCES +=

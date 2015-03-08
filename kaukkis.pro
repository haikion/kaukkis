#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T23:16:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXX = g++-4.6
QMAKE_CC = gcc-4.6
LIBS += -B /usr/binutils2.22/bin

contains(QMAKE_HOST.arch, arm): QMAKE_CXXFLAGS += -mcpu=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp -O3 -fomit-frame-pointer -ffast-math

INCLUDEPATH += src
TARGET = kaukkis
TEMPLATE = app

SOURCES += src/main.cpp\
    src/remote.cpp \
    src/buttondialog.cpp \
    src/button.cpp \
    src/theme.cpp \
    src/mainwindow.cpp \
    src/newbuttondialog.cpp \
    src/plugins/NetworkOutput/networkoutput.cpp \
    src/plugins/NetworkOutput/client.cpp \
    src/plugins/NetworkOutput/message.cpp \
    src/plugindialog.cpp \
    src/mobileview.cpp

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
    src/plugins/NetworkOutput/networkoutput.h \
    src/plugins/NetworkOutput/networkoutput_global.h \
    src/plugins/NetworkOutput/client.h \
    src/plugins/NetworkOutput/message.h \
    src/plugindialog.h \
    src/mobileview.h

FORMS    += \
    src/mainwindow.ui \
    src/newbuttondialog.ui \
    src/buttondialog.ui \
    src/plugindialog.ui \
    src/plugins/NetworkOutput/networkoutputdialog.ui

DISTFILES +=

RESOURCES +=

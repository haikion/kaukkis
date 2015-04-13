#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T12:32:37
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x
maemo5: QMAKE_CXXFLAGS += -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -O2 -fomit-frame-pointer -ffast-math

QT       += network widgets

TARGET = NetworkOutput
TEMPLATE = lib

maemo5: QMAKE_CXX = g++-4.6
maemo5: QMAKE_CC = gcc-4.6
maemo5: LIBS += -B /usr/binutils2.22/bin

#Builds files in a directory where a kaukkis excutable
#can find them.
release: DESTDIR = ../../../build/release/plugins/NetworkOutput
debug:   DESTDIR = ../../../build/debug/plugins/NetworkOutput
maemo5: DESTDIR = ../../../build/maemo5/plugins/NetworkOutput
#OBJECTS_DIR = $$DESTDIR #Does not compile when ".." is used
MOC_DIR = $$DESTDIR
RCC_DIR = $$DESTDIR
UI_DIR = $$DESTDIR


DEFINES += NETWORKOUTPUT_LIBRARY

SOURCES += networkoutput.cpp \
    client.cpp \
    message.cpp

HEADERS += networkoutput.h \
    ../../iremoteoutput.h \
    ../../buttonaction.h \
    client.h \
    message.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    networkoutputdialog.ui

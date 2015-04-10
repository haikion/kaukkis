#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T19:29:38
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x
maemo5: QMAKE_CXXFLAGS += -mcpu=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp -O3 -fomit-frame-pointer -ffast-math

QT       += widgets

#Builds files in a directory where a kaukkis excutable
#can find them.
release: DESTDIR = ../../../build/release/plugins/PluginStub
debug:   DESTDIR = ../../../build/debug/plugins/PluginStub
maemo5: DESTDIR = ../../../build/maemo5/plugins/PluginStub
#OBJECTS_DIR = $$DESTDIR #Does not compile when ".." is used
MOC_DIR = $$DESTDIR
RCC_DIR = $$DESTDIR
UI_DIR = $$DESTDIR

TARGET = PluginStub
TEMPLATE = lib

DEFINES += PLUGINSTUB_LIBRARY

SOURCES += pluginstub.cpp

HEADERS += pluginstub.h\
    ../../iremoteoutput.h \
    ../../buttonaction.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

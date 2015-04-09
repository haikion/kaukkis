#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T12:32:37
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

QT       += network widgets

TARGET = NetworkOutput
TEMPLATE = lib

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

SOURCES += networkoutput.cpp

HEADERS += networkoutput.h\
        networkoutput_global.h \
    ../kaukkis/iremoteoutput.h \
    ../kaukkis/buttonaction.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    networkoutputdialog.ui

#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T12:32:37
#
#-------------------------------------------------

QT       += network widgets

TARGET = NetworkOutput
TEMPLATE = lib

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

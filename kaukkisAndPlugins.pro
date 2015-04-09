#! [0]
TEMPLATE    = subdirs
SUBDIRS	    = kaukkis \
	                       networkOutput
# Combine
kaukkis.file = kaukkis.pro
networkOutput.file = src/plugins/NetworkOutput/NetworkOutput.pro
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

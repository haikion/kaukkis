#! [0]
TEMPLATE    = subdirs
SUBDIRS	    = kaukkis \
	                       networkOutput
# Combine
kaukkis.file = kaukkis.pro
networkOutput.file = src/plugins/NetworkOutput/NetworkOutput.pro
#INSTALLS += target sources
QT       -= core gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG += create_prl link_prl




SOURCES += \
	allmessage.cpp \
        commandmessage.cpp \
        echomessage.cpp \
	groupmessage.cpp \
	header.cpp \
	onemessage.cpp \
        message.cpp \
        plainmessage.cpp \

HEADERS += \
	allmessage.h \
        commandmessage.h \
        echomessage.h \
	groupmessage.h \
	header.h \
	onemessage.h \
        message.h \
        plainmessage.h \
	messageType.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

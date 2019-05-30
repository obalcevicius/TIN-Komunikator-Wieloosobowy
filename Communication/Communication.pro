QT       -= core gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14
CONFIG += create_prl link_prl




SOURCES += \
        clientsocket.cpp \
        commandmessage.cpp \
        constants.cpp \
        datamessage.cpp \
        echomessage.cpp \
        message.cpp \
        participationmessage.cpp \
        plainmessage.cpp \
        serversocket.cpp \
        socket.cpp \
        subscriptionmessage.cpp \
        tokenmessage.cpp

INCLUDEPATH += $$PWD/../Node

HEADERS += \
        clientsocket.h \
        commandmessage.h \
        constants.h \
        datamessage.h \
        echomessage.h \
        message.h \
        participationmessage.h \
        plainmessage.h \
        serversocket.h \
        socket.h \
        subscriptionmessage.h \
        tokenmessage.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

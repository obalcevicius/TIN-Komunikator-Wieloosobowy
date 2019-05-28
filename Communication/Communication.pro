QT       -= core gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG += create_prl link_prl




SOURCES += \
        clientsocket.cpp \
        commandmessage.cpp \
        constants.cpp \
        datamessage.cpp \
        echomessage.cpp \
        message.cpp \
        serversocket.cpp \
        socket.cpp \
        subscriptionmessage.cpp \
        tokenmessage.cpp

HEADERS += \
        clientsocket.h \
        commandmessage.h \
        constants.h \
        datamessage.h \
        echomessage.h \
        message.h \
        serversocket.h \
        socket.h \
        subscriptionmessage.h \
        tokenmessage.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

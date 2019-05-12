QT       -= core gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG += create_prl link_prl




SOURCES += \
        clientsocket.cpp \
        commandmessage.cpp \
        connection.cpp \
        constants.cpp \
        message.cpp \
        serversocket.cpp \
        socket.cpp

HEADERS += \
        clientsocket.h \
        commandmessage.h \
        connection.h \
        constants.h \
        message.h \
        serversocket.h \
        socket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

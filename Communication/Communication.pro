QT       -= core gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG += create_prl link_prl




SOURCES += \
        clientsocket.cpp \
        communication.cpp \
        connection.cpp \
        serversocket.cpp \
        socket.cpp

HEADERS += \
        clientsocket.h \
        communication.h \
        connection.h \
        serversocket.h \
        socket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

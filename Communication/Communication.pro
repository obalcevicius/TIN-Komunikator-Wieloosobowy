QT       -= core gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++17
CONFIG += create_prl link_prl



SOURCES += \
        clientsocket.cpp \
        commandmessage.cpp \
        constants.cpp \
        datamessage.cpp \
        echomessage.cpp \
        groupmembersmessage.cpp \
        message.cpp \
        messagevisitor.cpp \
        participationmessage.cpp \
        plainmessage.cpp \
        serversocket.cpp \
        socket.cpp \





HEADERS += \
        clientsocket.h \
        commandmessage.h \
        constants.h \
        datamessage.h \
        echomessage.h \
        groupmembersmessage.h \
        message.h \
        messagevisitor.h \
        participationmessage.h \
        plainmessage.h \
        serversocket.h \
        socket.h \


unix {
    target.path = /usr/lib
    INSTALLS += target
}

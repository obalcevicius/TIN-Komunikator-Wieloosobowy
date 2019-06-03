#-------------------------------------------------
#
# Project created by QtCreator 2019-06-03T00:41:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Komunikator
TEMPLATE = app


CONFIG += console
QMAKE_CXXFLAGS += -std=c++17


SOURCES += \
        addressdialog.cpp \
        controller.cpp \
        main.cpp \
        mainwindow.cpp \
        messagecontroller.cpp \
        node.cpp \
        nodegroup.cpp \
        nodeinfo.cpp \
        portdialog.cpp

HEADERS += \
        addressdialog.h \
        controller.h \
        mainwindow.h \
        messagecontroller.h \
        node.h \
        nodegroup.h \
        nodeinfo.h \
        portdialog.h

FORMS += \
        addressdialog.ui \
        mainwindow.ui \
        portdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Communication/release/ -lCommunication
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Communication/debug/ -lCommunication
else:unix: LIBS += -L$$OUT_PWD/../Communication/ -lCommunication

INCLUDEPATH += $$PWD/../Communication
DEPENDPATH += $$PWD/../Communication

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/release/libCommunication.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/debug/libCommunication.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/release/Communication.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/debug/Communication.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Communication/libCommunication.a

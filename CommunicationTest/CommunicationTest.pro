QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app


INCLUDEPATH += $$PWD/../Node



SOURCES +=  tst_communicationtest.cpp \
               ../Node/nodeinfo.cpp

HEADERS += ../Node/nodeinfo.h



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

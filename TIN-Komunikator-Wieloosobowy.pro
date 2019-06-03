TEMPLATE = subdirs

SUBDIRS += \
    Communication \
    Node

Node.subdir = Node
Communication.subdir = Communication

SOURCES += main.cpp

Node.depends += Communication

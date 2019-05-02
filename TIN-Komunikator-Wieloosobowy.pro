TEMPLATE = subdirs

SUBDIRS += \
    Communication \
    Node

Node.subdir = Node
Communication.subdir = Communication

Node.depends += Communication

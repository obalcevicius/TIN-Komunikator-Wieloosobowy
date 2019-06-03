TEMPLATE = subdirs

SUBDIRS += \
    Communication \
    Komunikator \
    Node

Node.subdir = Node
Communication.subdir = Communication

Node.depends += Communication

TEMPLATE = subdirs

SUBDIRS += \
    Communication \
    Komunikator

Node.subdir = Node
Communication.subdir = Communication

Node.depends += Communication

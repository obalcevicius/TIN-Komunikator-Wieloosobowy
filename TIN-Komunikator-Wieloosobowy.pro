TEMPLATE = subdirs

SUBDIRS += \
    Communication \
    CommunicationTest \
    Node

Node.subdir = Node
Communication.subdir = Communication

Node.depends += Communication

#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>

#include <string>

#include "controller.h"
#include "mainwindow.h"
#include "node.h"


int main(int argc, char *argv[])
{
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<NodeInfo>("NodeInfo");
    qRegisterMetaType<std::set<NodeInfo>>("std::set<NodeInfo>");
    qRegisterMetaType<Communication::Message*>("Communication::Message*");

    QApplication a(argc, argv);
    Node mainNode;
    Controller mainController(mainNode);
    mainNode.setController(&mainController);
    MainWindow w(mainController, mainNode);
    w.show();
    mainController.showPortDialog();

    return a.exec();
}

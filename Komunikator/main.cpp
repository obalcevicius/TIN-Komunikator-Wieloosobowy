#include "mainwindow.h"
#include <QApplication>

#include "controller.h"
#include "mainwindow.h"
#include "node.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Node mainNode;
    Controller mainController(mainNode);
    MainWindow w(mainController);
    w.show();
    mainController.showPortDialog();

    return a.exec();
}

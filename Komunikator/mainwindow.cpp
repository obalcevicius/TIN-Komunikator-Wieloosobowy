#include <QMessageBox>

#include <arpa/inet.h>
#include <algorithm>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addressdialog.h"
#include "controller.h"

MainWindow::MainWindow(Controller &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(groupJoinRequest(std::string, std::string)), &controller, SLOT(groupJoinRequest(std::string, std::string)));
    connect(&controller, SIGNAL(joinResponse(const std::string&)), this, SLOT(joinResponse(const std::string&)));
    connect(this, SIGNAL(leaveGroup()), &controller, SLOT(leaveGroup()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::joinResponse(const std::string& t_response) {
    if(!t_response.compare("accepted")) {
        ui->leaveGroupButton->setEnabled(true);
    }
    QMessageBox::information(this, tr("Group"), tr(("Your request to join was" + t_response).c_str()));
}

void MainWindow::on_joinGroupButton_clicked() {
    AddressDialog addressDialog;
    addressDialog.setModal(true);
    addressDialog.exec();
    int protocol4_, protocol6_;
    char address6_[INET6_ADDRSTRLEN];
    char address4_[INET_ADDRSTRLEN];
    protocol6_ = inet_pton(AF_INET6, addressDialog.getIPAddress().c_str(), address6_);
    protocol4_ = inet_pton(AF_INET, addressDialog.getIPAddress().c_str(), address4_);
    auto port = addressDialog.getPortNumber();

    if(!port.empty() && std::find_if(port.begin(), port.end(), [](char c){return !std::isdigit(c); }) != port.end()) {
        QMessageBox::critical(this, tr("Error"), tr("Wrong PORT"));
        return;
    }
    if(!protocol4_ && !protocol6_) {
        QMessageBox::critical(this, tr("Error"), tr("Wrong I.P. address"));
        return;
    }
    emit groupJoinRequest(addressDialog.getIPAddress(), addressDialog.getPortNumber());
}

void MainWindow::on_leaveGroupButton_clicked() {

    QMessageBox::StandardButton reply_;
    reply_ = QMessageBox::question(this, "Confirmation", "Are you sure you want to leave group?", QMessageBox::Yes|QMessageBox::Cancel);
    if(reply_ == QMessageBox::Yes) {
        emit leaveGroup();
    }

}

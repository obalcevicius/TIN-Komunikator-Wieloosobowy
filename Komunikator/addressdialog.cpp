#include <QMessageBox>

#include <arpa/inet.h>


#include "addressdialog.h"
#include "ui_addressdialog.h"
#include "constants.h"

AddressDialog::AddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddressDialog)
{
    ui->setupUi(this);
}

AddressDialog::~AddressDialog()
{
    delete ui;
}

std::string AddressDialog::getIPAddress() const {
    return ui->ipAddress->text().toStdString();
}

std::string AddressDialog::getPortNumber() const {
    return ui->portNumber->text().toStdString();
}

void AddressDialog::on_buttonBox_accepted()
{
    int protocol4_, protocol6_;
    char address6_[INET6_ADDRSTRLEN];
    char address4_[INET_ADDRSTRLEN];
    protocol6_ = inet_pton(AF_INET6, getIPAddress().c_str(), address6_);
    protocol4_ = inet_pton(AF_INET, getIPAddress().c_str(), address4_);
    auto port = getPortNumber();

    if(!getPortNumber().compare("") || !getIPAddress().compare("")) {
        QMessageBox::critical(this, tr("Error"), tr("Please Enter Connection Information"));
        return;
    }
    if(!port.empty() && std::find_if(port.begin(), port.end(), [](char c){return !std::isdigit(c); }) != port.end()) {
        QMessageBox::critical(this, tr("Error"), tr("Wrong Port"));
        return;
    }
    if(!protocol4_ && !protocol6_) {
        QMessageBox::critical(this, tr("Error"), tr("Wrong I.P. address"));
        return;
    }
//    if(ui->portNumber->text().toUInt() > Communication::Constants::maxPort) {

//    }
    if(port == "" && (!getIPAddress().compare("127.0.0.1") || !getIPAddress().compare("::1"))) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot join yourself"));

    }
    emit groupJoinRequest(getIPAddress(), getPortNumber());
}

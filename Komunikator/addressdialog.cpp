#include "addressdialog.h"
#include "ui_addressdialog.h"

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

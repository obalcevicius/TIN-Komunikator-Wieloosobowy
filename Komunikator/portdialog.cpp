#include "portdialog.h"
#include "ui_portdialog.h"

PortDialog::PortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortDialog)
{
    ui->setupUi(this);
}

PortDialog::~PortDialog()
{
    delete ui;
}

unsigned short PortDialog::getPort() const {
    return ui->lineEdit->text().toUShort();
}

Communication::Constants::ipVersion PortDialog::getIPVersion() const {
    if(ui->ipv4->isChecked()) {
        return Communication::Constants::ipVersion::IPv4;
    }
    else {
        return Communication::Constants::ipVersion::IPv6;
    }
}

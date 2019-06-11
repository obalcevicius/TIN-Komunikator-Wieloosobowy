#include <QMessageBox>

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
    return ui->portLine->text().toUShort();
}

Communication::Constants::ipVersion PortDialog::getIPVersion() const {
    if(ui->ipv4->isChecked()) {
        return Communication::Constants::ipVersion::IPv4;
    }
    else {
        return Communication::Constants::ipVersion::IPv6;
    }
}

void PortDialog::on_buttonBox_accepted() {
    std::string port = ui->portLine->text().toStdString();
    if(!port.empty() && std::find_if(port.begin(), port.end(), [](char c){return !std::isdigit(c); }) != port.end()) {
        QMessageBox::critical(this, tr("Error"), tr("Wrong Port"));
        QCoreApplication::quit();
    }
    emit setPort(getPort(), getIPVersion());
    emit setUI(port, getIPVersion());
}

void PortDialog::on_PortDialog_rejected() {
    QCoreApplication::quit();
}

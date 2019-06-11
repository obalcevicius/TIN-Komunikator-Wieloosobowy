#include <QInputDialog>
#include <QListView>
#include <QMessageBox>
#include <QString>

#include <algorithm>
#include <string>

#include "mainwindow.h"
#include "constants.h"
#include "controller.h"
#include "node.h"


MainWindow::MainWindow(Controller &controller, Node& t_node, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&addressDialog, SIGNAL(groupJoinRequest(std::string, std::string)), &controller, SLOT(groupJoinRequest(std::string, std::string)));
    connect(&portDialog, SIGNAL(setPort(unsigned short, Communication::Constants::ipVersion)), &controller, SLOT(startNode(unsigned short, Communication::Constants::ipVersion)));
    connect(&portDialog, SIGNAL(setUI(const std::string&, Communication::Constants::ipVersion)), this, SLOT(setUI(const std::string&, Communication::Constants::ipVersion)));
    connect(&controller, SIGNAL(showMessageBox(const std::string&, const std::string&)), this, SLOT(showMessageBox(const std::string&, const std::string&)));
    connect(this, SIGNAL(quit()), &controller, SLOT(quit()));
    connect(this, SIGNAL(listMembersUI()), &t_node, SLOT(listMembers()));


    connect(this, SIGNAL(leaveGroup()), &controller, SLOT(leaveGroup()));
    connect(this, SIGNAL(broadcastMessage(const std::string&)), &controller, SLOT(broadcastMessage(const std::string&)));

    PortDialog portDialog;
    portDialog.setModal(true);
    portDialog.show();

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessageBox(const std::string& t_type, const std::string& t_response) {
    QMessageBox::information(this, t_type.c_str(), t_response.c_str());
}

void MainWindow::on_joinGroupButton_clicked() {
    addressDialog.setModal(true);
    addressDialog.show();
}

void MainWindow::on_leaveGroupButton_clicked() {
    QMessageBox::StandardButton reply_;
    reply_ = QMessageBox::question(this, "Confirmation", "Are you sure you want to leave group?", QMessageBox::Yes|QMessageBox::Cancel);
    if(reply_ == QMessageBox::Yes) {
        emit leaveGroup();
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit quit();
    event->ignore();
}

void MainWindow::setUI(const std::string& t_port, Communication::Constants::ipVersion t_version) {
    if(t_version == Communication::Constants::ipVersion::IPv4) {
        ui->ip->setText("IPv4");
    }
    else if(t_version == Communication::Constants::ipVersion::IPv6) {
        ui->ip->setText("IPv6");
    }
    ui->port->setText(t_port.c_str());
}

void MainWindow::showPortDialog() {
    portDialog.setModal(true);
    portDialog.show();
}

void MainWindow::on_listMembersButton_clicked() {
    emit listMembersUI();
}

void MainWindow::on_broadcastMessageButton_clicked() {

    bool ok;
    std::string text = QInputDialog::getText(this, tr("Please enter message"), tr("Message:"),QLineEdit::Normal, tr("default"), &ok).toStdString();
    emit broadcastMessage(text);
}

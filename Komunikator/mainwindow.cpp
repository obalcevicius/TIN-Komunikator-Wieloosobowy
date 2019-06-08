#include <QInputDialog>
#include <QMessageBox>

#include <algorithm>
#include <string>

#include "mainwindow.h"
#include "controller.h"
#include "node.h"

MainWindow::MainWindow(Controller &controller, Node& t_node, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&addressDialog, SIGNAL(groupJoinRequest(std::string, std::string)), &controller, SLOT(groupJoinRequest(std::string, std::string)));
    connect(&controller, SIGNAL(showMessageBox(const std::string&, const std::string&)), this, SLOT(showMessageBox(const std::string&, const std::string&)));
    connect(this, SIGNAL(listMembersUI()), &t_node, SLOT(listMembers()));
    connect(this, SIGNAL(leaveGroup()), &controller, SLOT(leaveGroup()));
    connect(this, SIGNAL(broadcastMessage(const std::string&)), &controller, SLOT(broadcastMessage(const std::string&)));

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

void MainWindow::on_listMembersButton_clicked() {
    emit listMembersUI();
}

void MainWindow::on_broadcastMessageButton_clicked() {
    bool ok;
    std::string text = QInputDialog::getText(this, tr("Please enter message"), tr("Message:"),QLineEdit::Normal, tr("default"), &ok).toStdString();
    emit broadcastMessage(text);
}

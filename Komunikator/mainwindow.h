#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>


#include "ui_mainwindow.h"
#include "addressdialog.h"
#include "portdialog.h"


namespace Ui {
class MainWindow;
}

class Controller;
class Node;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller &controller,Node& node,  QWidget *parent = nullptr);
    ~MainWindow();
    void showPortDialog();

signals:
    void quit();
    void leaveGroup();
    void broadcastMessage(const std::string&);
    void listMembersUI();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_joinGroupButton_clicked();
    void showMessageBox(const std::string&, const std::string&);
    void setUI(const std::string&, Communication::Constants::ipVersion);
    void on_leaveGroupButton_clicked();
    void on_listMembersButton_clicked();
    void on_broadcastMessageButton_clicked();
    void showCommand(const std::string&);

private:
    Ui::MainWindow *ui;
    AddressDialog addressDialog;
    PortDialog portDialog;

};

#endif // MAINWINDOW_H

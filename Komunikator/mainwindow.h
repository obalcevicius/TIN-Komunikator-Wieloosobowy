#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "addressdialog.h"


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

signals:
    void leaveGroup();
    void broadcastMessage(const std::string&);
    void listMembersUI();
private slots:
    void on_joinGroupButton_clicked();
    void showMessageBox(const std::string&, const std::string&);
    void on_leaveGroupButton_clicked();
    void on_listMembersButton_clicked();
    void on_broadcastMessageButton_clicked();

private:
    Ui::MainWindow *ui;
    AddressDialog addressDialog;

};

#endif // MAINWINDOW_H

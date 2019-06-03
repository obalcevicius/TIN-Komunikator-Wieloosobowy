#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller &controller, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void groupJoinRequest(std::string, std::string);
    void leaveGroup();
private slots:
    void on_joinGroupButton_clicked();
    void joinResponse(const std::string&);

    void on_leaveGroupButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

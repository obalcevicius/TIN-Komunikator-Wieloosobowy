#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>

#include <string>
namespace Ui {
class AddressDialog;
}

class AddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddressDialog(QWidget *parent = nullptr);
    ~AddressDialog();

    std::string getIPAddress() const;
    std::string getPortNumber() const;
signals:
    void groupJoinRequest(std::string, std::string);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddressDialog *ui;
};

#endif // ADDRESSDIALOG_H

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

private:
    Ui::AddressDialog *ui;
};

#endif // ADDRESSDIALOG_H

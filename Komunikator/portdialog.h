#ifndef PORTDIALOG_H
#define PORTDIALOG_H

#include <QDialog>
#include <constants.h>

namespace Ui {
class PortDialog;
}

class PortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PortDialog(QWidget *parent = nullptr);
    ~PortDialog();
    unsigned short getPort() const;
    Communication::Constants::ipVersion getIPVersion() const;


private:
    Ui::PortDialog *ui;
};

#endif // PORTDIALOG_H
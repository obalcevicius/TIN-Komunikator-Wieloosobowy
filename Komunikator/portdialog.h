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
signals:
    void setPort(unsigned short, Communication::Constants::ipVersion) const;
    void setUI(const std::string&, Communication::Constants::ipVersion) const;

private slots:
    void on_buttonBox_accepted();

    void on_PortDialog_rejected();

private:
    Ui::PortDialog *ui;
};

#endif // PORTDIALOG_H

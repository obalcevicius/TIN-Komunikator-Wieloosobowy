#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <future>
#include <set>

#include "constants.h"
#include "mainwindow.h"
#include "messagevisitor.h"
#include "message.h"
#include "nodeinfo.h"
#include "portdialog.h"

class Node;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Node& t_node, QObject *parent = nullptr);

    void showPortDialog();

signals:
    void startListening(unsigned short, Communication::Constants::ipVersion);
    void resetGroup();
    void setGroup(const std::set<NodeInfo>&, std::string) const;
    void showMessageBox(const std::string&, const std::string&) const;
    void broadcastMessage(const Communication::Message*) const;
    void showCommand(const std::string& t_command) const;
public slots:

    void quit();
    void showResponse(const std::string&, const std::string&);
    void groupJoinRequest(std::string, std::string);
    void startNode(unsigned short, Communication::Constants::ipVersion);
    void leaveGroup();
    void broadcastMessage(const std::string&);
    void receivedMessage(const std::string&);

private:
    void joinGroup(const std::string&, const std::string&);
    Node* m_node;
    unsigned short m_port;


};

#endif // CONTROLLER_H

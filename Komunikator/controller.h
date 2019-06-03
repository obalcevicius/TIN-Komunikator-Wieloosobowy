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

class Controller : public QObject, public Communication::MessageVisitor
{
    Q_OBJECT
public:
    explicit Controller(Node& t_node, QObject *parent = nullptr);

    void showPortDialog();

signals:
    void startListening(unsigned short, Communication::Constants::ipVersion);
    void setGroup(const std::set<NodeInfo>&, const std::string&) const;
    void joinResponse(const std::string&) const;
    void broadcastMessage(const Communication::Message&) const;
public slots:

    void groupJoinRequest(std::string, std::string);
    void startNode();
    void leaveGroup();
    virtual void visit(const Communication::ParticipationMessage& t_message) const override;
    virtual void visit(const Communication::CommandMessage& t_message) const override;
    virtual void visit(const Communication::EchoMessage& t_message) const override;
    virtual void visit(const Communication::GroupMembersMessage& t_message) const override;

private:
    void joinGroup(const std::string&, const std::string&);
    PortDialog m_portDialog;


};

#endif // CONTROLLER_H

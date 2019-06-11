#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <QObject>

#include <functional>
#include <string>

#include "messagevisitor.h"
#include "node.h"
#include "nodegroup.h"
#include "nodeinfo.h"
#include "socket.h"


class Controller;

class MessageController : public QObject, public Communication::MessageVisitor
{
    Q_OBJECT
public:
    explicit MessageController(Node* t_node, Communication::Socket t_socket, Controller* t_controller, QObject *parent = nullptr);
    virtual void visit(const Communication::ParticipationMessage& t_message) const override;
    virtual void visit(const Communication::CommandMessage& t_message) const override;
    virtual void visit(const Communication::EchoMessage& t_message) const override;
    virtual void visit(const Communication::GroupMembersMessage& t_message) const override;
signals:
    void addNode(const NodeInfo&, const std::string&) const;
    void broadcastMessage(const Communication::Message&) const;
    void joinResponse(const std::string&) const;
    void removeNode(const NodeInfo&, const std::string&) const;
    void receivedMessage(const std::string&) const ;
    void setGroup(const std::set<NodeInfo>&, const std::string&) const;
    void showResponse(const std::string&, const std::string&) const;

public slots:

private:
    Communication::Socket m_socket;
    Node* m_node;


};

#endif // MESSAGECONTROLLER_H

#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <QObject>

#include <string>

#include "messagevisitor.h"
#include "node.h"
#include "nodegroup.h"
#include "nodeinfo.h"
#include "socket.h"

class MessageController : public QObject, public Communication::MessageVisitor
{
    Q_OBJECT
public:
    explicit MessageController(Node* t_node, Communication::Socket t_socket, QObject *parent = nullptr);

signals:
    void addNode(const NodeInfo&, const std::string&) const;
    void removeNode(const NodeInfo&, const std::string&) const;
    void setGroup(const std::set<NodeInfo>&, const std::string&) const;
    void joinResponse(const std::string&) const;


public slots:
    virtual void visit(const Communication::ParticipationMessage& t_message) const override;
    virtual void visit(const Communication::CommandMessage& t_message) const override;
    virtual void visit(const Communication::EchoMessage& t_message) const override;
    virtual void visit(const Communication::GroupMembersMessage& t_message) const override;



private:
    Communication::Socket m_socket;
    Node* m_node;

};

#endif // MESSAGECONTROLLER_H

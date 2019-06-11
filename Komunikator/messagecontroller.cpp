#include <QMessageBox>

#include "messagecontroller.h"

MessageController::MessageController(Node* t_node, Communication::Socket t_socket, Controller* t_controller, QObject *parent) :
    QObject(parent),
    m_socket(std::move(t_socket)),
    m_node(t_node)
{
    connect(this, SIGNAL(addNode(const NodeInfo&, const std::string&)), t_node, SLOT(addNode(const NodeInfo&, const std::string&)), Qt::QueuedConnection);
    connect(this, SIGNAL(removeNode(const NodeInfo&, const std::string&)), t_node, SLOT(removeNode(const NodeInfo&, const std::string&)), Qt::QueuedConnection);
    connect(this, SIGNAL(setGroup(const std::set<NodeInfo>&, const std::string&)), t_node, SLOT(setGroup(const std::set<NodeInfo>&, const std::string&)), Qt::QueuedConnection);
    //connect(this, SIGNAL(broadcastMessage(const Communication::Message&)), t_node, SLOT(broadcastMessage(const Communication::Message&)), Qt::QueuedConnection);
    connect(this, SIGNAL(showResponse(const std::string&, const std::string&)), t_controller, SLOT(showResponse(const std::string&, const std::string&)),Qt::QueuedConnection);
}


void MessageController::visit(const Communication::ParticipationMessage& t_message) const {
    qDebug("received participation message");
    std::cout << t_message.getCommand() <<" " <<t_message.getNodeInfo().getPort() <<"\n";
    if(!t_message.getCommand().compare("subscribe")) {
    }
    else if(!t_message.getCommand().compare("unsubscribe")) {
    }
    else if(!t_message.getCommand().compare("join")) {

        Communication::ParticipationMessage msg_(NodeInfo(t_message.getNodeInfo().getIPAddress(), t_message.getNodeInfo().getPort()),
                                            "add", "member");
        m_node->broadcastMessage(msg_);

        auto members = m_node->getGroup(NodeGroup::GroupType::Member);
        std::cout << m_socket.getIPAddress() << " \n";
        members.insert(NodeInfo(m_socket.getIPAddress(), std::to_string(m_node->getListeningPort())));

        auto subscribers = m_node->getGroup(NodeGroup::GroupType::Subscriber);

        Communication::GroupMembersMessage memberMessage("accepted", "members", members);
        Communication::GroupMembersMessage subMessage("accepted", "subscribers", subscribers);

        m_socket.sendMessage(memberMessage.serialize());
        m_socket.sendMessage(subMessage.serialize());

        m_node->addNode(t_message.getNodeInfo(), "member");
    }
    else if(!t_message.getCommand().compare("leave")) {
        m_node->removeNode(t_message.getNodeInfo(), "member");

        Communication::ParticipationMessage msg_(NodeInfo(t_message.getNodeInfo().getIPAddress(), t_message.getNodeInfo().getPort()),
                                                 "remove", "member");
        m_node->broadcastMessage(msg_);

    }
    else if(!t_message.getCommand().compare("add")) {
        if(!t_message.getGroup().compare("member")) {
            emit addNode(t_message.getNodeInfo(), "member");
        }
        else if(!t_message.getGroup().compare("subscriber")) {
            emit addNode(t_message.getNodeInfo(), "subscriber");
        }
    }
    else if(!t_message.getCommand().compare("remove")) {
        if(!t_message.getGroup().compare("member")) {
            m_node->removeNode(t_message.getNodeInfo(), "member");
        }
        else if(!t_message.getGroup().compare("subscriber")) {
            emit addNode(t_message.getNodeInfo(), "subscriber");
        }
    }
}



void MessageController::visit(const Communication::CommandMessage& t_message) const {
    std::cout << "RECEIVED MESSAGE: " << t_message.getCommand() << std::endl;

}

void MessageController::visit(const Communication::EchoMessage& t_message) const {


}

void MessageController::visit(const Communication::GroupMembersMessage& t_message) const {
    qDebug("received group message");
    if(!t_message.getCommand().compare("accepted")) {
        emit setGroup(t_message.getGroup(), t_message.getGroupType());
    }
    std::string response("Request to join ");
    response.append(t_message.getCommand());
    emit showResponse("Group Join", response);

}

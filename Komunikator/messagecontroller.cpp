#include "messagecontroller.h"

MessageController::MessageController(Node* t_node, Communication::Socket t_socket, QObject *parent) :
    QObject(parent),
    m_socket(std::move(t_socket)),
    m_node(t_node)
{
    connect(this, SIGNAL(addNode(const NodeInfo&, const std::string&)), t_node, SLOT(addNode(const NodeInfo&, const std::string&)));
    connect(this, SIGNAL(removeNode(const NodeInfo&, const std::string&)), t_node, SLOT(removeNode(const NodeInfo&, const std::string&)));
    connect(this, SIGNAL(setGroup(const std::set<NodeInfo>&, const std::string&)), t_node, SLOT(setGroup(const std::set<NodeInfo>&, const std::string&)));


}


void MessageController::visit(const Communication::ParticipationMessage& t_message) const {

    if(!t_message.getCommand().compare("subscribe")) {
//broadcast
    }
    else if(!t_message.getCommand().compare("unsubscribe")) {
//broadcast
    }
    else if(!t_message.getCommand().compare("join")) {
        if(m_node->isMember(t_message.getNodeInfo())) {
            //broadcast
        }
    }
    else if(!t_message.getCommand().compare("leave")) {
        //broadcast

    }
    else if(!t_message.getCommand().compare("add")) {
        if(!t_message.getGroup().compare("member") && m_node->isMember(t_message.getNodeInfo())) {
            emit addNode(t_message.getNodeInfo(), "member");
        }
        else if(!t_message.getGroup().compare("subscriber") && m_node->isSubscriber(t_message.getNodeInfo())) {
            emit addNode(t_message.getNodeInfo(), "subscriber");
        }
    }
    else if(!t_message.getCommand().compare("remove")) {
        if(!t_message.getGroup().compare("member") && m_node->isMember(t_message.getNodeInfo())) {
            emit addNode(t_message.getNodeInfo(), "member");
        }
        else if(!t_message.getGroup().compare("subscriber") && m_node->isSubscriber(t_message.getNodeInfo())) {
            emit addNode(t_message.getNodeInfo(), "subscriber");
        }
    }
}

void MessageController::visit(const Communication::CommandMessage& t_message) const {

}

void MessageController::visit(const Communication::EchoMessage& t_message) const {


}

void MessageController::visit(const Communication::GroupMembersMessage& t_message) const {
    if(t_message.getCommand().compare("accepted")) {
        emit setGroup(t_message.getGroup(), t_message.getGroupType());
    }
    emit joinResponse(t_message.getCommand());
}

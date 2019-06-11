#include <QMessageBox>
#include <QMetaType>
#include <QString>

#include <utility>

#include "clientsocket.h"
#include "node.h"
#include "messagecontroller.h"
#include "constants.h"



using sendResult = std::pair<NodeInfo, bool> ;

Node::Node(QObject *parent) : QObject(parent), m_isMember(false), m_isSubscriber(false)
{

}

void Node::startServer(unsigned short t_port, Communication::Constants::ipVersion t_version) {
    try {
        std::cout << "START SERVER\n";
        m_server = std::make_unique<Communication::ServerSocket>(t_version, t_port);
        m_server->listen();

        m_acceptingThread = std::thread(&Node::acceptConnections, this);
        m_acceptingThread.detach();
    }
    catch(std::runtime_error ex) {
        std::string errorString("Could not start server.\n");
        errorString.append(ex.what());
        QMessageBox::critical(nullptr, tr("Fatal Error"), errorString.c_str());

        QCoreApplication::quit();
    }

}

void Node::acceptConnections() {
    while(true) {
        Communication::Socket newConnection = m_server->accept();
        auto parsingThread(std::thread(&Node::parseConnection, this, std::move(newConnection)));
        parsingThread.detach();
    }
}
bool Node::isMember() const {
    return m_isMember;
}
bool Node::isSubscriber() const {
    return m_isSubscriber;
}

void Node::parseConnection(Communication::Socket t_socket) {
    auto newBuffer(t_socket.readMessage());
    auto newMessage = newBuffer->getMessage();
    MessageController controller_(this, std::move(t_socket), m_controller);
    newMessage->accept(controller_);
}

void Node::setController(Controller* t_controller) {
    m_controller = t_controller;
}

void Node::setGroup(const std::set<NodeInfo>& t_group, std::string t_type) {
    m_isMember = true;
    if(!t_type.compare("members")) {
        for(const auto& member_ : t_group) {
            m_members.addMember(member_);
        }
    }
    else if(!t_type.compare("subscribers")) {
        for(const auto& sub_ : t_group) {
            m_subscribers.addMember(sub_);
        }

    }
}

void Node::resetGroup() {
    m_members.clear();
    m_subscribers.clear();
    m_isMember = false;
    m_isSubscriber = false;
}



void Node::addNode(const NodeInfo& t_node, std::string t_type) {
    if(!t_type.compare("member")) {
        m_isMember = true;
        m_members.addMember(t_node);
    }
    else if(!t_type.compare("subscriber")) {
        m_subscribers.addMember(t_node);
    }
}
void Node::removeNode(const NodeInfo& t_node, std::string t_type) {
    if(!t_type.compare("member")) {
        m_members.removeMember(t_node);
    }
    else if(!t_type.compare("subscriber")) {
        m_subscribers.removeMember(t_node);
    }
}

const std::set<NodeInfo>& Node::getGroup(NodeGroup::GroupType t_type) const {
    switch (t_type) {
    case NodeGroup::GroupType::Member:
        return m_members.getMembers();
    case NodeGroup::GroupType::Subscriber:
        return m_subscribers.getMembers();
    }
    return std::move(std::set<NodeInfo>());
}

unsigned short Node::getListeningPort() const {
    return m_server->getPort();
}

void Node::broadcastMessage(const Communication::Message& t_msg) const {
    std::vector<std::thread> threads_;
    for(const auto& member_ : m_members.getMembers()) {
        threads_.push_back(std::thread(&Node::sendMessage, const_cast<Node*>(this), member_, std::ref(t_msg)));
    }

    for(auto& thread_ : threads_) {
        thread_.join();
    }
}

void Node::sendMessage(const NodeInfo& t_node, const Communication::Message& t_msg) {

    Communication::ClientSocket socket(Communication::Constants::ipVersion::IPv6);
    socket.connect(t_node.getIPAddress(), t_node.getPort());
    socket.sendMessage(t_msg.serialize());
}

void Node::listMembers() {
    std::string members;

    for(const auto& member_ : m_members.getMembers()) {
        members.append(member_.getIPAddress() + " " + member_.getPort() + "\n");
    }
    QMessageBox::information(nullptr, "MEMBERS", members.c_str());
}


#include <utility>

#include "clientsocket.h"
#include "node.h"
#include "messagecontroller.h"
#include "constants.h"


using sendResult = std::pair<NodeInfo, bool> ;

Node::Node(QObject *parent) : QObject(parent)
{
    addNode(NodeInfo("127.0.0.1", "2500"), "member");
    addNode(NodeInfo("127.0.0.1", "2501"), "member");
    addNode(NodeInfo("127.0.0.1", "2502"), "member");


}

void Node::startServer(unsigned short t_port, Communication::Constants::ipVersion t_version) {
    m_server = std::make_unique<Communication::ServerSocket>(t_version, t_port);
    m_server->listen();

    m_acceptingThread = std::thread(&Node::acceptConnections, this);
    m_acceptingThread.detach();
}

void Node::acceptConnections() {
    while(true) {
        std::cout << "START accept";
        Communication::Socket newConnection = m_server->accept();
        auto parsingThread(std::thread(&Node::parseConnection, this, std::move(newConnection)));
        parsingThread.detach();
        //parseConnection(std::move(newConnection));
    }
}

void Node::parseConnection(Communication::Socket t_socket) {
    while(true) {
        std::cout << "START CONNECTION";
        auto newBuffer = t_socket.readMessage();

        auto newMessage = newBuffer->getMessage();
        MessageController controller_(this, std::move(t_socket));
        newMessage->accept(*m_controller);
    }
}

void Node::setGroup(const std::set<NodeInfo>& t_group, const std::string& t_type) {
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

bool Node::isMember(const NodeInfo & t_node) {
    if(auto it = m_members.getMembers().find(t_node); it != m_members.getMembers().end()) {
        return true;
    }
    return false;
}
bool Node::isSubscriber(const NodeInfo &t_node) {
    if(auto it = m_subscribers.getMembers().find(t_node); it != m_subscribers.getMembers().end()) {
        return true;
    }
    return false;
}

void Node::addNode(const NodeInfo& t_node, const std::string& t_type) {
    qDebug("hello");
    if(!t_type.compare("member")) {
        m_members.addMember(t_node);
    }
    else if(!t_type.compare("subscriber")) {
        m_subscribers.addMember(t_node);
    }
}
void Node::removeNode(const NodeInfo& t_node, const std::string& t_type) {
    if(!t_type.compare("member")) {
        m_members.removeMember(t_node);
    }
    else if(!t_type.compare("subscriber")) {
        m_subscribers.removeMember(t_node);
    }
}

void Node::broadcastMessage(const Communication::Message& t_msg) const {
    std::vector<std::thread> threads_;
    qDebug("broadcast");
    std::cout << m_members.getMembers().size();
    //std::vector<std::promise<sendResult>> vals_;
    //std::vector<std::future<sendResult>> returnValue;
    for(const auto& member_ : m_members.getMembers()) {
        qDebug("thread");
        threads_.push_back(std::thread(&Node::sendMessage, const_cast<Node*>(this), member_, std::ref(t_msg)));
    }

    for(auto& thread_ : threads_) {
        thread_.join();
    }
}

void Node::sendMessage(const NodeInfo& t_node, const Communication::Message& t_msg) {
    qDebug("thread send");

    Communication::ClientSocket socket(Communication::Constants::ipVersion::IPv4);
    socket.connect(t_node.getIPAddress(), t_node.getPort());
    socket.sendMessage(t_msg.serialize());

}


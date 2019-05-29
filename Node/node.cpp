#include <arpa/inet.h>

#include "constants.h"
#include "node.h"
#include "plainmessage.h"


Node::Node(Communication::Constants::ipVersion t_ipVersion, std::string t_ipAddress, std::string t_port) :
    m_thisNode(t_ipAddress, t_port),
    m_server(t_ipVersion, static_cast<unsigned short>(std::stoi(t_port)))
{

}

void Node::startListening() {
    m_server.listen();
    m_isListening = true;
    m_acceptingThread = std::thread(&Node::acceptConnections, this, std::ref(m_isListening));
    m_acceptingThread.detach();
}

void Node::stopListening() {
    m_isListening = false;
}

void Node::acceptConnections(bool& t_finish) {
    while(t_finish) {
       m_server.accept();
    }
}

void Node::broadcastMessage(const Communication::PlainMessage& t_msg) {
    m_server.sendToAll(t_msg.getMessage(), t_msg.getMessageLength());
}

void Node::joinGroup(std::string t_ipAddress, std::string t_port) {
    int protocol_;
    char address_[INET6_ADDRSTRLEN];
    protocol_ = inet_pton(AF_INET6, t_ipAddress.c_str(), address_);

    Communication::ClientSocket client(protocol_ ? Communication::Constants::ipVersion::IPv6 : Communication::Constants::ipVersion::IPv4);
    client.connect(t_ipAddress, t_port);

}

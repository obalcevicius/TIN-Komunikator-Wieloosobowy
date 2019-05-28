#include "constants.h"
#include "node.h"


Node::Node(Communication::Constants::ipVersion t_ipVersion, std::string t_ipAddress, std::string t_port) :
    m_thisNode(t_ipAddress, t_port),
    m_server(t_ipVersion, static_cast<unsigned short>(std::stoi(t_port)))
{

}

void Node::startListening() {
    m_server.listen();
}

void Node::acceptConnection() {
    m_server.accept();
}

void Node::broadcastMessage(const Communication::Message& t_message) {
    for(const auto& member : m_members.getMembers()) {


    }
}

#include <arpa/inet.h>

#include "commandmessage.h"
#include "constants.h"
#include "node.h"

#include "nodeinfo.h"
#include "nodegroup.h"
#include "plainmessage.h"
#include "groupmembersmessage.h"
#include "participationmessage.h"


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
    //acceptConnections(m_isListening);
}

void Node::stopListening() {
    m_isListening = false;
}

void Node::acceptConnections(bool& t_finish) {
    while(t_finish) {
        std::cout << "START accept";
        Communication::Socket newConnection = m_server.accept();
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
        //NodeController controller();
        //newMessage->accept(*this);
    }
}
bool Node::broadcastMessage(const Communication::Message& t_message) const {
    std::vector<std::thread> threads_;
    std::vector<std::promise<bool>> retValues_;
    std::vector<std::future<bool>> sentValue_;


    for(const auto& member_ : m_members.getMembers()) {
        retValues_.push_back(std::promise<bool>());
        sentValue_.push_back(retValues_.back().get_future());
        threads_.push_back(std::thread(&Node::sendMessage, const_cast<Node*>(this), member_, std::ref(t_message), std::move(retValues_.back())));
    }

    for(auto& thread : threads_) {
        thread.join();
    }

    for(auto& val : sentValue_) {
        if(val.get() == false) {
            return false;
        }
    }
    return true;
}

void Node::sendMessage(const NodeInfo& t_node, const Communication::Message& t_msg, std::promise<bool>&& t_return) const {

    Communication::ClientSocket socket(Communication::Constants::ipVersion::IPv4); //todo: configuration file
    socket.connect(t_node.getIPAddress(), t_node.getPort());
    try {
        socket.sendMessage(t_msg.serialize());
    } catch (std::exception ex) {
        std::cout<< "Couldn't send message " << ex.what() << std::endl;
        t_return.set_value(false);
        return;
    }
    t_return.set_value(true);
}

void Node::joinGroup(std::string t_ipAddress, std::string t_port) {
    int protocol_;
    char address_[INET6_ADDRSTRLEN];
    protocol_ = inet_pton(AF_INET6, t_ipAddress.c_str(), address_);

    Communication::ClientSocket client(protocol_ ? Communication::Constants::ipVersion::IPv6 : Communication::Constants::ipVersion::IPv4);
    client.connect(t_ipAddress, t_port);
    Communication::ParticipationMessage msg(NodeInfo(t_ipAddress, t_port), "join", "member");
    client.sendMessage(Communication::PlainMessage(msg.serialize()));
}


//todo: change managing




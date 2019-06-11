#include <QMessageBox>
#include <string>
#include <thread>

#include "controller.h"
#include "clientsocket.h"
#include "commandmessage.h"
#include "echomessage.h"
#include "groupmembersmessage.h"
#include "messagecontroller.h"
#include "node.h"
#include "nodeinfo.h"
#include "participationmessage.h"



Controller::Controller(Node& t_node, QObject *parent) : QObject(parent), m_node(&t_node)
{
    //connect controller signals
    connect(this, SIGNAL(startListening(unsigned short, Communication::Constants::ipVersion)), &t_node, SLOT(startServer(unsigned short, Communication::Constants::ipVersion)));
    connect(this, SIGNAL(setGroup(const std::set<NodeInfo>&, const std::string&)), &t_node, SLOT(setGroup(const std::set<NodeInfo>&, const std::string&)));
    connect(this, SIGNAL(resetGroup()), &t_node, SLOT(resetGroup()));
}

void Controller::groupJoinRequest(std::string t_ipAddress, std::string t_portNumber) {
    auto joinThread = std::thread(&Controller::joinGroup, this, t_ipAddress, t_portNumber );
    joinThread.detach();

}
void Controller::joinGroup(const std::string& t_ip,const std::string& t_port) {
    using Communication::ParticipationMessage;
    Communication::ClientSocket client;
    try {
        if(Communication::Constants::isIPv6Address(t_ip)) {
            client = Communication::ClientSocket(Communication::Constants::ipVersion::IPv6);
        }
        else if (Communication::Constants::isIPv4Address(t_ip)) {
            client = Communication::ClientSocket(Communication::Constants::ipVersion::IPv4);
        }
        client.connect(t_ip, t_port);
    }
    catch (std::runtime_error ex) {
        std::string errorString("Could not join group\n");
        errorString.append(ex.what());
        emit showResponse("Error", errorString);
        return;
    }

    //ParticipationMessage msg(NodeInfo(client.getIPAddress(), std::to_string(m_port)), "join", "member");

    ParticipationMessage msg(NodeInfo("::1", std::to_string(m_port)), "join", "member");

    client.sendMessage(Communication::PlainMessage(msg.serialize()));

    auto responseBuffer_ = client.readMessage();
    auto response = responseBuffer_->getMessage();
    MessageController controller(m_node, std::move(client), this);
    response->accept(controller);
}

void Controller::startNode(unsigned short t_port, Communication::Constants::ipVersion t_version) {
    m_port = t_port;
    emit startListening(t_port, t_version);
}

void Controller::showResponse(const std::string& t_type, const std::string& t_message) {
    emit showMessageBox(t_type, t_message);
}

void Controller::quit() {
    if(m_node->isMember()) {
        leaveGroup();        
    }

    QApplication::quit();
}

void Controller::receivedMessage(const std::string& t_command) {
    emit showCommand(t_command);
}




void Controller::leaveGroup() {
    using Communication::ParticipationMessage;

    if(m_node->isMember()) {
        using Communication::ParticipationMessage;
        auto member_ = m_node->getGroup(NodeGroup::GroupType::Member).begin();
        Communication::ClientSocket client;
        try {
            if(Communication::Constants::isIPv6Address(member_->getIPAddress())) {
                client = Communication::ClientSocket(Communication::Constants::ipVersion::IPv6);
            }
            else if (Communication::Constants::isIPv4Address(member_->getIPAddress())) {
                client = Communication::ClientSocket(Communication::Constants::ipVersion::IPv4);
            }
            client.connect(member_->getIPAddress(), member_->getPort());
        }
        catch (std::runtime_error ex) {
            return;
        }

        ParticipationMessage msg(NodeInfo(client.getIPAddress(), std::to_string(m_port)), "leave", "member");

        client.sendMessage(Communication::PlainMessage(msg.serialize()));
        emit resetGroup();
    }
    else {
        QMessageBox::warning(nullptr, "Warning", "You're not a group member");
    }

}
void Controller::broadcastMessage(const std::string& t_message) {
    Communication::CommandMessage msg_(t_message, 5);
    m_node->broadcastMessage(msg_);
}

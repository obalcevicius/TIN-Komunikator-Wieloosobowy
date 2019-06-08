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
    connect(&m_portDialog, SIGNAL(accepted()), this, SLOT(startNode()));
    connect(this, SIGNAL(startListening(unsigned short, Communication::Constants::ipVersion)), &t_node, SLOT(startServer(unsigned short, Communication::Constants::ipVersion)));
    connect(this, SIGNAL(setGroup(const std::set<NodeInfo>&, const std::string&)), &t_node, SLOT(setGroup(const std::set<NodeInfo>&, const std::string&)));
    //connect(this, SIGNAL(broadcastMessage(const Communication::Message*)), &t_node, SLOT(broadcastMessage(const Communication::Message*)));
}

void Controller::groupJoinRequest(std::string t_ipAddress, std::string t_portNumber) {
    auto joinThread = std::thread(&Controller::joinGroup, this, t_ipAddress, t_portNumber );
    joinThread.detach();

}
void Controller::joinGroup(const std::string& t_ip,const std::string& t_port) {
    using Communication::ParticipationMessage;
    using Communication::Constants;

    try {
        auto client = Communication::ClientSocket(Constants::ipVersion::IPv4);
        client.connect(t_ip, t_port);

        ParticipationMessage msg(NodeInfo(client.getIPAddress(), std::to_string(m_port)), "join", "member");

        client.sendMessage(Communication::PlainMessage(msg.serialize()));

        auto responseBuffer_ = client.readMessage();
        auto response = responseBuffer_->getMessage();
        MessageController controller(m_node, std::move(client), this);
        response->accept(controller);

    } catch (std::runtime_error ex) {
        std::string errorString("Could not join group");
        errorString.append(ex.what());
        emit showResponse("Error", errorString);
    }
}

void Controller::startNode() {
    m_port = m_portDialog.getPort();
    emit startListening(m_portDialog.getPort(), m_portDialog.getIPVersion());
}
void Controller::showPortDialog() {
    m_portDialog.setModal(true);
    m_portDialog.show();
}



void Controller::showResponse(const std::string& t_type, const std::string& t_message) {
    emit showMessageBox(t_type, t_message);
}

void Controller::leaveGroup() {

}
void Controller::broadcastMessage(const std::string& t_message) {
    Communication::CommandMessage msg_(t_message);
    m_node->broadcastMessage(msg_);
}

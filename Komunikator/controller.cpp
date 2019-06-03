#include <QMessageBox>

#include <thread>

#include "controller.h"
#include "clientsocket.h"
#include "commandmessage.h"
#include "echomessage.h"
#include "groupmembersmessage.h"
#include "node.h"
#include "nodeinfo.h"
#include "participationmessage.h"




Controller::Controller(Node& t_node, QObject *parent) : QObject(parent)
{
    //connect controller signals
    connect(&m_portDialog, SIGNAL(accepted()), this, SLOT(startNode()));
    connect(this, SIGNAL(startListening(unsigned short, Communication::Constants::ipVersion)), &t_node, SLOT(startServer(unsigned short, Communication::Constants::ipVersion)));
    connect(this, SIGNAL(setGroup(const std::set<NodeInfo>&, const std::string&)), &t_node, SLOT(setGroup(const std::set<NodeInfo>&, const std::string&)));
    connect(this, SIGNAL(broadcastMessage(const Communication::Message&)), &t_node, SLOT(broadcastMessage(const Communication::Message&)));
    //connect(this, SIGNAL(joinGroup(std::string, std::string)), )
}

void Controller::groupJoinRequest(std::string t_ipAddress, std::string t_portNumber) {
    auto joinThread = std::thread(&Controller::joinGroup, this, t_ipAddress, t_portNumber );
    joinThread.detach();

}
void Controller::joinGroup(const std::string& t_ip,const std::string& t_port) {
    Communication::ClientSocket client(Communication::Constants::ipVersion::IPv4);
    client.connect(t_ip, t_port);
    Communication::ParticipationMessage msg(NodeInfo(t_ip, t_port), "join", "member");
    client.sendMessage(Communication::PlainMessage(msg.serialize()));

    auto responseBuffer_ = client.readMessage();
    auto response = responseBuffer_->getMessage();
    response->accept(*this);
}

void Controller::startNode() {
    emit startListening(m_portDialog.getPort(), m_portDialog.getIPVersion());
}
void Controller::showPortDialog() {
    m_portDialog.setModal(true);
    m_portDialog.exec();
}


void Controller::visit(const Communication::ParticipationMessage& t_message) const {

    if(!t_message.getCommand().compare("subscribe")) {

    }
    else if(!t_message.getCommand().compare("unsubscribe")) {

    }
    else if(!t_message.getCommand().compare("join")) {

    }
    else if(!t_message.getCommand().compare("leave")) {

    }
    else if(!t_message.getCommand().compare("add")) {

    }
    else if(!t_message.getCommand().compare("remove")) {

    }
}

void Controller::visit(const Communication::CommandMessage& t_message) const {

}

void Controller::visit(const Communication::EchoMessage& t_message) const {


}

void Controller::visit(const Communication::GroupMembersMessage& t_message) const {
    if(t_message.getCommand().compare("accepted")) {
        emit setGroup(t_message.getGroup(), t_message.getGroupType());
    }
    emit joinResponse(t_message.getCommand());
}

void Controller::leaveGroup() {
    qDebug("emit broadcast");
    Communication::ParticipationMessage msg(NodeInfo("HELLO", "DUXAS"), "add", "sub");
    emit broadcastMessage(msg);

}

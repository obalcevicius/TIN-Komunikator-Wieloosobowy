#include <arpa/inet.h>
#include <bitset>
#include <iostream>

#include "messagevisitor.h"
#include "participationmessage.h"

#include "plainmessage.h"


namespace Communication {

ParticipationMessage::ParticipationMessage()
{

}

ParticipationMessage::ParticipationMessage(const NodeInfo& t_thisNode, const std::string& t_command, const std::string& t_group) :
    m_thisNode(t_thisNode),
    m_command(t_command),
    m_group(t_group){}


int ParticipationMessage::getHeader() const {
    return Constants::participationMessageHeader;
}

NodeInfo ParticipationMessage::getNodeInfo() const {
    return m_thisNode;
}

std::string ParticipationMessage::getCommand() const {
    return  m_command;
}

std::string ParticipationMessage::getGroup() const {
    return m_group;
}

PlainMessage ParticipationMessage::serialize() const {
    std::stringstream body;
    // Add message data into stream
    body << getHeader() << " ";
    body << m_command << " ";
    body << m_group << " ";
    body << m_thisNode.getIPAddress() << " " << m_thisNode.getPort();

    return PlainMessage(body.str());
}

void ParticipationMessage::deserialize(const PlainMessage& t_message)  {
    std::string messageString(t_message.getMessageBody(), t_message.getMessageLength());
    std::stringstream messageStream(messageString);
    int messageHeader;
    messageStream >> messageHeader;
    if(messageHeader != getHeader()) {
        std::cout << "WRONG MESSAGE!: " << messageHeader << std::endl;
        return;
    }
    messageStream >> m_command >> m_group;
    std::string ipAddress; std::string port;
    messageStream >> ipAddress >> port;
    m_thisNode = NodeInfo(ipAddress, port);
}

void ParticipationMessage::accept(const MessageVisitor& t_visitor) {
    t_visitor.visit(*this);
}



ParticipationMessage::~ParticipationMessage() {

}
} // namespace Communication

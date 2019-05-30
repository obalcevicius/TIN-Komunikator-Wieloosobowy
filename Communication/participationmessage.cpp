#include <arpa/inet.h>
#include <bitset>
#include <iostream>

#include "constants.h"
#include "participationmessage.h"

namespace Communication {

ParticipationMessage::ParticipationMessage()
{

}

ParticipationMessage::ParticipationMessage(NodeInfo t_thisNode, std::string t_command) :
    m_thisNode(t_thisNode),
    m_command(t_command) {}


int ParticipationMessage::getHeader() const {
    return Constants::participationMessageHeader;
}

NodeInfo ParticipationMessage::getNodeInfo() const {
    return m_thisNode;
}

std::string ParticipationMessage::getCommand() const {
    return  m_command;
}

PlainMessage ParticipationMessage::serialize() const {
    std::stringstream body;
    // Add message data into stream
    body << getHeader() << " ";
    body << m_command << " ";
    body << m_thisNode.getIPAddress() << " " << m_thisNode.getPort();

    return PlainMessage(body.str());
}

void ParticipationMessage::deserialize(std::unique_ptr<PlainMessage> t_message)  {
    std::string messageString(t_message->getMessage(), t_message->getMessageLength());
    std::stringstream messageStream(messageString);
    int messageHeader;
    messageStream >> messageHeader;
    if(messageHeader != getHeader()) {
        std::cout << "WRONG MESSAGE!: " << messageHeader << std::endl;
        return;
    }
    messageStream >> m_command;
    std::string ipAddress; std::string port;
    messageStream >> ipAddress >> port;
    m_thisNode = NodeInfo(ipAddress, port);
}

ParticipationMessage::~ParticipationMessage() {

}
} // namespace Communication

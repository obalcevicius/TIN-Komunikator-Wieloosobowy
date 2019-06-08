#include <arpa/inet.h>
#include <bitset>
#include <iostream>


#include "groupmembersmessage.h"
#include "messagevisitor.h"
#include "plainmessage.h"


namespace Communication {

GroupMembersMessage::GroupMembersMessage()
{

}

GroupMembersMessage::GroupMembersMessage(const std::string& t_command, const std::string& t_type, const std::set<NodeInfo>& t_group) :
    m_command(t_command),
    m_groupType(t_type),
    m_group(t_group) {}

int GroupMembersMessage::getHeader() const {
    return Constants::groupMembersMessageHeader;
}

std::string GroupMembersMessage::getGroupType() const {
    return m_groupType;
}
const std::set<NodeInfo>& GroupMembersMessage::getGroup() const {
    return m_group;
}

std::string GroupMembersMessage::getCommand() const {
    return m_command;
}


PlainMessage GroupMembersMessage::serialize() const {
    std::stringstream body;

    // Add message data into stream
    body << getHeader() << " ";
    body << m_command << " ";
    body << m_groupType << " ";
    body << m_group.size() << " ";
    for(auto& member: m_group) {
        body << member.getIPAddress() << " " << member.getPort() << " ";
    }

    return PlainMessage(body.str());
}

void GroupMembersMessage::deserialize(const PlainMessage &t_message) {
    std::string messageString(t_message.getMessageBody(), t_message.getMessageLength());
    std::stringstream messageStream(messageString);
    int messageHeader, groupCount;
    messageStream >> messageHeader;
    if(messageHeader != getHeader()) {
        std::cout << "WRONG MESSAGE!: " << messageHeader << std::endl;
        return;
    }
    messageStream >> m_command >> m_groupType >> groupCount;
    for (int i = 0; i < groupCount; ++i) {

        std::string ipAddress, port;
        messageStream >> ipAddress >> port;
        m_group.insert(NodeInfo(ipAddress, port));
    }
}

void GroupMembersMessage::accept(const MessageVisitor& t_visitor) {
    t_visitor.visit(*this);
}
GroupMembersMessage::~GroupMembersMessage() {}
} // namespace Communication

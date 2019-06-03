
#include <iostream>
#include <sstream>


#include "commandmessage.h"
#include "constants.h"
#include "messagevisitor.h"
#include "plainmessage.h"

namespace Communication {


CommandMessage::CommandMessage() {

}

CommandMessage::CommandMessage(std::string t_command, int t_info) :
    m_command(t_command),
    m_info(t_info)
{
    std::cout <<t_command.size();

}


int CommandMessage::getHeader() const {
    return Constants::commandMessageHeader;
}
std::string CommandMessage::getCommand() const {
    return m_command;
}

int CommandMessage::getInfo() const {
    return m_info;
}

PlainMessage CommandMessage::serialize() const {
    std::stringstream body;
    // Add message data into stream
    body << getHeader() << " ";
    body << m_command << " ";
    body << m_info;

    return PlainMessage(body.str());
}
void CommandMessage::deserialize(const PlainMessage& t_message)  {
    std::string messageString(t_message.getMessageBody(), t_message.getMessageLength());
    std::stringstream messageStream(messageString);
    int messageHeader;
    messageStream >> messageHeader;
    if(messageHeader != getHeader()) {
        std::cout << "WRONG MESSAGE!: " << messageHeader << std::endl;
        return;
    }
    messageStream >> m_command;
    messageStream >> m_info;
}

void CommandMessage::accept(const MessageVisitor& t_visitor) {
    t_visitor.visit(*this);
}
CommandMessage::~CommandMessage() {

}
} // namespace Communication

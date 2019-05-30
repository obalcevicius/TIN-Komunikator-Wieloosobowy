#include <arpa/inet.h>
#include <bitset>
#include <iostream>
#include <sstream>
#include "commandmessage.h"
#include "constants.h"


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

PlainMessage CommandMessage::serialize() const {
    std::stringstream body, message;
    // Add message data into stream
    body << getHeader() << " ";
    body << m_command << " ";
    body << m_info;
    // Prepend message size in binary format. Always 32 bytes.
    message << std::bitset<32>(htonl(body.str().size())).to_string();
    message << body.str().data();
    return PlainMessage(message.str());
}
void CommandMessage::deserialize(std::unique_ptr<PlainMessage> t_message)  {
    std::string messageString(t_message->getMessage(), t_message->getMessageLength());
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

CommandMessage::~CommandMessage() {

}
} // namespace Communication

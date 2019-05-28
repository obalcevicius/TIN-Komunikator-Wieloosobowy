#include <sstream>
#include <iomanip>
#include <arpa/inet.h>
#include <iostream>

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

PlainMessage CommandMessage::serialize() const {
    std::stringstream sstream;
    std::stringstream msg;
    sstream << getHeader();
    sstream << m_info;
    sstream << m_command;


    msg << std::hex << std::setw(8) << std::setfill('0') << htonl(sstream.str().size());

    msg << sstream.str().data();
    std::cout << "message size: " << msg.str().size() << std::endl;
    return PlainMessage(msg.str());

}
void CommandMessage::deserialize(std::istream &t_istream) {
    std::getline(t_istream, m_command);
}

CommandMessage::~CommandMessage() {

}
} // namespace Communication

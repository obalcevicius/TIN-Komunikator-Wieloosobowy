#include "commandmessage.h"
#include "constants.h"


namespace Communication {


CommandMessage::CommandMessage(std::string t_command) :m_command(t_command) {

}


int CommandMessage::getHeader() const {
    return Constants::commandMessageHeader;
}

void CommandMessage::serialize(std::ostream &t_ostream) const {
    t_ostream << getHeader();
    t_ostream << m_command;
}

CommandMessage::~CommandMessage() {

}
} // namespace Communication

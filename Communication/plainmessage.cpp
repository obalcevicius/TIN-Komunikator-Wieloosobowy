#include <arpa/inet.h>
#include <bitset>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>


#include "constants.h"
#include "plainmessage.h"


namespace Communication {


PlainMessage::PlainMessage(const std::string& t_data) {
    m_buffer = std::make_unique<char[]>(t_data.size());
    std::memcpy(m_buffer.get(), t_data.data(), t_data.size());
    m_length = t_data.size();
    m_messageType = std::stoi(t_data);
    prepareHeader();
}

PlainMessage::PlainMessage(std::unique_ptr<char[]> t_data, unsigned int t_length, int t_messageType) :
    m_buffer(std::move(t_data)),
    m_length(t_length),
    m_messageType(t_messageType)
{
    prepareHeader();

}

PlainMessage::~PlainMessage() {

}

PlainMessage::PlainMessage(PlainMessage&& rhs) :
    m_header(rhs.m_header),
    m_buffer(std::move(rhs.m_buffer)),
    m_length(rhs.m_length),
    m_messageType(rhs.m_messageType)
{

}


int PlainMessage::getMessageType() const {
    if(m_buffer != nullptr) {
        return m_messageType;
    }
    return Constants::incorrectHeader;
}

const char* PlainMessage::getMessageHeader() const {
    return m_header.data();
}

const char* PlainMessage::getMessageBody() const {
    return m_buffer.get();
}

void PlainMessage::prepareHeader() {
    std::stringstream header;
    header << std::bitset<32>(htonl(getMessageLength())).to_string() << " " << getMessageType();
    m_header = header.str();
}

std::unique_ptr<Message> PlainMessage::getMessage() const {
    if(m_buffer != nullptr) {
        if(getMessageType() == Constants::participationMessageHeader) {
            ParticipationMessage* m = new ParticipationMessage();
            m->deserialize(*this);
            return std::unique_ptr<Message>(m);
        }
        else if(getMessageType() == Constants::commandMessageHeader) {
            CommandMessage* m = new CommandMessage();
            m->deserialize(*this);
            return std::unique_ptr<Message>(m);
        }
        else if(getMessageType() == Constants::groupMembersMessageHeader) {
            GroupMembersMessage* m = new GroupMembersMessage();
            m->deserialize(*this);
            return std::unique_ptr<Message>(m);
        }
        throw std::runtime_error("GETMESSAGE IF");

    }
    throw  std::runtime_error("GETMESSAGE FUNC");
    return std::unique_ptr<Message>(nullptr);
}



unsigned int PlainMessage::getMessageLength() const {
    return m_length;
}

} // namespace Communication

#include <arpa/inet.h>
#include <bitset>
#include <cstring>
#include <sstream>
#include <iostream>
#include "constants.h"
#include "plainmessage.h"

namespace Communication {


PlainMessage::PlainMessage(const std::string& t_data) {
    m_buffer = std::unique_ptr<char>(new char[t_data.size()]);
    std::memcpy(m_buffer.get(), t_data.data(), t_data.size());
    m_length = t_data.size();
    prepareHeader();
}

PlainMessage::PlainMessage(std::unique_ptr<char> t_data, unsigned int t_length) :
    m_buffer(std::move(t_data)),
    m_length(t_length)
{
    prepareHeader();

}

PlainMessage::~PlainMessage() {

}

PlainMessage::PlainMessage(PlainMessage&& rhs) :
    m_header(rhs.m_header),
    m_buffer(std::move(rhs.m_buffer)),
    m_length(rhs.m_length)
{

}


int PlainMessage::getMessageType() const {
    if(m_buffer != nullptr) {
        return m_buffer.get()[0] - '0';
    }
    return Constants::incorrectHeader;
}

const char* PlainMessage::getMessageHeader() const {
    return m_header.data();
}

const char* PlainMessage::getMessage() const {
    return m_buffer.get();
}

void PlainMessage::prepareHeader() {
    std::stringstream header;
    header << std::bitset<32>(htonl(getMessageLength())).to_string() << " " << getMessageType();
    m_header = header.str();
}



unsigned int PlainMessage::getMessageLength() const {
    return m_length;
}

} // namespace Communication

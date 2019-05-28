#include <cstring>
#include "plainmessage.h"

namespace Communication {

PlainMessage::PlainMessage() : m_buffer(nullptr), m_length(0) {

}

PlainMessage::PlainMessage(const std::string& t_data) {
    m_buffer = std::unique_ptr<char>(new char[t_data.size()]);
    std::memcpy(m_buffer.get(), t_data.data(), t_data.size());
    m_length = t_data.size();
}

PlainMessage::PlainMessage(std::unique_ptr<char> t_data) :
    m_buffer(std::move(t_data)) {}

PlainMessage::~PlainMessage() {

}

PlainMessage::PlainMessage(PlainMessage&& rhs) :
    m_buffer(std::move(rhs.m_buffer)),
    m_length(rhs.m_length)
{

}
char* PlainMessage::getMessage() const {
    return m_buffer.get();
}

unsigned int PlainMessage::getMessageLength() const {
    return m_length;
}

} // namespace Communication

#ifndef PLAINMESSAGE_H
#define PLAINMESSAGE_H

#include <memory>

namespace Communication {

class PlainMessage
{
public:
    PlainMessage();
    PlainMessage(const std::string& t_data);
    PlainMessage(std::unique_ptr<char> t_data);
    PlainMessage(PlainMessage&& rhs);
    char* getMessage() const;
    unsigned int getMessageLength() const;
    ~PlainMessage();
private:
    std::unique_ptr<char> m_buffer;
    unsigned int m_length;
};

} // namespace Communication

#endif // PLAINMESSAGE_H

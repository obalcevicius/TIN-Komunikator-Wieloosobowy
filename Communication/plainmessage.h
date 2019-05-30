#ifndef PLAINMESSAGE_H
#define PLAINMESSAGE_H

#include <memory>

namespace Communication {

/**
 * @brief The PlainMessage constains serialized message
 */
class PlainMessage
{
public:
    PlainMessage();
    /**
     * @brief Constructs PlainMessage from string constaining message
     * @param t_data  String with serialized message
     */
    PlainMessage(const std::string& t_data);
    /**
     * @brief Constructs class out of char buffer
     * @param t_data buffer containg message data
     * @param t_length length of t_data buffer
     */
    PlainMessage(std::unique_ptr<char> t_data, unsigned int t_length);
    PlainMessage(const PlainMessage&) = delete;
    PlainMessage& operator=(const PlainMessage&) = delete;
    /**
     * @brief Move copy constructor
     */
    PlainMessage(PlainMessage&& rhs);

    /**
     * @brief returns type of serialized message
     * @return Message header type as of constants.h
     */
    int getMessageType() const;
    const char* getMessage() const;
    unsigned int getMessageLength() const;
    ~PlainMessage();
private:
    std::unique_ptr<char> m_buffer;
    unsigned int m_length;
};

} // namespace Communication

#endif // PLAINMESSAGE_H

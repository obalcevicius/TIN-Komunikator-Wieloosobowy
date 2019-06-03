#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <sstream>

namespace Communication {

class MessageVisitor;

class PlainMessage;
/**
 * @brief Base class for all messages
 */
class Message
{
public:
    Message();
    /**
     * @brief Returns message ID, which is used to identify message type
     * @return message type
     */
    virtual int getHeader() const = 0;
    /**
     * @brief Serializes message to output stream, all derived classes override this method
     * @param t_ostream Stream to serialize data to
     */
    virtual PlainMessage serialize() const = 0;

    /**
     * @brief Deserialized message from output stream, all derived classes override this method
     * @param t_ostream Stream with message data
     */
    virtual void deserialize(const PlainMessage& t_message) = 0;

    virtual void accept(const MessageVisitor& visitor) = 0;

    virtual ~Message();
};

} // namespace Communication

#endif // MESSAGE_H

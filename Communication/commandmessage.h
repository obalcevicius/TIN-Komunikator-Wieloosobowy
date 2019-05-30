#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include <string>
#include <sstream>

#include "message.h"

namespace Communication {

/**
 * @brief Message used to organise system
 */
class CommandMessage : public Message
{
public:
    CommandMessage();
    CommandMessage(std::string t_command, int t_info = 0);

    virtual int getHeader() const override;
    /**
     * @brief Serializes current message into form ready to be sent over network
     * @return Serialized Message in PlainMessage class
     */
    virtual PlainMessage serialize() const override;

    /**
     * @brief Populates fields out of PlainMessage
     * @param t_message PlainMessage with Message data
     */
    virtual void deserialize(std::unique_ptr<PlainMessage> t_message) override;
    /**
     * @brief Getter for command
     * @return command of the message
     */
    std::string getCommand() const;
    virtual ~CommandMessage() override;
private:
    std::string m_command;
    int m_info;
};

} // namespace Communication

#endif // COMMANDMESSAGE_H

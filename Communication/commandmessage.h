#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include <string>
#include <sstream>

#include "message.h"

namespace Communication {


class CommandMessage : public Message
{
public:
    CommandMessage(std::string t_command);

    virtual int getHeader() const override;
    virtual void serialize(std::ostream& t_ostream) const override;
    std::string getCommand() const;
    virtual ~CommandMessage() override;
private:
    std::string m_command;
};

} // namespace Communication

#endif // COMMANDMESSAGE_H

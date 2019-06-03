#ifndef ECHOMESSAGE_H
#define ECHOMESSAGE_H

#include "message.h"

namespace Communication {

class MessageVisitor;

class EchoMessage : public Message
{
public:
    EchoMessage();

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(const PlainMessage& t_message) override;

     virtual void accept(const MessageVisitor& translator) override;

    virtual ~EchoMessage() override;

private:

};

} // namespace Communication

#endif // ECHOMESSAGE_H

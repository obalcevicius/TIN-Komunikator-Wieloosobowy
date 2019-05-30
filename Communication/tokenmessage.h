#ifndef TOKENMESSAGE_H
#define TOKENMESSAGE_H

#include <memory>

#include "message.h"
#include "plainmessage.h"
namespace Communication {

class TokenMessage : public Message
{
public:
    TokenMessage();

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(std::unique_ptr<PlainMessage> t_message) override;

    virtual ~TokenMessage() override;
private:

};

} // namespace Communication

#endif // TOKENMESSAGE_H

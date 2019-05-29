#ifndef TOKENMESSAGE_H
#define TOKENMESSAGE_H

#include "message.h"

namespace Communication {

class TokenMessage : public Message
{
public:
    TokenMessage();

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(std::istream& t_istream) override;

    virtual ~TokenMessage() override;
private:

};

} // namespace Communication

#endif // TOKENMESSAGE_H

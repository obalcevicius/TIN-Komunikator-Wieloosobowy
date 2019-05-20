#ifndef ECHOMESSAGE_H
#define ECHOMESSAGE_H

#include "message.h"

namespace Communication {

class EchoMessage : public Message
{
public:
    EchoMessage();

    virtual int getHeader() const override;
    virtual void serialize(std::ostream& t_ostream) const override;
    virtual void deserialize(std::istream& t_istream) override;

    virtual ~EchoMessage() override;

private:

};

} // namespace Communication

#endif // ECHOMESSAGE_H
#ifndef MESSAGE_H
#define MESSAGE_H

#include <sstream>

namespace Communication {

class MessageVisitor;
class Message
{
public:
    Message();

    virtual int getHeader() const = 0;
    virtual void serialize(std::ostream& t_ostream) const = 0;
    virtual void deserialize(std::istream& t_istream) = 0;

    virtual ~Message();
};

} // namespace Communication

#endif // MESSAGE_H

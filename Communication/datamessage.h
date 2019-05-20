#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

#include "message.h"

namespace Communication {

class DataMessage : public Message
{
public:
    DataMessage();
    virtual int getHeader() const override;
    virtual void serialize(std::ostream& t_ostream) const override;
    virtual void deserialize(std::istream& t_istream) override;

    virtual ~DataMessage() override;
private:

};

} // namespace Communication

#endif // DATAMESSAGE_H

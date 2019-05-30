#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

#include "message.h"

namespace Communication {

/**
 * @brief DataMessage is used to send data between group members
 */
class DataMessage : public Message
{
public:
    DataMessage();
    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    //virtual void deserialize(std::istream& t_istream) override;

    virtual ~DataMessage() override;
private:

};

} // namespace Communication

#endif // DATAMESSAGE_H

#ifndef SUBSCRIPTIONMESSAGE_H
#define SUBSCRIPTIONMESSAGE_H

#include <memory>

#include "message.h"
#include "plainmessage.h"
namespace Communication {

/**
 * @brief SubscribtionMessage is used to subscribe to group
 */
class SubscriptionMessage : public Message
{
public:
    SubscriptionMessage();

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(std::unique_ptr<PlainMessage> t_message) override;

    virtual ~SubscriptionMessage() override;
private:

};

} // namespace Communication

#endif // SUBSCRIPTIONMESSAGE_H

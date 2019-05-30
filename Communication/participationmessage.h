#ifndef PARTICIPATIONMESSAGE_H
#define PARTICIPATIONMESSAGE_H

#include "message.h"
#include "nodeinfo.h"

namespace Communication {

/**
 * @brief This message is used to express wish to join or leave group, whether as a member or subscriber
 */
class ParticipationMessage : public Message
{
public:
    ParticipationMessage();
    ParticipationMessage(NodeInfo t_node, std::string t_command);

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(std::unique_ptr<PlainMessage> t_message) override;

    std::string getCommand() const;
    NodeInfo getNodeInfo() const;

    virtual ~ParticipationMessage() override;
private:
    NodeInfo m_thisNode;

    /**
     * @brief m_command [join/leave/subsribe/unsubscribe]
     */
    std::string m_command;
};

} // namespace Communication

#endif // PARTICIPATIONMESSAGE_H

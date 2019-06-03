#ifndef PARTICIPATIONMESSAGE_H
#define PARTICIPATIONMESSAGE_H

#include "constants.h"
#include "message.h"
#include "../Node/nodeinfo.h"

namespace Communication {


class MessageVisitor;
/**
 * @brief This message is used to express wish to join or leave group, whether as a member or subscriber
 */
class ParticipationMessage : public Message
{
public:
    ParticipationMessage();
    ParticipationMessage(const NodeInfo& t_node, const std::string& t_command, const std::string& t_group);

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(const PlainMessage& t_message) override;

    std::string getCommand() const;
    NodeInfo getNodeInfo() const;
    std::string getGroup() const;

     virtual void accept(const MessageVisitor& t_visitor) override;

    virtual ~ParticipationMessage() override;
private:
    NodeInfo m_thisNode;

    /**
     * @brief m_command [join/leave/subsribe/unsubscribe/add_[s/a]/remove_[s/a]]
     */
    std::string m_command;
    std::string m_group;
};

} // namespace Communication

#endif // PARTICIPATIONMESSAGE_H

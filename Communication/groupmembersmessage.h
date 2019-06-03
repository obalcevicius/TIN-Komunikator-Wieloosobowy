#ifndef GROUPMEMBERSMESSAGE_H
#define GROUPMEMBERSMESSAGE_H

#include <set>

#include "constants.h"
#include "message.h"
#include "../Node/nodegroup.h"

namespace Communication {

class MessageVisitor;

class GroupMembersMessage : public Message
{
public:
    GroupMembersMessage();
    GroupMembersMessage(const std::string& m_command, const std::string& t_type, const std::set<NodeInfo>& t_group);

    virtual int getHeader() const override;
    virtual PlainMessage serialize() const override;
    virtual void deserialize(const PlainMessage& t_message) override;
    virtual void accept(const MessageVisitor& translator) override;

    std::string getCommand() const;
    std::string getGroupType() const;
    const std::set<NodeInfo>& getGroup() const;

    virtual ~GroupMembersMessage() override;
private:
    std::string m_command;
    std::string m_groupType; // subscribers/members
    std::set<NodeInfo> m_group;
};

} // namespace Communication

#endif // GROUPMEMBERSMESSAGE_H

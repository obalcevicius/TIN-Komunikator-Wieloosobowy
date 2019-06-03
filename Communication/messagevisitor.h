#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H


namespace Communication {

class CommandMessage;
class GroupMembersMessage;
class ParticipationMessage;
class EchoMessage;

class MessageVisitor
{
public:
    MessageVisitor();
    virtual void visit(const CommandMessage& t_commandMessage) const = 0;
    virtual void visit(const ParticipationMessage& t_participationMessage) const  = 0;
    virtual void visit(const EchoMessage& t_echoMessage) const = 0;
    virtual void visit(const GroupMembersMessage& t_groupMessage) const = 0;
    virtual ~MessageVisitor();
};

} // namespace Communication

#endif // MESSAGEVISITOR_H

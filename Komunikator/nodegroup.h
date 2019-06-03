#ifndef NODEGROUP_H
#define NODEGROUP_H

#include <mutex>
#include <set>

#include "nodeinfo.h"

class NodeGroup
{
public:
    NodeGroup();
    void addMember(NodeInfo t_member);
    void removeMember(NodeInfo t_member);
    const std::set<NodeInfo>& getMembers() const;
    enum class GroupType {
        Subscriber,
        Member
    };

private:
    std::mutex m_lock;
    std::set<NodeInfo> m_members;
};

#endif // NODEGROUP_H

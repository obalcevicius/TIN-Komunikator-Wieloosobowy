#ifndef NODEGROUP_H
#define NODEGROUP_H

#include <mutex>
#include <set>

#include "nodeinfo.h"

class NodeGroup
{
public:
    NodeGroup();
    void addMember(const NodeInfo&);
    void removeMember(const NodeInfo&);
    bool isMember(const NodeInfo&) const;
    const std::set<NodeInfo>& getMembers() const;
    void clear();
    enum class GroupType {
        Subscriber,
        Member
    };

private:
    std::mutex m_lock;
    std::set<NodeInfo> m_members;
};

#endif // NODEGROUP_H

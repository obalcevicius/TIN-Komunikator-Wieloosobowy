#ifndef NODEGROUP_H
#define NODEGROUP_H


#include <set>

#include "nodeinfo.h"

class NodeGroup
{
public:
    NodeGroup();
    void addMember(NodeInfo t_member);
    void removeMember(NodeInfo t_member);
    const std::set<NodeInfo>& getMembers() const;
private:
    std::set<NodeInfo> m_members;
};

#endif // NODEGROUP_H

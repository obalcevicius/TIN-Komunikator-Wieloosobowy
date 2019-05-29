#include "nodegroup.h"

NodeGroup::NodeGroup()
{

}

void NodeGroup::addMember(NodeInfo t_member) {
    m_members.insert(t_member);
}

void NodeGroup::removeMember(NodeInfo t_member) {
    m_members.erase(t_member);
}

const std::set<NodeInfo>& NodeGroup::getMembers() const {
    return m_members;
}

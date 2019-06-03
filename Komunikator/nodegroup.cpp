#include "nodegroup.h"

NodeGroup::NodeGroup()
{

}

void NodeGroup::addMember(NodeInfo t_member) {
    std::lock_guard<std::mutex> lc(m_lock);
    m_members.insert(t_member);
}

void NodeGroup::removeMember(NodeInfo t_member) {
    std::lock_guard<std::mutex> lc(m_lock);
    m_members.erase(t_member);
}

const std::set<NodeInfo>& NodeGroup::getMembers() const {
    return m_members;
}

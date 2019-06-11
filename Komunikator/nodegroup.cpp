#include "nodegroup.h"

NodeGroup::NodeGroup()
{

}

void NodeGroup::addMember(const NodeInfo& t_member) {
    std::lock_guard<std::mutex> lc(m_lock);
    m_members.insert(t_member);
}

void NodeGroup::removeMember(const NodeInfo& t_member) {
    std::lock_guard<std::mutex> lc(m_lock);
    for(auto it = m_members.begin(); it != m_members.end(); ++it) {
        if(it->getIPAddress() == t_member.getIPAddress() && it->getPort() == t_member.getPort()) {
            m_members.erase(it);
            return;
        }
    }

}

const std::set<NodeInfo>& NodeGroup::getMembers() const {
    return m_members;
}

bool NodeGroup::isMember(const NodeInfo& t_node) const {
    if(auto it = m_members.find(t_node); it != m_members.end()) {
        return true;
    }
    return false;
}

void NodeGroup::clear() {
     std::lock_guard<std::mutex> lc(m_lock);
     m_members.clear();
}

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
    m_members.erase(t_member);
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
//bool NodeGroup::isSubscriber(const NodeInfo &t_node) {
//    if(auto it = m_subscribers.getMembers().find(t_node); it != m_subscribers.getMembers().end()) {
//        return true;
//    }
//    return false;
//}

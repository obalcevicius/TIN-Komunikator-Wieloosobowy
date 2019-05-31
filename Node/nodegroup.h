#ifndef NODEGROUP_H
#define NODEGROUP_H


#include <set>

#include "nodeinfo.h"

#include <istream>
#include <ostream>

namespace Node {

class NodeGroup;
std::ostream & operator << (std::ostream & out, const NodeGroup & group);
std::istream & operator >> (std::istream & in, NodeGroup & group);

class NodeGroup
{
public:
    NodeGroup();
    friend std::ostream & operator << (std::ostream & out, const NodeGroup & group);
    friend std::istream & operator >> (std::istream & in, NodeGroup & group);
    void addMember(NodeInfo t_member);
    void removeMember(NodeInfo t_member);
    const std::set<NodeInfo>& getMembers() const;
    void present();
private:
    std::set<NodeInfo> m_members;
};

} //namespace Node

#endif // NODEGROUP_H

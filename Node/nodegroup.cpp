#include "nodegroup.h"
#include <iostream>
using std::ostream;
using std::istream;
using std::cout;
using std::endl;

namespace Node {

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

ostream & operator << (ostream & out, const NodeGroup & group) {
	out << group.m_members.size() << " ";
	for (NodeInfo node : group.m_members) {
		out << node;
	}
	return out;
}
istream & operator >> (istream & in, NodeGroup & group) {
	int n;
	in >> n;
	for(int ni = 0; ni != n; ni++) {
		NodeInfo node("", "");
		in >> node;
		group.addMember(node);
	}
	return in;
}
void NodeGroup::present() {
	cout << "Jestem grupą:" << endl;
	cout << "Liczność: " << m_members.size() << endl;
	for (NodeInfo node: m_members) {
		node.present();
	}
}
	

} //namespace Node			

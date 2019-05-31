#include "nodeinfo.h"
#include <iostream>
using std::ostream;
using std::istream;
using std::cout;
using std::endl;

namespace Node {

NodeInfo::NodeInfo(std::string t_ipAddress, std::string t_port) :
    m_ipAddress(t_ipAddress),
    m_port(t_port) {}

std::string NodeInfo::getIPAddress() const {
    return m_ipAddress;
}

std::string NodeInfo::getPort() const {
    return m_port;
}

bool NodeInfo::operator<(const NodeInfo& rhs) const{
    if(m_ipAddress.compare(rhs.m_ipAddress) == 0) {
        return m_port.compare(rhs.m_port);
    }
    else {
        return m_ipAddress.compare(rhs.m_ipAddress);
    }
}

ostream & operator << (ostream & out, const NodeInfo & node) {
	out << node.m_ipAddress << " " << node.m_port << " ";
}
istream & operator >> (istream & in, NodeInfo & node) {
	in >> node.m_ipAddress >> node.m_port;
}

void NodeInfo::present() {
	cout << "Węzeł: " << m_ipAddress << " : " << m_port << endl;
}
} //namespace Node

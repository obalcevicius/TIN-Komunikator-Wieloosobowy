#include "nodeinfo.h"

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


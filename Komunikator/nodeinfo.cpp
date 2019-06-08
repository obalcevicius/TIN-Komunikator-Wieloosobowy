#include "nodeinfo.h"

NodeInfo::NodeInfo() {}
NodeInfo::NodeInfo(const std::string& t_ipAddress, const std::string& t_port) :
    m_ipAddress(t_ipAddress),
    m_port(t_port) {}

NodeInfo::NodeInfo(const NodeInfo& rhs) :
    m_ipAddress(rhs.getIPAddress()),
    m_port(rhs.getPort()) {}

NodeInfo& NodeInfo::operator=(const NodeInfo& other) {
    if(&other == this) {
        return *this;
    }
    m_ipAddress = other.m_ipAddress;
    m_port = other.m_port;

    return *this;
}

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


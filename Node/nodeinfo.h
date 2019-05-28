#ifndef NODEINFO_H
#define NODEINFO_H

#include <string>

class NodeInfo
{
public:
    NodeInfo(std::string t_ipAddress, std::string t_port);
    std::string getIPAddress() const;
    std::string getPort() const;

    bool operator<(const NodeInfo& rhs) const;

private:
    std::string m_ipAddress;
    std::string m_port;
};

#endif // NODEINFO_H

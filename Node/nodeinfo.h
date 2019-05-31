#ifndef NODEINFO_H
#define NODEINFO_H

#include <string>
#include <istream>
#include <ostream>

namespace Node {

class NodeInfo;
std::ostream & operator << (std::ostream & out, const NodeInfo & node);
std::istream & operator >> (std::istream & in, NodeInfo & node);

class NodeInfo
{
public:
    NodeInfo(std::string t_ipAddress, std::string t_port);
    std::string getIPAddress() const;
    std::string getPort() const;
    friend std::ostream & operator << (std::ostream & out, const NodeInfo & node);
    friend std::istream & operator >> (std::istream & in, NodeInfo & node);
    bool operator<(const NodeInfo& rhs) const;
    void present();
private:
    std::string m_ipAddress;
    std::string m_port;
};

} //namespace Node
#endif // NODEINFO_H

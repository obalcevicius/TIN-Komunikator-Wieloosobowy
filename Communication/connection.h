#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include "clientsocket.h"

namespace Communication {

class Connection
{
public:
    Connection(std::string t_serverAddress,
               std::string t_serverPort,
               char t_ipVersion);
    void send(const std::string t_message) const;
    void receive() const;
private:
    ClientSocket m_socket;

};

} // namespace Communication

#endif // CONNECTION_H

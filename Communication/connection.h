#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include "clientsocket.h"

namespace Communication {

class Connection
{
public:
    Connection(std::string t_ipAddress,
               unsigned short t_serverPort,
               char t_ipVersion);
private:
    ClientSocket m_socket;

};

} // namespace Communication

#endif // CONNECTION_H

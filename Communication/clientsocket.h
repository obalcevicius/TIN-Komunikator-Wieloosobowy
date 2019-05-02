#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <netinet/in.h>
#include <netdb.h>

#include <string>

#include "socket.h"

namespace Communication {

class ClientSocket : public Socket
{
public:
    ClientSocket();
    ~ClientSocket() override;
    void connect(std::string t_ipAddress, std::string t_port);
private:
    struct sockaddr_in m_server;

};

} // namespace Communication

#endif // CLIENTSOCKET_H

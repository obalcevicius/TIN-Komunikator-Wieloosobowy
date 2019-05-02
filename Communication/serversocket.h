#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <vector>

#include "socket.h"

namespace Communication {

class ServerSocket : public Socket
{
public:
    ServerSocket(unsigned short t_port);
    virtual ~ServerSocket() override;
    void listen();
    void accept();
private:
    struct sockaddr_in m_server;
    std::vector<int> m_clients;
};

} // namespace Communication

#endif // SERVERSOCKET_H

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <arpa/inet.h>
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
    void sendToAll(const char* t_buffer, size_t length);
private:
    struct sockaddr_in m_server;
    std::vector<Socket> m_clients;
};

} // namespace Communication

#endif // SERVERSOCKET_H

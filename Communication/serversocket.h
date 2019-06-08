#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <vector>

#include "socket.h"

namespace Communication {
/**
 * @brief Lightweight wrapper for server socket
 */
class ServerSocket : public Socket
{
public:
    /**
     * @brief Initializes server, bind address and port to socket
     * @param t_port Port to listen on
     */
    ServerSocket(Constants::ipVersion t_ipVersion, unsigned short t_port);
    virtual ~ServerSocket() override;

    /**
     * @brief Starts listening for incoming connections
     */
    void listen();

    /**
     * @brief Accepts incoming connection
     */
    Socket accept();
    /**
     * @brief Sends data from buffer to all connected clients
     * @param Buffer with data to send
     * @param Length of buffer
     */
    void sendToAll(const PlainMessage& t_message);

    unsigned short getPort() const;
private:
    //struct sockaddr_in m_server;
    std::vector<std::unique_ptr<Socket>> m_clients;
    unsigned short m_port;
};

} // namespace Communication

#endif // SERVERSOCKET_H

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <netinet/in.h>
#include <netdb.h>
#include <string>

#include "constants.h"
#include "socket.h"

namespace Communication {

/**
 * @brief Lightweight wrapper for client socket
 */
class ClientSocket : public Socket
{
public:
    ClientSocket(Constants::ipVersion t_ipVersion);
    ~ClientSocket() override;
    /**
     * @brief Connects to specified server
     * @param t_ipAddress IP address of server to connect to
     * @param t_port Port of server
     */
    void connect(std::string t_ipAddress, std::string t_port);
private:
    Constants::ipVersion m_ipVersion;
    struct sockaddr_in m_server;

};

} // namespace Communication

#endif // CLIENTSOCKET_H

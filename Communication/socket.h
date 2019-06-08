#ifndef SOCKET_H
#define SOCKET_H

#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "constants.h"
#include "plainmessage.h"
namespace Communication {
/**
 * @brief Socket wrapper class
 */


class Socket
{
public:
    /**
     * @brief Initializes and open socket
     */
    Socket(Constants::ipVersion t_ipVersion);
    Socket(int t_sockfd);
    Socket(Socket&&);
    virtual ~Socket();
    Socket& operator=(const Socket&) = delete;

    /**
     * @brief Send data from buffer to socket
     * @param t_buffer Buffer with data to send
     * @param t_length Length of the buffer
     */
    void send(const char* t_buffer, size_t t_length) const;

    /**
     * @brief Sends serialized message
     * @param t_message
     */
    void sendMessage(const PlainMessage& t_message) const;

    /**
     * @brief Reads data from socket to buffer
     * @param t_buffer Buffer to read data to
     * @param t_length Length of data to read
     */
    void receive(char* t_buffer, size_t t_length);
    std::unique_ptr<PlainMessage> readMessage();

    /**
     * @brief Closes socket
     */
    void close();
    /**
     * @brief Getter for socket descriptor
     * @return Socket descriptor
     */
    int getSocketFD() const;

    /**
     * @brief Gets bound ip address if socket is connected
     * @return String representation of i.p. address
     */
    std::string getIPAddress() const;
private:
    int m_sockfd;
};

} // namespace Communication

#endif // SOCKET_H

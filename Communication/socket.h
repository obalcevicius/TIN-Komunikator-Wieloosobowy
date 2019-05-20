#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

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
    Socket();
    Socket(int t_sockfd);
    virtual ~Socket();
    Socket& operator=(const Socket&) = delete;

    /**
     * @brief Send data from buffer to socket
     * @param t_buffer Buffer with data to send
     * @param t_length Length of the buffer
     */
    void send(const char* t_buffer, size_t t_length);

    /**
     * @brief Reads data from socket to buffer
     * @param t_buffer Buffer to read data to
     * @param t_length Length of data to read
     */
    void receive(char* t_buffer, size_t t_length);

    /**
     * @brief Closes socket
     */
    void close();
    /**
     * @brief Getter for socket descriptor
     * @return Socket descriptor
     */
    int getSocketFD() const;
private:
    int m_sockfd;
};

} // namespace Communication

#endif // SOCKET_H

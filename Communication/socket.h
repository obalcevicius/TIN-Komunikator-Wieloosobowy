#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace Communication {

class Socket
{
public:
    Socket();
    Socket(int t_sockfd);
    virtual ~Socket();
    Socket& operator=(const Socket&) = delete;
    void send(const char* t_buffer, size_t t_length);
    void receive(char* t_buffer, size_t t_length);

    void close();
    int getSocketFD() const;
private:
    int m_sockfd;
};

} // namespace Communication

#endif // SOCKET_H

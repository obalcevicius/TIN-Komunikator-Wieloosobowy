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
    virtual ~Socket();
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    void close();
    int getSocketFD() const;
private:
    int m_sockfd;
};

} // namespace Communication

#endif // SOCKET_H

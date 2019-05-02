#include <iostream>
#include <exception>

#include "socket.h"


namespace Communication {

Socket::Socket() {
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sockfd == -1) {
        throw std::runtime_error("Couldn't create socket");
    }
}
Socket::~Socket() {
    close();
}
void Socket::close() {
    if(m_sockfd != -1) {
        ::close(m_sockfd);
    }
}
int Socket::getSocketFD() const {
    return m_sockfd;
}

} // namespace Communication

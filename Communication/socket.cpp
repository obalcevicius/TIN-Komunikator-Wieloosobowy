#include <iostream>
#include <exception>

#include "socket.h"


namespace Communication {

Socket::Socket() {
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sockfd == -1) {
        throw std::runtime_error("Couldn't create socket");
    }
    std::cout << "new socket created: " << m_sockfd << std::endl;
}
Socket::Socket(int t_sockfd) : m_sockfd(t_sockfd) {

}
Socket::~Socket() {
    close();
}
void Socket::close() {
    if(m_sockfd != -1) {
        ::close(m_sockfd);
    }
}

void Socket::send(const char* t_buffer, size_t t_length) {
    size_t offset = 0;
    long sValue;
    while(offset != t_length) {
        sValue = ::send(getSocketFD(), t_buffer + offset, t_length-offset, 0);
        if(sValue == -1 ) {
            throw std::runtime_error("Couln't send message");
        }
        std::cout << sValue << " bytes Sent\n";
        offset += static_cast<unsigned long>(sValue);
    }
}

void Socket::receive(char* t_buffer, size_t t_length) {
    long bytesRead = ::recv(getSocketFD(),t_buffer, t_length, 0);
    std::cout << "read " << bytesRead << "bytes\n";
    if(bytesRead == -1) {
        throw std::runtime_error("Couln't read message");
    }
}


int Socket::getSocketFD() const {
    return m_sockfd;
}

} // namespace Communication

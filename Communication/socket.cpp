#include <iostream>
#include <exception>
#include <cstdlib>
#include "constants.h"
#include "socket.h"
#include <arpa/inet.h>

namespace Communication {

Socket::Socket(Constants::ipVersion t_ipVersion) {
    if(t_ipVersion == Constants::ipVersion::IPv4) {
        std::cout << "CREATING IPv4 SOCKET\n";
        m_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    }
    else if(t_ipVersion == Constants::ipVersion::IPv6) {
         std::cout << "CREATING IPv6 SOCKET\n";
        m_sockfd = socket(PF_INET6, SOCK_STREAM, 0);
    }

    if(m_sockfd == -1) {
        throw std::runtime_error("Couldn't create socket");
    }
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
    std::cout << "SENDING " << t_buffer << " " << t_length <<std::endl;
    while(offset != t_length) {
        sValue = ::send(getSocketFD(), t_buffer + offset, t_length-offset, 0);
        if(sValue == -1 ) {
            throw std::runtime_error("Couln't send message");
        }
        offset += static_cast<unsigned long>(sValue);
    }
}

void Socket::receive(char* t_buffer, size_t t_length) {
    long bytesRead = ::recv(getSocketFD(),t_buffer, t_length, 0);
    if(bytesRead == -1) {
        throw std::runtime_error("Couln't read message");
    }
}

std::unique_ptr<PlainMessage> Socket::readMessage() {
    auto headerInfo = std::unique_ptr<char>(new char[9]);
    receive(headerInfo.get(), 8);
    headerInfo.get()[8] = '\0';
    unsigned long int hVAL = strtoul(headerInfo.get(), NULL, 16);
    std::cout << "BYTES TO READ " << ntohl(hVAL) << std::endl;
    auto msg_body = std::unique_ptr<char>(new char[ntohl(hVAL) +1 ]);
    msg_body.get()[ntohl(hVAL)] = '\0';
    receive(msg_body.get(), ntohl(hVAL));
    auto msgBody = std::unique_ptr<PlainMessage>( new PlainMessage(std::move(msg_body)));
    return msgBody;

}
int Socket::getSocketFD() const {
    return m_sockfd;
}

} // namespace Communication

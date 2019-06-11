#include <arpa/inet.h>
#include <bitset>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <typeinfo>


#include "constants.h"
#include "socket.h"


namespace Communication {

Socket::Socket() {};

Socket::Socket(Constants::ipVersion t_ipVersion) {
    if(t_ipVersion == Constants::ipVersion::IPv4) {
        m_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    }
    else if(t_ipVersion == Constants::ipVersion::IPv6) {
        m_sockfd = socket(PF_INET6, SOCK_STREAM, 0);
    }
    if(m_sockfd == -1) {
        throw std::runtime_error("Couldn't create socket");
    }
}

Socket::Socket(int t_sockfd) : m_sockfd(t_sockfd) {

}

Socket::Socket(Socket&& rhs) :  m_sockfd(rhs.m_sockfd)
{
    rhs.m_sockfd = -1;
}

Socket& Socket::operator=(Socket&& rhs) {
    m_sockfd = rhs.m_sockfd;
    rhs.m_sockfd = -1;
    return *this;
}


Socket::~Socket() {
    close();
}
void Socket::close() {
    if(m_sockfd != -1) {
        ::close(m_sockfd);
    }
}

void Socket::send(const char* t_buffer, size_t t_length) const{
    size_t offset = 0;
    long sValue;
    while(offset != t_length) {
        sValue = ::send(getSocketFD(), t_buffer + offset, t_length-offset, 0);
        if(sValue == -1 ) {
            throw std::runtime_error("Couln't send message");
        }
        offset += static_cast<unsigned long>(sValue);
    }
}

void Socket::receive(char* t_buffer, size_t t_length) {
    size_t offset = 0;
    long bytesRead;
    while(offset != t_length) {
        bytesRead = ::recv(getSocketFD(),t_buffer+offset, t_length-offset, 0);
        if(bytesRead == -1) {
            throw std::runtime_error("Couln't read message");
        }
        offset +=  static_cast<unsigned long>(bytesRead);
    }
}

void Socket::sendMessage(const PlainMessage &t_message) const {
    send(t_message.getMessageHeader(), Constants::headerSize);
    send(t_message.getMessageBody(), t_message.getMessageLength());
}

std::unique_ptr<PlainMessage> Socket::readMessage() {
    // first we read message size into a string, then we convert binary string form
    //  into number and then convert from network to host format
    char headerInfo[Constants::headerSize];
    receive(headerInfo, Constants::headerSize);
    std::string headerStr(headerInfo, Constants::headerSize);
    std::stringstream messageHeader(headerStr); std::bitset<32> messageSize;
    int messageType;
    messageHeader >> messageSize >> messageType;

    unsigned long int messageLength = messageSize.to_ulong();

    messageLength = ntohl(messageLength);
    auto msg_body = std::make_unique<char[]>(messageLength);

    receive(msg_body.get(), messageLength);
    auto msgBody = std::make_unique<PlainMessage>(std::move(msg_body), messageLength, messageType);

    return msgBody;
}

std::string Socket::getIPAddress() const {
    int s;
    struct sockaddr_storage address;
    socklen_t length = sizeof(address);

    s =  getsockname(getSocketFD(), reinterpret_cast<struct sockaddr*>(&address), &length);
    if(s == 0) {
        if(address.ss_family == AF_INET6) {
            char addr[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &reinterpret_cast<struct sockaddr_in6*>(&address)->sin6_addr.s6_addr, addr, INET6_ADDRSTRLEN);
            return std::string(addr);
        }
        else if(address.ss_family == AF_INET) {
            char addr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &reinterpret_cast<struct sockaddr_in*>(&address)->sin_addr, addr, INET_ADDRSTRLEN);
            return std::string(addr);
        }
    }
    return "";
}

int Socket::getSocketFD() const {
    return m_sockfd;
}

} // namespace Communication

#include "clientsocket.h"

#include <cstring>
#include <chrono>
#include <exception>
#include <thread>
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>



#include "constants.h"

namespace Communication {

ClientSocket::ClientSocket() {};

ClientSocket::ClientSocket(Constants::ipVersion t_ipVersion) :
    Socket(t_ipVersion),
    m_ipVersion(t_ipVersion)
{

}

ClientSocket::ClientSocket(ClientSocket&& rhs) :
    Socket (std::move(rhs))
{
}

ClientSocket& ClientSocket::operator=(ClientSocket&& rhs) {
    m_sockfd = rhs.m_sockfd;
    m_ipVersion = rhs.m_ipVersion;
    rhs.m_sockfd = -1;
    return *this;

}





void ClientSocket::connect(std::string t_serverAddress, std::string t_serverPort) {
    struct addrinfo hints, *res;
    int connection;
    std::memset(&hints, 0, sizeof hints);

    if(m_ipVersion == Constants::ipVersion::IPv4) {
        hints.ai_family = AF_INET;
    }
    else if(m_ipVersion == Constants::ipVersion::IPv6) {
        hints.ai_family = AF_INET6;
    }

    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(t_serverAddress.c_str(), t_serverPort.c_str(), &hints, &res);
    connection = ::connect(getSocketFD(), res->ai_addr, res->ai_addrlen);
    std::cout << "CONNECT: " << connection << "\n";
    if(connection == -1) {
        switch (errno) {
        case ETIMEDOUT : throw std::runtime_error("Connection timeout");
        case ECONNREFUSED : throw std::runtime_error("Connection refused");
        case ENETUNREACH : throw std::runtime_error("Network is unreachable");
        default: throw std::runtime_error(strerror(errno));
        }
    }
    else {
        std::cout << " Connection established" << std::endl;
    }
}

ClientSocket::~ClientSocket() {
    close();
}

} // namespace Communication

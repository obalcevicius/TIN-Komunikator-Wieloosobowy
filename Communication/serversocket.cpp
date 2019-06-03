#include <errno.h>
#include <cstring>
#include <chrono>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "constants.h"
#include "serversocket.h"
namespace Communication {

ServerSocket::ServerSocket(Constants::ipVersion t_ipVersion, unsigned short t_port) : Socket(t_ipVersion) {
    int bind;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    if(t_ipVersion == Constants::ipVersion::IPv4) {
        hints.ai_family = AF_INET;
    }
    else if(t_ipVersion == Constants::ipVersion::IPv6) {
        hints.ai_family = AF_INET6;
    }
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, std::to_string(t_port).c_str() , &hints, &res); // change NULL to specific address if required, drop AI_PASSIVE FLAG above

    bind = ::bind(getSocketFD(), res->ai_addr, res->ai_addrlen);

    if(bind == -1) {
        switch (errno) {
        case EACCES : throw std::runtime_error("Permission Denied");
        case EBADF : throw  std::runtime_error("Unvalid socket descriptor");
        case EINVAL : throw std::runtime_error("Socket already bound");
        case EADDRINUSE: throw std::runtime_error("Address already in use");
        default: throw  std::runtime_error("Couldn't bind address to socket");
        }
    }
}

ServerSocket::~ServerSocket() {

}

void ServerSocket::listen() {
    int listen;
    listen = ::listen(getSocketFD(), 10);
    if(listen == -1) {
        switch (errno) {
        case EADDRINUSE: throw std::runtime_error("Another socket is listening on this port");
        case EBADF : throw std::runtime_error("Sock FD is not a valid descriptor");
        case ENOTSOCK: throw std::runtime_error("Sock FD is not a socket");
        default: throw std::runtime_error("Couldn't start listening");

        }
    }
}

Socket ServerSocket::accept() {
    int newConnectionFD = 0;
    struct sockaddr_storage their_addr;
    int addrSize = sizeof their_addr;

    newConnectionFD = ::accept(getSocketFD(), reinterpret_cast<struct sockaddr*>(&their_addr), reinterpret_cast<socklen_t*>(&addrSize));


    if(newConnectionFD == -1) {
        switch (errno) {
        case EINVAL : throw std::runtime_error("Socket is not listening for connections");
        case ECONNABORTED : throw std::runtime_error("Connection aborted");
        case ENOTSOCK : throw std::runtime_error("Sock FD does not refer to socket");
        case EPROTO : throw std::runtime_error("Protocol error");
        }
    }
    // todo: check who has connected
    if(their_addr.ss_family == AF_INET) {
        char addr[INET_ADDRSTRLEN];
        std::cout << "CONNECTED : " << inet_ntop(AF_INET, &reinterpret_cast<struct sockaddr_in*>(&their_addr)->sin_addr, addr, INET_ADDRSTRLEN) << std::endl;
        std::cout << "CONNECTED : " << ntohs(reinterpret_cast<struct sockaddr_in*>(&their_addr)->sin_port) << std::endl;
    }
    else if (their_addr.ss_family == AF_INET6) {
        char addr[INET6_ADDRSTRLEN];
        std::cout << "CONNECTED : " << inet_ntop(AF_INET6, &reinterpret_cast<struct sockaddr_in6*>(&their_addr)->sin6_addr, addr, INET6_ADDRSTRLEN) << std::endl;
        std::cout << "CONNECTED : " << ntohs(reinterpret_cast<struct sockaddr_in6*>(&their_addr)->sin6_port) << std::endl;
    }
    return Socket(newConnectionFD);
}
void ServerSocket::sendToAll(const PlainMessage& t_message) {
    for(auto& client : m_clients) {
        client->sendMessage(t_message);
    }
}


} // namespace Communication

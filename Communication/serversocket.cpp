#include "serversocket.h"
#include <errno.h>
#include <string.h>
#include <chrono>
#include <thread>
namespace Communication {

ServerSocket::ServerSocket(unsigned short t_port) : Socket() {
    int bind;
    m_server.sin_family = AF_INET;
    m_server.sin_addr.s_addr = INADDR_ANY;
    m_server.sin_port = static_cast<in_port_t>(htons(t_port));

    bind = ::bind(getSocketFD(), reinterpret_cast<struct sockaddr*>(&m_server), sizeof m_server);

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

void ServerSocket::accept() {
    int newConnectionFD = 0;
    struct sockaddr_storage their_addr;
    int addrSize = sizeof their_addr;

    newConnectionFD = ::accept(getSocketFD(), reinterpret_cast<struct sockaddr*>(&their_addr), reinterpret_cast<socklen_t*>(&addrSize));

    // todo: check who has connected

    if(newConnectionFD == -1) {
        switch (errno) {
        case EINVAL : throw std::runtime_error("Socket is not listening for connections");
        case ECONNABORTED : throw std::runtime_error("Connection aborted");
        case ENOTSOCK : throw std::runtime_error("Sock FD does not refer to socket");
        case EPROTO : throw std::runtime_error("Protocol error");
        }
    }
    std::cout << newConnectionFD <<" connected\n";
    m_clients.emplace_back(newConnectionFD);
}
void ServerSocket::sendToAll(const char* t_buffer, size_t t_length) {
    for(auto& client : m_clients) {
        client.send(t_buffer, t_length);
    }
}


} // namespace Communication

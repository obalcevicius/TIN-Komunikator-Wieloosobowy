#include "clientsocket.h"

#include <cstring>
#include <chrono>
#include <exception>
#include <thread>
#include <iostream>
#include <memory>
#include <unistd.h>

namespace Communication {

ClientSocket::ClientSocket() : Socket() {

}

void ClientSocket::connect(std::string t_serverAddress, std::string t_serverPort) {
    struct addrinfo hints, *res;
    int connection;
    std::memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(t_serverAddress.c_str(), t_serverPort.c_str(), &hints, &res);
    connection = ::connect(getSocketFD(), res->ai_addr, res->ai_addrlen);
    if(connection == -1) {
        switch (errno) {
        case ETIMEDOUT : throw std::runtime_error("Connection timeout");
        case ECONNREFUSED : throw std::runtime_error("Connection refused");
        case ENETUNREACH : throw std::runtime_error("Network is unreachable");
        default: throw std::runtime_error("Connection couldn't be established");
        }
    }
    else {
        std::cout << " Connection established" << std::endl;
    }
}

ClientSocket::~ClientSocket() {

}

} // namespace Communication

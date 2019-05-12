#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "connection.h"
#include "clientsocket.h"
#include "serversocket.h"


int main(int argc, char* argv[]) {
    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    if(*argv[1] == 'S') {
        Communication::ServerSocket serverSock(atoi(argv[2]));
        serverSock.listen();
        serverSock.accept();//serverSock.accept();//serverSock.accept();
        std::string msg;
        std::cin >> msg;
        serverSock.sendToAll(msg.c_str(), msg.length());

    }
    else if(*argv[1] == 'C') {
        Communication::ClientSocket clientSock;
        clientSock.connect("localhost", std::string(argv[2]));
        std::this_thread::sleep_for(std::chrono::seconds(5));
        auto msg = std::unique_ptr<char>(new char[20]);
        msg.get()[19] = '\0';
        clientSock.receive(msg.get(), 19);
        clientSock.receive(msg.get(), 19);
        std::cout << std::string(msg.get()) << std::endl;



    }




    return 0;
}

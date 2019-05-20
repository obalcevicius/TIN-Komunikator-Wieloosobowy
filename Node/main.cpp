#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

#include "connection.h"
#include "clientsocket.h"
#include "commandmessage.h"
#include "serversocket.h"




int main(int argc, char* argv[]) {
    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    if(argc != 3) {
        return 0;
    }
    if(*argv[1] == 'S') {
        Communication::ServerSocket serverSock(atoi(argv[2]));
        serverSock.listen();
        serverSock.accept();
        std::string command;
        std::cout << "Please enter commands to send to client. Enter '0' to quit" << std::endl;
        do {
            std::getline(std::cin, command);
            Communication::CommandMessage msg(command);
            std::stringstream serializer;
            msg.serialize(serializer);
            serverSock.sendToAll(serializer.str().data(), serializer.str().length());
        }
        while(command != "0");
    }

    else if(*argv[1] == 'C') {
        Communication::ClientSocket clientSock;
        clientSock.connect("localhost", std::string(argv[2]));
        auto msg = std::unique_ptr<char>(new char[128]);
        do {
            std::memset(msg.get(), 0, 128);
            clientSock.receive(msg.get(), 128);
            msg.get()[127] = '\0';
            Communication::CommandMessage revMes;
            //revMes.deserialize(msg.get());
            std::cout << std::string(msg.get()) << std::endl;
        }
        while(msg.get()[1] != '0');
    }






    return 0;
}

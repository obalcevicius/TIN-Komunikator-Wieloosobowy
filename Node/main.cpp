#include <cstdlib>
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

    if(*argv[1] == 'S') {
        Communication::ServerSocket serverSock(atoi(argv[2]));
        serverSock.listen();
        serverSock.accept();

        Communication::CommandMessage msg("SENDING NEW COMMAND MESSAGE\n");
        std::stringstream serializer;
        msg.serialize(serializer);
        serverSock.sendToAll(serializer.str().data(), serializer.str().length());

    }
    else if(*argv[1] == 'C') {
        Communication::ClientSocket clientSock;
        clientSock.connect("localhost", std::string(argv[2]));
        auto msg = std::unique_ptr<char>(new char[128]);
        msg.get()[127] = '\0';
        clientSock.receive(msg.get(), 128);

        std::cout << std::string(msg.get()) << std::endl;
    }





    return 0;
}

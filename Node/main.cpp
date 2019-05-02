#include <iostream>


#include "clientsocket.h"
#include "serversocket.h"


int main(int argc, char* argv[]) {
    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    if(*argv[1] == 'S') {
        Communication::ServerSocket serverSock(2500);
        serverSock.listen();
        serverSock.accept();
    }
    else if(*argv[1] == 'C') {
        Communication::ClientSocket clientSock;
        std::cout <<"C-tor ended\n";
        clientSock.connect("127.0.0.1" , "2500");
    }



    std::cout << "Hello World!" << std::endl;
    return 0;
}

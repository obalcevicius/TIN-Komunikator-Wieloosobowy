#include <cstdlib>
#include <cstring>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <thread>

#include <bitset>

#include "clientsocket.h"
#include "commandmessage.h"
#include "constants.h"
#include "commandmessage.h"
#include "participationmessage.h"
#include "node.h"
#include "serversocket.h"

#include <limits>


int main(int argc, char* argv[]) {

    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    if(argc != 3) {
        return 0;
    }
    if(*argv[1] == 'S') {
        Node myNode(Communication::Constants::ipVersion::IPv6, "localhost", argv[2]);
        myNode.startListening();


        std::cout << "Please enter commands to send to client. Enter '0' to quit" << std::endl;
        do {
            std::string command;
            std::getline(std::cin, command);
            if(!command.compare("stop")) {
                myNode.stopListening();
                continue;
            }
            else if(!command.compare("0")) {
                break;
            }
            NodeInfo nd("127.0.0.2", "2500");
            Communication::ParticipationMessage msg(nd, command);
            myNode.broadcastMessage(msg.serialize());

        }
        while(true);
    }

    else if(*argv[1] == 'C') {
        Communication::ClientSocket clientSock(Communication::Constants::ipVersion::IPv6);
        clientSock.connect("localhost", std::string(argv[2]));
        auto msg = std::unique_ptr<char>(new char[128]);
        do {

            auto msg = clientSock.readMessage();

            Communication::ParticipationMessage labas;
            labas.deserialize(std::move(msg));

            std::cout <<"MESSAGE: " << labas.getHeader() << " " << labas.getCommand() << " "
                << labas.getNodeInfo().getIPAddress() << "  " << labas.getNodeInfo().getPort() << std::endl;
        }
        while(msg.get()[1] != '0');
    }






    return 0;
}

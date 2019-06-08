#include <cstdlib>
#include <cstring>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <thread>

#include <sys/socket.h>

#include <bitset>

#include "clientsocket.h"
#include "commandmessage.h"
#include "constants.h"
#include "commandmessage.h"
#include "participationmessage.h"
#include "groupmembersmessage.h"
#include "node.h"
#include "nodeinfo.h"
#include "nodegroup.h"
#include "serversocket.h"

#include <typeinfo>
#include <limits>


int main(int argc, char* argv[]) {

    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    if(argc != 3) {
        return 0;
    }
    if(*argv[1] == 'S') {
//        Node myNode(Communication::Constants::ipVersion::IPv6, "localhost", argv[2]);
//        myNode.startListening();
        Communication::ServerSocket server(Communication::Constants::ipVersion::IPv6, atoi(argv[2]));
        server.listen();
        auto sock = server.accept();
        auto buff = sock.readMessage();
        auto msg = buff->getMessage();
        std::cout << dynamic_cast<Communication::ParticipationMessage*>(msg.get())->getCommand() << std::endl;
        std::cout <<dynamic_cast<Communication::ParticipationMessage*>(msg.get())->getNodeInfo().getIPAddress() <<std::endl;
        std::cout << dynamic_cast<Communication::ParticipationMessage*>(msg.get())->getNodeInfo().getPort() <<std::endl;
        //std::cout << "Please enter commands to send to client. Enter '0' to quit" << std::endl;
        do {
            std::this_thread::sleep_for(std::chrono::seconds(1000));

        }
        while(true);
    }

    else if(*argv[1] == 'C') {
        //Node myNode(Communication::Constants::ipVersion::IPv6, "localhost", "2501");

        //myNode.joinGroup("localhost", argv[2]);
        Communication::ClientSocket clientSock(Communication::Constants::ipVersion::IPv6);
        Communication::ServerSocket serverSock(Communication::Constants::ipVersion::IPv6, 2500);




        clientSock.connect("localhost", std::string(argv[2]));
        auto msg = std::unique_ptr<char>(new char[128]);
        do {
            std::string command;

            NodeGroup ndg;
            std::getline(std::cin, command);
            for (int i = 0; i <3; ++i) {
                std::string ip, port;
                std::getline(std::cin, ip);
                std::getline(std::cin, port);
                ndg.addMember(NodeInfo(ip, port));
            }
            for(const auto& member : ndg.getMembers()) {
                std::cout << member.getIPAddress() << " " << member.getPort() << std::endl;
            }
            //                        if(!command.compare("stop")) {
            //                            myNode.stopListening();
            //                            continue;
            //                        }
            if(!command.compare("0")) {
                break;
            }

            Communication::GroupMembersMessage msg(command, "members", ndg.getMembers() );
            clientSock.sendMessage(msg.serialize());

        }
        while(msg.get()[1] != '0');
    }






    return 0;
}

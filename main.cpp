#include <cstdlib>
#include <cstring>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <thread>

#include <bitset>

#include "message.h"
#include "plainmessage.h"
#include "groupmessage.h"
#include "messageType.h"
#include "clientsocket.h"
#include "constants.h"
#include "commandmessage.h"
#include "node.h"
#include "serversocket.h"
#include "nodegroup.h"

#include <limits>
using namespace Node;
using namespace Communication;

int main(int argc, char* argv[]) {

    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    if(*argv[1] == 'S') {
	    if(argc != 3) {
		return 0;
	    }
        Node::Node myNode(Communication::Constants::ipVersion::IPv4, "localhost", argv[2]);
        myNode.acceptConnection();

	NodeGroup grupa;
	grupa.addMember(NodeInfo("ADRES1", "PORT1"));
	grupa.addMember(NodeInfo("ADRES2", "PORT2"));
	grupa.addMember(NodeInfo("ADRES3", "PORT3"));
	grupa.addMember(NodeInfo("ADRES4", "PORT4"));
	grupa.addMember(NodeInfo("ADRES5", "PORT5"));
	bool continuation = true;
        do {
	    std::string command;
		std::cout << "Podaj komendę: ";
	    std::getline(std::cin, command);
		if (command == "stop") continuation = false;
		GroupMessage msg(grupa, command);
		PlainMessage mess = msg.serialize();
	std::cout << "Ciało wiadomości: " << std::endl << 
		mess.getBody()
		<< std::endl;
		mess.pack();
	
            myNode.broadcastMessage(mess);
		mess.destroy();
        }
        while(continuation);
    }

    else if(*argv[1] == 'C') {

	    if(argc != 4) {
		return 0;
	    }
        Communication::ClientSocket clientSock(Communication::Constants::ipVersion::IPv4);
        clientSock.connect(std::string(argv[3]), std::string(argv[2]));
	bool continuation = true;	
        do {
            std::unique_ptr<PlainMessage> msg = clientSock.readMessage();
	    msg->unpack();
	std::cout << "Ciało wiadomości: " << std::endl << 
		msg->getBody() << 
		std::endl;
	    Message * mess = Message::deserialize(*msg.get());
	    msg.get()->destroy();
	    if(mess->typeCheck() == groupMess) {
		std::cout << "Tak - jest group-message" << std::endl;
		GroupMessage * gMess = static_cast<GroupMessage *>(mess);
		//przez powyższą linijkę nie odważyłem się
		//zrobić smart pointera
		gMess->getGroup().present();
		std::string com = gMess->getCommand();
		std::cout << "Oto komenda: " << com << std::endl;
		if (com == "stop") continuation = false;
		delete mess;
	    }
	    else {
		std::cout << "To nie jest group-message" << std::endl;
	    }
        }
        while(continuation);
    }






    return 0;
}

#ifndef ONEMESSAGE_H
#define ONEMESSAGE_H

#include <string>
#include "message.h"
#include "../Node/nodeinfo.h"

namespace Communication {

class OneMessage: public Message {

	public:
	OneMessage();
	OneMessage(PlainMessage mess);
	void virt_deserialize(PlainMessage mess);
	OneMessage(const Node::NodeInfo & node, std::string command);
	PlainMessage serialize();
	Node::NodeInfo getNode();
	std::string getCommand();
	MessageType typeCheck();
	
	private:
	Node::NodeInfo one;
	std::string command;
}; 
} //namespace Communication
	
#endif //ONEMESSAGE_H	

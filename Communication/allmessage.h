#ifndef ALLMESSAGE_H
#define ALLMESSAGE_H

#include <string>
#include "message.h"
#include "../Node/nodegroup.h"

namespace Communication {

class AllMessage: public Message {
	
	public:
	AllMessage();
	AllMessage(PlainMessage mess);
	void virt_deserialize(PlainMessage mess);
	AllMessage(const Node::NodeGroup & group, 
		 std::string command);
	PlainMessage serialize();
	MessageType typeCheck();

	private:
	Node::NodeGroup group;
	Node::NodeGroup subscribers;
	std::string command;
};

} //namespace Communication

#endif //ALLMESSAGE_H

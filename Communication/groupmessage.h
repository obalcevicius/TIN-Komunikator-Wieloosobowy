#ifndef GROUPMESSAGE_H
#define GROUPMESSAGE_H

#include "message.h"
#include <string>
#include "../Node/nodegroup.h" //popraw to Olgierd

namespace Communication {

class GroupMessage: public Message {

	public:
	GroupMessage();
	GroupMessage(PlainMessage mess);
	void virt_deserialize(PlainMessage mess);
	GroupMessage(const Node::NodeGroup & group, std::string command);
	PlainMessage serialize();
	MessageType typeCheck();
	Node::NodeGroup getGroup();
	std::string getCommand();
	private:
	Node::NodeGroup group;
	std::string command;
};	

} //namespace Communication

#endif //GROUPMESSAGE_H

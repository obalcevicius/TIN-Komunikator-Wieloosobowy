#ifndef GROUPMESSAGE_H
#define GROUPMESSAGE_H

#include "commandmessage.h"
#include <string>
#include "../Node/nodegroup.h" //popraw to Olgierd

namespace Communication {

class GroupMessage: public CommandMessage {

	public:
	GroupMessage();
	GroupMessage(PlainMessage t_mess);
	virtual void virt_deserialize(PlainMessage t_mess);
	GroupMessage(const Node::NodeGroup & t_group, std::string t_command);
	virtual PlainMessage serialize();
	virtual MessageType typeCheck();
	Node::NodeGroup getGroup();

	protected:
	Node::NodeGroup m_group;
};	

} //namespace Communication

#endif //GROUPMESSAGE_H

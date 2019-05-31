#ifndef ALLMESSAGE_H
#define ALLMESSAGE_H

#include <string>
#include "groupmessage.h"
#include "../Node/nodegroup.h"

namespace Communication {

class AllMessage: public GroupMessage {
	
	public:
	AllMessage();
	AllMessage(PlainMessage t_mess);
	virtual void virt_deserialize(PlainMessage t_mess);
	AllMessage(const Node::NodeGroup & t_group, 
		 const Node::NodeGroup & t_subscribers,
		 std::string t_command);
	virtual PlainMessage serialize();
	virtual MessageType typeCheck();
	Node::NodeGroup getSubscribers();

	protected:
	Node::NodeGroup m_subscribers;
};

} //namespace Communication

#endif //ALLMESSAGE_H

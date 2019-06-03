#ifndef ONEMESSAGE_H
#define ONEMESSAGE_H

#include <string>
#include "commandmessage.h"
#include "nodeinfo.h"

namespace Communication {

class OneMessage: public CommandMessage {

	public:
	OneMessage();
	OneMessage(PlainMessage t_mess);
	virtual void virt_deserialize(PlainMessage t_mess);
	OneMessage(const Node::NodeInfo & t_node, std::string t_command);
	virtual PlainMessage serialize();
	Node::NodeInfo getNode();
	virtual MessageType typeCheck();
	
	protected:
	Node::NodeInfo m_one;
}; 

} //namespace Communication
	
#endif //ONEMESSAGE_H	

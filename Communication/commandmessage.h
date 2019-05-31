#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include <string>
#include "message.h"

namespace Communication {

class CommandMessage: public Message {

	public:
	CommandMessage();
	CommandMessage(PlainMessage t_mess);
	virtual void virt_deserialize(PlainMessage t_mess);
	CommandMessage(std::string t_command);
	virtual PlainMessage serialize();
	virtual MessageType typeCheck();
	std::string getCommand();
	
	protected:
	std::string m_command;
};	

} //namespace Communication

#endif //COMMANDMESSAGE_H

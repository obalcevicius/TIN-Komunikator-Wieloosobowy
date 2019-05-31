#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include <string>
#include "message.h"

namespace Communication {

class CommandMessage: public Message {

	public:
	CommandMessage();
	CommandMessage(PlainMessage mess);
	void virt_deserialize(PlainMessage mess);
	CommandMessage(std::string command);
	PlainMessage serialize();
	MessageType typeCheck();
	private:
	std::string command;
};	

} //namespace Communication

#endif //COMMANDMESSAGE_H

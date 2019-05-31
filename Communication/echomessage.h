#ifndef ECHOMESSAGE_H
#define ECHOMESSAGE_H

#include "message.h"

namespace Communication {

class EchoMessage: public Message {

	public:
	EchoMessage();
	EchoMessage(PlainMessage mess);
	void virt_deserialize(PlainMessage mess);
	EchoMessage(char command);
	PlainMessage serialize();
	MessageType typeCheck();
	private:
	char command;
};	

} //Communication

#endif //ECHOMESSAGE_H

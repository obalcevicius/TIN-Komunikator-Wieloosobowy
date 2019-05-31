#ifndef ECHOMESSAGE_H
#define ECHOMESSAGE_H

#include "message.h"

namespace Communication {

class EchoMessage: public Message {

	public:
	EchoMessage();
	EchoMessage(PlainMessage t_mess);
	virtual void virt_deserialize(PlainMessage t_mess);
	EchoMessage(char t_command);
	virtual PlainMessage serialize();
	virtual MessageType typeCheck();
	char getCommand();

	private:
	char m_command; //'?' lub '.'
};	

} //Communication

#endif //ECHOMESSAGE_H

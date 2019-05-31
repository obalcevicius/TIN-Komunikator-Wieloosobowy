#include "message.h"
#include "allmessage.h"
#include "echomessage.h"
#include "commandmessage.h"
#include "groupmessage.h"
#include "onemessage.h"

namespace Communication {

	Message * Message::createMessage(Header * t_head) {
		switch (t_head->getType()) {
			case commandMess: return new CommandMessage();
			case echoMess: return new EchoMessage();
			case oneMess: return new OneMessage();
			case groupMess: return new GroupMessage();
			case allMess: return new AllMessage();
			//case dataMess: return new DataMessage();
		//itd.
		}
	}
	Message * Message::transform(PlainMessage t_oldMessage) {
		//tu właśnie przekazuję ją przez wartość
		Message * r_newMessage = 
		createMessage(t_oldMessage.getHeader());
		r_newMessage->virt_deserialize(t_oldMessage);
		return r_newMessage;
	}

	Message * Message::deserialize(PlainMessage t_mess) {
		switch (t_mess.getHeader()->getType()) {
			case commandMess: return new CommandMessage(t_mess);
			case echoMess: return new EchoMessage(t_mess);
			case oneMess: return new OneMessage(t_mess);
			case groupMess: return new GroupMessage(t_mess);
			case allMess: return new AllMessage(t_mess);
			//case dataMess: return new DataMessage(t_mess);
		//itd.
		}
	}
	/* - Message nic nie wie o wysyłaniu
	void send(NodeInfo node) {
		PlainMessage mess = serialize();
		ClientSocket sock;
		sock.connect(node);
		mess.sendMe(sock);
		//sock się zamyka
	}*/	
} //namespace communication

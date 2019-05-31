#include "message.h"
#include "allmessage.h"
#include "echomessage.h"
#include "commandmessage.h"
#include "groupmessage.h"
#include "onemessage.h"

namespace Communication {

	Message * Message::createMessage(Header * head) {
		switch (head->getType()) {
			case commandMess: return new CommandMessage();
			case echoMess: return new EchoMessage();
			case oneMess: return new OneMessage();
			case groupMess: return new GroupMessage();
			case allMess: return new AllMessage();
			//case dataMess: return new DataMessage();
		//itd.
		}
	}
	Message * Message::transform(PlainMessage oldMessage) {
		Message * newMessage = createMessage(oldMessage.getHeader());
		newMessage->virt_deserialize(oldMessage);
		return newMessage;
	}

	Message * Message::deserialize(PlainMessage mess) {
		switch (mess.getHeader()->getType()) {
			case commandMess: return new CommandMessage(mess);
			case echoMess: return new EchoMessage(mess);
			case oneMess: return new OneMessage(mess);
			case groupMess: return new GroupMessage(mess);
			case allMess: return new AllMessage(mess);
			//case dataMess: return new DataMessage(mess);
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

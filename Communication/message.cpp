#include "message.h"
	Message * Message::createMessage(Header * head) {
		switch (head->getType()) {
			case ...: return new CommandMessage();
			case ...: return new TokenMessage();
		//itd.
		}
	}
	Message * Message::transform(PlainMessage oldMessage) {
		Message * newMessage = createMessage(oldMessage.getHeader());
		newMessage->virt_deserialize(oldMessage);
		return Message;
	}

	Message * Message::deserialize(PlainMessage mess) {
		switch (mess.getHeader()->getType()) {
			case ...: return new CommandMessage(mess);
			case ...: return new TokenMessage(mess);
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

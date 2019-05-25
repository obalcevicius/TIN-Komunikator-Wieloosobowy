class Message {
	static Message * createMessage(Header * head) {
		switch (head->getType()) {
			case ...: return new CommandMessage();
			case ...: return new TokenMessage();
		//itd.
		}
	}
	static Message * transform(PlainMessage oldMessage) {
		Message * newMessage = createMessage(oldMessage.getHeader());
		newMessage->deserialize(oldMessage);
		return Message;
	}
	virtual void deserialize(PlainMessage mess) = 0;
	virtual PlainMessage serialize() = 0;
	void send(NodeInfo node) {
		PlainMessage mess = serialize();
		ClientSocket sock;
		sock.connect(node);
		mess.sendMe(sock);
		//sock się zamyka
	}	
};

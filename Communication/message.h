#pragma once
#include "plainMessage.h"
#include "messageType.h"
class Message {
	static Message * createMessage(Header * head);
	//tu są oba schematy deserializacji uwzględnione
	static Message * transform(PlainMessage oldMessage);

	static Message * deserialize(PlainMessage mess);
	virtual void virt_deserialize(PlainMessage mess) = 0;
	virtual PlainMessage serialize() = 0;
	virtual MessageType presentType() = 0;
	//void send(NodeInfo node);
};

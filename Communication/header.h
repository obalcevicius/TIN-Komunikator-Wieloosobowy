#pragma once
#include "messageType.h"
#include <arpa/inet.h> //bodajże ten
namespace Communication {

class Header {
	//pisz sobie gettery i settery jak chcesz i tak Message
	//się dobiera do wszyskich pól
	public:
	Header();
	Header(MessageType type);
	MessageType type; //tu trzeba stworzyć enum
	int restSize;
	int getOriginalNum();
	Header flip();
	Header prepare();
	MessageType getType();
};

} //namespace Communication

#pragma once
#include "messageType.h"
#include <arpa/inet.h> //bodajże ten
class Header {
	//pisz sobie gettery i settery jak chcesz i tak Message
	//się dobiera do wszyskich pól
	public:
	MessageType type; //tu trzeba stworzyć enum
	int restSize;
	int getOriginalNum();
	Header flip();
	Header prepare();
};

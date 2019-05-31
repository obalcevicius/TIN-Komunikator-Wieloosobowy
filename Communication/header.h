#pragma once
#include "messageType.h"
#include <arpa/inet.h> //bodajże ten
namespace Communication {

class Header {
	//pisz sobie gettery i settery jak chcesz i tak Message
	//się dobiera do wszyskich pól
	public:
	Header();
	Header(MessageType t_type);
	int getOriginalNum();
	int getActualNum(); //nie użyta nigdzie dotąd
	Header pack();
	Header unpack();
	MessageType getType();

	private:
	MessageType m_type; //tu trzeba stworzyć enum
	int m_restSize;
};

} //namespace Communication

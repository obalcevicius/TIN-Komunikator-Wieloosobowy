#include "header.h" 

namespace Communication {

	Header::Header():
		type(noMess), restSize(0) {
	}
	Header::Header(MessageType type):
		type(type), restSize(0) {
	}
	int Header::getOriginalNum() {
		return ::ntohl(restSize);
	}
	Header Header::flip() {
		Header flipped;
		flipped.type = 
		(MessageType)::ntohl((uint32_t)type); //pytanie czy to na nich
						// będzie działać
		flipped.restSize = ::ntohl(restSize);
		return flipped;
	}
	Header Header::prepare() {
		Header prepared;
		prepared.type =  //pytanie czy to na nich
						// będzie działać
		(MessageType)::htonl((uint32_t)type); //pytanie czy to na nich
		prepared.restSize = ::htonl(restSize);
		return prepared;
	}
	MessageType Header::getType() {
		return type;
	}

} //namespace Communication

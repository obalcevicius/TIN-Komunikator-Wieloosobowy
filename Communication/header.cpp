#include "header.h"
	int Header::getOriginalNum() {
		return ::ntohl(restSize);
	}
	Header Header::flip() {
		Header flipped;
		flipped.type = 
		(MessageType)::ntohl((uint32_t)type); //pytanie czy to na nich
						// będzie działać
		flipped.restSize = ::ntohl(restSize);
	}
	Header Header::prepare() {
		Header prepared;
		prepared.type =  //pytanie czy to na nich
						// będzie działać
		(MessageType)::htonl((uint32_t)type); //pytanie czy to na nich
		prepared.restSize = ::htonl(restSize);
	}


#include "header.h" 

namespace Communication {

	Header::Header():
		m_type(noMess), m_restSize(0) {
	}
	Header::Header(MessageType t_type):
		m_type(t_type), m_restSize(0) {
	}
	int Header::getOriginalNum() {
		return ::ntohl(m_restSize);
	}
	int Header::getActualNum() {
		return m_restSize;
	}
	Header Header::unpack() {
		Header r_changed;
		r_changed.m_type = 
		(MessageType)::ntohl((uint32_t)m_type); //pytanie czy to na nich
						// będzie działać
		r_changed.m_restSize = ::ntohl(m_restSize);
		return r_changed;
	}
	Header Header::pack() {
		Header r_changed;
		r_changed.m_type =  //pytanie czy to na nich
						// będzie działać
		(MessageType)::htonl((uint32_t)m_type); //pytanie czy to na nich
		r_changed.m_restSize = ::htonl(m_restSize);
		return r_changed;
	}
	MessageType Header::getType() {
		return m_type;
	}

} //namespace Communication

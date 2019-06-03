#include "onemessage.h"
#include <sstream>

using std::string;
using std::stringstream;
using Node::NodeInfo;

namespace Communication {

	OneMessage::OneMessage(): m_one("", "")  {
	}
	OneMessage::OneMessage(PlainMessage t_mess): m_one("", "") {
		virt_deserialize(t_mess); //to trzeba będzie tu też wpisać
		//w innych wiadomościach
	}
	void OneMessage::virt_deserialize(PlainMessage t_mess) {
		std::stringstream strm(
		t_mess.getBody());
		strm >> m_one >> m_command;
	}
	OneMessage::OneMessage(const NodeInfo & t_node, string t_command):
		CommandMessage(t_command), m_one(t_node) {
	}
	PlainMessage OneMessage::serialize() {
		PlainMessage r_mess(oneMess);
		stringstream strm;
		strm << m_one << m_command;
		r_mess.setBody(strm.str());
		return r_mess;
	}
	
	NodeInfo OneMessage::getNode() {
		return m_one;
	}
	MessageType OneMessage::typeCheck() {
		return oneMess;
	}
} //namespace Communication
			

#include "allmessage.h"
#include <sstream>
using std::string;
using std::stringstream;
using Node::NodeGroup;

namespace Communication {

	AllMessage::AllMessage() {
	}
	AllMessage::AllMessage(PlainMessage t_mess) {
		virt_deserialize(t_mess);
	}
	void AllMessage::virt_deserialize(PlainMessage t_mess) {
		stringstream strm(
		t_mess.getBody());
		strm >> m_group >> m_subscribers >> m_command;
	}
	AllMessage::AllMessage(const NodeGroup & t_group,
		const NodeGroup & t_subscribers,
		std::string t_command): GroupMessage(t_group, t_command),
		m_subscribers(t_subscribers) {
	}
	PlainMessage AllMessage::serialize() {
		PlainMessage r_mess(allMess);
		stringstream strm;
		strm << m_group << m_subscribers << m_command;
		r_mess.setBody(strm.str());
		return r_mess;
	}
	MessageType AllMessage::typeCheck() {
		return allMess;
	}
	NodeGroup AllMessage::getSubscribers() {
		return m_subscribers;
	}
} //namespace Communication

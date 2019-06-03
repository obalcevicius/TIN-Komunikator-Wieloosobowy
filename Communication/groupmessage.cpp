#include "groupmessage.h"
#include <sstream>
using std::string;
using std::stringstream;
using Node::NodeGroup;
namespace Communication {

	GroupMessage::GroupMessage() {
	}
	GroupMessage::GroupMessage(PlainMessage t_mess) {
		virt_deserialize(t_mess);
	}
	void GroupMessage::virt_deserialize(PlainMessage t_mess) {
		stringstream strm(
		t_mess.getBody());
		strm >> m_group >> m_command;
	}
	GroupMessage::GroupMessage(const NodeGroup & t_group,
		string t_command): CommandMessage(t_command),
		m_group(t_group) {
	}
	PlainMessage GroupMessage::serialize() {
		PlainMessage r_mess(groupMess);
		stringstream strm;
		strm << m_group << m_command;
		r_mess.setBody(strm.str());
		return r_mess;
	}
	MessageType GroupMessage::typeCheck() {
		return groupMess;
	}
	NodeGroup GroupMessage::getGroup() {
		return m_group;
	}

} //namespace Communication

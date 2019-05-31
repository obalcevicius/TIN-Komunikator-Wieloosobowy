#include "commandmessage.h"
#include <sstream>

using std::string;
using std::stringstream;

namespace Communication {

	CommandMessage::CommandMessage() {
	}
	CommandMessage::CommandMessage(PlainMessage t_mess) {
		virt_deserialize(t_mess);
	}
	void CommandMessage::virt_deserialize(PlainMessage t_mess) {
		stringstream strm(
		string(
		t_mess.getContent(), t_mess.getContentSize()));
		strm >> m_command;
	}
	CommandMessage::CommandMessage(string t_command):
		m_command(t_command) {
	}
	PlainMessage CommandMessage::serialize() {
		PlainMessage r_mess(commandMess);
		stringstream strm;
		strm << m_command;
		r_mess.setContent(strm.str());
		return r_mess;
	}
	string CommandMessage::getCommand() {
		return m_command;
	}
	MessageType CommandMessage::typeCheck() {
		return commandMess;
	}

} // namespace Communication
			

#include "echomessage.h"
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Communication {

	EchoMessage::EchoMessage() {
	}
	EchoMessage::EchoMessage(PlainMessage t_mess) {
		virt_deserialize(t_mess);
	}
	void EchoMessage::virt_deserialize(PlainMessage t_mess) {
		stringstream strm(
		string(
		t_mess.getContent(), t_mess.getContentSize()));
		strm >> m_command;
	}
	EchoMessage::EchoMessage(char t_command):
		m_command(t_command) {
	}
	PlainMessage EchoMessage::serialize() {
		PlainMessage r_mess(commandMess);
		stringstream strm;
		strm << m_command;
		r_mess.setContent(strm.str());
		return r_mess;
	}
	char EchoMessage::getCommand() {
		return m_command;
	}
	MessageType EchoMessage::typeCheck() {
		return echoMess;
	}

} //namespace Communication

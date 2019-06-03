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
		m_command = *t_mess.getContent();
	}
	EchoMessage::EchoMessage(char t_command):
		m_command(t_command) {
	}
	PlainMessage EchoMessage::serialize() {
		PlainMessage r_mess(echoMess);
		r_mess.setBody(std::string(1, m_command));
		return r_mess;
	}
	char EchoMessage::getCommand() {
		return m_command;
	}
	MessageType EchoMessage::typeCheck() {
		return echoMess;
	}

} //namespace Communication

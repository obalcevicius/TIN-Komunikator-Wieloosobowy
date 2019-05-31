#include "echomessage.h"
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Communication {

	EchoMessage::EchoMessage() {
	}
	EchoMessage::EchoMessage(PlainMessage mess) {
		std::stringstream strm(
		std::string(
		mess.getContent(), mess.getContentSize()));
		strm >> command;
	}
	void EchoMessage::virt_deserialize(PlainMessage mess) {
		std::stringstream strm(
		std::string(
		mess.getContent(), mess.getContentSize()));
		strm >> command;
	}
	EchoMessage::EchoMessage(char command):
		command(command) {
	}
	PlainMessage EchoMessage::serialize() {
		PlainMessage mess(commandMess);
		stringstream strm;
		strm << command;
		mess.setContent(strm.str());
		return mess;
	}
	MessageType EchoMessage::typeCheck() {
		return echoMess;
	}

} //namespace Communication

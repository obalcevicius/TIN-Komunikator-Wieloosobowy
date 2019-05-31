#include "commandmessage.h"
#include <sstream>

using std::string;
using std::stringstream;

namespace Communication {

	CommandMessage::CommandMessage() {
	}
	CommandMessage::CommandMessage(PlainMessage mess) {
		stringstream strm(
		string(
		mess.getContent(), mess.getContentSize()));
		strm >> command;
	}
	void CommandMessage::virt_deserialize(PlainMessage mess) {
		stringstream strm(
		string(
		mess.getContent(), mess.getContentSize()));
		strm >> command;
	}
	CommandMessage::CommandMessage(string command):
		command(command) {
	}
	PlainMessage CommandMessage::serialize() {
		PlainMessage mess(commandMess);
		stringstream strm;
		strm << command;
		mess.setContent(strm.str());
		return mess;
	}
	MessageType CommandMessage::typeCheck() {
		return commandMess;
	}

} // namespace Communication
			

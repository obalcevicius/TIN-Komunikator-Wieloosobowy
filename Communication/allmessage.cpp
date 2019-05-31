#include "allmessage.h"
#include <sstream>
using std::string;
using std::stringstream;
using Node::NodeGroup;

namespace Communication {

	AllMessage::AllMessage() {
	}
	AllMessage::AllMessage(PlainMessage mess) {
		std::stringstream strm(
		std::string(
		mess.getContent(), mess.getContentSize()));
		strm >> group >> subscribers >> command;
	}
	void AllMessage::virt_deserialize(PlainMessage mess) {
		std::stringstream strm(
		std::string(
		mess.getContent(), mess.getContentSize()));
		strm >> group >> subscribers >> command;
	}
	AllMessage::AllMessage(const NodeGroup & group, 
		const std::string command):
		group(group), command(command) {
	}
	PlainMessage AllMessage::serialize() {
		PlainMessage mess(allMess);
		stringstream strm;
		strm << group << subscribers << command;
		mess.setContent(strm.str());
		return mess;
	}
	MessageType AllMessage::typeCheck() {
		return allMess;
	}
} //namespace Communication

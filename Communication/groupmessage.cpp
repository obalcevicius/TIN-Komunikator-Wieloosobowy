#include "groupmessage.h"
#include <sstream>
using std::string;
using std::stringstream;
using Node::NodeGroup;
namespace Communication {

	GroupMessage::GroupMessage() {
	}
	GroupMessage::GroupMessage(PlainMessage mess) {
		virt_deserialize(mess);
	}
	void GroupMessage::virt_deserialize(PlainMessage mess) {
		stringstream strm(
		string(
		mess.getContent(), mess.getContentSize()));
		strm >> group >> command;
	}
	GroupMessage::GroupMessage(const NodeGroup & group,
		string command):
		group(group), command(command) {
	}
	PlainMessage GroupMessage::serialize() {
		PlainMessage mess(groupMess);
		stringstream strm;
		strm << group << command;
		mess.setContent(strm.str());
		return mess;
	}
	MessageType GroupMessage::typeCheck() {
		return groupMess;
	}
	NodeGroup GroupMessage::getGroup() {
		return group;
	}
	string GroupMessage::getCommand() {
		return command;
	}

} //namespace Communication

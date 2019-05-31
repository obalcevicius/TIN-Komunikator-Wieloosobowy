#include "onemessage.h"
#include <sstream>

using std::string;
using std::stringstream;
using Node::NodeInfo;

namespace Communication {

	OneMessage::OneMessage(): one("", "") {
	}
	OneMessage::OneMessage(PlainMessage mess): one("", "") {
		virt_deserialize(mess); //to trzeba będzie tu też wpisać
		//w innych wiadomościach
	}
	void OneMessage::virt_deserialize(PlainMessage mess) {
		std::stringstream strm(
		std::string(
		mess.getContent(), mess.getContentSize()));
		strm >> one >> command;
	}
	OneMessage::OneMessage(const NodeInfo & node, string command):
		one(node), command(command) {
	}
	PlainMessage OneMessage::serialize() {
		PlainMessage mess(oneMess);
		stringstream strm;
		strm << one << command;
		mess.setContent(strm.str());
		return mess;
	}
	
	NodeInfo OneMessage::getNode() {
		return one;
	}
	string OneMessage::getCommand() {
		return command;
	}
	MessageType OneMessage::typeCheck() {
		return oneMess;
	}
} //namespace Communication
			

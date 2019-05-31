#include "../Node/nodegroup.h"
#include "../Communication/onemessage.h"
#include "../Communication/groupmessage.h"
#include <string>
#include <sstream>
#include <iostream>
using Node::NodeGroup;
using Node::NodeInfo;
using Communication::Message;
using Communication::PlainMessage;
using Communication::OneMessage;
using Communication::GroupMessage;
using namespace std;

int main() {
	NodeGroup grupa;
	grupa.addMember(NodeInfo("ADRES1", "PORT1"));
	grupa.addMember(NodeInfo("ADRES2", "PORT2"));
	grupa.addMember(NodeInfo("ADRES3", "PORT3"));
	grupa.addMember(NodeInfo("ADRES4", "PORT4"));
	grupa.addMember(NodeInfo("ADRES5", "PORT5"));
	stringstream strm;
	strm << grupa;
	cout << strm.str() << endl;
	NodeGroup druga;
	strm >> druga;
	druga.present();
	cout << "------------------" << endl;
	{
	GroupMessage mess(grupa, "use");
	PlainMessage pmess = mess.serialize();
		string a(pmess.getContent(), pmess.getContentSize());
		cout << a << endl;
	pmess.prepareHeader();
	//teraz wiadomość może być przesłana
	PlainMessage nmess = pmess.flip_copy();
	Message * gmess = Message::deserialize(nmess);
	if(gmess->typeCheck() == groupMess) {
		cout << "Tak, jest groupMessage!" << endl;
		string a(nmess.getContent(), nmess.getContentSize());
		cout << a << endl;
		GroupMessage * ggmess = static_cast<GroupMessage *>(gmess);
		ggmess->getGroup().present();
		cout << ggmess->getCommand() << endl;
	}
	else cout << "Nie, nie jest groupMessage." << endl;
	}
	{
	cout << "-----------------------" << endl;
	OneMessage mess(NodeInfo("ADRES6", "PORT6"), "use");
	PlainMessage pmess = mess.serialize();
		string a(pmess.getContent(), pmess.getContentSize());
		cout << a << endl;
	pmess.prepareHeader();
	//teraz wiadomość może być przesłana
	PlainMessage nmess = pmess.flip_copy();
	Message * gmess = Message::deserialize(nmess);
	if(gmess->typeCheck() == oneMess) {
		cout << "Tak, jest oneMessage!" << endl;
		string a(nmess.getContent(), nmess.getContentSize());
		cout << a << endl;
		OneMessage * ggmess = static_cast<OneMessage *>(gmess);
		ggmess->getNode().present();
		cout << ggmess->getCommand() << endl;
	}
	else cout << "Nie, nie jest oneMessage." << endl;
	}
		
	return 0;
}

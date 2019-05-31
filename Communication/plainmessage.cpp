#include "plainmessage.h"
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
namespace Communication {

	int PlainMessage::headerSize = sizeof(Header);
	int PlainMessage::getHeaderSize() {
		return headerSize;
	}
	PlainMessage::PlainMessage(): 
		content(nullptr), contentSize(0)
	{
		header = new Header();
	}
	PlainMessage::PlainMessage(MessageType type):
		content(nullptr), contentSize(0)
	{
		header = new Header(type);
	}
	PlainMessage PlainMessage::flip_copy() {
		PlainMessage mess;
		if(content != nullptr) {
			*mess.header = header->flip();
			mess.prepareAgain(contentSize);
			std::memcpy(mess.content, content, contentSize);
		}
		return mess;
	}		
	char * PlainMessage::getContent() {
		return content;
	}
	int PlainMessage::getSize() {
		return headerSize + contentSize;
	}
	int PlainMessage::getContentSize() {
		return contentSize;
	}
	Header * PlainMessage::getHeader() {
		return header;
	}
	void PlainMessage::prepare() {
		contentSize = header->getOriginalNum();
		content = new char[contentSize];
	}
	void PlainMessage::prepareAgain(int contentSize) {
		this->contentSize = contentSize;
		content = new char[contentSize];
	}
	void PlainMessage::prepareHeader() {
		*header = header->prepare();
	}

	void PlainMessage::setContent(std::string cont) {
		contentSize = cont.length();
		//tak, może być niezwolniony, jeśli był
		//wcześniej zaalokowany
		content = new char[contentSize];
		std::memcpy(content, cont.data(), contentSize);
	}
	/* - wiadomość nic nie wie o wysyłaniu
	void PlainMessage::receiveMe(Socket sock) {
		sock.receive(header, headerSize);
		prepare();
		sock.receive(content, contentSize);
	}
	void PlainMessage::sendMe(Socket sock) {
		sock.send(header, headerSize);
		sock.send(content, contentSize);
	}
	*/

} //namespace Communication

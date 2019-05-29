#include "plainMessage.h"
	int PlainMessage::headerSize = sizeof(Header);
	int PlainMessage::getHeaderSize() {
		return headerSize;
	}
	PlainMessage::PlainMessage(): 
		content(nullptr), contentSize(0)
	{
		header = new Header;
	}
	PlainMessage PlainMessage::flip_copy() {
		PlainMessage mess;
		if(content != nullptr) {
			*mess.header = header->flip();
			mess.prepare();
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

#include "plainmessage.h"
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
using std::memcpy;
using std::string;
using std::unique_ptr;
namespace Communication {

	int PlainMessage::m_headerSize = sizeof(Header);
	int PlainMessage::getHeaderSize() {
		return m_headerSize;
	}
	PlainMessage::PlainMessage(): 
		m_content(nullptr), m_contentSize(0)
	{
		m_header = new Header();
	}
	PlainMessage::PlainMessage(MessageType t_type):
		m_content(nullptr), m_contentSize(0)
	{
		m_header = new Header(t_type);
	}
	char * PlainMessage::getContent() {
		return m_content;
	}
	int PlainMessage::getSize() const {
		return m_headerSize + m_contentSize;
	}
	int PlainMessage::getContentSize() {
		return m_contentSize;
	}
	Header * PlainMessage::getHeader() {
		return m_header;
	}
	void PlainMessage::prepare() {
		m_contentSize = m_header->getOriginalNum();
		m_content = new char[m_contentSize];
	}
	void PlainMessage::prepareAgain(int t_contentSize) {
		m_contentSize = t_contentSize;
		m_content = new char[t_contentSize];
	}
	void PlainMessage::pack() {
		*m_header = m_header->pack();
	}
	void PlainMessage::unpack() {
		*m_header = m_header->unpack();
	}
	PlainMessage PlainMessage::copyAndUnpack() {
		PlainMessage r_mess;
		if(m_content != nullptr) {
			*r_mess.m_header = m_header->unpack();
			r_mess.prepareAgain(m_contentSize);
			memcpy(r_mess.m_content, m_content, m_contentSize);
		}
		return r_mess; //tu by się przydał konstruktor move
	}		
	void PlainMessage::setBody(std::string t_cont) {
		if(m_content != nullptr) delete m_content;
		m_contentSize = t_cont.length();
		m_content = new char[m_contentSize];
		m_header->setSize(m_contentSize);
		memcpy(m_content, t_cont.data(), m_contentSize);
	}
	std::string PlainMessage::getBody() {
		return string(m_content, m_contentSize);
	}
	void PlainMessage::destroy() {
		if (m_content != nullptr) delete m_content;
		delete m_header;
	}
	unique_ptr<char> PlainMessage::getOnce() const { 
		unique_ptr<char> r_buff = unique_ptr<char>(new char[getSize()]);
		memcpy(r_buff.get(), m_header, m_headerSize);
		memcpy(r_buff.get() + m_headerSize, m_content, m_contentSize);
		return r_buff;
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

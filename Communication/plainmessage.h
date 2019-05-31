#ifndef PLAINMESSAGE_H
#define PLAINMESSAGE_H

#include "header.h"
#include <string>

namespace Communication {

class PlainMessage { //istnieje hipotetyczna potrzeba kopiowania
	//tylko jeszcze nie wiadomo gdzie
	public:
	static int getHeaderSize();
	PlainMessage();
	void destroy();
	PlainMessage(MessageType t_type);
	PlainMessage copyAndUnpack();	
	char * getContent();
	int getSize();
	int getContentSize();
	Header * getHeader();
	void prepare();
	void unpack();
	void pack(); 
	void setContent(std::string t_cont);
	/* - wiadomość nic nie wie o wysyłaniu
	void receiveMe(Socket sock);
	void sendMe(Socket sock);
	*/

	private:
	void prepareAgain(int t_contentSize);
	static int m_headerSize;
	Header * m_header;
	int m_contentSize;
	char * m_content;
};

} //namespace Communication

#endif //PLAINMESSAGE_H

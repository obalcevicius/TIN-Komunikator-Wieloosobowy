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
	PlainMessage(MessageType type);
	PlainMessage flip_copy();	
	char * getContent();
	int getSize();
	int getContentSize();
	Header * getHeader();
	void prepare();
	void prepareAgain(int contentSize);
	void prepareHeader(); 
	void setContent(std::string cont);
	/* - wiadomość nic nie wie o wysyłaniu
	void receiveMe(Socket sock);
	void sendMe(Socket sock);
	*/

	private:
	static int headerSize;
	Header * header;
	int contentSize;
	char * content;
};

} //namespace Communication

#endif //PLAINMESSAGE_H

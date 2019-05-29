#pragma once
#include "header.h"
class PlainMessage { //istnieje hipotetyczna potrzeba kopiowania
	//tylko jeszcze nie wiadomo gdzie
	private:
	static int headerSize;
	Header * header;
	int contentSize;
	char * content;
	public:
	static int getHeaderSize();
	PlainMessage();
	PlainMessage flip_copy();	
	char * getContent();
	int getSize();
	int getContentSize();
	Header * getHeader();
	void prepare();
	/* - wiadomość nic nie wie o wysyłaniu
	void receiveMe(Socket sock);
	void sendMe(Socket sock);
	*/	
};

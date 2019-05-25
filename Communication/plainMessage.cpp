class PlainMessage { //istnieje hipotetyczna potrzeba kopiowania
	//tylko jeszcze nie wiadomo gdzie
	private:
	static int headerSize = sizeof Header;
	Header * header;
	int contentSize;
	char * content;
	public:
	static int getHeaderSize() {
		return headerSize;
	}
	PlainMessage(): 
		content(std::nullptr), contentSize(0)
	{
		header = std::malloc(headerSize);
	}
	char * getContent() {
		return content + restSize;
	}
	int getSize() {
		return headerSize + restSize;
	}
	int getContentSize() {
		return contentSize;
	}
	Header * getHeader() {
		return header;
	}
	void prepare() {
		contentSize = header.getOriginalNum();
		content = std::malloc(contentSize);
	}
	void receiveMe(Socket sock) {
		sock.receive(header, headerSize);
		prepare();
		sock.receive(content, contentSize);
	}
	void sendMe(Socket sock) {
		sock.send(header, headerSize);
		sock.send(content, contentSize);
	}
		

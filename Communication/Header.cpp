class Header {
	MessageType type; //tu trzeba stworzyć enum
	int restSize;
	int getOriginalNum() {
		return ::ntoh(restSize);
	}
};

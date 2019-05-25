using std::string;
class NodeInfo {
	string address;
	string port;
	//tu jeszcze może być numer węzła
	public:
	NodeInfo(string address, string port) {
		this->address;
		this->port = port;
	}
	string getAddress() {
		return address;
	}
	string getPort() {
		return port;
	}
};

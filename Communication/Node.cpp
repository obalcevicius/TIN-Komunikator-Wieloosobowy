using std::map;
using std::string;
typedef MapType map<string, void *> args;
class Node {
	public:
	vector<NodeThread *> spawned;
	Thread * key;
	NodeInfo me;
	NodeInfo friend1;
	NodeInfo friend2;
	vector<NodeInfo> subscribers;
	vector<NodeInfo> members;
	void send(NodeInfo node, Message mess) {
		
	void tryMethod() {
	}//tu jakiś scenariusz testowy
	void join(NodeInfo node) {
		NodeInfo * second = node.copy(); //je trzeba kopiować
		MapType * map = new map;
		(*map)["node"] = second;
		spawned.push_back(new NodeThread(this, internalJoin, map));
	}
	void internalJoin(MapType * map) {
		NodeInfo * node = (NodeInfo *) (*map)["node"];
		
	

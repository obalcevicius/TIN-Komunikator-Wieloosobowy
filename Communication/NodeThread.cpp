using std::tuple;
using std::map;
typedef MapType map<string, void *> args;
typedef NodeMethod Node::*(MapType)
typedef NodeTuple tuple<Node *, NodeMethod, MapType>;
class NodeThread: public Thread {
	NodeThread(Node * main, 
	NodeMethod method, MapType * args):
	Thread()	
	{
		auto * set = new NodeTuple;
		*set = make_tuple(main, args);
		spawn(set, &nodeSpawn);
	}	
	void nodeSpawn(NodeTuple * set) {
		Node * node = get<0>(*set);
		NodeMethod method = get<1>(*set);
		auto * args = get<2>(*set); //czy to poprawny zapis?
		node->method(args);
		delete set;
	}
};


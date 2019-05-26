#include "NodeThread.h"
using std::get;
	NodeThread::NodeThread(Node * main, 
	NodeMethod method, MapType * args):
	Thread()	
	{
		NodeTuple * set = new NodeTuple;
		*set = make_tuple(main, method, args);
		spawn(set, (void*)&NodeThread::nodeSpawn);
	}	
	void NodeThread::nodeSpawn(NodeTuple * set) {
		Node * node = get<0>(*set);
		NodeMethod method = get<1>(*set);
		MapType * args = get<2>(*set); //czy to poprawny zapis?
		(node->*method)(args);
		delete set;
	}


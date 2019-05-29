#pragma once
#include "Thread.h"
#include "Node.h"
#include <tuple>
#include <map>
#include <string>
using std::string;
using std::tuple;
using std::map;
typedef map<string, void *> MapType;
typedef void(Node::*NodeMethod)(MapType *); 
typedef tuple<Node *, NodeMethod, MapType *> NodeTuple;
class NodeThread: public Thread {
	private:
	void nodeSpawn(NodeTuple * set);
	public:
	NodeThread(Node * main, 
	NodeMethod method, MapType * args);
};


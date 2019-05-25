#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
class Thread {
	public:
	Node * main;
	pthread_t id;
	void * method;
	Thread();
	static void * spawn(Thread * self);
	virtual void * run() = 0;
	void spawnAt(void * method); 
		
	void start();
	void wait();
	void quit();
	bool isMe();
	bool isRunning();
};

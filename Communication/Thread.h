#pragma once
#include <pthread.h>

class Thread {
	//static pthread_attr_t attr; - statyczny konstruktor klasy
	private:
	pthread_t id;
	bool active;
	pthread_mutex_t locker;
	void makeLocker();
	protected:
	void spawn(void * object, void * method);
	public:
	Thread();
	Thread(void * object, void * method);
	void lock();
	void unlock();
	void wait();
	bool isRunning();
	void quit();
	bool isMe();
	~Thread();
};

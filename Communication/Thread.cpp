#include "Thread.h"
	Thread::Thread(): id(0), active(false)
	{
		makeLocker();
	}
	Thread::Thread(void * object, void * method): id(0), active(false) {
		makeLocker();
		spawn(object, method);
	}
	void Thread::spawn(void * object, void * method) {
		pthread_attr_t attr; //to trzeba będzie trzymać w pogotowiu
		pthread_attr_init(&attr);
		pthread_create(&id, &attr, (void*(*)(void *))method,
		object);
		pthread_attr_destroy(&attr);
		active = true;
	}
	void Thread::makeLocker() {
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutex_init(&locker, &attr);
		pthread_mutexattr_destroy(&attr);
	}
	void Thread::lock() {
		pthread_mutex_lock(&locker);
	}
	void Thread::unlock() {
		pthread_mutex_unlock(&locker);
	}
	void Thread::wait() {
		pthread_join(id, (void **)0);
		active = false;
	}
	bool Thread::isRunning() {
		if(!active) return false;
		//to może się nie skompilować bo możecie nie mieć
		//poniższej funkcji
		bool i = pthread_tryjoin_np(id, (void**)0)==0;
		if(i) {
			active = false;
			return false;
		}
		return true;
	}	
	void Thread::quit() {
		if (isMe()) pthread_exit((void *)0);
	}
	bool Thread::isMe() {
		return pthread_self() == id;
	}
	Thread::~Thread() {
		pthread_mutex_destroy(&locker);
	}

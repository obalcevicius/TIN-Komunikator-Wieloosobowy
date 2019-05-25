#include "thread.h"
Thread::Thread(): id(-1)
{
}
void * Thread::spawn(Thread * self) {
	self->run();
}
void * Thread::spawnAtNode(Thread * self) {
	self->Node->method(); //bezargumentowa
	delete this; //kwestia sporna
}
void * Thread::run()
{
}
void Thread::startAtNode(void * method) {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&id, &attr, (void*(*)(void *))&Thread::spawnAtNode,
	this);
	pthread_attr_destroy(&attr);
void Thread::start() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&id, &attr, (void*(*)(void *))&Thread::spawn,
	this);
	pthread_attr_destroy(&attr);
}
void Thread::lock() {
	pthread_mutex_lock(locker);
}
void Thread::unlock() {
	pthread_mutex_unlock(locker);
}
void Thread::wait() {
	pthread_join(id, (void **)0);
	id = -1;
}
bool Thread::isRunning() {
	if(id == -1) return false;
	//to może się nie skompilować bo możecie nie mieć
	//poniższej funkcji
	bool i = pthread_tryjoin_np(id, (void**)0)==0;
	if(i) {
		id = -1;
		return false;
	}
	return true;
}	
void Thread::quit() {
	pthread_exit((void *)0);
}
bool Thread::isMe() {
	return pthread_self() == id;
}

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
class Thread {
	public:
	pthread_t id;
	pthread_mutex_t locker;
	int writerOutside;
	int readerInside;
	int writerInside;
	int readerOutside;
	int cash;
	Thread(int cash);
	static void * spawn(Thread * self);
	virtual void * run();
	void makeWriteToInside();
	void makeWriteToOutside();
	void writeOutside(const void * info, int infoSize);
	void writeInside(const void * info, int infoSize);
	void readOutside(void * info, int infoSize);
	void readInside(void * info, int infoSize);
	void start();
	void startMethod(void * method);
	void wait();
	void quit();
	void * fajnaMetoda();
	bool isMe();
	bool isRunning();
	void lock();
	void unlock();
};
class SpecificThread: public Thread {
	public:
	int num;
	SpecificThread(int cash, int num);
	void * run();
	void * fajniejszaMetoda();
};

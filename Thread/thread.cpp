#include "thread.h"
Thread::Thread(int cash) {
	this->cash = cash;
	id = -1;
	locker = -1;
	readerInside = writerOutside = 
	readerOutside = writerInside = -1;
}
void * Thread::spawn(Thread * self) {
	self->run();
}
void * Thread::run() { //Mechanizm taki jak w javie
	//chyba tak jest najbezpiecznej
	printf("Metoda run klasy Thread\n");
	printf("Jestem wątkiem o id: %lu\n", id);
	printf("Mój cash: %d\n", cash);
	if (cash==6) return (void *)0;
	else quit(); //pokazanie że można skończyć na 2 sposoby
}
void Thread::makeWriteToInside() {
	int pipefd[2];
	int result = pipe(pipefd);
	if(result == -1) {
		printf(
		"Nie udało się otworzyć komunikacji pipem:\n%s\n",
		strerror(errno));
	}
	readerInside = pipefd[0];
	writerOutside = pipefd[1];
}
void Thread::makeWriteToOutside() {
	int pipefd[2];
	int result = pipe(pipefd);
	if(result == -1) {
		printf(
		"Nie udało się otworzyć komunikacji pipem:\n%s\n",
		strerror(errno));
	}
	readerOutside = pipefd[0];
	writerInside = pipefd[1];
}
void Thread::writeOutside(const void * info, int infoSize) {
	write(writerOutside, info, infoSize);
}

void Thread::writeInside(const void * info, int infoSize) {
	write(writerInside, info, infoSize);
}

void Thread::readOutside(void * info, int infoSize) {
	read(readerOutside, info, infoSize);
}

void Thread::readInside(void * info, int infoSize) {
	read(readerInside, info, infoSize);
}
void Thread::start() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&id, &attr, (void*(*)(void *))&Thread::spawn,
	this);
	pthread_attr_destroy(&attr);
}
void Thread::startMethod(void * method) {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&id, &attr, (void*(*)(void *))method,
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
void 
void * Thread::fajnaMetoda() {
	//można w zasadzie zacząć wątek na dowolnej
	//metodzie tej klasy
	printf("fajnaMetoda klasy Thread\n");
	printf("Jestem wątkiem o id: %lu\n", id);
	printf("Mój cash: %d\n", cash);
	return (void *)0;
}
bool Thread::isMe() {
	return pthread_self() == id;
}
SpecificThread::SpecificThread(int cash, int num):
	Thread(cash), num(num) {}
void * SpecificThread::run() {
	printf("Metoda run klasy SpecificThread\n");
	printf("Jestem wątkiem o id: %lu\n", id);
	printf("Mój cash: %d\n", cash);
	printf("Mój num: %d\n", num);
	quit();
}
void * SpecificThread::fajniejszaMetoda() {
	printf("fajniejszaMetoda klasy SpecificThread\n");
	printf("Jestem wątkiem o id: %lu\n", id);
	printf("Mój cash: %d\n", cash);
	printf("Mój num: %d\n", num);
	char dana[20];
	readInside(dana, 20);
	printf("Oto odczytana dana z pipe'a: %s\n", dana);
	quit();
}

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
class Thread {
	public:
	pthread_t id;
	int writerOutside;
	int readerInside;
	int writerInside;
	int readerOutside;
	int cash;
	Thread(int cash) {
		this->cash = cash;
		id = -1;
		readerInside = writerOutside = 
		readerOutside = writerInside = -1;
	}
	static void * spawn(Thread * self) {
		self->run();
	}
	virtual void * run() { //Mechanizm taki jak w javie
		//chyba tak jest najbezpiecznej
		printf("Metoda run klasy Thread\n");
		printf("Jestem wątkiem o id: %lu\n", id);
		printf("Mój cash: %d\n", cash);
		if (cash==6) return (void *)0;
		else quit(); //pokazanie że można skończyć na 2 sposoby
	}
	void makeWriteToInside() {
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
	void makeWriteToOutside() {
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
	void writeOutside(const void * info, int infoSize) {
		write(writerOutside, info, infoSize);
	}
	
	void writeInside(const void * info, int infoSize) {
		write(writerInside, info, infoSize);
	}

	void readOutside(void * info, int infoSize) {
		read(readerOutside, info, infoSize);
	}

	void readInside(void * info, int infoSize) {
		read(readerInside, info, infoSize);
	}
	void start() {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&id, &attr, (void*(*)(void *))&Thread::spawn,
		this);
		pthread_attr_destroy(&attr);
	}
	void startMethod(void * method) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&id, &attr, (void*(*)(void *))method,
		this);
		pthread_attr_destroy(&attr);
	}
	void wait() {
		pthread_join(id, (void **)0);
	}
	void quit() {
		pthread_exit((void *)0);
	}
	void * fajnaMetoda() { //można w zasadzie zacząć wątek na dowolnej
		//metodzie tej klasy
		printf("fajnaMetoda klasy Thread\n");
		printf("Jestem wątkiem o id: %lu\n", id);
		printf("Mój cash: %d\n", cash);
		return (void *)0;
	}
};
class SpecificThread: public Thread {
	public:
	int num;
	SpecificThread(int cash, int num): Thread(cash), num(num) {}
	void * run() {
		printf("Metoda run klasy SpecificThread\n");
		printf("Jestem wątkiem o id: %lu\n", id);
		printf("Mój cash: %d\n", cash);
		printf("Mój num: %d\n", num);
		quit();
	}
	void * fajniejszaMetoda() {
		printf("fajniejszaMetoda klasy SpecificThread\n");
		printf("Jestem wątkiem o id: %lu\n", id);
		printf("Mój cash: %d\n", cash);
		printf("Mój num: %d\n", num);
		char dana[20];
		readInside(dana, 20);
		printf("Oto odczytana dana z pipe'a: %s\n", dana);
		quit();
	}
};
int main() {
	Thread t(6);
	t.start();
	printf("Jest wątek o id: %lu\n", t.id); //niby może być wyścig
	//o zajęcie stdouta
	t.wait();
	Thread m(7);
	m.startMethod((void *)&Thread::fajnaMetoda);
	printf("Jest wątek o id: %lu\n", m.id);
	m.wait();
	SpecificThread st1(4, 5);
	st1.start();
	printf("Jest wątek o id: %lu\n", st1.id);
	st1.wait();
	SpecificThread st2(-10, 3);
	st2.makeWriteToInside();
	const char * message = "Greetings!";
	st2.writeOutside(message, strlen(message) + 1);
	st2.startMethod((void *)&SpecificThread::fajniejszaMetoda);
	printf("Jest wątek o id: %lu\n", st2.id);
	st2.wait();
}
		
		

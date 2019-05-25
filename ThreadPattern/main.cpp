#include "thread.cpp"
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

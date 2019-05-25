class Thread {
	//static pthread_attr_t attr; - statyczny konstruktor klasy
	pthread_t id;
	bool active;
public:
	Thread(): id(0), active(false)
	{
	}
	Thread(void * object, void * method): id(0), active(true) {
		spawn(object, method);
	}
	void spawn() {
		pthread_attr_t attr; //to trzeba będzie trzymać w pogotowiu
		pthread_attr_init(&attr);
		pthread_create(&id, &attr, (void*(*)(void *))method,
		object);
		pthread_attr_destroy(&attr);
		active = true;
	}
	void lock() {
		pthread_mutex_lock(locker);
	}
	void unlock() {
		pthread_mutex_unlock(locker);
	}
	void wait() {
		pthread_join(id, (void **)0);
		active = false;
	}
	bool isRunning() {
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
	void quit() {
		if (isMe()) pthread_exit((void *)0);
	}
	bool isMe() {
		return pthread_self() == id;
	}
};

#ifndef THREADWRAPPER_H
#define THREADWRAPPER_H

#include <functional>
#include <thread>


class ThreadWrapper
{
public:
    ThreadWrapper();
    void start(bool t_detach);
    void finish();
    void terminate();
private:
    std::thread m_thread;
    void m_method();
    volatile bool m_finish;
};

#endif // THREADWRAPPER_H

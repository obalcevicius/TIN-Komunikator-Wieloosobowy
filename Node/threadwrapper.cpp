#include "threadwrapper.h"


ThreadWrapper::ThreadWrapper() :
    m_finish(false)
{

}

void ThreadWrapper::start(bool t_detach) {
    m_thread = std::thread();
    if(t_detach) {
        m_thread.detach();
    }
}

void ThreadWrapper::finish() {
    m_finish = true;
}
void ThreadWrapper::terminate() {
    std::terminate();
}

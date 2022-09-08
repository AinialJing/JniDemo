#include "ThreadOperator.h"

void printIds(const char *s) {
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    LOGD("%s pid %u tid %u(0x%x)\n", s, (unsigned int) pid, (unsigned int) tid);
}

void *thr_fn(void *arg) {
    printIds("new Thread:");
    return ((void *) 0);
}

void *thr_loop(void *arg){
    while (true){
        LOGD("Loop");
        sleep(1);
    }
}
ThreadOperator::ThreadOperator() {}

void ThreadOperator::createThread() {
    pthread_t handle;
    int err;
    err=pthread_create(&handle,NULL,thr_fn,NULL);
    if (err !=0)
        LOGD("can`t create thread");
    printIds("Main thread:");
}

void ThreadOperator::jointThread() {

}

void ThreadOperator::exitThread() {
}

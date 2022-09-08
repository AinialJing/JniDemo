#ifndef JNIDEMO_THREADOPERATOR_H
#define JNIDEMO_THREADOPERATOR_H

#include <pthread.h>
#include <unistd.h>
#include "UnixLog.h"

class ThreadOperator {
public:
    ThreadOperator();

    void createThread();

    void jointThread();

    void exitThread();
};


#endif //JNIDEMO_THREADOPERATOR_H

#ifndef JNIDEMO_STREAMIOOPERATOR_H
#define JNIDEMO_STREAMIOOPERATOR_H

#include <jni.h>
#include <stdio.h>
#include <pthread.h>
#include "UnixLog.h"

//为了在线程中调用java方法
extern JavaVM *jvm_g;
extern jobject obj_g;

class StreamIOOperator {
private:
    const char *pathName;
public:
    StreamIOOperator();

    StreamIOOperator(const char *path);

    FILE *openFile();

    int readFile(FILE *file, int len);

    int writeFile(FILE *file, const char *data, int len);

    int closeFile(FILE *file);
};


#endif //JNIDEMO_STREAMIOOPERATOR_H

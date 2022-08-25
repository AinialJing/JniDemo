#ifndef JNIDEMO_FILEOPERATOR_H
#define JNIDEMO_FILEOPERATOR_H

#include <jni.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <string.h>
#include "UnixLog.h"

//为了在线程中调用java方法
extern JavaVM *jvm_g;
extern jobject obj_g;

class FileOperator {
private:
    const char *direct;
    const char *fileName;
public:
    FileOperator();

    FileOperator(const char *direct);

    int createFile(const char *fileName);

    int openFile(const char *fileName);

    int readFile(const int fd);

    int writeFile(const int fd, unsigned char *data, int size);

    int lseekFile(const int fd);

    int closeFile(const int fd);
};


#endif //JNIDEMO_FILEOPERATOR_H

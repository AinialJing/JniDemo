#ifndef JNIDEMO_FILEOPERATOR_H
#define JNIDEMO_FILEOPERATOR_H

#include <unistd.h>
#include <fcntl.h>
#include "UnixLog.h"

class FileOperator {
private:
    const char *path;
public:
    FileOperator();

    FileOperator(const char *path);

    int createFile();

    int openFile();

    int readFile();

    int writeFile();

    int lseekFile();

    int closeFile();
};


#endif //JNIDEMO_FILEOPERATOR_H

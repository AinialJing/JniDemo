#ifndef JNIDEMO_STREAMIOOPERATOR_H
#define JNIDEMO_STREAMIOOPERATOR_H

#include <stdio.h>
#include "UnixLog.h"

class StreamIOOperator {
private:
    const char *pathName;
public:
    StreamIOOperator();
    StreamIOOperator(const char *path);

    FILE* openFile();

    int readFile(FILE *file);

    int writeFile(FILE *file, const  char*data);

    int closeFile(FILE *file);
};


#endif //JNIDEMO_STREAMIOOPERATOR_H

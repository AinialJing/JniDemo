#include "StreamIOOperator.h"

StreamIOOperator::StreamIOOperator() {}

StreamIOOperator::StreamIOOperator(const char *path) {
    StreamIOOperator::pathName = path;
}

FILE *StreamIOOperator::openFile() {
    LOGD("Stream file path:%s", pathName);
    return fopen(pathName, "ab+");
}

int StreamIOOperator::readFile(FILE *file) {
    return fgetc(file);
}

int StreamIOOperator::writeFile(FILE *file, const char *data) {
    return fputs(data, file);
}

int StreamIOOperator::closeFile(FILE *file) {
    return fclose(file);
}
#include "FileOperator.h"

FileOperator::FileOperator() {}

FileOperator::FileOperator(const char *path) {
    FileOperator::path = path;
}

int FileOperator::createFile() {
    LOGI("create file path is:%s", path);
    int ret = creat(path, O_RDWR);
    if (ret == -1){
        LOGD("create file failed");
    }else{
        LOGI("create file %s is success!", path);
    }

    return ret;
}

int FileOperator::openFile() {

}

int FileOperator::readFile() {

}

int FileOperator::writeFile() {

}

int FileOperator::lseekFile() {

}

int FileOperator::closeFile() {

}

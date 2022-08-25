#include "FileOperator.h"


FileOperator::FileOperator() {}

FileOperator::FileOperator(const char *path) {
    FileOperator::direct = path;
}

int FileOperator::createFile(const char *fileName) {
    LOGI("create file director is:%s", direct);
    FileOperator::fileName = fileName;
    LOGD("create director path %s", direct);
    struct stat sb;
    //判断目录是否存在，如果存在则返回0；不存在返回-1
    int ac = stat(direct, &sb);
    if (ac == -1) {
        LOGD("director %s is not exist", direct);
        mkdir(direct, O_RDWR);
    }
    const int len = (sizeof(direct) / sizeof(direct[0])) + (sizeof(fileName) / sizeof(fileName[0]));
    char *buffer = new char[len + 1];
    //拷贝目录字符串
    strcpy(buffer, direct);
    //追加文件名字符串
    strcat(buffer, fileName);
    LOGD("create file path %s", buffer);
    struct stat file;
    //判断文件是否存在，如果存在则返回0；不存在返回-1
    int fileState = stat(buffer, &file);
    LOGD("file state is %d", fileState);
    if (fileState == 0) {
        LOGD("file %s is exist", buffer);
        return fileState;
    } else {
        int ret = creat(buffer, O_RDWR);
        if (ret == -1) {
            LOGD("create file failed:%d", ret);
        } else {
            LOGI("create file %s is success!", buffer);
        }
        return ret;
    }

}

int FileOperator::openFile(const char *fileName) {
    const int len = (sizeof(direct) / sizeof(direct[0])) + (sizeof(fileName) / sizeof(fileName[0]));
    char *buffer = new char[len + 1];
    strcpy(buffer, direct);
    strcat(buffer, fileName);
    int ret = open(buffer, O_CREAT | O_RDWR, 0666);
    if (ret == -1) {
        LOGD("open file %s failed.", buffer);
    } else {
        LOGD("open file %s success.", buffer);
    }
    return ret;
}

int FileOperator::readFile(const int fd) {
    char *buff = new char[20];
    int len = read(fd, buff, 20);
    LOGD("read file 1:len=%d", len);
    if (len > 0) {
        JNIEnv *env;
        // 获取当前线程的 env
        jvm_g->AttachCurrentThread(&env, NULL);
        jclass native = env->GetObjectClass(obj_g);
        jbyteArray arr;
        arr = env->NewByteArray(len);
        if (NULL != buff) {
            env->SetByteArrayRegion(arr, 0, len, (const jbyte *) buff);
        }
        LOGD("read file 2");
        jmethodID callBack = env->GetMethodID(native, "readCallBack", "([B)V");
        LOGD("read file 3 data len %d", env->GetArrayLength(arr));
        env->CallVoidMethod(obj_g, callBack, arr);
    }
}

int FileOperator::writeFile(const int fd, unsigned char *data, int size) {
    int ret = write(fd, data, size);
    return ret;
}

int FileOperator::lseekFile(const int fd) {
    return lseek(fd, 0, SEEK_END);
}

int FileOperator::closeFile(const int fd) {
    return close(fd);
}
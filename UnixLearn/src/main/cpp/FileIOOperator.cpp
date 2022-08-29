#include "FileIOOperator.h"

struct ThreadArgs {
    int fd;
};

void *readData(void *arg) {
    JNIEnv *env;
    // 获取当前线程的 env
    jvm_g->AttachCurrentThread(&env, NULL);
    jclass native = env->GetObjectClass(obj_g);
    jmethodID callBack = env->GetMethodID(native, "readCallBack", "([B)V");
    jbyteArray arr;

    ThreadArgs *threadArgs = static_cast<ThreadArgs *>(arg);
    int fd = threadArgs->fd;
    //SEEK_END 文件指针移到文件尾
    int total = lseek(fd, 0, SEEK_END);
    LOGD("total is %d", total);
    const int readLen = total;
    char *buff = new char[readLen];
    //SEEK_SET  文件指针移到文件开头
    lseek(fd, 0, SEEK_SET);
    //read方法会读取后文件指针自动移动
    int len = read(fd, buff, readLen);
    LOGD("Read len:%d", len);
    arr = env->NewByteArray(len);
    if (NULL != buff) {
        env->SetByteArrayRegion(arr, 0, len, (const jbyte *) buff);
    }
    env->CallVoidMethod(obj_g, callBack, arr);
    jvm_g->DetachCurrentThread();
    //一定要有返回值，否则会发生异常
    return NULL;
}

FileIOOperator::FileIOOperator() {}

FileIOOperator::FileIOOperator(const char *path) {
    FileIOOperator::direct = path;
}

int FileIOOperator::createFile(const char *fileName) {
    LOGI("create file director is:%s", direct);
    FileIOOperator::fileName = fileName;
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

int FileIOOperator::getFileInfo(const char *filePath, struct stat *info) {
    LOGD("getFileInfo path:%s", filePath);
    int ret=stat(filePath,info);
    LOGD("Get File size:%d",info->st_size);
    return ret;
}

int FileIOOperator::openFile(const char *fileName) {
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

int FileIOOperator::readFile(const int fd) {
    pthread_t handle;
    ThreadArgs *threadArgs = new ThreadArgs;
    threadArgs->fd = fd;
    int result = pthread_create(&handle, nullptr, readData, threadArgs);
    if (result == 0) {
        LOGD("create read file data thread success");
    }
    return result;
}

int FileIOOperator::writeFile(const int fd, unsigned char *data, int size) {
    int ret = write(fd, data, size);
    return ret;
}

int FileIOOperator::lseekFile(const int fd) {
    return lseek(fd, 0, SEEK_END);
}

int FileIOOperator::closeFile(const int fd) {
    return close(fd);
}


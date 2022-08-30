#include "StreamIOOperator.h"

struct StreamReadArgs {
    FILE *file;
    int size;
};

void *readStream(void *arg) {
    StreamReadArgs *args = static_cast<StreamReadArgs *>(arg);
    FILE *file = args->file;
    int size = args->size;
    LOGD("read stream file point:%p,size:%d", file, size);
    char *buf = new char[size + 1];
    //文件指针移到头，读的时候要从头开始读
    fseek(file, 0, SEEK_SET);
    size_t result = fread(buf, 1, size, file);
    LOGD("read stream length:%d,content:%s", result, buf);
    JNIEnv *env;
    jvm_g->AttachCurrentThread(&env, NULL);
    jclass unixNativeClass = env->GetObjectClass(obj_g);
    jmethodID callBack = env->GetMethodID(unixNativeClass, "readCallBack", "([B)V");
    //char*转化为jbyteArray
    jbyteArray arr = NULL;
    arr = env->NewByteArray(size);
    if (NULL != arr) {
        env->SetByteArrayRegion(arr, 0, size, reinterpret_cast<const jbyte *>(buf));
        env->CallVoidMethod(obj_g, callBack, arr);
    }
    jvm_g->DetachCurrentThread();
    return NULL;
}

StreamIOOperator::StreamIOOperator() {}

StreamIOOperator::StreamIOOperator(const char *path) {
    StreamIOOperator::pathName = path;
}

FILE *StreamIOOperator::openFile() {
    LOGD("Stream file path:%s", pathName);
    FILE *file = fopen(pathName, "rb+");
    LOGD("Stream file open:%p", file);
    return file;
}

int StreamIOOperator::readFile(FILE *file, int len) {
    pthread_t handle;
    StreamReadArgs *args = new StreamReadArgs();
    args->file = file;
    args->size = len;
    int ret = pthread_create(&handle, nullptr, readStream, args);
    if (ret == 0) {
        LOGD("create read stream thread success");
    }
    return ret;
}

int StreamIOOperator::writeFile(FILE *file, const char *data, int len) {
    //文件指针移到文件尾部，从尾部开始写
    fseek(file, 0, SEEK_END);
//    int ret = fputs(data, file);
    int ret = fwrite(data, sizeof(char), len,file);
    //写以后，一定要调用fflush,才能真正把数据写入文件
    fflush(file);
    return ret;
}

int StreamIOOperator::closeFile(FILE *file) {
    return fclose(file);
}
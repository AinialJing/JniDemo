#include <jni.h>
#include "FileIOOperator.h"
#include "StreamIOOperator.h"

//为了在线程中调用java方法
JavaVM *jvm_g = NULL;
jobject obj_g = NULL;

FileIOOperator fileOperator;
StreamIOOperator streamIoOperator;


extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_initLib(JNIEnv *env, jobject obj) {
    env->GetJavaVM(&jvm_g);        //保存到全局变量中JVM
    obj_g = env->NewGlobalRef(obj);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_creatFile(JNIEnv *env, jobject obj, jstring path,
                                                     jstring fileName) {
    const char *_path = NULL;
    _path = env->GetStringUTFChars(path, 0);
    LOGD("Path is %s", _path);
    fileOperator = FileIOOperator(_path);
    return fileOperator.createFile(env->GetStringUTFChars(fileName, 0));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_getFileInfo(JNIEnv *env, jobject thiz, jstring path) {
    const char *_path = NULL;
    _path = env->GetStringUTFChars(path, 0);
    LOGD("GetFile info path is %s", _path);
    fileOperator = FileIOOperator();
    struct stat info;
    int ret = fileOperator.getFileInfo(_path, &info);
    jclass fileInfoCLZ = env->FindClass("com/anniljing/unixlearn/FileInfo");
    jmethodID contruct = env->GetMethodID(fileInfoCLZ, "<init>", "()V");
    jobject fileInfo = env->NewObject(fileInfoCLZ, contruct);
    jfieldID fileSize = env->GetFieldID(fileInfoCLZ, "size", "J");
    if (ret == 0) {
        env->SetLongField(fileInfo, fileSize, info.st_size);
        return fileInfo;
    }
    return NULL;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_openFile(JNIEnv *env, jobject obj, jstring path,
                                                    jstring fileName) {
    const char *_path = NULL;
    _path = env->GetStringUTFChars(path, 0);
    LOGD("Path is %s", _path);
    fileOperator = FileIOOperator(_path);
    return fileOperator.openFile(env->GetStringUTFChars(fileName, 0));
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_readFile(JNIEnv *env, jobject obj, jint fd) {
    fileOperator = FileIOOperator();
    fileOperator.readFile(fd);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_writeFile(JNIEnv *env, jobject obj, jint fd,
                                                     jbyteArray data, jint size) {
    unsigned char *buf = reinterpret_cast<unsigned char *>(env->GetByteArrayElements(data, 0));
    fileOperator = FileIOOperator();
    return fileOperator.writeFile(fd, buf, size);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_lseekFile(JNIEnv *env, jobject obj, jint fd) {
    fileOperator = FileIOOperator();
    return fileOperator.lseekFile(fd);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_closeFile(JNIEnv *env, jobject obj, jint fd) {
    fileOperator = FileIOOperator();
    return fileOperator.closeFile(fd);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_openStreamFile(JNIEnv *env, jobject thiz,
                                                          jstring file_name) {
    const char *_path = NULL;
    _path = env->GetStringUTFChars(file_name, 0);
    streamIoOperator = StreamIOOperator(_path);
    FILE *file = streamIoOperator.openFile();
    if (NULL != file) {
        return reinterpret_cast<jlong>(file);
    } else {
        LOGD("Open stream file failed");
    }
    return -1;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_writeStreamFile(JNIEnv *env, jobject thiz, jlong file,
                                                           jbyteArray data) {
    char *buff = reinterpret_cast<char *>(env->GetByteArrayElements(data, 0));
    streamIoOperator = StreamIOOperator();
    FILE *fileStream = reinterpret_cast<FILE *>(file);
    int ret = streamIoOperator.writeFile(fileStream, buff);
    LOGD("Stream file write:%d", ret);
    return ret;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_closeStreamFile(JNIEnv *env, jobject thiz, jlong file) {
    streamIoOperator = StreamIOOperator();
    FILE *fileStream = reinterpret_cast<FILE *>(file);
    int ret=streamIoOperator.closeFile(fileStream);
    LOGD("Stream file close:%d", ret);
    return ret;
}
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
    //强转会出现多余的字符
//    unsigned char *buf = reinterpret_cast<unsigned char *>(env->GetByteArrayElements(data, 0));
    unsigned char *buf = NULL;
    jbyte *bytes = NULL;
    bytes = env->GetByteArrayElements(data, 0);
    buf = new u_char[size + 1];
    memset(buf, 0, size + 1);
    memcpy(buf, bytes, size);
    buf[size] = 0;
    fileOperator = FileIOOperator();
    int ret = fileOperator.writeFile(fd, buf, size);
    env->ReleaseByteArrayElements(data, bytes, 0);
    delete[] buf;
    return ret;
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
        //java层保存C层的结构体则以指针的形式保存
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
    //jbyteArray类型的数据转换成C层的char
    char *buff = NULL;
    jbyte *bytes = NULL;
    bytes = env->GetByteArrayElements(data, 0);
    int buff_len = env->GetArrayLength(data);
    buff = new char[buff_len + 1];
    memset(buff, 0, buff_len + 1);
    memcpy(buff, bytes, buff_len);
    buff[buff_len] = 0;
    streamIoOperator = StreamIOOperator();
    //java层传过来的long类型强转为C层的结构体
    FILE *fileStream = reinterpret_cast<FILE *>(file);
    LOGD("write buffer:%s", buff);
    int ret = streamIoOperator.writeFile(fileStream, buff, buff_len);
    LOGD("Stream file write:%d", ret);
    env->ReleaseByteArrayElements(data, bytes, 0);
    delete[] buff;
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_readStreamIO(JNIEnv *env, jobject thiz, jlong file,
                                                        jint size) {
    streamIoOperator = StreamIOOperator();
    //java层传过来的long类型强转为C层的结构体
    FILE *fileStream = reinterpret_cast<FILE *>(file);
    return streamIoOperator.readFile(fileStream, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_closeStreamFile(JNIEnv *env, jobject thiz, jlong file) {
    streamIoOperator = StreamIOOperator();
    FILE *fileStream = reinterpret_cast<FILE *>(file);
    LOGD("JNI file %p", fileStream);
    int ret = streamIoOperator.closeFile(fileStream);
    LOGD("Stream file close:%d", ret);
    return ret;
}

#include <jni.h>
#include "FileOperator.h"

//为了在线程中调用java方法
JavaVM *jvm_g = NULL;
jobject obj_g = NULL;

FileOperator fileOperator;

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
    fileOperator = FileOperator(_path);
    return fileOperator.createFile(env->GetStringUTFChars(fileName, 0));
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_openFile(JNIEnv *env, jobject obj, jstring path,
                                                    jstring fileName) {
    const char *_path = NULL;
    _path = env->GetStringUTFChars(path, 0);
    LOGD("Path is %s", _path);
    fileOperator = FileOperator(_path);
    return fileOperator.openFile(env->GetStringUTFChars(fileName, 0));
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_readFile(JNIEnv *env, jobject obj, jint fd) {
    fileOperator = FileOperator();
    fileOperator.readFile(fd);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_writeFile(JNIEnv *env, jobject obj, jint fd,
                                                     jbyteArray data, jint size) {
    unsigned char *buf = reinterpret_cast<unsigned char *>(env->GetByteArrayElements(data, 0));
    fileOperator = FileOperator();
    return fileOperator.writeFile(fd, buf, size);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_lseekFile(JNIEnv *env, jobject obj, jint fd) {
    fileOperator = FileOperator();
    return fileOperator.lseekFile(fd);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_closeFile(JNIEnv *env, jobject obj, jint fd) {
    fileOperator = FileOperator();
    return fileOperator.closeFile(fd);
}

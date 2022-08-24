#include <jni.h>
#include "FileOperator.h"

FileOperator fileOperator;
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_creatFile(JNIEnv *env, jclass clazz, jstring path) {
    const char *_path = NULL;
    _path = env->GetStringUTFChars(path, 0);
    LOGD("Path is %s",_path);
    fileOperator = FileOperator(_path);
    return fileOperator.createFile();
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_openFile(JNIEnv *env, jclass clazz, jstring path) {

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_readFile(JNIEnv *env, jclass clazz, jstring file) {

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_writeFile(JNIEnv *env, jclass clazz, jbyteArray data) {

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_lseekFile(JNIEnv *env, jclass clazz, jbyteArray data) {

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_closeFile(JNIEnv *env, jclass clazz, jstring file) {

}


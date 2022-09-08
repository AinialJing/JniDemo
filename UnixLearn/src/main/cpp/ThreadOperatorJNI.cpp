#include <jni.h>
#include "ThreadOperator.h"

ThreadOperator threadOperator;
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_createThread(JNIEnv *env, jobject thiz) {
    threadOperator = ThreadOperator();
    threadOperator.createThread();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_jointThread(JNIEnv *env, jobject thiz) {
    threadOperator = ThreadOperator();
    threadOperator.jointThread();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_unixlearn_UnixNativeLib_exitThread(JNIEnv *env, jobject thiz) {
    threadOperator = ThreadOperator();
    threadOperator.exitThread();
}
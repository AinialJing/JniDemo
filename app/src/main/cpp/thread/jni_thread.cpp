#include <pthread.h>
#include <AndroidLog.h>
#include <jni.h>
#include <jvm.h>
#include <unistd.h>
#include <queue>

extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniThread_createNativeThread(JNIEnv *env, jobject thiz) {
   
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniThread_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {

}


extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniThread_joinNativeThread(JNIEnv *env, jobject thiz) {

}


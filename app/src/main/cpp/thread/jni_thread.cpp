#include <pthread.h>
#include <AndroidLog.h>
#include <jni.h>
#include <jvm.h>
#include <unistd.h>
#include <queue>

void *printThreadHello(void *) {
    LOGD("Hello thread");
    return nullptr;
}

struct ThreadRunArgs{
    int id;
    int result;
};

void *printThreadArgs(void *arg){
    ThreadRunArgs *args= static_cast<ThreadRunArgs *>(arg);
    LOGD("thread id is &d",args ->result);
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniThread_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handles;
    int result = pthread_create(&handles, nullptr, printThreadHello, nullptr);
    if (result == 0) {
        LOGD("create thread success");
    } else {
        LOGD("create thread failed");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniThread_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    ThreadRunArgs *runArgs=new ThreadRunArgs;
    runArgs ->id =2;
    runArgs ->result=100;
    pthread_t handles;
    int result = pthread_create(&handles, nullptr, printThreadArgs, runArgs);
    if (result == 0) {
        LOGD("create thread success");
    } else {
        LOGD("create thread failed");
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniThread_joinNativeThread(JNIEnv *env, jobject thiz) {

}


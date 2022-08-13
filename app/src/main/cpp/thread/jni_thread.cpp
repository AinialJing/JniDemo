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

struct ThreadRunArgs {
    int id;
    int result;
};

void *printThreadArgs(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    LOGD("thread id is &d", args->result);
    return nullptr;
}

void *printThreadJoin(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    struct timeval begin;
    gettimeofday(&begin, nullptr);
    LOGD("start time is %ld", begin.tv_sec);
    sleep(3);
    struct timeval end;
    gettimeofday(&end, nullptr);
    LOGD("end time is %ld", end.tv_sec);
    LOGD("Time used is %ld", end.tv_sec - begin.tv_sec);
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
    ThreadRunArgs *runArgs = new ThreadRunArgs;
    runArgs->id = 2;
    runArgs->result = 100;
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
    pthread_t handles;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 2;
    args->result = 100;
    int result = pthread_create(&handles, nullptr, printThreadJoin, args);

    void *ret = nullptr;

    pthread_join(handles, &ret);

    LOGD("result is %d", ret);
}


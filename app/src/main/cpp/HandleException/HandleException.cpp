#include <jni.h>
#include <AndroidLog.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_exception_HandleException_handleJniExeption(JNIEnv *env, jclass clazz) {
    //向 Java 层抛出异常
    jclass exceptionClz = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(exceptionClz, "来自 Native 的异常");
    //检查当前环境是否发生异常（类似于 Java try{}）
    jthrowable exc = env->ExceptionOccurred();
    if (exc) {
        // 处理异常（类似于 Java 的 catch{}）
        env->ExceptionDescribe();
        LOGD("exception from native");
    }
    //清除异常
    env->ExceptionClear();
}
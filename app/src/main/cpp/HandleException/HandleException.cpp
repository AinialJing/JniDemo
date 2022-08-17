#include <jni.h>
#include <AndroidLog.h>
#include <jni.h>
#include <jni.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_ExceptionHandle_HandleException_handleJniExeption(JNIEnv *env,
                                                                             jclass clazz) {
    //向 Java 层抛出异常
    jclass exceptionClz = env->FindClass("com/anniljing/jnidemo/JavaClass");
    jmethodID constructure = env->GetMethodID(exceptionClz, "<init>", "()V");
    jobject obj = env->NewObject(exceptionClz, constructure);
    jmethodID getResulteID = env->GetMethodID(exceptionClz, "getResulte", "()V");
    env->CallVoidMethod(obj, getResulteID);
    //检查当前环境是否发生异常（类似于 Java try{}）
    if (env->ExceptionCheck()) {
        // 处理异常（类似于 Java 的 catch{}）
        env->ExceptionDescribe();
        LOGD("exception from native");
    }
    //清除异常
    env->ExceptionClear();
}
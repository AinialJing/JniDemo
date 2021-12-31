#include <jni.h>
#include <AndroidLog.h>

extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_jnidemo_BasicTypeNative_callNativeInt(JNIEnv *env, jobject thiz, jint num) {
    LOGD("Java int value is:%d", num);
    return num * 2;
}


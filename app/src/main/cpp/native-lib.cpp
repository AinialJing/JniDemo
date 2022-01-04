#include <jni.h>
#include <string>
#include <AndroidLog.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_anniljing_jnidemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGD("Get native message success");
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniInvokeMethod_nativeCallBack(JNIEnv *env, jobject thiz,
                                                          jobject call_back) {
    LOGD("nativeCallBack");
    jclass callBackClazz = env->GetObjectClass(call_back);
    jmethodID jmethodId = env->GetMethodID(callBackClazz, "callback", "()V");
    env->CallVoidMethod(call_back, jmethodId);
}
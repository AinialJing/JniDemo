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
#include <jni.h>

extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_jnidemo_VersionInformation_VersionInformation_getVersionInformation(JNIEnv *env,
                                                                                       jclass clazz) {
    return env->GetVersion();
}
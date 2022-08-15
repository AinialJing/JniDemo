#include <jni.h>
#include "AndroidLog.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_jnidemo_JavaClassOperator_JniOperatorJavaClass_operatorJavaClass(JNIEnv *env,
                                                                                    jclass clazz) {
    jclass jc=env->FindClass("com/anniljing/jnidemo/JavaClass");
    jmethodID construct=env->GetMethodID(jc,"<init>", "()V");
    jobject  javaClassObg=env->NewObject(jc,construct);
    return javaClassObg;
}
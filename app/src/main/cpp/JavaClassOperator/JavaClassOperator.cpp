#include <jni.h>
#include "AndroidLog.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_jnidemo_ClassOperator_FindClassForJava_InitAnimal(JNIEnv *env, jobject thiz) {
    jclass js = env->FindClass("com/anniljing/jnidemo/Animal");
    jmethodID objConstruct = env->GetMethodID(js, "<init>", "()V");
    jobject objAnimal = env->NewObject(js, objConstruct);
    jmethodID setName = env->GetMethodID(js, "setName", "(Ljava/lang/String;)V");
    env->CallVoidMethod(objAnimal, setName, env->NewStringUTF("My name is WangWang"));
    return objAnimal;
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_jnidemo_JavaClassOperator_JniOperatorJavaClass_operatorJavaClass(JNIEnv *env,
                                                                                    jclass clazz) {
    jclass jc=env->FindClass("com/anniljing/jnidemo/JavaClass");
    jmethodID construct=env->GetMethodID(jc,"<init>", "()V");
    jobject  javaClassObg=env->NewObject(jc,construct);
    return javaClassObg;
}
//
// Created by WRTRD02 on 2022-01-04.
//
#include <jni.h>
#include <AndroidLog.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_JniCallJavaField_initPeopleData(JNIEnv *env, jobject jb,
                                                           jobject people) {
    jclass jc = env->GetObjectClass(people);
    jfieldID fidAge = env->GetFieldID(jc, "age", "I");
    jfieldID fidName = env->GetFieldID(jc, "name", "Ljava/lang/String;");
    env->SetIntField(people, fidAge, 18);
    jstring name = env->NewStringUTF("Jack");
    env->SetObjectField(people, fidName, name);
}

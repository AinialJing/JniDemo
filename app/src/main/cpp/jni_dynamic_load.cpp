//
// Created by WRTRD02 on 2021-12-31.
//
#include <jni.h>
#include <AndroidLog.h>

#define JAVA_CLASS "com/anniljing/jnidemo/JniDynamicLoad"

jint sum(JNIEnv *env, jobject jobj, int x, int y) {
    return x + y;
}

jstring getMessage(JNIEnv *env, jobject jobj) {
    return env->NewStringUTF("This is from native string");
}

static JNINativeMethod gMethods[] = {
        {"sum",             "(II)I",                (void *) sum},
        {"getNativeString", "()Ljava/lang/String;", (void *) getMessage}
};

int registerNativeMethods(JNIEnv *env, const char *name, const JNINativeMethod *methods,
                          jint nMethods) {
    jclass jcls;
    jcls = env->FindClass(name);
    if (jcls == nullptr) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(jcls, methods, nMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    registerNativeMethods(env, JAVA_CLASS, gMethods, 2);
    LOGD("Dynamic load success");
    return JNI_VERSION_1_6;
}

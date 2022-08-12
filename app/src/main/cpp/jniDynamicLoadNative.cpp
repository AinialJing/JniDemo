//动态注册native方法,需要c/c++中定义与native方法映射的方法
#include <jni.h>
#include <AndroidLog.h>

#define JAVA_CLASS "com/anniljing/jnidemo/ClassOperator/JniDynamicLoad"

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

#define NELEM(x) ((int)(sizeof(x)/sizeof((x)[0])))

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    registerNativeMethods(env, JAVA_CLASS, gMethods, NELEM(gMethods));
    LOGD("Dynamic load success");
    return JNI_VERSION_1_6;
}

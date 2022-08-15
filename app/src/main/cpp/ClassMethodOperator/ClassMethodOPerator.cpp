#include <jni.h>


extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_jnidemo_classMethodOperator_ClassMethodOperator_operatorClassMethod(JNIEnv *env,
                                                                                       jclass clazz) {
    jclass javaClass = env->FindClass("com/anniljing/jnidemo/JavaClass");
    jmethodID constrcture = env->GetMethodID(javaClass, "<init>", "()V");
    jobject javaClassObj = env->NewObject(javaClass, constrcture);
    jmethodID setVersion = env->GetMethodID(javaClass, "setVersion", "(Ljava/lang/String;)V");
    env->CallVoidMethod(javaClassObj, setVersion, env->NewStringUTF("1.1.1"));
    return javaClassObj;
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_jnidemo_classMethodOperator_ClassMethodOperator_operatorClassStaticMethod(
        JNIEnv *env, jclass clazz) {
    jclass javaClass = env->FindClass("com/anniljing/jnidemo/JavaClass");
    jmethodID constrcture = env->GetMethodID(javaClass, "<init>", "()V");
    jobject javaClassObj = env->NewObject(javaClass, constrcture);
    jmethodID staticCode=env->GetStaticMethodID(javaClass,"setCode", "(I)V");
    env->CallStaticVoidMethod(javaClass,staticCode,11);
    return javaClassObj;
}
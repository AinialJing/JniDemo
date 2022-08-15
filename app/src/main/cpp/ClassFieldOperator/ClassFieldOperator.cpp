#include <jni.h>
#include <AndroidLog.h>

extern "C"
JNIEXPORT jobject JNICALL
Java_com_anniljing_jnidemo_ClassFieldOperator_ClassFieldOperator_classFieldOperator(JNIEnv *env,
                                                                                    jobject thiz) {
    jclass javaClass = env->FindClass("com/anniljing/jnidemo/JavaClass");
    jmethodID constructor = env->GetMethodID(javaClass, "<init>", "()V");
    jobject obj = env->NewObject(javaClass, constructor);
    jfieldID versionId = env->GetFieldID(javaClass, "version", "Ljava/lang/String;");
    jobject versionValue = env->GetObjectField(obj, versionId);
    jstring value=((jstring) versionValue);
    //不能使用%s打印jstring，需要做一下处理
    const char *c_str = NULL;
    char buff[128] = {0};
    jboolean isCopy;    // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
    c_str = env->GetStringUTFChars(value, &isCopy);
    LOGD("Current version value: %s", c_str);
    env->SetObjectField(obj, versionId, env->NewStringUTF("Version:1.00.00"));
    return obj;
}


#include <jni.h>
#include <AndroidLog.h>
#include <string.h>
#include <stdlib.h>

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_anniljing_jnidemo_ArrayHandle_ArrayHandle_getArrayData(JNIEnv *env, jclass clazz) {
    jintArray intArray = env->NewIntArray(10);
    //通过GetIntArrayElements拿到C类型的数组的指针，然后才能进行C数组的操作
    jint *element = env->GetIntArrayElements(intArray, NULL);
    LOGD("Before GetIntArrayElements element[0]:%d", *element);
    jint len = env->GetArrayLength(intArray);
    for (int i = 0; i < len; ++i) {
        *(element + i) = (i * 10 + 1);
        LOGD("For intArray:address(%p),value(%d)", (element + i), *(element + i));
        LOGD("elment address:%p", element);
    }
    env->ReleaseIntArrayElements(intArray, element, 0);
    return intArray;
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_anniljing_jnidemo_ArrayHandle_ArrayHandle_handleJavaArray(JNIEnv *env, jclass clazz,
                                                                   jintArray java_data) {
    jintArray result = env->NewIntArray(2);
    jint buf[2];
    //将java_data数据复制到buf里面
    env->GetIntArrayRegion(java_data, 0, 2, buf);
    for (int i = 0; i < 2; ++i) {
        LOGD("buf data:%d", buf[i]);
    }
    //将buf数据复制到result里面
    env->SetIntArrayRegion(result, 0, 2, buf);
    return result;
}
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_anniljing_jnidemo_ArrayHandle_ArrayHandle_handleStringArray(JNIEnv *env, jclass clazz,
                                                                     jobjectArray src_data) {
    jint len = env->GetArrayLength(src_data);
    jboolean isCopy = false;
    for (int i = 0; i < len; ++i) {
        const char *content = NULL;
        jstring element = static_cast<jstring>(env->GetObjectArrayElement(src_data, i));
        content = env->GetStringUTFChars(element, &isCopy);
        const size_t contentLen = strlen(content);
        char *replace = new char[contentLen + 1];
        strncpy(replace, content, contentLen);
        memcpy(replace, "李", strlen("李"));
        jstring last = env->NewStringUTF(replace);
        env->SetObjectArrayElement(src_data, i, last);
        LOGD("Replace content:%s", replace);
        delete[] replace;
    }
    return src_data;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_anniljing_jnidemo_ArrayHandle_ArrayHandle_handleObjectArray(JNIEnv *env, jclass clazz,
                                                                     jobjectArray objects) {
    jclass javaClass = env->FindClass("com/anniljing/jnidemo/JavaClass");
    int len = env->GetArrayLength(objects);
    for (int i = 0; i < len; ++i) {
        jobject javaJObject = env->GetObjectArrayElement(objects, i);
        jfieldID versionField = env->GetFieldID(javaClass, "version", "Ljava/lang/String;");
        jstring versionValue = static_cast<jstring>(env->GetObjectField(javaJObject, versionField));
        const char *_version = NULL;
        _version = env->GetStringUTFChars(versionValue, NULL);
        LOGD("%s", _version);
        char *nativeVersion = new char[30];
        strcpy(nativeVersion, "Native version v1.0.");
        char *index = new char[10];
        sprintf(index, "%d", i);
        strcat(nativeVersion, index);

        jmethodID setVersion = env->GetMethodID(javaClass, "setVersion", "(Ljava/lang/String;)V");
        env->CallVoidMethod(javaJObject, setVersion, env->NewStringUTF(nativeVersion));
        env->SetObjectArrayElement(objects, i, javaJObject);
    }

    return objects;
}
#include <jni.h>
#include <AndroidLog.h>

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_anniljing_jnidemo_ArrayHandle_ArrayHandle_getArrayData(JNIEnv *env, jclass clazz) {
    jintArray intArray = env->NewIntArray(10);
    //通过GetIntArrayElements拿到C类型的数组的指针，然后才能进行C数组的操作
    jint *element = env->GetIntArrayElements(intArray, NULL);
    LOGD("Before GetIntArrayElements element[0]:%d", *element);
    jint len = env->GetArrayLength(intArray);
    for (int i = 0; i < len; ++i) {
        *element = (i * 10 + 1);
        LOGD("For intArray:address(%p),value(%d)", element, *element);
        element++;
    }
    element = element - len;
    LOGD("After GetIntArrayElements:%d", *element);
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
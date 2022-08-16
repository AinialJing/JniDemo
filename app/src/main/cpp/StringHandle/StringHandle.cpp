#include <jni.h>
#include <AndroidLog.h>
#include <cstdlib>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_anniljing_jnidemo_StringHandle_StringHandle_stringHandle(JNIEnv *env, jclass clazz) {
    jstring newNativeString = env->NewStringUTF("Hello string from native");
    //定义一个const char数组
    const char *_str = NULL;
    jsize stringSize = env->GetStringLength(newNativeString);
    LOGD("String size is:%d", stringSize);
    jboolean isCopy = false;
    //将java字符串转为UTF-8格式的const char数组
    _str = env->GetStringUTFChars(newNativeString, &isCopy);
    LOGD("GetStringUTFChars is：%s", _str);
    env->ReleaseStringUTFChars(newNativeString,_str);
    //在栈上分配buffer，不需要手动释放，函数结束自动释放
    char inputbuf[128];
    env->GetStringUTFRegion(newNativeString, 0, 6, inputbuf);
    LOGD("GetStringUTFRegion is：%s", inputbuf);
    //在自由存储区分配buffer空间。自由存储区不仅可以是堆，还可以是静态存储区
    char *p = new char[128];
    env->GetStringUTFRegion(newNativeString,0,6,p);
    LOGD("GetStringUTFRegion with new:%s",p);
    //释放自由存储区空间，与new[]关键字成对使用
    delete[] p;

    //在堆分配buffer空间
    char *ptr = (char *)malloc(sizeof(char) * 6);
    env->GetStringUTFRegion(newNativeString,0,6,ptr);
    LOGD("GetStringUTFRegion with malloc:%s",ptr);
    //释放堆空间，与malloc函数成对使用
    free(ptr);

    //释放const char数组
    env->ReleaseStringUTFChars(newNativeString, _str);
    return newNativeString;
}
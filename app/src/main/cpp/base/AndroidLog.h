//头文件只有被其他CPP文件依赖以后才能正常导入
#include <android/log.h>
#include <jni.h>

#ifndef JNIDEMO_ANDROIDLOG_H
#define JNIDEMO_ANDROIDLOG_H

#define TAG "JniDemo"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
#endif //JNIDEMO_ANDROIDLOG_H

//
// Created by WRTRD02 on 2022-08-24.
//

#ifndef JNIDEMO_UNIXLOG_H
#define JNIDEMO_UNIXLOG_H

#include <android/log.h>
#define LOG_TAG "UnixLog"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)

#endif //JNIDEMO_UNIXLOG_H

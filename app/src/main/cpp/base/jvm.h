#include <android/log.h>
#include <jni.h>

#ifndef JNIDEMO_JVM_H
#define JNIDEMO_JVM_H
#include <AndroidLog.h>
#include <jni.h>
#ifdef __cplusplus
extern "C" {
#endif
void setJvm(JavaVM *jvm);


JavaVM *getJvm();
#ifdef __cplusplus
}
#endif


#endif //JNIDEMO_JVM_H

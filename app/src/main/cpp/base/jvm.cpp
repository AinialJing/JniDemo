#include "jvm.h"
static  JavaVM *gVm= nullptr;
#ifdef __cplusplus
extern "C"{
#endif

void setJvm(JavaVM *jvm){
    gVm=jvm;
}

JavaVM * getJvm(){
    return gVm;
}
#ifdef __cplusplus
};
#endif

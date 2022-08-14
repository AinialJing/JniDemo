#include <jni.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_jnidemo_ClassFieldOperator_ClassStaticFieldOperator_setClassStaticField(
        JNIEnv *env, jclass clazz, jobject static_field_class) {
    jclass staticField = env->GetObjectClass(static_field_class);
    jfieldID staticFieldId = env->GetStaticFieldID(staticField, "name", "Ljava/lang/String;");
    env->SetStaticObjectField(staticField, staticFieldId, env->NewStringUTF("我是静态属性"));
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_anniljing_jnidemo_ClassFieldOperator_ClassStaticFieldOperator_getClassStaticField(
        JNIEnv *env, jclass clazz, jobject static_field_class) {
    jclass staticClass = env->GetObjectClass(static_field_class);
    jfieldID nameField = env->GetStaticFieldID(staticClass, "name", "Ljava/lang/String;");
    return static_cast<jstring>(env->GetStaticObjectField(staticClass, nameField));
}
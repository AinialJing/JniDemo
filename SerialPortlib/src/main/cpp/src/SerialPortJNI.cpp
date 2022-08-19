#include <jni.h>
#include <string>
#include "../include/SerialPort.h"
#include "../include/SerialPortLog.h"

SerialPort serialPort;

extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_serialportlib_SerialPortJNI_openSerialPort(JNIEnv *env, jclass clazz, jstring path,
                                                              jint baud_rate, jint data_bits, jint stop_bits, jchar parity) {
    try {
        SerialPortConfig config;
        config.baudrate = baud_rate;
        config.dataBits = data_bits;
        config.stopBits = stop_bits;
        config.parity = parity;
        serialPort = SerialPort(env->GetStringUTFChars(path, 0));
        return serialPort.openSerialPort(config);
    } catch (char *exception) {
        LOGE("Open device is error! Message:%s", exception);
        return FALSE;
    }

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_anniljing_serialportlib_SerialPortJNI_setMode(JNIEnv *env, jclass clazz, jint mode) {
    return serialPort.setMode(mode);
}
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_anniljing_serialportlib_SerialPortJNI_readData(JNIEnv *env, jclass clazz, jint max_size) {
    BYTE buf[max_size];
    int len = serialPort.readData(buf, max_size);
    if (len < 1) return NULL;
    jbyteArray byteArray;
    //强转为jni层的byte
    jbyte *bytes = reinterpret_cast<jbyte *>(buf);
    //创建jni层的数组
    byteArray = env->NewByteArray(len);
    //把C层的数据写入到jni层的数组里面
    env->SetByteArrayRegion(byteArray, 0, len, bytes);
    return byteArray;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_serialportlib_SerialPortJNI_writeData(JNIEnv *env, jclass clazz, jbyteArray datas) {
    //获取数组首元素
    jbyte *data = env->GetByteArrayElements(datas, 0);
    //获取数组的长度
    int len = env->GetArrayLength(datas);
    //强转类型
    BYTE *bytes = reinterpret_cast<BYTE *>(data);
    serialPort.writeData(bytes, len);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_anniljing_serialportlib_SerialPortJNI_closePort(JNIEnv *env, jclass clazz) {
    serialPort.closePort();
    serialPort = NULL;
}
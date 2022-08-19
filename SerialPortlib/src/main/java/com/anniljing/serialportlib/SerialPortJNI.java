package com.anniljing.serialportlib;

public class SerialPortJNI {

    static {
        System.loadLibrary("SerialPortlib");
    }

    /**
     * @brief 打开串口并设置串口数据位，校验位, 速率，停止位
     * @param path 串口地址
     * @param baudRate 串口波特率
     * @param dataBits 串口的数据位
     * @param stopBits 串口的结束位
     * @param parity   串口的检验位
     * @return
     */
    public static native int openSerialPort(String path,int baudRate,int dataBits,int stopBits,char parity);

    /**
     * @brief 设置是否使用原始模式(Raw Mode)方式来通讯 取值0,1,2
     * @param mode 0=nothing
     *             1=Raw mode
     *             2=no raw mode
     * @return
     */
    public static native int setMode(int mode);

    /**
     * @brief 读取数据
     * @param maxSize
     * @return
     */
    public static native byte[] readData(int maxSize);

    /**
     * @brief 写入数据
     * @param datas
     */
    public static native void writeData(byte[] datas);

    /**
     * 关闭串口
     */
    public static native void closePort();
}
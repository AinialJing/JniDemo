package com.anniljing.unixlearn;

public class UnixNativeLib {

    static {
        System.loadLibrary("unixlearn");
    }

    public static native int creatFile(String path);

    public static native int openFile(String path);

    public static native int readFile(String file);

    public static native int writeFile(byte[] data);

    public static native int lseekFile(byte[] data);

    public static native int closeFile(String file);
}
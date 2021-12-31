package com.anniljing.jnidemo;

public class BasicTypeNative {
    static {
        System.loadLibrary("basicType-lib");
    }

    public native int callNativeInt(int num);
}

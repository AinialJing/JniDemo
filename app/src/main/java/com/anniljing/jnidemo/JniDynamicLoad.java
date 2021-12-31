package com.anniljing.jnidemo;

public class JniDynamicLoad {
    static {
        System.loadLibrary("dynamicLoad-lib");
    }

    public native int sum(int x, int y);

    public native String getNativeString();
}

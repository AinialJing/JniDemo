package com.anniljing.jnidemo;

public class JniDynamicLoad {
    public native int sum(int x, int y);

    public native String getNativeString();
}

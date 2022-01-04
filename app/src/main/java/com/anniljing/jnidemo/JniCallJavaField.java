package com.anniljing.jnidemo;

public class JniCallJavaField {
    static {
        System.loadLibrary("jniCallJavaClassField-lib");
    }

    public native void initPeopleData(People people);
}

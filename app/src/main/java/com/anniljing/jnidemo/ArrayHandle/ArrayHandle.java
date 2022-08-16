package com.anniljing.jnidemo.ArrayHandle;

public class ArrayHandle {
    public static native int[] getArrayData();

    public static native int[] handleJavaArray(int[] srcData);
}

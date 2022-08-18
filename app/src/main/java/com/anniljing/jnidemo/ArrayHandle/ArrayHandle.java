package com.anniljing.jnidemo.ArrayHandle;

public class ArrayHandle {
    public static native int[] getArrayData();

    public static native int[] handleJavaArray(int[] srcData);

    public static native String[] handleStringArray(String[] srcData);

    public static native Object[] handleObjectArray(Object[] objects);

}

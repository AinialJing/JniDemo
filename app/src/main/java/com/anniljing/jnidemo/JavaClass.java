package com.anniljing.jnidemo;

import android.util.Log;

public class JavaClass {
    public static String name;
    private String version = "hello";
    private static int sCode;

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public static void setCode(int code) {
        sCode = code;
    }

    @Override
    public String toString() {
        return "JavaClass{" +
                "version='" + version + '\'' + "Code=" + sCode + '\'' +
                '}';
    }

    public void getResulte() {
        int data[]=new int[2];
        data[3]=5;
        Log.d("JavaClass", "getResulte");
    }
}

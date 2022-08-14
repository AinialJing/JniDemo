package com.anniljing.jnidemo;

import android.util.Log;

public class JavaClass {
    public static String name;
    private String version;
    private static int sCode;

    public JavaClass() {
        Log.d("MainActivity","Init JavaClass");
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public static void setCode(int code){
        sCode=code;
    }

    @Override
    public String toString() {
        return "JavaClass{" +
                "version='" + version + '\''+"Code="+sCode+'\'' +
                '}';
    }
}

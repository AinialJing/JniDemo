package com.anniljing.jnidemo.ClassFieldOperator;

import com.anniljing.jnidemo.StaticFieldClass;

public class ClassStaticFieldOperator {

    public static native void setClassStaticField(StaticFieldClass staticFieldClass);
    public static native String getClassStaticField(StaticFieldClass staticFieldClass);
}

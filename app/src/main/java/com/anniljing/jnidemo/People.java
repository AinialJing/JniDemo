package com.anniljing.jnidemo;

import android.util.Log;

public class People {
    public int age;
    public String name;

    public void doIntroduce() {
        Log.d("People", "My name is " + name + ",I am " + age + "years old!");
    }
}

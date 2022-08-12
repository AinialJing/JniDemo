package com.anniljing.jnidemo;

public class JniThread {
    public native void createNativeThread();

    public native void createNativeThreadWithArgs();

    public native void joinNativeThread();

    public native void startProductAndConsumerThread();
}

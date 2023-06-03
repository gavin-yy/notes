package com.example.calc;

public class JNI {
    {
        System.loadLibrary("mycjni");
    }

    public native String sayHello();

    public native int calc(int a, int b);
}




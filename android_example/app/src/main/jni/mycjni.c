#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

JNIEXPORT jstring JNICALL Java_com_example_calc_JNI_sayHello(JNIEnv *env, jobject jobj)
{
    char *text = "txt from c";
    return (*env)->NewStringUTF(env, text);
}

JNIEXPORT jint JNICALL Java_com_example_calc_JNI_calc(JNIEnv *env, jobject jobj, jint a, jint b)
{
    return a + b;
}


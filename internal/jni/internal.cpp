#include <jni.h>
#include <include/internal.hpp>
#include <android/log.h>


extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_example_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject, /* this */
        jint jjint) {
    

    int tmp = jjint;
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "Value %d", jjint);
    string test = i + return_string(to_string(tmp));

    return env->NewStringUTF(test.c_str());
}
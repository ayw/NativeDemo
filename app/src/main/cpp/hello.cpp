#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nativedemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    return env->NewStringUTF("hello world");
}

// 动态注册的函数
jstring dynamicRegisterFunction(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("hello, I'm from dynamicRegisterFunction");
}

// 在动态库加载时进行函数注册
int JNI_OnLoad(JavaVM *javaVM, void *reserved) {
    JNIEnv *jniEnv;

    if (javaVM->GetEnv((void **) (&jniEnv), JNI_VERSION_1_4) != JNI_OK) {
        return JNI_ERR;
    }
    jclass registerClass = jniEnv->FindClass("com/example/nativedemo/MainActivity");
    JNINativeMethod jniNativeMethods[] = {
            // name signature nativeFunction
            {"dynamicRegisterFunction", "()Ljava/lang/String;",
             (void *) (dynamicRegisterFunction)}
    };
    if (jniEnv->RegisterNatives(registerClass, jniNativeMethods,
                                sizeof(jniNativeMethods) / sizeof((jniNativeMethods)[0])) < 0) {
        return JNI_ERR;
    } else {
        return JNI_VERSION_1_4;
    }
}

//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//



#ifndef MY_APPLICATION_JNIIMPL_H
#define MY_APPLICATION_JNIIMPL_H

#include "jni.h"
#include "LogUtil.h"
#include "GLUtils.h"
#include "MyGLRenderContext.h"


#define NATIVE_RENDER_CLASS_NAME "com/mihoyo/opengl/core/MyNativeRender"

extern "C"
JNIEXPORT void JNICALL
native_Init(JNIEnv *env, jobject thiz) {
    LOGCATE("native_Init ");

}

extern "C"
JNIEXPORT void JNICALL
native_OnSurfaceCreated(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

extern "C"
JNIEXPORT void JNICALL
native_OnSurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
native_OnDrawFrame(JNIEnv *env, jobject thiz) {

    MyGLRenderContext::GetInstance()->OnDrawFrame();

}


static JNINativeMethod g_RenderMethods[] = {
        {"native_Init",             "()V",   (void *) (native_Init)},
        {"native_OnSurfaceCreated", "()V",   (void *) (native_OnSurfaceCreated)},
        {"native_OnSurfaceChanged", "(II)V", (void *) (native_OnSurfaceChanged)},
        {"native_OnDrawFrame",      "()V",   (void *) (native_OnDrawFrame)},
};


static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum) {
    LOGCATE("RegisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        LOGCATE("RegisterNativeMethods fail. clazz == NULL");
        return JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, methods, methodNum) < 0) {
        LOGCATE("RegisterNativeMethods fail");
        return JNI_FALSE;
    }

    return JNI_TRUE;
}


static void UnregisterNativeMethods(JNIEnv *env, const char *className) {
    LOGCATE("UnregisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
        return;
    }
    if (env != NULL) {
        env->UnregisterNatives(clazz);
    }
}

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = NULL;

    // Get JNIEnv pointer for this thread
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    jint regRet = RegisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME,
                                        g_RenderMethods,
                                        sizeof(g_RenderMethods) / sizeof(g_RenderMethods[0]));

    if (regRet != JNI_TRUE) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}



extern "C" JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved) {

    JNIEnv *env = NULL;

    // Get JNIEnv pointer for this thread
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);
}

#endif //MY_APPLICATION_JNIIMPL_H



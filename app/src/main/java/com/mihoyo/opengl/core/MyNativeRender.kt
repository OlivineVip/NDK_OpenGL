package com.mihoyo.opengl.core

class MyNativeRender {


    init {
        System.loadLibrary("render")
    }

    external fun native_Init()

    external fun native_OnSurfaceCreated()

    external fun native_OnSurfaceChanged(width: Int, height: Int)

    external fun native_OnDrawFrame()
}
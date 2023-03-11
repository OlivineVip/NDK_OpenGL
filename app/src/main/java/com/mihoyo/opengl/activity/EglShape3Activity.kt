package com.mihoyo.opengl.activity

import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.mihoyo.opengl.core.MyNativeRender
import com.mihoyo.opengl.databinding.ActivityEglShape3Binding
import com.mihoyo.opengl.databinding.ActivityEglShapeBinding
import com.mihoyo.opengl.render.Triangle
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class EglShape3Activity : AppCompatActivity() {
    private val binding: ActivityEglShape3Binding by lazy { ActivityEglShape3Binding.inflate(layoutInflater) }

    private val nativeRender: MyNativeRender by lazy {
        MyNativeRender()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)

        binding.glSurface.setEGLContextClientVersion(3)
        binding.glSurface.setRenderer(MyRender())
        binding.glSurface.renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY;


    }


    inner class MyRender : GLSurfaceView.Renderer {

        override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
            nativeRender.native_OnSurfaceCreated()
        }

        override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
            nativeRender.native_OnSurfaceChanged(width, height)
        }

        override fun onDrawFrame(gl: GL10?) {
            nativeRender.native_OnDrawFrame()
        }
    }


}
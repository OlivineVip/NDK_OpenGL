package com.mihoyo.opengl.activity

import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.mihoyo.opengl.databinding.ActivityEglShapeBinding
import com.mihoyo.opengl.databinding.ActivityMainBinding
import com.mihoyo.opengl.render.Triangle

class EglShapeActivity : AppCompatActivity() {

    private val binding: ActivityEglShapeBinding by lazy { ActivityEglShapeBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)

        binding.glSurface.setEGLContextClientVersion(2)
        binding.glSurface.setRenderer(Triangle())
        binding.glSurface.renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY;


    }


}
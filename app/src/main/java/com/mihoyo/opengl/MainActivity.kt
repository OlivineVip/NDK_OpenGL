package com.mihoyo.opengl

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.mihoyo.opengl.activity.EglShape3Activity
import com.mihoyo.opengl.activity.EglShapeActivity
import com.mihoyo.opengl.core.MyNativeRender
import com.mihoyo.opengl.databinding.ActivityMainBinding
import org.webrtc.SurfaceEglRenderer

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)


        binding.btnEgl.setOnClickListener {
            startActivity(Intent(this@MainActivity, EglShapeActivity::class.java))
        }

        binding.btnEgl3.setOnClickListener {
            startActivity(Intent(this@MainActivity, EglShape3Activity::class.java))
        }


        MyNativeRender().native_Init()
    }

}
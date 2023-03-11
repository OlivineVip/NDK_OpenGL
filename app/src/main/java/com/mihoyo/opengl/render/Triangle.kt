package com.mihoyo.opengl.render

import android.opengl.GLES20
import android.opengl.GLSurfaceView
import com.mihoyo.opengl.utils.ShaderUtil
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class Triangle : GLSurfaceView.Renderer {
    private val vertexShaderCode = "attribute vec4 vPosition;" +
            "void main() {" +
            "  gl_Position = vPosition;" +
            "}"

    private val fragmentShaderCode = "precision mediump float;" +
            "uniform vec4 vColor;" +
            "void main() {" +
            "  gl_FragColor = vColor;" +
            "}"


    var triangleCoords = floatArrayOf(
        0.5f, 0.5f, 0.0f,  // top
        -0.5f, -0.5f, 0.0f,  // bottom left
        0.5f, -0.5f, 0.0f // bottom right
    )

    private val COORDS_PER_VERTEX = 3

    //顶点之间的偏移量
    private val vertexStride = COORDS_PER_VERTEX * 4 // 每个顶点四个字节

    //顶点个数
    private val vertexCount: Int = triangleCoords.size / COORDS_PER_VERTEX


    //设置颜色，依次为红绿蓝和透明通道
    var color = floatArrayOf(0.9f, 0.5f, 0.4f, 1.0f)


    private lateinit var vertexBuffer: FloatBuffer
    private var mProgram = 0
    fun load() {
        val bb = ByteBuffer.allocateDirect(
            triangleCoords.size * 4
        )
        bb.order(ByteOrder.nativeOrder())
        vertexBuffer = bb.asFloatBuffer()
        vertexBuffer.put(triangleCoords)
        vertexBuffer.position(0)
        mProgram = ShaderUtil.createProgram(vertexShaderCode, fragmentShaderCode)
    }


    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        load()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
    }

    override fun onDrawFrame(gl: GL10) {
        GLES20.glClearColor(1.0f, 0f, 0f, 1f)
        GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT or GLES20.GL_COLOR_BUFFER_BIT)

        //将程序加入到OpenGLES2.0环境
        GLES20.glUseProgram(mProgram);
        //获取顶点着色器的vPosition成员句柄
        val mPositionHandle = GLES20.glGetAttribLocation(mProgram, "vPosition");
        //启用三角形顶点的句柄
        GLES20.glEnableVertexAttribArray(mPositionHandle);
        //准备三角形的坐标数据
        GLES20.glVertexAttribPointer(
            mPositionHandle, COORDS_PER_VERTEX,
            GLES20.GL_FLOAT, false,
            vertexStride, vertexBuffer
        )


        //获取片元着色器的vColor成员的句柄
        val mColorHandle = GLES20.glGetUniformLocation(mProgram, "vColor");
        //设置绘制三角形的颜色
        GLES20.glUniform4fv(mColorHandle, 1, color, 0)
        //绘制三角形
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, vertexCount)
        //禁止顶点数组的句柄
        GLES20.glDisableVertexAttribArray(mPositionHandle)

    }
}
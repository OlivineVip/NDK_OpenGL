package com.mihoyo.opengl.utils

import android.opengl.GLES20
import android.util.Log

object ShaderUtil {


    /**
     * 加载制定shader的方法
     * @param shaderType GL_VERTEX_SHADER、GL_FRAGMENT_SHADER
     * @param source   shader的脚本字符串
     */
    fun loadShader(shaderType: Int, source: String): Int {
        //创建一个新shader
        var shader = GLES20.glCreateShader(shaderType)
        //若创建成功则加载shader
        if (shader != 0) {
            //加载shader的源代码
            GLES20.glShaderSource(shader, source)
            //编译shader
            GLES20.glCompileShader(shader)
            //存放编译成功shader数量的数组
            val compiled = IntArray(1)
            //获取Shader的编译情况
            GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compiled, 0)
            if (compiled[0] == 0) { //若编译失败则显示错误日志并删除此shader
                Log.e("ES30_ERROR", "Could not compile shader $shaderType:")
                Log.e("ES30_ERROR", GLES20.glGetShaderInfoLog(shader))
                GLES20.glDeleteShader(shader)
                shader = 0
            }
        }
        return shader
    }


    /**
     * 创建shader程序的方法
     */
    fun createProgram(vertexSource: String, fragmentSource: String): Int {
        //加载顶点着色器
        val vertexShader = loadShader(GLES20.GL_VERTEX_SHADER, vertexSource)
        if (vertexShader == 0) {
            return 0
        }

        //加载片元着色器
        val pixelShader = loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentSource)
        if (pixelShader == 0) {
            return 0
        }

        //创建程序
        var program = GLES20.glCreateProgram()
        //若程序创建成功则向程序中加入顶点着色器与片元着色器
        if (program != 0) {
            //向程序中加入顶点着色器
            GLES20.glAttachShader(program, vertexShader)
            checkGlError("glAttachShader")
            //向程序中加入片元着色器
            GLES20.glAttachShader(program, pixelShader)
            checkGlError("glAttachShader")
            //链接程序
            GLES20.glLinkProgram(program)
            //存放链接成功program数量的数组
            val linkStatus = IntArray(1)
            //获取program的链接情况
            GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linkStatus, 0)
            //若链接失败则报错并删除程序
            if (linkStatus[0] != GLES20.GL_TRUE) {
                Log.e("ES30_ERROR", "Could not link program: ")
                Log.e("ES30_ERROR", GLES20.glGetProgramInfoLog(program))
                GLES20.glDeleteProgram(program)
                program = 0
            }
        }
        return program
    }

    //检查每一步操作是否有错误的方法
    fun checkGlError(op: String) {
        var error: Int
        while (GLES20.glGetError().also { error = it } != GLES20.GL_NO_ERROR) {
            Log.e("ES30_ERROR", "$op: glError $error")
            throw RuntimeException("$op: glError $error")
        }
    }


}
//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//

#include "GLUtils.h"
#include "LogUtil.h"
#include <GLES3/gl3.h>
#include <stdlib.h>


GLint GLUtils::LoadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = 0;
    FUN_BEGIN_TIME("GLUtils::LoadShader")
        //创建一个新shader
        shader = glCreateShader(shaderType);
        if (shader) {
            //加载shader的源代码
            glShaderSource(shader, 1, &pSource, NULL);
            //编译shader
            glCompileShader(shader);
            GLint compiled = 0;
            //获取Shader的编译情况
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen) {
                    char *buf = (char *) malloc((size_t) infoLen);
                    if (buf) {
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        LOGCATE("GLUtils::LoadShader Could not compile shader %d:\n%s\n", shaderType, buf);
                        free(buf);
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
        }
    FUN_END_TIME("GLUtils::LoadShader")
    return shader;
}

GLuint
GLUtils::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource, GLuint &vertexShaderHandle,
                       GLuint &fragShaderHandle) {
    GLuint program = 0;

    //加载顶点着色器
    vertexShaderHandle = LoadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if (!vertexShaderHandle) {
        return program;
    }

    //加载片元着色器
    fragShaderHandle = LoadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if (!fragShaderHandle) {
        return program;
    }

    //创建程序
    program = glCreateProgram();
    if (program) {
        //向程序中加入顶点着色器
        glAttachShader(program, vertexShaderHandle);
        CheckGLError("glAttachShader");
        //向程序中加入片元着色器
        glAttachShader(program, fragShaderHandle);
        CheckGLError("glAttachShader");
        //链接程序
        glLinkProgram(program);

        //获取program的链接情况
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        //分离&删除着色器
        glDetachShader(program, vertexShaderHandle);
        glDeleteShader(vertexShaderHandle);
        vertexShaderHandle = 0;

        //分离&删除着色器
        glDetachShader(program, fragShaderHandle);
        glDeleteShader(fragShaderHandle);
        fragShaderHandle = 0;

        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc((size_t) bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGCATE("GLUtils::CreateProgram Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}


void GLUtils::CheckGLError(const char *pGLOperation) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGCATE("GLUtils::CheckGLError GL Operation %s() glError (0x%x)\n", pGLOperation, error);
    }
}




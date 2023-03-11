//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//

#ifndef MY_APPLICATION_GLUTILS_H
#define MY_APPLICATION_GLUTILS_H

#include <GLES3/gl3.h>
#include <stdlib.h>

class GLUtils {

public:

    static GLint LoadShader(GLenum shaderType, const char *pSource);


    static void CheckGLError(const char *pGLOperation);


    static GLuint
    CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource, GLuint &vertexShaderHandle,
                  GLuint &fragShaderHandle);
};


#endif //MY_APPLICATION_GLUTILS_

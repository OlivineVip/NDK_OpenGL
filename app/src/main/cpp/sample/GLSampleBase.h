//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//

#ifndef MY_APPLICATION_GLSAMPLEBASE_H
#define MY_APPLICATION_GLSAMPLEBASE_H

#include <GLES3/gl3.h>

class GLSampleBase {
public:
    GLSampleBase() {
        m_ProgramObj = 0;
        m_VertexShader = 0;
        m_FragmentShader = 0;

        m_SurfaceWidth = 0;
        m_SurfaceHeight = 0;

    }

    virtual ~GLSampleBase() {

    }


    virtual void Init() = 0;

    virtual void Draw(int screenW, int screenH) = 0;

    virtual void Destroy() = 0;


protected:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ProgramObj;
    int m_SurfaceWidth;
    int m_SurfaceHeight;
};

#endif //MY_APPLICATION_GLSAMPLEBASE_H

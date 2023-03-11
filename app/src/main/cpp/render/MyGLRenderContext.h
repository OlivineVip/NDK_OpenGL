//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//

#ifndef MY_APPLICATION_MYGLRENDERCONTEXT_H
#define MY_APPLICATION_MYGLRENDERCONTEXT_H

#include <GLES3/gl3.h>
#include "GLSampleBase.h"

class MyGLRenderContext {
    MyGLRenderContext();

    ~MyGLRenderContext();


public:
    void OnSurfaceCreated();

    void OnSurfaceChanged(int width, int height);

    void OnDrawFrame();

    static MyGLRenderContext *GetInstance();

    static void DestroyInstance();

private:
    static MyGLRenderContext *m_pContext;
    GLSampleBase *glSampleBase;
    int m_ScreenW;
    int m_ScreenH;


};


#endif //MY_APPLICATION_MYGLRENDERCONTEXT_H

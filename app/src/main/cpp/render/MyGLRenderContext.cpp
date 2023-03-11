//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//

#include "MyGLRenderContext.h"
#include "../util/LogUtil.h"
#include "../sample/TriangleSample.h"

// todo 为什么
MyGLRenderContext *MyGLRenderContext::m_pContext = nullptr;

MyGLRenderContext::MyGLRenderContext() {
    glSampleBase = new TriangleSample();

}

MyGLRenderContext::~MyGLRenderContext() {
    if (glSampleBase) {
        delete glSampleBase;
        glSampleBase = nullptr;
    }

}

void MyGLRenderContext::OnSurfaceCreated() {
    glSampleBase->Init();
}

void MyGLRenderContext::OnSurfaceChanged(int width, int height) {
    m_ScreenW = width;
    m_ScreenH = height;
}

void MyGLRenderContext::OnDrawFrame() {
    LOGCATE("MyGLRenderContext::OnDrawFrame");
    glSampleBase->Draw(m_ScreenW, m_ScreenH);

}

MyGLRenderContext *MyGLRenderContext::GetInstance() {
    if (m_pContext == nullptr) {
        m_pContext = new MyGLRenderContext();
    }
    return m_pContext;
}


void MyGLRenderContext::DestroyInstance() {
    if (m_pContext) {
        delete m_pContext;
        m_pContext = nullptr;
    }
}

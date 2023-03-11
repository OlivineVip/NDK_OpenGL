//
// Created by 杨永路(Yonglu.Y) on 2023/3/11.
//

#ifndef MY_APPLICATION_TRIANGLESAMPLE_H
#define MY_APPLICATION_TRIANGLESAMPLE_H

#include <GLES3/gl3.h>
#include "GLSampleBase.h"

class TriangleSample: public GLSampleBase{

public:

    void Init();

    void Draw(int with, int height);

    void Destroy();


};


#endif //MY_APPLICATION_TRIANGLESAMPLE_H

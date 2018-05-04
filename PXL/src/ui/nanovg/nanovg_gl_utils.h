#ifndef _NANOVG_GL_UTILS_H
#define _NANOVG_GL_UTILS_H


#include "nanovg.h"

struct NVGLUframebuffer {
    NVGcontext * ctx;

    GLuint fbo;

    GLuint rbo;

    GLuint texture;

    int image;

};
#endif

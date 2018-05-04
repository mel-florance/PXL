#ifndef _NANOVG_GL_H
#define _NANOVG_GL_H


#include "nanovg.h"

struct NVGvertex;

// Create flags
enum NVGcreateFlags {
  NVG_ANTIALIAS =  1<<0,
  NVG_STENCIL_STROKES =  1<<1,
  NVG_DEBUG =  1<<2
};
// These are additional flags on top of NVGimageFlags.
enum NVGimageFlagsGL {
  NVG_IMAGE_NODELETE =  1<<16
};
enum GLNVGuniformLoc {
  GLNVG_LOC_VIEWSIZE,
  GLNVG_LOC_TEX,
  GLNVG_LOC_FRAG,
  GLNVG_MAX_LOCS
};
enum GLNVGshaderType {
  NSVG_SHADER_FILLGRAD,
  NSVG_SHADER_FILLIMG,
  NSVG_SHADER_SIMPLE,
  NSVG_SHADER_IMG
};
enum GLNVGuniformBindings {
  GLNVG_FRAG_BINDING =  0
};
struct GLNVGshader {
    GLuint prog;

    GLuint frag;

    GLuint vert;

    GLint loc[GLNVG_MAX_LOCS];

};
struct GLNVGtexture {
    int id;

    GLuint tex;

    int width;

    int height;

    int type;

    int flags;

};
struct GLNVGblend {
    GLenum srcRGB;

    GLenum dstRGB;

    GLenum srcAlpha;

    GLenum dstAlpha;

};
enum GLNVGcallType {
  GLNVG_NONE =  0,
  GLNVG_FILL,
  GLNVG_CONVEXFILL,
  GLNVG_STROKE,
  GLNVG_TRIANGLES
};
struct GLNVGcall {
    int type;

    int image;

    int pathOffset;

    int pathCount;

    int triangleOffset;

    int triangleCount;

    int uniformOffset;

    GLNVGblend blendFunc;

};
struct GLNVGpath {
    int fillOffset;

    int fillCount;

    int strokeOffset;

    int strokeCount;

};
struct GLNVGfragUniforms {
    // matrices are actually 3 vec4s
    float scissorMat[12];

    float paintMat[12];

    NVGcolor innerCol;

    NVGcolor outerCol;

    float scissorExt[2];

    float scissorScale[2];

    float extent[2];

    float radius;

    float feather;

    float strokeMult;

    float strokeThr;

    int texType;

    int type;

    NVGcolor ;

    NVGcolor ;

};
struct GLNVGcontext {
    GLNVGshader shader;

    GLNVGtexture * textures;

    float view[2];

    int ntextures;

    int ctextures;

    int textureId;

    GLuint vertBuf;

    GLuint vertArr;

    GLuint fragBuf;

    int fragSize;

    int flags;

    // Per frame buffers
    
    GLNVGcall * calls;

    int ccalls;

    int ncalls;

    GLNVGpath * paths;

    int cpaths;

    int npaths;

    NVGvertex * verts;

    int cverts;

    int nverts;

    unsigned char uniforms;

    int cuniforms;

    int nuniforms;

    GLuint boundTexture;

    GLuint stencilMask;

    GLenum stencilFunc;

    GLint stencilFuncRef;

    GLuint stencilFuncMask;

    GLNVGblend blendFunc;

};
#endif

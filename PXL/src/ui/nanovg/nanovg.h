#ifndef _NANOVG_H
#define _NANOVG_H


typedef NVGcontext NVGcontext;
struct NVGcolor {
    float rgba[4];

    float r;

    float g;

    float b;

    float a;

};
struct NVGpaint {
    float xform[6];

    float extent[2];

    float radius;

    float feather;

    NVGcolor innerColor;

    NVGcolor outerColor;

    int image;

};
enum NVGwinding {
  NVG_CCW =  1,
  NVG_CW =  2
};
// Winding for solid shapes
// Winding for holes
enum NVGsolidity {
  NVG_SOLID =  1,
  NVG_HOLE =  2
};
// CCW
// CW
enum NVGlineCap {
  NVG_BUTT,
  NVG_ROUND,
  NVG_SQUARE,
  NVG_BEVEL,
  NVG_MITER
};
enum NVGalign {
  NVG_ALIGN_LEFT =  1<<0,
  NVG_ALIGN_CENTER =  1<<1,
  NVG_ALIGN_RIGHT =  1<<2,
  NVG_ALIGN_TOP =  1<<3,
  NVG_ALIGN_MIDDLE =  1<<4,
  NVG_ALIGN_BOTTOM =  1<<5,
  NVG_ALIGN_BASELINE =  1<<6
};
// Horizontal align
// Default, align text horizontally to left.
// Align text horizontally to center.
// Align text horizontally to right.
// Vertical align
// Align text vertically to top.
// Align text vertically to middle.
// Align text vertically to bottom.
// Default, align text vertically to baseline.
enum NVGblendFactor {
  NVG_ZERO =  1<<0,
  NVG_ONE =  1<<1,
  NVG_SRC_COLOR =  1<<2,
  NVG_ONE_MINUS_SRC_COLOR =  1<<3,
  NVG_DST_COLOR =  1<<4,
  NVG_ONE_MINUS_DST_COLOR =  1<<5,
  NVG_SRC_ALPHA =  1<<6,
  NVG_ONE_MINUS_SRC_ALPHA =  1<<7,
  NVG_DST_ALPHA =  1<<8,
  NVG_ONE_MINUS_DST_ALPHA =  1<<9,
  NVG_SRC_ALPHA_SATURATE =  1<<10
};
enum NVGcompositeOperation {
  NVG_SOURCE_OVER,
  NVG_SOURCE_IN,
  NVG_SOURCE_OUT,
  NVG_ATOP,
  NVG_DESTINATION_OVER,
  NVG_DESTINATION_IN,
  NVG_DESTINATION_OUT,
  NVG_DESTINATION_ATOP,
  NVG_LIGHTER,
  NVG_COPY,
  NVG_XOR
};
struct NVGcompositeOperationState {
    int srcRGB;

    int dstRGB;

    int srcAlpha;

    int dstAlpha;

};
struct NVGglyphPosition {
    // Position of the glyph in the input string.
    const char str;

    // The x-coordinate of the logical glyph position.
    float x;

    float minx;

    // The bounds of the glyph shape.
    float maxx;

};
struct NVGtextRow {
    // Pointer to the input text where the row starts.
    const char start;

    // Pointer to the input text where the row ends (one past the last character).
    const char end;

    // Pointer to the beginning of the next row.
    const char next;

    // Logical width of the row.
    float width;

    float minx;

    // Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
    float maxx;

};
enum NVGimageFlags {
  NVG_IMAGE_GENERATE_MIPMAPS =  1<<0,
  NVG_IMAGE_REPEATX =  1<<1,
  NVG_IMAGE_REPEATY =  1<<2,
  NVG_IMAGE_FLIPY =  1<<3,
  NVG_IMAGE_PREMULTIPLIED =  1<<4,
  NVG_IMAGE_NEAREST =  1<<5
};
// Internal Render API

enum NVGtexture {
  NVG_TEXTURE_ALPHA =  0x01,
  NVG_TEXTURE_RGBA =  0x02
};
struct NVGscissor {
    float xform[6];

    float extent[2];

};
struct NVGvertex {
    float x;

    float y;

    float u;

    float v;

};
struct NVGpath {
    int first;

    int count;

    unsigned char closed;

    int nbevel;

    NVGvertex * fill;

    int nfill;

    NVGvertex * stroke;

    int nstroke;

    int winding;

    int convex;

};
struct NVGparams {
    void userPtr;

    int edgeAntiAlias;

    int (*)(void* uptr) renderCreate;

    int (*)(void* uptr, int type, int w, int h, int imageFlags, const unsigned char* data) renderCreateTexture;

    int (*)(void* uptr, int image) renderDeleteTexture;

    int (*)(void* uptr, int image, int x, int y, int w, int h, const unsigned char* data) renderUpdateTexture;

    int (*)(void* uptr, int image, int* w, int* h) renderGetTextureSize;

    void (*)(void* uptr, int width, int height, float devicePixelRatio) renderViewport;

    void (*)(void* uptr) renderCancel;

    void (*)(void* uptr) renderFlush;

    void (*)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, float fringe, const float* bounds, const NVGpath* paths, int npaths) renderFill;

    void (*)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, float fringe, float strokeWidth, const NVGpath* paths, int npaths) renderStroke;

    void (*)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, const NVGvertex* verts, int nverts) renderTriangles;

    void (*)(void* uptr) renderDelete;

};
#endif

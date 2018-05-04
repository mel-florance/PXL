#ifndef _FONTSTASH_H
#define _FONTSTASH_H


enum FONSflags {
  FONS_ZERO_TOPLEFT =  1,
  FONS_ZERO_BOTTOMLEFT =  2
};
enum FONSalign {
  FONS_ALIGN_LEFT =  1<<0,
  FONS_ALIGN_CENTER =  1<<1,
  FONS_ALIGN_RIGHT =  1<<2,
  FONS_ALIGN_TOP =  1<<3,
  FONS_ALIGN_MIDDLE =  1<<4,
  FONS_ALIGN_BOTTOM =  1<<5,
  FONS_ALIGN_BASELINE =  1<<6
};
// Horizontal align
// Default
// Vertical align
// Default
enum FONSglyphBitmap {
  FONS_GLYPH_BITMAP_OPTIONAL =  1,
  FONS_GLYPH_BITMAP_REQUIRED =  2
};
enum FONSerrorCode {
  FONS_ATLAS_FULL =  1,
  FONS_SCRATCH_FULL =  2,
  FONS_STATES_OVERFLOW =  3,
  FONS_STATES_UNDERFLOW =  4
};
// Font atlas is full.
// Scratch memory used to render glyphs is full, requested size reported in 'val', you may need to bump up FONS_SCRATCH_BUF_SIZE.
// Calls to fonsPushState has created too large stack, if you need deep state stack bump up FONS_MAX_STATES.
// Trying to pop too many states fonsPopState().
struct FONSparams {
    int width;

    int height;

    unsigned char flags;

    void userPtr;

    int (*)(void* uptr, int width, int height) renderCreate;

    int (*)(void* uptr, int width, int height) renderResize;

    void (*)(void* uptr, int* rect, const unsigned char* data) renderUpdate;

    void (*)(void* uptr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts) renderDraw;

    void (*)(void* uptr) renderDelete;

};
struct FONSquad {
    float x0;

    float y0;

    float s0;

    float t0;

    float x1;

    float y1;

    float s1;

    float t1;

};
struct FONStextIter {
    float x;

    float y;

    float nextx;

    float nexty;

    float scale;

    float spacing;

    unsigned int codepoint;

    short isize;

    short iblur;

    FONSfont * font;

    int prevGlyphIndex;

    const char str;

    const char next;

    const char end;

    unsigned int utf8state;

    int bitmapOption;

};
typedef FONScontext FONScontext;
struct FONSttFontImpl {
    FT_Face font;

};
struct FONSglyph {
    unsigned int codepoint;

    int index;

    int next;

    short size;

    short blur;

    short x0;

    short y0;

    short x1;

    short y1;

    short xadv;

    short xoff;

    short yoff;

};
struct FONSfont {
    FONSttFontImpl font;

    char name[64];

    unsigned char data;

    int dataSize;

    unsigned char freeData;

    float ascender;

    float descender;

    float lineh;

    FONSglyph * glyphs;

    int cglyphs;

    int nglyphs;

    int lut[FONS_HASH_LUT_SIZE];

    int fallbacks[FONS_MAX_FALLBACKS];

    int nfallbacks;

};
struct FONSstate {
    int font;

    int align;

    float size;

    unsigned int color;

    float blur;

    float spacing;

};
struct FONSatlasNode {
    short x;

    short y;

    short width;

};
struct FONSatlas {
    int width;

    int height;

    FONSatlasNode * nodes;

    int nnodes;

    int cnodes;

};
#endif

#ifndef _STB_TRUETYPE_H
#define _STB_TRUETYPE_H


typedef unsigned char stbtt_uint8;
typedef signed char stbtt_int8;
typedef unsigned short stbtt_uint16;
typedef signed short stbtt_int16;
typedef unsigned int stbtt_uint32;
typedef signed int stbtt_int32;
typedef char stbtt__check_size32;
typedef char stbtt__check_size16;
//////////////////////////////////////////////////////////////////////////////
//
// TEXTURE BAKING API
//
// If you use this API, you only have to call two functions ever.

struct stbtt_bakedchar {
    unsigned short x0;

    unsigned short y0;

    unsigned short x1;

    // coordinates of bbox in bitmap
    unsigned short y1;

    float xoff;

    float yoff;

    float xadvance;

};
// you allocate this, it's num_chars long
// if return is positive, the first unused row of the bitmap
// if return is negative, returns the negative of the number of characters that fit
// if return is 0, no characters fit and no rows were used
// This uses a very crappy packing.
struct stbtt_aligned_quad {
    float x0;

    float y0;

    float s0;

    // top-left
    float t0;

    float x1;

    float y1;

    float s1;

    // bottom-right
    float t1;

};
// true if opengl fill rule; false if DX9 or earlier
// Call GetBakedQuad with char_index = 'character - first_char', and it
// creates the quad you need to draw and advances the current position.
//
// The coordinate system used assumes y increases downwards.
//
// Characters will extend both above and below the current position;
// see discussion of "BASELINE" above.
//
// It's inefficient; you might want to c&p it and optimize it.
//////////////////////////////////////////////////////////////////////////////
//
// NEW TEXTURE BAKING API
//
// This provides options for packing multiple fonts into one atlas, not
// perfectly but better than nothing.
struct stbtt_packedchar {
    unsigned short x0;

    unsigned short y0;

    unsigned short x1;

    // coordinates of bbox in bitmap
    unsigned short y1;

    float xoff;

    float yoff;

    float xadvance;

    float xoff2;

    float yoff2;

};
typedef stbtt_pack_context stbtt_pack_context;
typedef stbtt_fontinfo stbtt_fontinfo;
typedef stbrp_rect stbrp_rect;
// Creates character bitmaps from the font_index'th font found in fontdata (use
// font_index=0 if you don't know what that is). It creates num_chars_in_range
// bitmaps for characters with unicode values starting at first_unicode_char_in_range
// and increasing. Data for how to render them is stored in chardata_for_range;
// pass these to stbtt_GetPackedQuad to get back renderable quads.
//
// font_size is the full height of the character from ascender to descender,
// as computed by stbtt_ScaleForPixelHeight. To use a point size as computed
// by stbtt_ScaleForMappingEmToPixels, wrap the point size in STBTT_POINT_SIZE()
// and pass that result as 'font_size':
//       ...,                  20 , ... // font max minus min y is 20 pixels tall
//       ..., STBTT_POINT_SIZE(20), ... // 'M' is 20 pixels tall
struct stbtt_pack_range {
    float font_size;

    // if non-zero, then the chars are continuous, and this is the first codepoint
    int first_unicode_codepoint_in_range;

    // if non-zero, then this is an array of unicode codepoints
    int array_of_unicode_codepoints;

    int num_chars;

    // output
    stbtt_packedchar * chardata_for_range;

    unsigned char h_oversample;

    // don't set these, they're used internally
    unsigned char v_oversample;

};
enum anonymous4 {
  STBTT_vmove = 1,
  STBTT_vline,
  STBTT_vcurve
};
struct stbtt_vertex {
    stbtt_vertex_type x;

    stbtt_vertex_type y;

    stbtt_vertex_type cx;

    stbtt_vertex_type cy;

    unsigned char type;

    unsigned char padding;

};
// @TODO: don't expose this structure
struct stbtt__bitmap {
    int w;

    int h;

    int stride;

    unsigned char pixels;

};
// returns the string (which may be big-endian double byte, e.g. for unicode)
// and puts the length in bytes in *length.
//
// some of the values for the IDs are below; for more see the truetype spec:
//     http://developer.apple.com/textfonts/TTRefMan/RM06/Chap6name.html
//     http://www.microsoft.com/typography/otspec/name.htm
enum anonymous5 {
  STBTT_PLATFORM_ID_UNICODE = 0,
  STBTT_PLATFORM_ID_MAC = 1,
  STBTT_PLATFORM_ID_ISO = 2,
  STBTT_PLATFORM_ID_MICROSOFT = 3

};
// platformID
enum anonymous6 {
  STBTT_UNICODE_EID_UNICODE_1_0 = 0,
  STBTT_UNICODE_EID_UNICODE_1_1 = 1,
  STBTT_UNICODE_EID_ISO_10646 = 2,
  STBTT_UNICODE_EID_UNICODE_2_0_BMP = 3,
  STBTT_UNICODE_EID_UNICODE_2_0_FULL = 4

};
// encodingID for STBTT_PLATFORM_ID_UNICODE
enum anonymous7 {
  STBTT_MS_EID_SYMBOL = 0,
  STBTT_MS_EID_UNICODE_BMP = 1,
  STBTT_MS_EID_SHIFTJIS = 2,
  STBTT_MS_EID_UNICODE_FULL = 10

};
// encodingID for STBTT_PLATFORM_ID_MICROSOFT
enum anonymous8 {
  STBTT_MAC_EID_ROMAN = 0,
  STBTT_MAC_EID_ARABIC = 4,
  STBTT_MAC_EID_JAPANESE = 1,
  STBTT_MAC_EID_HEBREW = 5,
  STBTT_MAC_EID_CHINESE_TRAD = 2,
  STBTT_MAC_EID_GREEK = 6,
  STBTT_MAC_EID_KOREAN = 3,
  STBTT_MAC_EID_RUSSIAN = 7

};
// encodingID for STBTT_PLATFORM_ID_MAC; same as Script Manager codes
enum anonymous9 {
  STBTT_MS_LANG_ENGLISH = 0x0409,
  STBTT_MS_LANG_ITALIAN = 0x0410,
  STBTT_MS_LANG_CHINESE = 0x0804,
  STBTT_MS_LANG_JAPANESE = 0x0411,
  STBTT_MS_LANG_DUTCH = 0x0413,
  STBTT_MS_LANG_KOREAN = 0x0412,
  STBTT_MS_LANG_FRENCH = 0x040c,
  STBTT_MS_LANG_RUSSIAN = 0x0419,
  STBTT_MS_LANG_GERMAN = 0x0407,
  STBTT_MS_LANG_SPANISH = 0x0409,
  STBTT_MS_LANG_HEBREW = 0x040d,
  STBTT_MS_LANG_SWEDISH = 0x041D

};
// languageID for STBTT_PLATFORM_ID_MICROSOFT; same as LCID...
// problematic because there are e.g. 16 english LCIDs and 16 arabic LCIDs
enum anonymous10 {
  STBTT_MAC_LANG_ENGLISH = 0 ,
  STBTT_MAC_LANG_JAPANESE = 11,
  STBTT_MAC_LANG_ARABIC = 12,
  STBTT_MAC_LANG_KOREAN = 23,
  STBTT_MAC_LANG_DUTCH = 4 ,
  STBTT_MAC_LANG_RUSSIAN = 32,
  STBTT_MAC_LANG_FRENCH = 1 ,
  STBTT_MAC_LANG_SPANISH = 6 ,
  STBTT_MAC_LANG_GERMAN = 2 ,
  STBTT_MAC_LANG_SWEDISH = 5 ,
  STBTT_MAC_LANG_HEBREW = 10,
  STBTT_MAC_LANG_CHINESE_SIMPLIFIED = 33,
  STBTT_MAC_LANG_ITALIAN = 3 ,
  STBTT_MAC_LANG_CHINESE_TRAD = 19

};
//////////////////////////////////////////////////////////////////////////////
//
//  Rasterizer
struct stbtt__hheap_chunk {
    stbtt__hheap_chunk * next;

};
struct stbtt__hheap {
    stbtt__hheap_chunk * head;

    void first_free;

    int num_remaining_in_head_chunk;

};
struct stbtt__edge {
    float x0;

    float y0;

    float x1;

    float y1;

    int invert;

};
struct stbtt__active_edge {
    stbtt__active_edge * next;

    int x;

    int dx;

    float ey;

    int direction;

    float fx;

    float fdx;

    float fdy;

    float sy;

};
struct stbtt__point {
    float x;

    float y;

};
typedef int stbrp_coord;
////////////////////////////////////////////////////////////////////////////////////
//                                                                                //
//                                                                                //
// COMPILER WARNING ?!?!?                                                         //
//                                                                                //
//                                                                                //
// if you get a compile warning due to these symbols being defined more than      //
// once, move #include "stb_rect_pack.h" before #include "stb_truetype.h"         //
//                                                                                //
////////////////////////////////////////////////////////////////////////////////////
struct stbrp_context {
    int width;

    int height;

    int x;

    int y;

    int bottom_y;

};
struct stbrp_node {
    unsigned char x;

};
#endif

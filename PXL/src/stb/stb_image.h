#ifndef _STB_IMAGE_H
#define _STB_IMAGE_H


enum anonymous1 {
  STBI_default =  0,
  STBI_grey =  1,
  STBI_grey_alpha =  2,
  STBI_rgb =  3,
  STBI_rgb_alpha =  4

};
// only used for req_comp
typedef unsigned char stbi_uc;
//////////////////////////////////////////////////////////////////////////////
//
// PRIMARY API - works on images of any type
//
//
// load image by filename, open file, or memory buffer

struct stbi_io_callbacks {
    // fill 'data' with 'size' bytes.  return number of bytes actually read
    int (*) (void *user,char *data,int size) read;

    // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
    void (*) (void *user,int n) skip;

    // returns nonzero if we are at end of file/data
    int (*) (void *user) eof;

};
typedef uint16_t stbi__uint16;
typedef int16_t stbi__int16;
typedef uint32_t stbi__uint32;
typedef int32_t stbi__int32;
// should produce compiler error if size is wrong
typedef unsigned char validate_uint32;
///////////////////////////////////////////////
//
//  stbi__context struct and start_xxx functions
// stbi__context structure is our basic context used by all images, so it
// contains all the IO context, plus some basic image information
struct stbi__context {
    stbi__uint32 img_x;

    stbi__uint32 img_y;

    int img_n;

    int img_out_n;

    stbi_io_callbacks io;

    void io_user_data;

    int read_from_callbacks;

    int buflen;

    stbi_uc buffer_start[128];

    stbi_uc * img_buffer;

    stbi_uc * img_buffer_end;

    stbi_uc * img_buffer_original;

    stbi_uc * img_buffer_original_end;

};
//////////////////////////////////////////////////////////////////////////////
//
// Common code used by all image loaders

enum anonymous2 {
  STBI__SCAN_load = 0,
  STBI__SCAN_type,
  STBI__SCAN_header
};
struct stbi__huffman {
    stbi_uc fast[1 << FAST_BITS];

    // weirdly, repacking this into AoS is a 10% speed loss, instead of a win
    
    stbi__uint16 code[256];

    stbi_uc values[256];

    stbi_uc size[257];

    unsigned int maxcode[18];

    // old 'firstsymbol' - old 'firstcode'
    int delta[17];

};
struct stbi__jpeg {
    stbi__context * s;

    stbi__huffman huff_dc[4];

    stbi__huffman huff_ac[4];

    stbi_uc dequant[4][64];

    stbi__int16 fast_ac[4][1 << FAST_BITS];

    // sizes for components, interleaved MCUs
    
    int img_h_max;

    int img_v_max;

    int img_mcu_x;

    int img_mcu_y;

    int img_mcu_w;

    int img_mcu_h;

    // definition of jpeg image component
    
    <complex type> img_comp[4];

    // jpeg entropy-coded buffer
    stbi__uint32 code_buffer;

    // number of valid bits
    int code_bits;

    // marker seen while filling entropy buffer
    unsigned char marker;

    // flag if we saw a marker so must stop
    int nomore;

    int progressive;

    int spec_start;

    int spec_end;

    int succ_high;

    int succ_low;

    int eob_run;

    int scan_n;

    int order[4];

    int restart_interval;

    int todo;

    // kernels
    
    // kernels void (*)(stbi_uc *out, int out_stride, short data[64]) idct_block_kernel;

    void (*)(stbi_uc *out, const stbi_uc *y, const stbi_uc *pcb, const stbi_uc *pcr, int count, int step) YCbCr_to_RGB_kernel;

    stbi_uc *(*)(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs) resample_row_hv_2_kernel;

};
// static jfif-centered resampling (across block boundaries)
typedef stbi_uc resample_row_func;
struct stbi__resample {
    resample_row_func resample;

    stbi_uc * line0;

    stbi_uc * line1;

    int hs;

    // expansion factor in each axis
    int vs;

    // horizontal pixels pre-expansion
    int w_lores;

    // how far through vertical expansion we are
    int ystep;

    // which pre-expansion row we're on
    int ypos;

};
// zlib-style huffman encoding
// (jpegs packs from left, zlib from right, so can't share code)
struct stbi__zhuffman {
    stbi__uint16 fast[1 << STBI__ZFAST_BITS];

    stbi__uint16 firstcode[16];

    int maxcode[17];

    stbi__uint16 firstsymbol[16];

    stbi_uc size[288];

    stbi__uint16 value[288];

};
// zlib-from-memory implementation for PNG reading
//    because PNG allows splitting the zlib stream arbitrarily,
//    and it's annoying structurally to have PNG call ZLIB call PNG,
//    we require PNG read all the IDATs and combine them into a single
//    memory buffer
struct stbi__zbuf {
    stbi_uc * zbuffer;

    stbi_uc * zbuffer_end;

    int num_bits;

    stbi__uint32 code_buffer;

    char zout;

    char zout_start;

    char zout_end;

    int z_expandable;

    stbi__zhuffman z_length;

    stbi__zhuffman z_distance;

};
struct stbi__pngchunk {
    stbi__uint32 length;

    stbi__uint32 type;

};
struct stbi__png {
    stbi__context * s;

    stbi_uc * idata;

    stbi_uc * expanded;

    stbi_uc * out;

};
enum anonymous3 {
  STBI__F_none = 0,
  STBI__F_sub = 1,
  STBI__F_up = 2,
  STBI__F_avg = 3,
  STBI__F_paeth = 4,
  STBI__F_avg_first,
  STBI__F_paeth_first
};
struct stbi__bmp_data {
    int bpp;

    int offset;

    int hsz;

    unsigned int mr;

    unsigned int mg;

    unsigned int mb;

    unsigned int ma;

    unsigned int all_a;

};
struct stbi__pic_packet {
    stbi_uc size;

    stbi_uc type;

    stbi_uc channel;

};
struct stbi__gif_lzw {
    stbi__int16 prefix;

    stbi_uc first;

    stbi_uc suffix;

};
struct stbi__gif {
    int w;

    int h;

    stbi_uc * out;

    // output buffer (always 4 components)
    stbi_uc * old_out;

    int flags;

    int bgindex;

    int ratio;

    int transparent;

    int eflags;

    int delay;

    stbi_uc pal[256][4];

    stbi_uc lpal[256][4];

    stbi__gif_lzw codes[4096];

    stbi_uc * color_table;

    int parse;

    int step;

    int lflags;

    int start_x;

    int start_y;

    int max_x;

    int max_y;

    int cur_x;

    int cur_y;

    int line_size;

};
#endif

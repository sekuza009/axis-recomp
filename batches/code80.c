/* batch 79 (lifted/grp25.c) */
#include "lifted/grp25.c"
/* 0x46eb00 ptx_open(path, out, &fmt, &w, &h) / 0x46ed80 ptx_decode(f, out, &fmt, &w, &h): a PTX image. 16-byte
   header ("PTX\0", version 0x100, width / 8, height / 8, type 0x81 = YCbCr (3 planes, fmt 2) or 0x82 = YCbCrA
   (4 planes, fmt 3), quality), then up to 64 KB of Huffman-coded 8x8 DCT blocks, each plane byte-aligned (planes
   1 and 2 use the second table pair); converted to RGB(A) rows in out. A bad header is fatal (ptx_error), and so
   is a failed open in ptx_open, which also closes the file */
LIFT_PLAIN8(ptx_open, 46eb00)
LIFT_PLAIN8(ptx_decode, 46ed80)

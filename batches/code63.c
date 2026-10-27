/* batch 62: image / texture / data-memory initialisers (lifted/grp9.c) */
#include "lifted/grp9.c"
/* 0x46ce80 (thiscall) image_copyTo(dst, dstW, dstH, depth, sx, sy, dx, dy, w, h, topDown): copy a w x h block of
   the open 24-bit BMP (file +4, data offset +0x12, size +0x3e / +0x42) at (sx, sy) into the dstW x dstH buffer at
   (dx, dy), both clipped; BGR -> RGB (depth 3) or RGBA with alpha 0xff (depth 4); rows bottom-up unless topDown */
static THISCALL DWORD image_copyTo(char *img, DWORD dst, DWORD dw, DWORD dh, DWORD depth, DWORD sx, DWORD sy,
                                   DWORD dx, DWORD dy, DWORD w, DWORD h, DWORD topDown)
{
	DWORD v[11] = { dst, dw, dh, depth, sx, sy, dx, dy, w, h, topDown };
	return run_lifted(lift_46ce80, (DWORD)img, 11, v);
}
/* 0x4557e0 (thiscall) tex_textureFileExist(name): is the texture there in the manager's format (+0xc0114): a dat
   entry (0, binary search of the index), a BMP (1) or a RAW file (2) of the manager's size (+0xc0118 / +0xc011c)? */
static THISCALL DWORD tex_textureFileExist(char *tm, DWORD name) { DWORD v[1] = { name }; return run_lifted(lift_4557e0, (DWORD)tm, 1, v); }
/* 0x455080 (thiscall) tex_initBy(dir, slots, format, w, h, a, b): the texture manager: directory (upper case),
   format and size; for the dat format the index of the size's Data\Image*.dat (count + 0x44-byte entries); then
   at most 0x200 texture slots in a ring, each with a GL texture name */
static THISCALL DWORD tex_initBy(char *tm, DWORD dir, DWORD slots, DWORD fmt, DWORD w, DWORD h, DWORD a, DWORD b)
{
	DWORD v[7] = { dir, slots, fmt, w, h, a, b };
	return run_lifted(lift_455080, (DWORD)tm, 7, v);
}
/* 0x466a60 (thiscall) shape_initBy(dir, n, a, extra, mem, memSize): free owned data memory, keep the directory,
   data memory for n shapes (0x98 bytes each) plus extra, from mem or allocated; clear the shape headers */
static THISCALL DWORD shape_initBy(char *self, DWORD dir, DWORD n, DWORD a, DWORD extra, DWORD mem, DWORD size)
{
	DWORD v[6] = { dir, n, a, extra, mem, size };
	return run_lifted(lift_466a60, (DWORD)self, 6, v);
}
/* 0x46aeb0 (thiscall) skel_loadFrom_46aeb0(dir, n, a, extra, mem, memSize): the same for n skeletons (0x70 bytes each) */
static THISCALL DWORD skel_loadFrom_46aeb0(char *self, DWORD dir, DWORD n, DWORD a, DWORD extra, DWORD mem, DWORD size)
{
	DWORD v[6] = { dir, n, a, extra, mem, size };
	return run_lifted(lift_46aeb0, (DWORD)self, 6, v);
}

/* batch 80 (lifted/grp26.c) */
#include "lifted/grp26.c"
/* 0x455aa0 (thiscall) tex_loadColorMask(i): load texture i's image (name +0xc0128 + i * 0x68, cut at '*', under the
   dir +8 if any) at +0x114, its alpha into the image's 4th bytes (the average of the ALPHA image's RGB at +0x40114,
   or 0xff without one) and its colour mask at +0x80114 (or the colour at 0xa1f238 in every pixel), by the manager's
   format +0xc0114: 0 PTX items of the texture dat (name, name_ALPHA, name_COLOR; tables set up on first use),
   1 BMP files (name.BMP must open), 2 PTX files (name.RAW, name_ALPHA.RAW, name_COLOR.RAW); a PTX of another size
   than +0xc0118 x +0xc011c is fatal */
static THISCALL DWORD tex_loadColorMask(char *tm, DWORD i)
{
	DWORD v[1] = { i };
	return run_lifted(lift_455aa0, (DWORD)tm, 1, v);
}

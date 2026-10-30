/* skel_data.c: a skeleton's data block: its header read or set, then one block (allocated, or the caller's memory
   when it is big enough, else a fatal message) laid out as the bones' records followed by their tables. */
#include "../game.h"
#include <string.h>

#define AT(type, p, offset) GAME_VAR(type, (u8 *)(p) + (offset))
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)

/* the block (+8; +4 its size): allocated (owned, +0xc 1) without memory given, else the memory given (owned 0 when
   own_flag; the caller's size checked) */
static void take_block(u8 *self, void *mem, int size, char *out, int own_flag)
{
	if (!mem) {
		AT(void *, self, 8) = operator_new(AT(u32, self, 4));
		if (!AT(void *, self, 8))
			sys_fatalError(out, (const char *)0x4c4bec, AT(int, self, 4));
		AT(int, self, 0xc) = 1;
	} else {
		if (size < AT(int, self, 4))
			sys_fatalErrorN(out, (const char *)0x4c4b08, AT(int, self, 4), size);
		AT(void *, self, 8) = mem;
		if (own_flag)
			AT(int, self, 0xc) = 0;
	}
}

/* 0x46aa10 (thiscall on a skeleton): read from f: the 0x24-byte header, the block (+8, its size +4), then the bones
   (0x70 bytes each, +0x10 of them, at the block's start: +0x14) and after them each bone's two tables (+0x60 keys of
   0x20 bytes at +0x64, +0x68 frames of 0x28 bytes at +0x6c). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom_46aa10)(u8 *self, void *f, void *mem, int size)
{
	FUN_004699a0(self);
	crt_fread(self, 0x24, 1, f);
	take_block(self, mem, size, (char *)0xa0eaa8, 1);
	u8 *bones = AT(u8 *, self, 0x14) = AT(u8 *, self, 8);
	crt_fread(bones, 0x70, AT(u32, self, 0x10), f);
	int at = AT(int, self, 0x10) * 0x70;
	for (int i = 0; i < AT(int, self, 0x10); i++) {
		u8 *bone = AT(u8 *, self, 0x14) + i * 0x70;
		AT(u8 *, bone, 0x64) = AT(u8 *, self, 8) + at;
		u32 keys = AT(u32, bone, 0x60);
		at += keys * 0x20;
		AT(u8 *, bone, 0x6c) = AT(u8 *, self, 8) + at;
		at += AT(int, bone, 0x68) * 0x28;
		crt_fread(AT(void *, bone, 0x64), 0x20, keys, f);
		crt_fread(AT(void *, bone, 0x6c), 0x28, AT(u32, bone, 0x68), f);
	}
}

/* 0x46aeb0 (thiscall on a skeleton set): set up for n skeletons from the directory dir (+0x10; none: 0x4b1304), a at
   +0x110, n at +0x114, extra bytes (+0x124) after them: the block (+8, its size n x 0x70 + extra at +4) holds the
   skeletons' 0x4c-byte records (+0x118), then their 0x24-byte skeletons (+0x11c, each created and released), then the
   rest (+0x128). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom_46aeb0)(u8 *self, const char *dir, int n, u32 a, int extra, void *mem, int size)
{
	load_46ae80(self);
	strcpy((char *)self + 0x10, dir ? dir : (const char *)0x4b1304);
	AT(u32, self, 0x110) = a;
	AT(int, self, 0x114) = n;
	AT(int, self, 0x124) = extra;
	AT(int, self, 4) = n * 0x70 + extra;
	take_block(self, mem, size, (char *)0xa0eaa0, 0);
	n = AT(int, self, 0x114);
	AT(u8 *, self, 0x118) = AT(u8 *, self, 8);
	AT(u8 *, self, 0x11c) = AT(u8 *, self, 8) + n * 0x4c;
	for (int i = 0; i < AT(int, self, 0x114); i++) {
		FUN_00469980(AT(u8 *, self, 0x11c) + i * 0x24);
		FUN_004699a0(AT(u8 *, self, 0x11c) + i * 0x24);
	}
	AT(u8 *, self, 0x128) = AT(u8 *, self, 8) + n * 0x70;
}

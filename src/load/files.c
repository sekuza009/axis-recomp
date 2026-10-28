/* files.c: small reads and writes of the game's files: the scrambled data files' record blocks (fread_scrambled:
   each byte rotated and xored), the chat macros, the replay file closed. */
#include "../game.h"
#include <stdarg.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* 0x48b460: a count (+0xe36210) and that many 0x30-byte records (+0xdc0f10) */
u32 THISCALL (load_48b460)(u8 *self, void *f)
{
	fread_scrambled(self + 0xe36210, 4, 1, f);
	return fread_scrambled(self + 0xdc0f10, 0x30, FIELD(u32, self, 0xe36210), f);
}

/* 0x483d70: two counts (+0xb004, +0xb008), the first's number of 0x2c-byte records (+4), and one more value
   (+0xb00c) */
u32 THISCALL (load_483d70)(u8 *self, void *f)
{
	fread_scrambled(self + 0xb004, 4, 1, f);
	fread_scrambled(self + 0xb008, 4, 1, f);
	fread_scrambled(self + 4, 0x2c, FIELD(u32, self, 0xb004), f);
	return fread_scrambled(self + 0xb00c, 4, 1, f);
}

/* 0x4617b0: the 100 chat macros (0x39 bytes each, from +0x2340d3d) written to "Chat.scp" (the name says load; it
   saves); fclose's result, 0 when the file cannot be opened */
u32 THISCALL (chat_loadMacros)(Scene *scene)
{
	void *f = crt_fopen((const char *)0x4c45ec, (const char *)0x4b2ab0);
	if (!f)
		return 0;
	crt_fwrite((u8 *)scene + 0x2340d3d, 0x39, 100, f);
	return fclose(f);
}

/* 0x487ed0: the replay being recorded closed (fclose's result; 0 when none) */
u32 THISCALL (match_487ed0)(Scene *scene)
{
	if (!scene->recording)
		return 0;
	u32 r = fclose(FIELD(void *, scene, 0x2340d08));
	scene->recording = 0;
	return r;
}

/* 0x46ca70: does the file named by the formatted path exist (opens for reading)? */
int (FUN_0046ca70)(const char *format, ...)
{
	char path[256];
	va_list args;
	va_start(args, format);
	vsprintf(path, format, args);
	va_end(args);
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		return 0;
	fclose(f);
	return 1;
}

/* 0x46cbe0: count records of size bytes read, each byte unscrambled: xor 0x59, rotated left by one. Returns fread's
   count */
u32 (FUN_0046cbe0)(u8 *p, u32 size, u32 count, void *f)
{
	int n = (int)(size * count);
	u32 r = GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f);   /* fread */
	for (int i = 0; i < n; i++) {
		u8 c = p[i] ^ 0x59;
		p[i] = (u8)(c << 1 | c >> 7);
	}
	return r;
}

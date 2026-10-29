/* files.c: small reads and writes of the game's files: the scrambled data files' record blocks (fread_scrambled:
   each byte rotated and xored), the chat macros, the replay file closed. */
#include "../game.h"
#include <string.h>
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

/* ---- an entry of a .dat archive (0x44-byte records, the data's offset at +0x40) found by name and the archive's
   file positioned at it; a missing name is reported to the log ---- */
static void *dat_entry(int index, const char *name, u32 table, u32 file, u32 log)
{
	if (index < 0) {
		GAME_CDECL(0x46c710, void, void *, const char *, const char *)((void *)log, (const char *)0x4b3f80, name);   /* sys_fatalError */
		return 0;
	}
	GAME_CDECL(0x49e91e, int, void *, int, int)(GAME_VAR(void *, file), FIELD(int, GAME_VAR(u8 *, table) + index * 0x44, 0x40), 0);   /* fseek */
	return GAME_VAR(void *, file);
}
/* 0x466d60: in Shape.dat */
void *(shape_findDatEntry)(const char *name)
{
	return dat_entry(GAME_CDECL(0x466ce0, int, const char *)(name), name, 0xa0e7a0, 0xa0e7a4, 0xa0e788);
}
/* 0x46b140: in the skeleton archive */
void *(skelDat_getItemFileBy)(const char *name)
{
	return dat_entry(GAME_CDECL(0x46b0c0, int, const char *)(name), name, 0xa0eab8, 0xa0eabc, 0xa0eaa0);
}

/* 0x4617f0: the chat macros (100 of 0x39 bytes at +0x2340d3d) read from their file (0x4c45ec); without the file, all
   emptied and the defaults made (chat_loadMacros). Returns what the original leaves in eax */
u32 THISCALL (chat_saveMacros)(Scene *scene)
{
	void *f = crt_fopen((const char *)0x4c45ec, (const char *)0x4ad170);
	if (f) {
		GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)((u8 *)scene + 0x2340d3d, 0x39, 100, f);   /* fread */
		return fclose(f);
	}
	for (int k = 0; k < 100; k++)
		((u8 *)scene)[0x2340d3d + k * 0x39] = 0;
	return GAME_THISCALL(0x4617b0, u32, Scene *)(scene);   /* chat_loadMacros */
}

/* 0x46cc30: count records of size bytes written scrambled (each byte rotated right by one, xor 0x59), then put back
   as they were. Returns fwrite's count */
u32 (FUN_0046cc30)(u8 *p, u32 size, u32 count, void *f)
{
	int n = (int)(size * count);
	for (int i = 0; i < n; i++) {
		u8 c = p[i];
		p[i] = (u8)(c >> 1 | c << 7);
		p[i] ^= 0x59;
	}
	u32 r = crt_fwrite(p, size, count, f);
	for (int i = 0; i < n; i++) {
		u8 c = p[i] ^ 0x59;
		p[i] = c;
		p[i] = (u8)(c << 1 | c >> 7);
	}
	return r;
}

/* 0x42c650: the player's section of axis.cfg written: its header, the name, the corporation (0..2) and the sex, by
   their keywords. Returns the last fputs */
u32 (cfg_parsePlayer)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)(s), f)
	FPUTS(0x4b1830);
	FPUTS(0x4dedb0);
	GAME_CDECL(0x49f135, u32, void *, const char *)(f, (const char *)0x4b182c);   /* fprintf */
	FPUTS(0x4b1818);
	int corp = GAME_VAR(int, 0x4dedd0);
	FPUTS(corp == 1 ? 0x4b1808 : corp == 2 ? 0x4b1810 : 0x4b1800);
	FPUTS(0x4b17e8);
	FPUTS(GAME_VAR(int, 0x4dedd4) == 1 ? 0x4b17e4 : 0x4b17dc);
	return FPUTS(0x4b182c);
#undef FPUTS
}

/* 0x42d730: axis.cfg written in the data folder (0x9dae7c): its header, then the player, server, sound, graphics and
   key binding sections (the original does not check that the file opened). Returns fclose's eax */
u32 (cfg_loadAxisCfg)(void)
{
	char path[0x184];
	strcpy(path, (const char *)0x9dae7c);
	strcat(path, (const char *)0x4b2198);   /* the file's name */
	void *f = crt_fopen(path, (const char *)0x4b21a4);
	GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)0x4b0f50, f);   /* fputs */
	GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)0x4b182c, f);
	static const u32 sections[5] = { 0x42c650, 0x42c6f0, 0x42c910, 0x42c9f0, 0x42cba0 };   /* player .. key bindings */
	for (int k = 0; k < 5; k++)
		GAME_CDECL(sections[k], u32, void *)(f);
	return fclose(f);
}

/* 0x43f8b0: the data files spoilt: a marker word (0xa1a2a3a4, 0xb1b2b3b4, 0xc1c2c3c4) written at offset 2000 of
   three files, then two more deleted. Returns the last DeleteFileA's eax */
u32 (app_deleteDataFiles)(void)
{
	static const u32 files[3] = { 0x4b03c4, 0x4b03dc, 0x4b03f4 };
	static const u32 marks[3] = { 0xa1a2a3a4, 0xb1b2b3b4, 0xc1c2c3c4 };
	for (int k = 0; k < 3; k++) {
		void *f = crt_fopen((const char *)files[k], (const char *)0x4b29e8);
		GAME_CDECL(0x49e91e, int, void *, int, int)(f, 2000, 0);   /* fseek */
		u32 mark = marks[k];
		crt_fwrite(&mark, 4, 1, f);
		fclose(f);
	}
	IMPORT(0x4a9104, u32, const char *)((const char *)0x4b040c);   /* DeleteFileA */
	return IMPORT(0x4a9104, u32, const char *)((const char *)0x4b0420);
}

/* ---- a .dat archive opened (unless already): its file (named by format), the entry count, then the 0x44-byte
   entries into a malloc'd table; a missing file or no memory is a fatal error (to log). Returns what the original
   leaves in eax ---- */
static u32 dat_open(u32 count, const char *format, void *log)
{
	u32 table = count + 4, file = count + 8;
	if (GAME_VAR(int, count) > 0)
		return GAME_VAR(u32, count);
	if (GAME_VAR(void *, file))
		return GAME_VAR(u32, file);
	char path[0x100];
	GAME_CDECL(0x49e9dd, int, char *, const char *)(path, format);   /* sprintf */
	GAME_VAR(void *, file) = crt_fopen(path, (const char *)0x4ad170);
	if (!GAME_VAR(void *, file))
		GAME_CDECL(0x46c710, void, void *, const char *, const char *)(log, (const char *)0x4b3ee4, path);
	GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)((void *)count, 4, 1, GAME_VAR(void *, file));   /* fread */
	GAME_VAR(void *, table) = crt_malloc(GAME_VAR(int, count) * 0x44);
	if (!GAME_VAR(void *, table))
		GAME_CDECL(0x46c710, void, void *, const char *, int)(log, (const char *)0x4b3eb4, GAME_VAR(int, count));
	return GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(GAME_VAR(void *, table), 0x44, GAME_VAR(int, count),
	                                                          GAME_VAR(void *, file));
}
/* 0x466c00: Shape.dat; 0x46afe0: the skeleton archive */
u32 (shapeDat_initBy)(void) { return dat_open(0xa0e79c, (const char *)0x4c4d20, (void *)0xa0e788); }
u32 (skelDat_initBy)(void) { return dat_open(0xa0eab4, (const char *)0x4c54b4, (void *)0xa0eaa0); }

/* 0x42c910: the sound section of axis.cfg written: the two volumes (0x4e0c90, 0x4e0c94) as numbers, then two on/off
   switches (0x4e0c98, 0x4e0c9c; 1 is on), each after its keyword. Returns the last fputs */
u32 (cfg_parseSound)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)(s), f)
	char number[12];
	itoa(GAME_VAR(int, 0x4e0c90), number, 10);
	FPUTS(0x4b1a4c);
	FPUTS(number);
	FPUTS(0x4b182c);
	itoa(GAME_VAR(int, 0x4e0c94), number, 10);
	FPUTS(0x4b1a34);
	FPUTS(number);
	FPUTS(0x4b182c);
	FPUTS(0x4b1a20);
	FPUTS(GAME_VAR(int, 0x4e0c98) == 1 ? 0x4b17e4 : 0x4b17dc);
	FPUTS(0x4b1a04);
	FPUTS(GAME_VAR(int, 0x4e0c9c) == 1 ? 0x4b17e4 : 0x4b17dc);
	return FPUTS(0x4b182c);
#undef FPUTS
}

/* 0x41e7c0: does map k's file exist ("map/" + its name (32 bytes a slot at 0x907b30) + ".bfd")? 1 when it opens, 0
   when not or when the name is shorter than 2 letters */
int (console_loadFile)(int k)
{
	const char *name = (const char *)(0x907b30 + k * 32);
	if (strlen(name) <= 1)
		return 0;
	char path[0x400];
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)0x4b0434);   /* "map/" */
	strcat(path, name);
	strcat(path, (const char *)0x4b042c);   /* ".bfd" */
	void *f = crt_fopen(path, (const char *)0x4ad170);
	if (!f)
		return 0;
	fclose(f);
	return 1;
}

#define crt_chdir(path) GAME_CDECL(0x49f8a6, int, const char *)(path)
#define crt_findfirst(pattern, data) GAME_CDECL(0x49f694, int, const char *, void *)(pattern, data)
#define crt_findnext(handle, data) GAME_CDECL(0x49f75e, int, int, void *)(handle, data)
#define crt_findclose(handle) GAME_CDECL(0x49f823, int, int)(handle)

/* 0x440c60: the autoplay folder's files (0x4b2a8c, pattern 0x4b2a84) appended to the map list (0x44-byte records
   from 0x9dda88, count 0x9dd928, at most 1023), then back to the parent folder (0x4b2a80). Returns the last chdir's
   eax */
int (autoplay_listFiles)(void)
{
	struct { u32 attrib, created, accessed, written, size; char name[260]; } found;   /* _finddata_t */
	int r = crt_chdir((const char *)0x4b2a8c);
	if (r)
		return r;
	int search = crt_findfirst((const char *)0x4b2a84, &found);
	if (search < 0)
		return crt_chdir((const char *)0x4b2a80);
	strcpy((char *)(0x9dda88 + GAME_VAR(int, 0x9dd928) * 0x44), found.name);
	GAME_VAR(int, 0x9dd928)++;
	while (!crt_findnext(search, &found)) {
		strcpy((char *)(0x9dda88 + GAME_VAR(int, 0x9dd928) * 0x44), found.name);
		if (++GAME_VAR(int, 0x9dd928) > 0x3fe)
			break;
	}
	crt_findclose(search);
	return crt_chdir((const char *)0x4b2a80);
}

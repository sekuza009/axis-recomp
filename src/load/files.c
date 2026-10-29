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

/* 0x41e260: eight check bytes read from the launcher's file (0x4b03b4; each at its own offset) into 0x4dd988 (12
   bytes cleared first). 1, or 0 when the file is missing */
int (app_checkLauncherRunning)(void)
{
	static const u16 offsets[8] = { 0x1a2b, 0x1a2c, 0x2dbf, 0x2dc0, 0x38a4, 0x38a5, 0x55f1, 0x55f2 };
	memset((void *)0x4dd988, 0, 12);
	void *f = crt_fopen((const char *)0x4b03b4, (const char *)0x4ad170);
	if (!f)
		return 0;
	for (int i = 0; i < 8; i++) {
		GAME_CDECL(0x49e91e, int, void *, int, int)(f, offsets[i], 0);   /* fseek */
		GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)((void *)(0x4dd988 + i), 1, 1, f);   /* fread */
	}
	fclose(f);
	return 1;
}

/* ---- axisuser.dat (in the data folder 0x9dae7c), written afresh: a magic word (0xfefefef7), the count (0x9f9008),
   the current profile (0x9f8c58, first set from 0x9f8d74), 0x9f8c4c, 0x9f8c5c, the 32-byte name 0x9f8fe8 and the
   0x48-byte profile records from 0x9f6848. Without the file the count is 0 ---- */
static void *profiles_create(void)
{
	char path[0x184];
	strcpy(path, (const char *)0x9dae7c);
	strcat(path, (const char *)0x4b2ab4);   /* "\axisuser.dat" */
	GAME_VAR(u32, 0x9f8c58) = GAME_VAR(u32, 0x9f8d74);
	void *f = crt_fopen(path, (const char *)0x4b2ab0);
	if (!f)
		GAME_VAR(int, 0x9f9008) = 0;
	return f;
}

/* returns fclose's eax */
static u32 profiles_write(void *f)
{
	u32 magic = 0xfefefef7;
	crt_fwrite(&magic, 4, 1, f);
	crt_fwrite((void *)0x9f9008, 4, 1, f);
	crt_fwrite((void *)0x9f8c58, 4, 1, f);
	crt_fwrite((void *)0x9f8c4c, 4, 1, f);
	crt_fwrite((void *)0x9f8c5c, 4, 1, f);
	crt_fwrite((void *)0x9f8fe8, 0x20, 1, f);
	for (int i = 0; i < GAME_VAR(int, 0x9f9008); i++)
		crt_fwrite((void *)(0x9f6848 + i * 0x48), 0x48, 1, f);
	return fclose(f);
}

/* 0x445f70: the file written with `count` profiles and the three header words cleared. Returns fclose's eax (0
   without the file) */
u32 (profile_loadList)(int count)
{
	void *f = profiles_create();
	if (!f)
		return 0;
	GAME_VAR(int, 0x9f9008) = count;
	GAME_VAR(u32, 0x9f8c58) = 0;
	GAME_VAR(u32, 0x9f8c4c) = 0;
	GAME_VAR(u32, 0x9f8c5c) = 0;
	return profiles_write(f);
}

/* 0x447320: the file written as the profiles stand, the name 0x9f8fe8 being the current profile's. Returns
   fclose's eax (0 without the file) */
u32 (profile_delete)(void)
{
	void *f = profiles_create();
	if (!f)
		return 0;
	memset((void *)0x9f8fe8, 0, 0x20);
	strcpy((char *)0x9f8fe8, (const char *)(0x9f684c + GAME_VAR(int, 0x9f8c58) * 0x48));
	return profiles_write(f);
}

#define crt_fseek(f, offset, whence) GAME_CDECL(0x49e91e, int, void *, int, int)(f, offset, whence)
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)

/* axis.mis (in the data folder) opened for reading */
static void *mis_open(void)
{
	char path[0x184];
	strcpy(path, (const char *)0x9dae7c);
	strcat(path, (const char *)0x4b2aa4);   /* "\axis.mis" */
	return crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
}

/* 0x4435f0: the mission list read from axis.mis: the list cleared first (skirmish_443570), four header words (the
   count 0x9ef2c0, then 0x9ef2c4 .. 0x9ef2cc), each mission's 0xfc-byte entry from 0x9ef2d0 (a word, the 0x40-byte
   name, 0x20 and 0x80-byte texts, four words) and then all their block sizes (+0xf4). Without the file, message
   0xb and its eax; otherwise fclose's */
u32 (mission_loadAxisMis)(void)
{
	void *f = mis_open();
	if (!f)
		return GAME_CDECL(0x41ee40, u32, int)(0xb);
	GAME_CDECL(0x443570, void, void)();   /* skirmish_443570 */
	for (int k = 0; k < 4; k++)
		crt_fread((void *)(0x9ef2c0 + k * 4), 4, 1, f);
	static const struct { int offset, size; } part[8] = {
		{ 0, 4 }, { 4, 0x40 }, { 0x44, 0x20 }, { 0x64, 0x80 }, { 0xe4, 4 }, { 0xe8, 4 }, { 0xec, 4 }, { 0xf0, 4 } };
	u8 *mission = (u8 *)0x9ef2d0;
	for (int i = 0; i < GAME_VAR(int, 0x9ef2c0); i++)
		for (int k = 0; k < 8; k++)
			crt_fread(mission + i * 0xfc + part[k].offset, part[k].size, 1, f);
	for (int i = 0; i < GAME_VAR(int, 0x9ef2c0); i++)
		crt_fread(mission + i * 0xfc + 0xf4, 4, 1, f);
	return fclose(f);
}

/* 0x443af0: mission k's block read from axis.mis (in the data folder): after a 0x1a-byte header, 0xf8 bytes for
   each of the 0x9ef2c0 entries and the blocks before it (sizes 0xfc apart from 0x9ef3c4) into a new buffer
   0x9ef1ec (the old one freed); its size into 0x9ef200, the settings page's state cleared and the page set to
   20 (the mission settings). Without the file, message 0xb and its eax; otherwise 0 */
u32 (mission_saveAxisMis)(int k)
{
	void *f = mis_open();
	if (!f)
		return GAME_CDECL(0x41ee40, u32, int)(0xb);
	const int *size = (const int *)0x9ef3c4;   /* size[i * 63] */
	int offset = 0;
	for (int i = 0; i < k; i++)
		offset += size[i * 63];
	crt_fseek(f, offset + GAME_VAR(int, 0x9ef2c0) * 0xf8 + 0x1a, 0);
	if (GAME_VAR(void *, 0x9ef1ec))
		crt_free(GAME_VAR(void *, 0x9ef1ec));
	void *block = crt_malloc(size[k * 63]);
	GAME_VAR(void *, 0x9ef1ec) = block;
	crt_fread(block, size[k * 63], 1, f);
	fclose(f);
	memset((void *)0x9eeadc, 0, 0xc8);
	GAME_VAR(int, 0x9ef218) = 0;
	memset((void *)0x9f1064, 0, 0x640);
	memset((void *)0x9eebac, 0, 0x640);
	GAME_VAR(int, 0x9ef1f4) = 0;
	GAME_VAR(int, 0x9f105c) = 0;
	GAME_VAR(int, 0x9eeba4) = 0;
	GAME_VAR(int, 0x4d7348) = 0;
	GAME_VAR(int, 0x9f1060) = 0;
	GAME_VAR(int, 0x9ef1f8) = 20;
	GAME_VAR(int, 0x9ef200) = size[k * 63];
	GAME_VAR(int, 0x9f16b8) = 0;
	return 0;
}

/* 0x42c9f0: the graphic section of axis.cfg written: the video mode by its number 0x83a9c0 (0 .. 7: 640x480 and
   the added wide modes, 1024x768, DESKTOP; nothing for another), the colour depth (0x83a9c4: 16 or 32), polygon
   detail (0x83a9c8: LOW or HIGH), then four on/off switches (0x83a9cc .. 0x83a9d8; 1 is on): linear filtering,
   mipmapping, the frame counter and the simple menu, each line after its keyword. Returns the last fputs */
u32 (cfg_parseGraphic)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)(s), f)
	static const u32 mode[8] = { 0x4b1b6c, 0x4ac84c, 0x4ac870, 0x4ac894, 0x4ac8b8, 0x4ac8dc, 0x4ac900, 0x4ac920 };
	static const u32 switches[4] = { 0x4b1aac, 0x4b1a94, 0x4b1a7c, 0x4b1a64 };
	FPUTS(0x4b1b78);   /* "set_graphic videomode " */
	if (GAME_VAR(u32, 0x83a9c0) <= 7)
		FPUTS(mode[GAME_VAR(u32, 0x83a9c0)]);
	FPUTS(0x4b1b00);   /* "set_graphic colordepth " */
	FPUTS(GAME_VAR(int, 0x83a9c4) ? 0x4b1af8 : 0x4b1afc);
	FPUTS(0x4b1adc);   /* "set_graphic polygondetail " */
	FPUTS(GAME_VAR(int, 0x83a9c8) ? 0x4b1acc : 0x4b1ad4);
	for (int i = 0; i < 4; i++) {
		FPUTS(switches[i]);
		FPUTS(GAME_VAR(int, 0x83a9cc + i * 4) == 1 ? 0x4b17e4 : 0x4b17dc);
	}
	return FPUTS(0x4b182c);
#undef FPUTS
}

/* 0x42c6f0: the server section of axis.cfg written from the player's record (0x4ded20): the name (with an extra
   line break by fprintf), the map and player count (signed bytes 0x4ded40 / 41), customize on/off (0x4ded42), the
   game type (0x4ded43: 1 .. 14 by name, any other DEATH MATCH) and the game and time flags (bytes 0x4ded44 / 45).
   Returns the last fputs */
u32 (cfg_parseServer)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)(s), f)
	static const u32 type[15] = { 0x4b1878, 0x4b1988, 0x4b1978, 0x4b1964, 0x4b1954, 0x4b1940, 0x4b192c, 0x4b1914,
	                              0x4b1904, 0x4b18f0, 0x4b18dc, 0x4b18c4, 0x4b18b0, 0x4b18a0, 0x4b1888 };
	const u8 *me = (const u8 *)0x4ded20;
	char number[12];
	FPUTS(0x4b19f0);   /* "set_server name " */
	FPUTS(me);
	GAME_CDECL(0x49f135, int, void *, const char *)(f, (const char *)0x4b182c);   /* fprintf "\n" */
	FPUTS(0x4b19e0);   /* "set_server map " */
	itoa((signed char)me[0x20], number, 10);
	FPUTS(number);
	FPUTS(0x4b182c);
	FPUTS(0x4b19c8);   /* "set_server numofplayer " */
	itoa((signed char)me[0x21], number, 10);
	FPUTS(number);
	FPUTS(0x4b182c);
	FPUTS(0x4b19b0);   /* "set_server customize " */
	FPUTS(me[0x22] == 1 ? 0x4b17e4 : 0x4b17dc);
	FPUTS(0x4b199c);   /* "set_server type " */
	u32 kind = (u32)(int)(signed char)me[0x23];
	FPUTS(type[kind <= 14 ? kind : 0]);
	itoa(me[0x24], number, 10);
	FPUTS(0x4b1860);   /* "set_server gameflag " */
	FPUTS(number);
	FPUTS(0x4b182c);
	itoa(me[0x25], number, 10);
	FPUTS(0x4b1848);   /* "set_server timeflag " */
	FPUTS(number);
	return FPUTS(0x4b1844);   /* "\n\n" */
#undef FPUTS
}

/* 0x43f160: the command line the launcher started the game with, split at spaces into 0x9dd890 (the count in
   0x9dd88c). "-net" alone: started for a network game when axiswl.dat is there (0x76d410 and 0x76d364 set);
   "-ip x <server>": the server's address into 0x4de748 (0x76d410 set). Empty or longer than 0x400: nothing.
   Returns what the original leaves in eax (the count, the comparison, fclose's or strcpy's length) */
u32 (arena_readLaunchFile)(char *line)
{
	size_t length = strlen(line);
	if (length > 0x400 || length <= 1) {
		GAME_VAR(int, 0x9dd88c) = 0;
		GAME_VAR(int, 0x76d410) = 0;
		GAME_VAR(int, 0x76d364) = 0;
		return 0;
	}
	char **args = (char **)0x9dd890;
	char *word = crt_strtok(line, (const char *)0x4b035c);   /* " " */
	GAME_VAR(int, 0x9dd88c) = 0;
	do {
		args[GAME_VAR(int, 0x9dd88c)++] = word;
		word = crt_strtok(NULL, (const char *)0x4b035c);
	} while (word);
	GAME_VAR(int, 0x76d410) = 0;
	GAME_VAR(int, 0x76d364) = 0;
	u32 r = GAME_VAR(u32, 0x9dd88c);
	if (r == 1) {
		r = (u32)str_order(args[0], (const char *)0x4b2880);   /* "-net" */
		if (r)
			return r;
		void *f = crt_fopen((const char *)0x4ad5e4, (const char *)0x4ad5e0);   /* "axiswl.dat", "rt" */
		if (f) {
			GAME_VAR(int, 0x76d410) = 1;
			GAME_VAR(int, 0x76d364) = 1;
			r = fclose(f);
		}
	}
	if (GAME_VAR(int, 0x9dd88c) != 3)
		return r;
	r = (u32)str_order(args[1], (const char *)0x4b287c);   /* "-ip" */
	if (r)
		return r;
	GAME_VAR(int, 0x76d410) = 1;
	memset((void *)0x4de748, 0, 0x400);
	GAME_VAR(int, 0x76d364) = 0;
	strcpy((char *)0x4de748, args[2]);
	return strlen(args[2]) + 1;
}

#define crt_fgets(line, size, f) GAME_CDECL(0x49ecd7, char *, char *, int, void *)(line, size, f)

/* 0x42b3e0: the game's messages read from msgkor.dat or msgeng.dat (by the language 0x9dae74; in the data folder),
   one line each into 0x80-byte slots from 0x74de24 with the line break cut off; "//" comment lines and empty lines
   skipped. Without the file a message box and the game ends. Returns fclose's eax */
u32 (data_loadMessages)(void)
{
	char path[0x105];
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)0x9dae7c);
	strcat(path, (const char *)(GAME_VAR(int, 0x9dae74) == 1 ? 0x4b1430 : 0x4b1424));   /* "msgkor.dat" / "msgeng.dat" */
	void *f = crt_fopen(path, (const char *)0x4ad5e0);   /* "rt" */
	if (!f) {
		MessageBoxA(NULL, (const char *)0x4b13f8, (const char *)0x4b141c, 0);   /* "Text Message Data File Not Found" */
		GAME_CDECL(0x49edac, void, int)(-1);   /* exit */
	}
	char *message = (char *)0x74de24;
	for (;;) {
		char line[0x80];
		memset(line, 0, sizeof line);
		if (!crt_fgets(line, 0x80, f))
			break;
		if ((line[0] == '/' && line[1] == '/') || strlen(line) == 1)
			continue;
		strcpy(message, line);
		size_t n = strlen(message);
		message[n - 1] = '\0';   /* the line break */
		message[n] = '\0';
		message += 0x80;
	}
	return fclose(f);
}

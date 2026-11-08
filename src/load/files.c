/* files.c: the game's file reads and writes: the scrambled data files' record blocks (file_readScrambled /
   file_writeScrambled), axis.cfg (cfg_*), the pilot profiles' files (profile_*), axis.mis (mission_*), the message,
   character, map-info and skirmish data files (data_load*), the component catalogue, the chat macros (Chat.scp), the
   archives' item files, the replay file opened and closed, the launcher's files and the command line. */
#include "../game.h"
#include <string.h>
#include <stdarg.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* 0x48b460: the stage's command count and that many 0x30-byte commands */
u32 THISCALL (map_readCommands)(u8 *self, void *f)
{
	Stage *st = (Stage *)self;
	fread_scrambled(&st->commandCount, 4, 1, f);
	return fread_scrambled(st->commands, 0x30, (u32)st->commandCount, f);
}

/* 0x483d70: a light factor pool read: its count and next free slot, that many 0x2c-byte records, and enabled */
u32 THISCALL (LightFactors_read)(u8 *self, void *f)
{
	LightFactors *lf = (LightFactors *)self;
	fread_scrambled(&lf->count, 4, 1, f);
	fread_scrambled(&lf->nextFree, 4, 1, f);
	fread_scrambled(lf->records, 0x2c, (u32)lf->count, f);
	return fread_scrambled(&lf->enabled, 4, 1, f);
}

/* 0x4617b0: the 100 chat macros (chatMacros, 0x39 bytes each) written to "Chat.scp"; fclose's result, 0 when the
   file cannot be opened */
u32 THISCALL (chat_saveMacros)(Scene *scene)
{
	void *f = crt_fopen((const char *)STR(0x4c45ec, "Chat.scp"), (const char *)STR(0x4b2ab0, "wb"));
	if (!f)
		return 0;
	crt_fwrite(scene->chatMacros, 0x39, 100, f);
	return fclose(f);
}

/* 0x462740 (thiscall on the scene): a chat line as a macro. "/N=text" (N one digit) stores text as macro N and saves
   them (-1); "/N" or "/NN" puts macro N into out (1); anything else is not a macro (0) */
int THISCALL (chat_applyMacro)(Scene *scene, const char *in, char *out)
{
	char line[0x100];
	if (in[0] != '/')
		return 0;
	strcpy(line, in + 1);
	if (line[0] < '0' || line[0] > '9')
		return 0;
	int n = line[0] - '0';
	if (line[1] >= '0' && line[1] <= '9')
		n = n * 10 + line[1] - '0';
	char *macro = scene->chatMacros[n];
	if (line[1] == '=') {
		strcpy(macro, line + 2);
		chat_saveMacros(scene);   /* chat_saveMacros: saves them */
		return -1;
	}
	strcpy(out, macro);
	return 1;
}

/* 0x487ed0: the replay being recorded closed (fclose's result; 0 when none) */
u32 THISCALL (replay_closeRecording)(Scene *scene)
{
	if (!scene->recording)
		return 0;
	u32 r = fclose(scene->replayFile);
	scene->recording = 0;
	return r;
}

/* 0x46ca70: does the file named by the formatted path exist (opens for reading)? */
int (file_existsf)(const char *format, ...)
{
	char path[256];
	va_list args;
	va_start(args, format);
	vsprintf(path, format, args);
	va_end(args);
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		return 0;
	fclose(f);
	return 1;
}

/* 0x46cbe0: count records of size bytes read, each byte unscrambled: xor 0x59, rotated left by one. Returns fread's
   count */
u32 (file_readScrambled)(u8 *p, u32 size, u32 count, void *f)
{
	int n = (int)(size * count);
	u32 r = crt_fread(p, size, count, f);   /* fread */
	for (int i = 0; i < n; i++) {
		u8 c = p[i] ^ 0x59;
		p[i] = (u8)(c << 1 | c >> 7);
	}
	return r;
}

/* ---- an entry of a .dat archive (0x44-byte records, the data's offset at +0x40) found by name and the archive's
   file positioned at it; a missing name is a fatal error (sys_fatalErrorN, under the archive's log name) ---- */
static void *dat_entry(int index, const char *name, u32 table, u32 file, u32 log)
{
	if (index < 0) {
		sys_fatalErrorN((void *)RELOC(log), (const char *)STR(0x4b3f80, "can't find item(%s) - getItemFileBy()"), name);   /* sys_fatalError */
		return 0;
	}
	crt_fseek(GAME_VAR(void *, file), ((const ArchiveEntry *)GAME_VAR(u8 *, table))[index].offset, 0);   /* fseek */
	return GAME_VAR(void *, file);
}
/* 0x466d60: in Shape.dat */
void *(shapeDat_getItemFileBy)(const char *name)
{
	return dat_entry(shapeDat_findByName(name), name, (OBJ(g_shapeDat) + 0x4), (OBJ(g_shapeDat) + 0x8), OBJ(g_logShapeManager));
}
/* 0x46b140: in the skeleton archive */
void *(skelDat_getItemFileBy)(const char *name)
{
	return dat_entry(skelDat_findByName(name), name, (OBJ(g_skelDat) + 0x4), (OBJ(g_skelDat) + 0x8), OBJ(g_logSkeletonManager));
}

/* 0x4617f0: the chat macros (chatMacros: 100 of 0x39 bytes) read from Chat.scp; without the file, all 100 emptied
   (first byte 0) and saved so (chat_saveMacros). Returns what the original leaves in eax */
u32 THISCALL (chat_loadMacros)(Scene *scene)
{
	void *f = crt_fopen((const char *)STR(0x4c45ec, "Chat.scp"), (const char *)STR(0x4ad170, "rb"));
	if (f) {
		crt_fread(scene->chatMacros, 0x39, 100, f);   /* fread */
		return fclose(f);
	}
	for (int k = 0; k < 100; k++)
		((u8 *)scene)[0x2340d3d + k * 0x39] = 0;
	return chat_saveMacros(scene);   /* chat_saveMacros */
}

/* 0x46cc30: count records of size bytes written scrambled (each byte rotated right by one, xor 0x59), then put back
   as they were. Returns fwrite's count */
u32 (file_writeScrambled)(u8 *p, u32 size, u32 count, void *f)
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

/* 0x42c650: the player's section of axis.cfg written, each after its keyword: the name (g_cfgPlayerName, with an
   extra line break by fprintf), the colour (g_playerCorporation: RED, BLUE or YELLOW) and the customize switch
   (g_playerCustomize: ON / OFF), then an empty line. Returns the last fputs */
u32 (cfg_writePlayer)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)RELOC(s), f)
	FPUTS(STR(0x4b1830, "set_player name "));
	FPUTS(OBJ(g_cfgPlayerName));
	crt_fprintf(f, (const char *)STR(0x4b182c, "\n"));   /* fprintf */
	FPUTS(STR(0x4b1818, "set_player color "));
	int corp = g_playerCorporation;
	FPUTS(corp == 1 ? STR(0x4b1808, "BLUE\n") : corp == 2 ? STR(0x4b1810, "YELLOW\n") : STR(0x4b1800, "RED\n"));
	FPUTS(STR(0x4b17e8, "set_player customize "));
	FPUTS(g_playerCustomize == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	return FPUTS(STR(0x4b182c, "\n"));
#undef FPUTS
}

/* 0x42cba0: the key bindings' section of axis.cfg: a "set_key <action><1|2> " line for each binding (g_keyForward, 64
   of them, written in the menu's order) with its key's name (g_keyNames), then the mouse: convert and smooth (ON / OFF:
   g_mouseInvert, g_mouseSmooth), the sensitivity (g_mouseSensitivity) and the crosshairs (g_crosshairSetting). Returns the last fputs */
u32 (cfg_writeKeyBindings)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)RELOC(s), f)
	static const struct { u32 line; u8 binding; } keys[64] = {
		{ STR(0x4b2184, "set_key forward1 "), 0 }, { STR(0x4b2170, "set_key forward2 "), 1 },   /* forward */
		{ STR(0x4b215c, "set_key backward1 "), 2 }, { STR(0x4b2148, "set_key backward2 "), 3 },   /* backward */
		{ STR(0x4b2134, "set_key left-step1 "), 4 }, { STR(0x4b2120, "set_key left-step2 "), 5 },   /* left-step */
		{ STR(0x4b2108, "set_key right-step1 "), 6 }, { STR(0x4b20f0, "set_key right-step2 "), 7 },   /* right-step */
		{ STR(0x4b20dc, "set_key left-turn1 "), 8 }, { STR(0x4b20c8, "set_key left-turn2 "), 9 },   /* left-turn */
		{ STR(0x4b20b0, "set_key right-turn1 "), 10 }, { STR(0x4b2098, "set_key right-turn2 "), 11 },   /* right-turn */
		{ STR(0x4b207c, "set_key fixed-altitude1 "), 12 }, { STR(0x4b2060, "set_key fixed-altitude2 "), 13 },   /* fixed-altitude */
		{ STR(0x4b204c, "set_key booster1 "), 14 }, { STR(0x4b2038, "set_key booster2 "), 15 },   /* booster */
		{ STR(0x4b2024, "set_key moveup1 "), 16 }, { STR(0x4b2010, "set_key moveup2 "), 17 },   /* moveup */
		{ STR(0x4b1ffc, "set_key movedown1 "), 18 }, { STR(0x4b1fe8, "set_key movedown2 "), 19 },   /* movedown */
		{ STR(0x4b1fd8, "set_key fire1 "), 20 }, { STR(0x4b1fc8, "set_key fire2 "), 21 },   /* fire */
		{ STR(0x4b1fb0, "set_key pre-weapon1 "), 22 }, { STR(0x4b1f98, "set_key pre-weapon2 "), 23 },   /* pre-weapon */
		{ STR(0x4b1f80, "set_key next-weapon1 "), 24 }, { STR(0x4b1f68, "set_key next-weapon2 "), 25 },   /* next-weapon */
		{ STR(0x4b1f4c, "set_key 1st-hand-weapon1 "), 30 }, { STR(0x4b1f30, "set_key 1st-hand-weapon2 "), 31 },   /* 1st-hand-weapon */
		{ STR(0x4b1f14, "set_key 2nd-hand-weapon1 "), 32 }, { STR(0x4b1ef8, "set_key 2nd-hand-weapon2 "), 33 },   /* 2nd-hand-weapon */
		{ STR(0x4b1edc, "set_key 3rd-hand-weapon1 "), 34 }, { STR(0x4b1ec0, "set_key 3rd-hand-weapon2 "), 35 },   /* 3rd-hand-weapon */
		{ STR(0x4b1ea4, "set_key 4th-hand-weapon1 "), 36 }, { STR(0x4b1e88, "set_key 4th-hand-weapon2 "), 37 },   /* 4th-hand-weapon */
		{ STR(0x4b1e68, "set_key right-shoulder-weapon1 "), 26 }, { STR(0x4b1e48, "set_key right-shoulder-weapon2 "), 27 },   /* right-shoulder-weapon */
		{ STR(0x4b1e28, "set_key left-shoulder-weapon1 "), 28 }, { STR(0x4b1e08, "set_key left-shoulder-weapon2 "), 29 },   /* left-shoulder-weapon */
		{ STR(0x4b1df8, "set_key zoom1 "), 38 }, { STR(0x4b1de8, "set_key zoom2 "), 39 },   /* zoom */
		{ STR(0x4b1dd4, "set_key alt-shoot1 "), 40 }, { STR(0x4b1dc0, "set_key alt-shoot2 "), 41 },   /* alt-shoot */
		{ STR(0x4b1db0, "set_key talk1 "), 42 }, { STR(0x4b1da0, "set_key talk2 "), 43 },   /* talk */
		{ STR(0x4b1d8c, "set_key team-talk1 "), 44 }, { STR(0x4b1d78, "set_key team-talk2 "), 45 },   /* team-talk */
		{ STR(0x4b1d64, "set_key use-item1 "), 46 }, { STR(0x4b1d50, "set_key use-item2 "), 47 },   /* use-item */
		{ STR(0x4b1d3c, "set_key feedback1 "), 48 }, { STR(0x4b1d28, "set_key feedback2 "), 49 },   /* feedback */
		{ STR(0x4b1d14, "set_key call-menu1 "), 50 }, { STR(0x4b1d00, "set_key call-menu2 "), 51 },   /* call-menu */
		{ STR(0x4b1ce8, "set_key quick-save1 "), 52 }, { STR(0x4b1cd0, "set_key quick-save2 "), 53 },   /* quick-save */
		{ STR(0x4b1cb8, "set_key quick-load1 "), 54 }, { STR(0x4b1ca0, "set_key quick-load2 "), 55 },   /* quick-load */
		{ STR(0x4b1c90, "set_key score1 "), 56 }, { STR(0x4b1c80, "set_key score2 "), 57 },   /* score */
		{ STR(0x4b1c64, "set_key mission-objective1 "), 58 }, { STR(0x4b1c48, "set_key mission-objective2 "), 59 },   /* mission-objective */
		{ STR(0x4b1c2c, "set_key change-viewmode1 "), 60 }, { STR(0x4b1c10, "set_key change-viewmode2 "), 61 },   /* change-viewmode */
		{ STR(0x4b1c00, "set_key help1 "), 62 }, { STR(0x4b1bf0, "set_key help2 "), 63 },   /* help */
	};
	const int *binding = (const int *)ADDR(g_keyForward);
	const char *const *key_name = (const char *const *)OBJ(g_keyNames);
	for (int k = 0; k < 64; k++) {
		FPUTS(keys[k].line);
		FPUTS(key_name[binding[keys[k].binding]]);
		FPUTS(STR(0x4b182c, "\n"));
	}
	FPUTS(STR(0x4b1bd8, "set_mouse convertmouse "));
	FPUTS(g_mouseInvert == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	FPUTS(STR(0x4b1bc0, "set_mouse smoothmouse "));
	FPUTS(g_mouseSmooth == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	char number[12];
	itoa(g_mouseSensitivity, number, 10);
	FPUTS(STR(0x4b1ba8, "set_mouse sensitivity "));
	FPUTS(number);
	FPUTS(STR(0x4b182c, "\n"));
	itoa(g_crosshairSetting, number, 10);
	FPUTS(STR(0x4b1b90, "set_mouse crosshairs "));
	FPUTS(number);
	return FPUTS(STR(0x4b182c, "\n"));
#undef FPUTS
}

/* 0x42d730: axis.cfg written in the data folder (g_dataDir): its header, then the player, server, sound, graphics and
   key binding sections (the original does not check that the file opened). Returns fclose's eax */
u32 (cfg_writeAxisCfg)(void)
{
	char path[0x184];
	strcpy(path, g_dataDir);
	strcat(path, (const char *)STR(0x4b2198, "\\axis.cfg"));   /* the file's name */
	void *f = crt_fopen(path, (const char *)STR(0x4b21a4, "wt"));
	crt_fputs((const char *)STR(0x4b0f50, "AXIS CONFIGURATION FILE Master ver 1...."), f);   /* fputs */
	crt_fputs((const char *)STR(0x4b182c, "\n"), f);
	static const u32 sections[5] = { FN(cfg_writePlayer), FN(cfg_writeServer), FN(cfg_writeSound), FN(cfg_writeGraphic), FN(cfg_writeKeyBindings) };   /* player .. key bindings */
	for (int k = 0; k < 5; k++)
		GAME_CDECL(sections[k], u32, void *)(f);
	return fclose(f);
}

/* 0x43f8b0: the launcher's marks made invalid at exit: other words (0xa1a2a3a4, 0xb1b2b3b4, 0xc1c2c3c4) written over
   the marks at offset 2000 of three data files, save\axisgame.dat and game.dat deleted (the files and marks the
   app_checkFile_* checks read). Returns the last DeleteFileA's eax */
u32 (app_invalidateLauncherMarks)(void)
{
	static const u32 files[3] = { STR(0x4b03c4, "initdata\\profeng.dat"), STR(0x4b03dc, "initdata\\profkor.dat"), STR(0x4b03f4, "initdata\\skirmish.dat") };
	static const u32 marks[3] = { 0xa1a2a3a4, 0xb1b2b3b4, 0xc1c2c3c4 };
	for (int k = 0; k < 3; k++) {
		void *f = crt_fopen((const char *)RELOC(files[k]), (const char *)STR(0x4b29e8, "r+"));
		crt_fseek(f, 2000, 0);   /* fseek */
		u32 mark = marks[k];
		crt_fwrite(&mark, 4, 1, f);
		fclose(f);
	}
	DeleteFileA((const char *)STR(0x4b040c, "save\\axisgame.dat"));   /* DeleteFileA */
	return DeleteFileA((const char *)STR(0x4b0420, "game.dat"));
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
	crt_sprintf(path, format);   /* sprintf */
	GAME_VAR(void *, file) = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!GAME_VAR(void *, file))
		sys_fatalErrorN(log, (const char *)STR(0x4b3ee4, "can't open file(%s) - initBy()"), path);
	crt_fread((void *)RELOC(count), 4, 1, GAME_VAR(void *, file));   /* fread */
	GAME_VAR(void *, table) = crt_malloc(GAME_VAR(int, count) * 0x44);
	if (!GAME_VAR(void *, table))
		sys_fatalErrorN(log, (const char *)STR(0x4b3eb4, "insufficient memory for itemBuffer(%d..."), GAME_VAR(int, count));
	return crt_fread(GAME_VAR(void *, table), 0x44, GAME_VAR(int, count),
	                                                          GAME_VAR(void *, file));
}
/* 0x466c00: Shape.dat; skelDat_initBy: the skeleton archive */
u32 (shapeDat_initBy)(void) { return dat_open(OBJ(g_shapeDat), (const char *)STR(0x4c4d20, "Data\\Shape.dat"), (void *)OBJ(g_logShapeManager)); }
u32 (skelDat_initBy)(void) { return dat_open(OBJ(g_skelDat), (const char *)STR(0x4c54b4, "Data\\Skeleton.dat"), (void *)OBJ(g_logSkeletonManager)); }

/* 0x42c910: the sound section of axis.cfg written: the two volumes (g_soundVolume, g_musicVolume) as numbers, then two on/off
   switches (g_sound3D, g_stereoReverse; 1 is on), each after its keyword. Returns the last fputs */
u32 (cfg_writeSound)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)RELOC(s), f)
	char number[12];
	itoa(g_soundVolume, number, 10);
	FPUTS(STR(0x4b1a4c, "set_sound effectvolume "));
	FPUTS(number);
	FPUTS(STR(0x4b182c, "\n"));
	itoa(g_musicVolume, number, 10);
	FPUTS(STR(0x4b1a34, "set_sound musicvolume "));
	FPUTS(number);
	FPUTS(STR(0x4b182c, "\n"));
	FPUTS(STR(0x4b1a20, "set_sound 3dsound "));
	FPUTS(g_sound3D == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	FPUTS(STR(0x4b1a04, "set_sound stereoreverse "));
	FPUTS(g_stereoReverse == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	return FPUTS(STR(0x4b182c, "\n"));
#undef FPUTS
}

/* 0x41e7c0: does map k's file exist ("map/" + its name (32 bytes a slot at g_mapNames) + ".bfd")? 1 when it opens, 0
   when not or when the name is shorter than 2 letters */
int (map_fileExists)(int k)
{
	const char *name = (const char *)(OBJ(g_mapNames) + k * 32);
	if (strlen(name) <= 1)
		return 0;
	char path[0x400];
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)STR(0x4b0434, "map/"));
	strcat(path, name);
	strcat(path, (const char *)STR(0x4b042c, ".bfd"));
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		return 0;
	fclose(f);
	return 1;
}

#define crt_findfirst(pattern, data) GAME_CDECL(0x49f694, int, const char *, void *)(pattern, data)
#define crt_findnext(handle, data) GAME_CDECL(0x49f75e, int, int, void *)(handle, data)
#define crt_findclose(handle) GAME_CDECL(0x49f823, int, int)(handle)

/* 0x440c60: the autoplay folder's files (0x4b2a8c, pattern 0x4b2a84) appended to the replay list (0x44-byte records
   from g_replayList, count g_replayFileCount, at most 1023), then back to the parent folder (0x4b2a80). Returns the last chdir's
   eax */
int (autoplay_listFiles)(void)
{
	struct { u32 attrib, created, accessed, written, size; char name[260]; } found;   /* _finddata_t */
	int r = crt_chdir((const char *)STR(0x4b2a8c, "autoplay"));
	if (r)
		return r;
	int search = crt_findfirst((const char *)STR(0x4b2a84, "*.ape"), &found);
	if (search < 0)
		return crt_chdir((const char *)STR(0x4b2a80, ".."));
	strcpy(g_replayList[g_replayFileCount].name, found.name);
	g_replayFileCount++;
	while (!crt_findnext(search, &found)) {
		strcpy(g_replayList[g_replayFileCount].name, found.name);
		if (++g_replayFileCount > 0x3fe)
			break;
	}
	crt_findclose(search);
	return crt_chdir((const char *)STR(0x4b2a80, ".."));
}

/* 0x41e260: eight check bytes read from the launcher's file (0x4b03b4; each at its own offset) into g_launcherCheck (12
   bytes cleared first). 1, or 0 when the file is missing */
int (app_readLauncherCheck)(void)
{
	static const u16 offsets[8] = { 0x1a2b, 0x1a2c, 0x2dbf, 0x2dc0, 0x38a4, 0x38a5, 0x55f1, 0x55f2 };
	memset((void *)OBJ(g_launcherCheck), 0, 12);
	void *f = crt_fopen((const char *)STR(0x4b03b4, "axisplay.exe"), (const char *)STR(0x4ad170, "rb"));
	if (!f)
		return 0;
	for (int i = 0; i < 8; i++) {
		crt_fseek(f, offsets[i], 0);   /* fseek */
		crt_fread((void *)(OBJ(g_launcherCheck) + i), 1, 1, f);   /* fread */
	}
	fclose(f);
	return 1;
}

/* ---- axisuser.dat (in the data folder g_dataDir), written afresh: a magic word (0xfefefef7), the count (g_profileCount),
   the current profile (g_currentProfile, first set from g_profileChosen), g_profileListTop, g_profileListRow, the 32-byte name g_profileName and the
   0x48-byte profile records from g_profiles. Without the file the count is 0 ---- */
static void profiles_path(char *path)
{
	strcpy(path, g_dataDir);
	strcat(path, (const char *)STR(0x4b2ab4, "\\axisuser.dat"));
}

static void *profiles_create(void)
{
	char path[0x184];
	profiles_path(path);
	(*(u32 *)&g_currentProfile) = (*(u32 *)&g_profileChosen);
	void *f = crt_fopen(path, (const char *)STR(0x4b2ab0, "wb"));
	if (!f)
		g_profileCount = 0;
	return f;
}

/* returns fclose's eax */
static u32 profiles_write(void *f)
{
	u32 magic = 0xfefefef7;
	crt_fwrite(&magic, 4, 1, f);
	crt_fwrite((void *)ADDR(g_profileCount), 4, 1, f);
	crt_fwrite((void *)ADDR(g_currentProfile), 4, 1, f);
	crt_fwrite((void *)ADDR(g_profileListTop), 4, 1, f);
	crt_fwrite((void *)ADDR(g_profileListRow), 4, 1, f);
	crt_fwrite((void *)OBJ(g_profileName), 0x20, 1, f);
	for (int i = 0; i < g_profileCount; i++)
		crt_fwrite((void *)(OBJ(g_profiles) + i * 0x48), 0x48, 1, f);
	return fclose(f);
}

/* 0x445f70: the file written with `count` profiles and the three header words cleared. Returns fclose's eax (0
   without the file) */
u32 (profile_writeCleared)(int count)
{
	void *f = profiles_create();
	if (!f)
		return 0;
	g_profileCount = count;
	(*(u32 *)&g_currentProfile) = 0;
	(*(u32 *)&g_profileListTop) = 0;
	(*(u32 *)&g_profileListRow) = 0;
	return profiles_write(f);
}

/* 0x447320: the file written as the profiles stand, the name g_profileName being the current profile's. Returns
   fclose's eax (0 without the file) */
u32 (profile_writeFile)(void)
{
	void *f = profiles_create();
	if (!f)
		return 0;
	memset((void *)OBJ(g_profileName), 0, 0x20);
	strcpy(g_profileName, (const char *)(OBJ(g_profileNames) + g_currentProfile * 0x48));
	return profiles_write(f);
}


/* axis.mis (in the data folder) opened for reading */
static void *mis_open(void)
{
	char path[0x184];
	strcpy(path, g_dataDir);
	strcat(path, (const char *)STR(0x4b2aa4, "\\axis.mis"));
	return crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
}

/* 0x4435f0: the mission list read from axis.mis: the list cleared first (missions_clear), four header words (the
   count g_missionCount, then 0x9ef2c4 .. 0x9ef2cc), each mission's entry (g_missions: all but its block size, field by
   field) and then all their block sizes. Without the file, message
   0xb and its eax; otherwise fclose's */
u32 (mission_loadAxisMis)(void)
{
	void *f = mis_open();
	if (!f)
		return menu_showMessage(0xb);
	missions_clear();   /* missions_clear */
	for (int k = 0; k < 4; k++)
		crt_fread((void *)(ADDR(g_missionCount) + k * 4), 4, 1, f);
	static const struct { int offset, size; } part[8] = {
		{ offsetof(Mission, unused0), 4 }, { offsetof(Mission, name), 0x40 }, { offsetof(Mission, title), 0x20 }, { offsetof(Mission, briefing), 0x80 },
		{ offsetof(Mission, number), 4 }, { offsetof(Mission, unusedE8), 4 }, { offsetof(Mission, result), 4 }, { offsetof(Mission, unusedF0), 4 } };
	Mission *mission = g_missions;
	for (int i = 0; i < g_missionCount; i++)
		for (int k = 0; k < 8; k++)
			crt_fread((u8 *)&mission[i] + part[k].offset, part[k].size, 1, f);
	for (int i = 0; i < g_missionCount; i++)
		crt_fread(&mission[i].blockSize, 4, 1, f);
	return fclose(f);
}

/* 0x443af0: mission k's block read from axis.mis (in the data folder): after a 0x1a-byte header, 0xf8 bytes for
   each of the g_missionCount entries and the blocks before it (their blockSize) into a new buffer
   (mission_loadAxisMis reads a 16-byte header, 0xf4 bytes an entry and then the sizes, 4 bytes each: so this starts
   10 bytes past the end of what it reads, whatever the count - a test file with 10 bytes there opens; no real
   axis.mis is known)
   g_briefingSource (the old one freed); its size into g_briefingEnd, the mission list's state cleared and the page set to
   20 (the mission settings). Without the file, message 0xb and its eax; otherwise 0 */
u32 (mission_loadBriefing)(int k)
{
	void *f = mis_open();
	if (!f)
		return menu_showMessage(0xb);
	const Mission *mission = g_missions;
	int offset = 0;
	for (int i = 0; i < k; i++)
		offset += mission[i].blockSize;
	crt_fseek(f, offset + g_missionCount * 0xf8 + 0x1a, 0);
	if ((*(void **)&g_briefingSource))
		crt_free((*(void **)&g_briefingSource));
	void *block = crt_malloc(mission[k].blockSize);
	(*(void **)&g_briefingSource) = block;
	crt_fread(block, mission[k].blockSize, 1, f);
	fclose(f);
	memset((void *)OBJ(g_briefingPageStarts), 0, 0xc8);
	g_unusedBriefingWord = 0;
	memset((void *)OBJ(g_briefingText), 0, 0x640);
	memset((void *)OBJ(g_missionClearBuffer), 0, 0x640);
	g_briefingShown = 0;
	g_briefingDone = 0;
	g_briefingStart = 0;
	g_textHitBottom = 0;
	g_briefingPage = 0;
	g_missionsPage = 20;
	g_briefingEnd = mission[k].blockSize;
	(*(int *)&g_briefingClock) = 0;
	return 0;
}

/* 0x42c9f0: the graphic section of axis.cfg written: the video mode by its number g_videoMode (0 .. 7: 640x480 and
   the added wide modes, 1024x768, DESKTOP; nothing for another), the colour depth (g_videoDepth: 16 or 32), polygon
   detail (0x83a9c8: LOW or HIGH), then four on/off switches (0x83a9cc .. 0x83a9d8; 1 is on): linear filtering,
   mipmapping, the frame counter and the simple menu, each line after its keyword. Returns the last fputs */
u32 (cfg_writeGraphic)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)RELOC(s), f)
	static const u32 mode[8] = { STR(0x4b1b6c, "640x480\n"), STR(0x4ac84c, "1280x720\n"), STR(0x4ac870, "1600x900\n"), STR(0x4ac894, "1920x1080\n"), STR(0x4ac8b8, "2560x1440\n"), STR(0x4ac8dc, "3840x2160\n"), STR(0x4ac900, "1024x768\n"), STR(0x4ac920, "DESKTOP\n") };
	static const u32 switches[4] = { STR(0x4b1aac, "set_graphic linearfiltering "), STR(0x4b1a94, "set_graphic mipmapping "), STR(0x4b1a7c, "set_graphic viewfps "), STR(0x4b1a64, "set_graphic simplemenu ") };
	FPUTS(STR(0x4b1b78, "set_graphic videomode "));
	if (g_videoMode <= 7)
		FPUTS(mode[g_videoMode]);
	FPUTS(STR(0x4b1b00, "set_graphic colordepth "));
	FPUTS(g_videoDepth ? STR(0x4b1af8, "32\n") : STR(0x4b1afc, "16\n"));
	FPUTS(STR(0x4b1adc, "set_graphic polygondetail "));
	FPUTS(g_highDetail ? STR(0x4b1acc, "HIGH\n") : STR(0x4b1ad4, "LOW\n"));
	for (int i = 0; i < 4; i++) {
		FPUTS(switches[i]);
		FPUTS(g_cfgSwitches[i] == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	}
	return FPUTS(STR(0x4b182c, "\n"));
#undef FPUTS
}

/* 0x42c6f0: the server section of axis.cfg written from the arena record (g_arenaName ..): the name (with an extra
   line break by fprintf), the map and the player count (signed bytes g_arenaMap / g_arenaMaxPlayers), customize on/off
   (g_arenaRotation), the game type (g_arenaGameType: 1 .. 14 by name, any other DEATH MATCH) and the frag and time
   limits (bytes g_arenaFragLimit / g_arenaTimeLimit, keywords gameflag / timeflag). Returns the last fputs */
u32 (cfg_writeServer)(void *f)
{
#define FPUTS(s) GAME_CDECL(0x49f167, u32, const char *, void *)((const char *)RELOC(s), f)
	static const u32 type[15] = { STR(0x4b1878, "DEATH MATCH\n"), STR(0x4b1988, "TEAM DEATH MATCH\n"), STR(0x4b1978, "SUDDEN DEATH\n"), STR(0x4b1964, "TEAM SUDDEN DEATH\n"), STR(0x4b1954, "SHOTGUN ARENA\n"), STR(0x4b1940, "TEAM SHOTGUN ARENA\n"), STR(0x4b192c, "IONCANNON ARENA\n"), STR(0x4b1914, "TEAM IONCANNON ARENA\n"),
	                              STR(0x4b1904, "ROCKET ARENA\n"), STR(0x4b18f0, "TEAM ROCKET ARENA\n"), STR(0x4b18dc, "GLADIATOR ARENA\n"), STR(0x4b18c4, "TEAM GLADIATOR ARENA\n"), STR(0x4b18b0, "KING ON THE HILL\n"), STR(0x4b18a0, "PLATOON MODE\n"), STR(0x4b1888, "ACCEPT ADVANCED MODE\n") };
	const u8 *arena = (const u8 *)OBJ(g_arenaName);
	char number[12];
	FPUTS(STR(0x4b19f0, "set_server name "));
	FPUTS(arena);
	crt_fprintf(f, (const char *)STR(0x4b182c, "\n"));   /* fprintf "\n" */
	FPUTS(STR(0x4b19e0, "set_server map "));
	itoa((signed char)arena[0x20], number, 10);
	FPUTS(number);
	FPUTS(STR(0x4b182c, "\n"));
	FPUTS(STR(0x4b19c8, "set_server numofplayer "));
	itoa((signed char)arena[0x21], number, 10);
	FPUTS(number);
	FPUTS(STR(0x4b182c, "\n"));
	FPUTS(STR(0x4b19b0, "set_server customize "));
	FPUTS(arena[0x22] == 1 ? STR(0x4b17e4, "ON\n") : STR(0x4b17dc, "OFF\n"));
	FPUTS(STR(0x4b199c, "set_server type "));
	u32 kind = (u32)(int)(signed char)arena[0x23];
	FPUTS(type[kind <= 14 ? kind : 0]);
	itoa(arena[0x24], number, 10);
	FPUTS(STR(0x4b1860, "set_server gameflag "));
	FPUTS(number);
	FPUTS(STR(0x4b182c, "\n"));
	itoa(arena[0x25], number, 10);
	FPUTS(STR(0x4b1848, "set_server timeflag "));
	FPUTS(number);
	return FPUTS(STR(0x4b1844, "\n\n"));
#undef FPUTS
}

/* 0x43f160: the command line the launcher started the game with, split at spaces into g_launchArgs (the count in
   g_argCount). "-net" alone: started for a network game when axiswl.dat is there (g_launchedForNetGame and g_launchedAsHost set);
   "<x> -ip <server>": the server's address into g_serverAddressArg (g_launchedForNetGame set). Empty or longer than 0x400:
   nothing. Returns what the original leaves in eax (the count, the comparison, fclose's or strcpy's length) */
u32 (app_parseCommandLine)(char *line)
{
	size_t length = strlen(line);
	if (length > 0x400 || length <= 1) {
		g_argCount = 0;
		g_launchedForNetGame = 0;
		g_launchedAsHost = 0;
		return 0;
	}
	char **args = (char **)OBJ(g_launchArgs);
	char *word = crt_strtok(line, (const char *)STR(0x4b035c, " "));
	g_argCount = 0;
	do {
		args[g_argCount++] = word;
		word = crt_strtok(NULL, (const char *)STR(0x4b035c, " "));
	} while (word);
	g_launchedForNetGame = 0;
	g_launchedAsHost = 0;
	u32 r = (*(u32 *)&g_argCount);
	if (r == 1) {
		r = (u32)str_order(args[0], (const char *)STR(0x4b2880, "-net"));
		if (r)
			return r;
		void *f = crt_fopen((const char *)STR(0x4ad5e4, "axiswl.dat"), (const char *)STR(0x4ad5e0, "rt"));
		if (f) {
			g_launchedForNetGame = 1;
			g_launchedAsHost = 1;
			r = fclose(f);
		}
	}
	if (g_argCount != 3)
		return r;
	r = (u32)str_order(args[1], (const char *)STR(0x4b287c, "-ip"));
	if (r)
		return r;
	g_launchedForNetGame = 1;
	memset((void *)OBJ(g_serverAddressArg), 0, 0x400);
	g_launchedAsHost = 0;
	strcpy(g_serverAddressArg, args[2]);
	return strlen(args[2]) + 1;
}

/* the game ended with an error box (title "ERROR") */
static void data_missing(u32 message)
{
	MessageBoxA(NULL, (const char *)RELOC(message), (const char *)STR(0x4b141c, "ERROR"), 0);
	crt_exit(-1);   /* exit */
}

#define crt_fgets(line, size, f) GAME_CDECL(0x49ecd7, char *, char *, int, void *)(line, size, f)

/* a data file (in folder, the data folder g_dataDir or the maps' g_mapInfoDir) opened with mode; without it the game
   ends with a message box */
static void *data_open(u32 folder, u32 name, u32 mode, u32 missing)
{
	char path[0x105];
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)RELOC(folder));
	strcat(path, (const char *)RELOC(name));
	void *f = crt_fopen(path, (const char *)RELOC(mode));
	if (!f)
		data_missing(missing);
	return f;
}

/* 0x42b3e0: the game's messages read from msgkor.dat or msgeng.dat (by the language g_language; in the data folder),
   one line each into 0x80-byte slots from MSG(0, "PRESS ENTER OR CLICK MOUSE") with the line break cut off; "//" comment lines and empty lines
   skipped. Without the file a message box and the game ends. Returns fclose's eax */
u32 (data_loadMessages)(void)
{
	void *f = data_open(OBJ(g_dataDir), g_language == 1 ? STR(0x4b1430, "msgkor.dat") : STR(0x4b1424, "msgeng.dat"), STR(0x4ad5e0, "rt"),
	                    STR(0x4b13f8, "Text Message Data File Not Found"));
	char *message = (char *)MSG(0, "PRESS ENTER OR CLICK MOUSE");
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

/* ---- the pilot's campaign file (in the save folder: the pilot's name + 0x4b2afc): the 0x3ac-byte record g_pilotSave
   (a signature 0x4b0fa0 first, the pilot's name at +0x80, its value at +0x100) between blocks of noise, 20000 bytes
   before it and 24999 after (the same 10000 random bytes below 0xfe each time), scrambled with key 0x7e ---- */
#define g_pilot g_profileChosen               /* the pilot chosen in the list */
#define pilot_name(i) ((const char *)(OBJ(g_profileNames) + (i) * 0x48))

/* the current profile's name as axisuser.dat keeps it */
static void set_current_name(void)
{
	memset((void *)OBJ(g_profileName), 0, 0x20);
	strcpy(g_profileName, pilot_name(g_currentProfile));
}

static void enter_save_folder(void)
{
	if (crt_chdir((const char *)STR(0x4b2adc, "save"))) {
		crt_mkdir((const char *)STR(0x4b2adc, "save"));   /* mkdir */
		crt_chdir((const char *)STR(0x4b2adc, "save"));
	}
}

static void pilot_path(char *path)
{
	memset(path, 0, 0x80);
	strcpy(path, pilot_name(g_pilot));
	strcat(path, (const char *)STR(0x4b2afc, ".axs"));
}

static void pilot_write(void *f)
{
	u8 *noise = g_pilotNoise;
	for (int i = 0; i < 10000; i++)
		noise[i] = (u8)(crt_rand() % 0xfe);
	crt_fwrite(noise, 10000, 1, f);
	crt_fwrite(noise, 10000, 1, f);
	u8 record[0x3ac];
	memcpy(record, g_pilotSave, sizeof record);
	save_cryptRecord(record, 0x7e);
	crt_fwrite(record, sizeof record, 1, f);
	crt_fwrite(noise, 10000, 1, f);
	crt_fwrite(noise, 10000, 1, f);
	crt_fwrite(noise, 4999, 1, f);
}

/* 0x447010: the campaign progress saved: axisuser.dat written (no file: nothing more), then the pilot's file with
   the profile's record (gathered by mech_storeToProfile); g_selectedCharacter = the profile's pilot character. Returns the last chdir's eax */
int (profile_saveProgress)(void)
{
	void *f = profiles_create();
	if (!f)
		return 0;
	set_current_name();
	profiles_write(f);
	mech_storeToProfile();
	enter_save_folder();
	char path[0x80];
	pilot_path(path);
	f = crt_fopen(path, (const char *)STR(0x4b2ab0, "wb"));
	(*(u32 *)&g_selectedCharacter) = GAME_VAR(u32, OBJ(g_profileNames) + 0x40 + g_pilot * 0x48);   /* g_profileRecords[g_pilot].pilot */
	if (f)
		pilot_write(f);
	fclose(f);
	return crt_chdir((const char *)STR(0x4b2a80, ".."));
}

/* a new pilot's record: the signature, the name, the value; no progress, the default parts (0x4b2af4, 0x4b2aec,
   0x4b2ae4) and settings, twelve (170, 0.4, 0) triples */
static void campaign_new(void)
{
	memset(g_pilotSave, 0, 0x80);
	strcpy((char *)g_pilotSave, (const char *)STR(0x4b0fa0, "AXIS USER PROFILE DATA Master ver 1.0..."));
	memset((void *)(OBJ(g_pilotSave) + 0x80), 0, 0x80);
	memcpy((void *)(OBJ(g_pilotSave) + 0x80), pilot_name(g_pilot), 0x80);
	(*(u32 *)&g_selectedCharacter) = GAME_VAR(u32, OBJ(g_profileNames) + 0x40 + g_pilot * 0x48);   /* g_profileRecords[g_pilot].pilot */
	g_progress = 0;
	memset((void *)(OBJ(g_pilotSave) + 0x108), 0, 0x190);
	memset((void *)(OBJ(g_pilotSave) + 0x298), 0, 0x40);
	static const u32 cleared[6] = { (OBJ(g_pilotSave) + 0x2d8), (OBJ(g_pilotSave) + 0x2f4), (OBJ(g_pilotSave) + 0x2dc), (OBJ(g_pilotSave) + 0x2f8), (OBJ(g_pilotSave) + 0x314), (OBJ(g_pilotSave) + 0x318) };
	for (int i = 0; i < 6; i++)
		GAME_VAR(u32, cleared[i]) = 0;
	strcpy((char *)(OBJ(g_pilotSave) + 0x2d8), (const char *)STR(0x4b2af4, "[TRAP]"));
	strcpy((char *)(OBJ(g_pilotSave) + 0x2f4), (const char *)STR(0x4b2aec, "[NOPA]"));
	strcpy((char *)(OBJ(g_pilotSave) + 0x314), (const char *)STR(0x4b2ae4, "[ROLO]"));
	g_profileMechItem5 = -1;
	g_profileMechItem0 = -1;
	for (u32 a = ADDR(g_profileMechHead); a <= ADDR(g_profileMechBooster); a += 4)
		GAME_VAR(int, a) = 0;
	g_profileMechItem2 = 0;
	g_profileMechItem3 = 2;
	g_profileMechItem4 = 8;
	g_profileMechItem1 = 0x11;
	for (u32 *t = (u32 *)(OBJ(g_pilotSave) + 0x31c); t < (u32 *)(OBJ(g_pilotSave) + 0x3ac); t += 3) {
		t[0] = 0x432a0000;   /* 170 */
		t[1] = 0x3ecccccd;   /* 0.4 */
		t[2] = 0;
	}
}

/* 0x446590: a new campaign for the chosen pilot: axisuser.dat written (no file: nothing more), the profile's record
   gathered (mech_storeToProfile), then a new record made and the pilot's file written with it. Returns the last chdir's
   eax */
int (profile_newCampaign)(void)
{
	void *f = profiles_create();
	if (!f)
		return 0;
	set_current_name();
	profiles_write(f);
	mech_storeToProfile();
	enter_save_folder();
	char path[0x80];
	pilot_path(path);
	campaign_new();
	f = crt_fopen(path, (const char *)STR(0x4b2ab0, "wb"));
	if (f)
		pilot_write(f);
	fclose(f);
	return crt_chdir((const char *)STR(0x4b2a80, ".."));
}

/* 1 when the pilot's file is there and signed */
static int campaign_signed(const char *path)
{
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		return 0;
	crt_fseek(f, 20000, 0);
	u8 head[0x80];
	crt_fread(head, 0x80, 1, f);
	crypt_record80(head, 0x7e);
	int ok = str_order((const char *)head, (const char *)STR(0x4b0fa0, "AXIS USER PROFILE DATA Master ver 1.0...")) == 0;
	fclose(f);
	return ok;
}

/* 0x446a10: the chosen pilot made current: axisuser.dat written (no file: nothing more); the pilot's file read
   into g_pilotSave (its name from the list at +0x80) when it is there and signed, else a new record made and written;
   then the mech read, g_progressWentUp / g_skirmishNewPartsNotice cleared, g_progressSeen = the progress. Returns mech_loadFromProfile's eax */
u32 (profile_makeCurrent)(void)
{
	set_current_name();
	void *f = profiles_create();
	if (!f)
		return 0;
	set_current_name();
	profiles_write(f);
	enter_save_folder();
	char path[0x80];
	pilot_path(path);
	if (campaign_signed(path)) {
		f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
		if (f) {
			crt_fseek(f, 20000, 0);
			u8 record[0x3ac];
			crt_fread(record, sizeof record, 1, f);
			save_cryptRecord(record, 0x7e);
			memcpy(g_pilotSave, record, sizeof record);
			memcpy((void *)(OBJ(g_pilotSave) + 0x80), pilot_name(g_pilot), 0x80);
		}
	} else {
		campaign_new();
		f = crt_fopen(path, (const char *)STR(0x4b2ab0, "wb"));
		if (f)
			pilot_write(f);
	}
	fclose(f);
	crt_chdir((const char *)STR(0x4b2a80, ".."));
	u32 r = mech_loadFromProfile();
	g_progressWentUp = 0;
	g_skirmishNewPartsNotice = 0;
	g_progressSeen = g_progress;
	return r;
}

/* 0x4474a0: axisuser.dat's header read back (the magic word, the count, the current profile, g_profileListTop, g_profileListRow and
   the last pilot's name g_profileName; no file or a wrong magic word: no profiles), the save folder made if it cannot be
   entered ("save " then "save"), and the current profile set to the one with that name, if any. Returns fclose's
   eax (0 without the file) */
u32 (profile_readHeader)(void)
{
	char path[0x184];
	profiles_path(path);
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f) {
		g_profileCount = 0;
		return 0;
	}
	u32 magic;
	crt_fread(&magic, 4, 1, f);
	if (magic != 0xfefefef7) {
		u32 r = fclose(f);
		g_profileCount = 0;
		return r;
	}
	crt_fread((void *)ADDR(g_profileCount), 4, 1, f);
	crt_fread((void *)ADDR(g_currentProfile), 4, 1, f);
	crt_fread((void *)ADDR(g_profileListTop), 4, 1, f);
	crt_fread((void *)ADDR(g_profileListRow), 4, 1, f);
	crt_fread((void *)OBJ(g_profileName), 0x20, 1, f);
	if (crt_chdir((const char *)STR(0x4b2b04, "save "))) {
		crt_mkdir((const char *)STR(0x4b2adc, "save"));   /* mkdir("save") */
		crt_chdir((const char *)STR(0x4b2adc, "save"));
	}
	crt_chdir((const char *)STR(0x4b2a80, ".."));
	for (int i = 0; i < g_profileCount; i++)
		if (str_order((const char *)(OBJ(g_profileNames) + i * 0x48), g_profileName) == 0) {
			g_currentProfile = i;
			break;
		}
	return fclose(f);
}

/* 0x42ba40: skirmish.dat read: at least 10000 bytes and starting with "AXIS SKIRMISH INFOMATION DATA FILE" (0x80
   bytes), else the game ends with "Skirmish Data File Not Found"; from 25000 on the count (g_skirmishInfoCount) and that many
   0x5c-byte entries into g_skirmishInfo. Returns fclose's eax */
u32 (data_loadSkirmishInfo)(void)
{
	void *f = data_open(OBJ(g_dataDir), STR(0x4b1554, "skirmish.dat"), STR(0x4ad170, "rb"), STR(0x4b1534, "Skirmish Data File Not Found"));
	crt_fseek(f, 0, 2);
	if (((int)crt_ftell(f)) < 10000) {   /* ftell */
		fclose(f);
		data_missing(STR(0x4b1534, "Skirmish Data File Not Found"));
	}
	crt_fseek(f, 0, 0);
	char header[0x80];
	crt_fread(header, 0x80, 1, f);
	if (str_order(header, (const char *)STR(0x4b1510, "AXIS SKIRMISH INFOMATION DATA FILE"))) {
		fclose(f);
		data_missing(STR(0x4b1534, "Skirmish Data File Not Found"));
	}
	crt_fseek(f, 25000, 1);
	crt_fread((void *)ADDR(g_skirmishInfoCount), 4, 1, f);
	for (int i = 0; i < g_skirmishInfoCount; i++)
		crt_fread((void *)(OBJ(g_skirmishInfo) + i * 0x5c), 0x5c, 1, f);
	return fclose(f);
}

/* 0x42b590: the pilots read from profkor.dat or profeng.dat (by the language g_language; in the data folder): at least
   10000 bytes starting with "AXIS CHARACTER PROFILE DATA FILE" (0x80 bytes), else the game ends ("... Not Found");
   0x1046a bytes on the record count and a version word (0x115c + 0x67, else the game ends: "wrong version", the file
   left open), then the 0x4c-byte records, each decoded with its own key ('a', 'b', ...) into g_characterProfiles. Then the 0x67
   records' stats are checked: eight above 30 and one (+0x44) above 50 become 0. The callers ignore the eax it leaves */
void (data_loadCharacterProfiles)(void)
{
	void *f = data_open(OBJ(g_dataDir), g_language == 1 ? STR(0x4b14b4, "profkor.dat") : STR(0x4b14a8, "profeng.dat"), STR(0x4ad170, "rb"),
	                    STR(0x4b1480, "Character Profile Data File Not Found"));
	crt_fseek(f, 0, 2);
	if (((int)crt_ftell(f)) < 10000) {   /* ftell */
		fclose(f);
		data_missing(STR(0x4b1480, "Character Profile Data File Not Found"));
	}
	crt_fseek(f, 0, 0);
	char header[0x80];
	crt_fread(header, 0x80, 1, f);
	if (strcmp(header, (const char *)STR(0x4b145c, "AXIS CHARACTER PROFILE DATA FILE"))) {
		fclose(f);
		data_missing(STR(0x4b1480, "Character Profile Data File Not Found"));
	}
	crt_fseek(f, 0x1046a, 1);
	int count, version;
	crt_fread(&count, 4, 1, f);
	crt_fread(&version, 4, 1, f);
	version -= 0x115c;
	if (version != 0x67)
		data_missing(STR(0x4b143c, "Character Profile wrong version"));
	u8 key = 'a';
	for (int i = 0; i < count; i++) {
		u8 record[0x4c];
		crt_fread(record, 0x4c, 1, f);
		crypt_countingKey(record, key++);
		memcpy(&((CharacterProfile *)g_characterProfiles)[i], record, 0x4c);
	}
	fclose(f);
	for (int i = 0; i < version; i++) {
		int *stats = ((CharacterProfile *)g_characterProfiles)[i].stats;
		static const u8 limited[8] = { 0, 2, 3, 1, 5, 4, 6, 8 };   /* (the original's order) */
		for (int k = 0; k < 8; k++)
			if (stats[limited[k]] > 30)
				stats[limited[k]] = 0;
		if (stats[7] > 50)
			stats[7] = 0;
	}
}

/* 0x42b830: mapinfo.dat read (from the maps' folder g_mapInfoDir): its header must start with "AXIS MAP INFOMATION DATA
   FILE" and have 0x1a at +0x32, else the game ends with "Map Infomation Data File Not Found"; then the map count
   (g_mapCount) and for each map its 32-byte name (g_mapNames) and 0x50-byte description (g_mapAbouts), both decoded
   (str_invert), and the names' trailing spaces cut. Returns 0, or the count when there are none */
u32 (data_loadMapInfo)(void)
{
	void *f = data_open(OBJ(g_mapInfoDir), STR(0x4b1504, "mapinfo.dat"), STR(0x4ad170, "rb"), STR(0x4b14e0, "Map Infomation Data File Not Found"));
	u8 header[0x80];
	crt_fread(header, 0x80, 1, f);
	if (str_order((const char *)header, (const char *)STR(0x4b14c0, "AXIS MAP INFOMATION DATA FILE"))) {   /* (the original compares a 0x30-byte copy) */
		fclose(f);
		data_missing(STR(0x4b14e0, "Map Infomation Data File Not Found"));
	}
	if (header[0x32] != 0x1a) {
		fclose(f);
		data_missing(STR(0x4b14e0, "Map Infomation Data File Not Found"));
	}
	crt_fread((void *)ADDR(g_mapCount), 4, 1, f);
	for (int i = 0; i < g_mapCount; i++) {
		char *name = (char *)(OBJ(g_mapNames) + i * 0x20), *about = (char *)(OBJ(g_mapAbouts) + i * 0x50);
		crt_fread(name, 0x20, 1, f);
		str_invert(name);    /* str_invert: decoded */
		crt_fread(about, 0x50, 1, f);
		str_invert(about);
	}
	fclose(f);
	int count = g_mapCount;
	if (count <= 0)
		return count;
	for (int i = 0; i < count; i++) {
		char *name = (char *)(OBJ(g_mapNames) + i * 0x20);
		for (int n = strlen(name); n > 0 && name[n - 1] == ' '; n--)
			name[n - 1] = '\0';
	}
	return 0;
}

/* 0x40d4e0: an arena's settings file read (text, "rt"): each line (but // comments) split at spaces and tabs, a
   keyword taking the next word as its value: gamename (into g_arenaGameName, 32 bytes), secret (g_arenaFileSecret), password
   (g_arenaFilePassword, 8 bytes), gametype (g_arenaFileGameType), maxplayer (g_arenaFilePlayers), map (g_arenaFileMap), fraglimit (g_arenaFileFragLimit), timelimit
   (g_arenaFileTimeLimit; the original then reads on from the keyword, not the value). Each test sees the word the one before
   left. Returns 1, or 0 when the file does not open */
int (arena_loadSettings)(const char *path)
{
	void *f = crt_fopen(path, (const char *)STR(0x4ad5e0, "rt"));
	if (!f)
		return 0;
	static const struct { u32 key, into; } numbers[4] = {
		{ STR(0x4ad5b0, "gametype"), ADDR(g_arenaFileGameType) }, { STR(0x4ad5a4, "maxplayer"), ADDR(g_arenaFilePlayers) }, { STR(0x4ad5a0, "map"), ADDR(g_arenaFileMap) }, { STR(0x4ad594, "fraglimit"), ADDR(g_arenaFileFragLimit) },
	};
	const char *gaps = (const char *)STR(0x4ad5dc, " \t");
	for (;;) {
		char line[0x50];
		memset(line, 0, sizeof line);
		if (!crt_fgets(line, 0x50, f))
			break;
		if (line[0] == '/' && line[1] == '/')
			continue;
		char *word = crt_strtok(line, gaps);
		while (word) {
			if (!strcmp(word, (const char *)STR(0x4ad5d0, "gamename"))) {   /* gamename */
				word = crt_strtok(NULL, gaps);
				memset((void *)OBJ(g_arenaGameName), 0, 0x20);
				strcpy(g_arenaGameName, word);
			}
			if (!strcmp(word, (const char *)STR(0x4ad5c8, "secret"))) {   /* secret */
				word = crt_strtok(NULL, gaps);
				g_arenaFileSecret = crt_atoi(word);
			}
			if (!strcmp(word, (const char *)STR(0x4ad5bc, "password"))) {   /* password */
				word = crt_strtok(NULL, gaps);
				g_arenaFilePassword = 0;
				g_arenaFilePassword4 = 0;
				strcpy((char *)ADDR(g_arenaFilePassword), word);
			}
			for (int k = 0; k < 4; k++)
				if (!strcmp(word, (const char *)numbers[k].key)) {
					word = crt_strtok(NULL, gaps);
					GAME_VAR(int, numbers[k].into) = crt_atoi(word);
				}
			if (!strcmp(word, (const char *)STR(0x4ad588, "timelimit")))   /* timelimit */
				g_arenaFileTimeLimit = crt_atoi(crt_strtok(NULL, gaps));
			word = crt_strtok(NULL, gaps);
		}
	}
	fclose(f);
	return 1;
}

/* ---- axis.cfg read back: each line cut at its last character (its newline), its keyword and the next word
   skipped and the rest joined into value (0x84 bytes; spaced: a space after each word) ---- */
static void read_value(void *f, char *value, int spaced)
{
	const char *gaps = (const char *)STR(0x4ad5dc, " \t");
	char line[0x50];
	crt_fgets(line, 0x50, f);
	line[strlen(line) - 1] = '\0';
	crt_strtok(line, gaps);
	crt_strtok(NULL, gaps);
	memset(value, 0, 0x84);
	for (char *word; (word = crt_strtok(NULL, gaps)) != NULL;) {
		strcat(value, word);
		if (spaced)
			strcat(value, (const char *)STR(0x4b035c, " "));
	}
}

/* a line read past */
static void skip_line(void *f)
{
	char line[0x50];
	crt_fgets(line, 0x50, f);
}

/* 0x42d7f0: the player's section read back (the lines cfg_writePlayer writes): the name (its words joined by
   spaces, then cut once more by str_dropLast, into g_cfgPlayerName), the corporation (RED 0, BLUE 1, YELLOW 2, else 0;
   g_playerCorporation) and the customize switch (ON: 1; g_playerCustomize); then one more line. The original leaves fgets's eax to callers that
   ignore it */
void (cfg_readPlayer)(void *f)
{
	char value[0x84];
	read_value(f, value, 1);
	str_dropLast(value);
	strcpy(g_cfgPlayerName, value);
	read_value(f, value, 0);
	if (!strcmp(value, (const char *)STR(0x4b21b8, "RED")))        /* RED */
		g_playerCorporation = 0;
	else if (!strcmp(value, (const char *)STR(0x4b21b0, "BLUE")))   /* BLUE */
		g_playerCorporation = 1;
	else
		g_playerCorporation = strcmp(value, (const char *)STR(0x4b21a8, "YELLOW")) ? 0 : 2;   /* YELLOW */
	read_value(f, value, 0);
	g_playerCustomize = !strcmp(value, (const char *)STR(0x4b21bc, "ON"));   /* ON */
	skip_line(f);
}

/* 0x42e080: the sound section read back: the two volumes (g_soundVolume, g_musicVolume) and two switches (ON: 1; 3D sound,
   stereo reverse),
   then one more line. The original leaves fgets's eax to callers that ignore it */
void (cfg_readSound)(void *f)
{
	char value[0x84];
	read_value(f, value, 0);
	g_soundVolume = crt_atoi(value);
	read_value(f, value, 0);
	g_musicVolume = crt_atoi(value);
	read_value(f, value, 0);
	g_sound3D = !strcmp(value, (const char *)STR(0x4b21bc, "ON"));   /* ON */
	read_value(f, value, 0);
	g_stereoReverse = !strcmp(value, (const char *)STR(0x4b21bc, "ON"));
	skip_line(f);
}

/* ---- the server, graphics and key binding sections: their buffers laid out as the originals' are, the line
   straight after the joined value, kept across the lines. At the file's end fgets leaves the last line as it was,
   cut once more; cutting an empty one writes the byte before it, the value's last (cleared next anyway). A few bytes
   lie before the value for str_dropLast's cut of an empty value (in the original the top byte of the caller's saved
   ebx, which is not reproduced) ---- */
typedef struct { char before[4]; char value[0x84]; char line[0x78]; } CfgBuf;

static void read_into(void *f, CfgBuf *b, int spaced)
{
	const char *gaps = (const char *)STR(0x4ad5dc, " \t");
	crt_fgets(b->line, 0x50, f);
	char *end = b->line + strlen(b->line) - 1;
	*end = '\0';
	crt_strtok(b->line, gaps);
	crt_strtok(NULL, gaps);
	memset(b->value, 0, 0x84);
	for (char *word; (word = crt_strtok(NULL, gaps)) != NULL;) {
		strcat(b->value, word);
		if (spaced)
			strcat(b->value, (const char *)STR(0x4b035c, " "));
	}
}

/* the value's position among count strings (1 ..), 0 when none */
static int named(const char *value, const u32 *names, int count)
{
	for (int k = 0; k < count; k++)
		if (!strcmp(value, (const char *)RELOC(names[k])))
			return k + 1;
	return 0;
}

#define IS_ON(value) (!strcmp((value), (const char *)STR(0x4b21bc, "ON")))

/* 0x42da70: the server section read back: the server's name (words joined by spaces, cut once more; g_arenaName),
   the map (0 .. 21, else 0; g_arenaMap), the players (0 .. 16, else 8; g_arenaMaxPlayers), a switch (ON; g_arenaRotation), the game
   type (TEAM DEATH MATCH 1 .. ACCEPT ADVANCED MODE 14, else 0; g_arenaGameType), two limits (above 250: 30; g_arenaFragLimit /
   g_arenaTimeLimit); then one more line */
void (cfg_readServer)(void *f)
{
	static const u32 types[14] = { STR(0x4b22b8, "TEAM DEATH MATCH"), STR(0x4b22a8, "SUDDEN DEATH"), STR(0x4b2294, "TEAM SUDDEN DEATH"), STR(0x4b2284, "SHOTGUN ARENA"), STR(0x4b2270, "TEAM SHOTGUN ARENA"), STR(0x4b2260, "IONCANNON ARENA"), STR(0x4b2248, "TEAM IONCANNON ARENA"), STR(0x4b2238, "ROCKET ARENA"),
	                               STR(0x4b2224, "TEAM ROCKET ARENA"), STR(0x4b2214, "GLADIATOR ARENA"), STR(0x4b21fc, "TEAM GLADIATOR ARENA"), STR(0x4b21e8, "KING ON THE HILL"), STR(0x4b21d8, "PLATOON MODE"), STR(0x4b21c0, "ACCEPT ADVANCED MODE") };
	CfgBuf b;
	__asm__("" : "=m"(b));   /* (left as the stack holds it) */
	for (int n = 0; n < 7; n++) {
		read_into(f, &b, n == 0 || n == 4);
		signed char v;
		switch (n) {
		case 0:
			str_dropLast(b.value);
			strcpy(g_arenaName, b.value);
			break;
		case 1:
			v = (signed char)crt_atoi(b.value);
			g_arenaMap = v < 0 || v > 0x15 ? 0 : v;
			break;
		case 2:
			v = (signed char)crt_atoi(b.value);
			(*(signed char *)&g_arenaMaxPlayers) = v < 0 || v > 0x10 ? 8 : v;
			break;
		case 3:
			g_arenaRotation = IS_ON(b.value);
			break;
		case 4:
			str_dropLast(b.value);
			g_arenaGameType = (u8)named(b.value, types, 14);
			break;
		default: {
			u8 limit = (u8)crt_atoi(b.value);
			(*(u8 *)&g_arenaName[0x24 + (n - 5)]) = limit > 250 ? 30 : limit;
			break;
		}
		}
	}
	crt_fgets(b.line, 0x50, f);
}

/* 0x42e240: the graphics section read back: the screen size (1280x720 1, 1600x900 2, 1920x1080 3, 2560x1440 4,
   3840x2160 5, 1024x768 6, DESKTOP 7, else 0; g_videoMode), 32 bits (g_videoDepth), HIGH (0x83a9c8) and four switches (ON;
   0x83a9cc .. 0x83a9d8); then one more line */
void (cfg_readGraphics)(void *f)
{
	static const u32 sizes[7] = { STR(0x4ac858, "1280x720"), STR(0x4ac87c, "1600x900"), STR(0x4ac8a0, "1920x1080"), STR(0x4ac8c4, "2560x1440"), STR(0x4ac8e8, "3840x2160"), STR(0x4ac90c, "1024x768"), STR(0x4ac92c, "DESKTOP") };
	CfgBuf b;
	__asm__("" : "=m"(b));
	for (int n = 0; n < 7; n++) {
		read_into(f, &b, 0);
		if (n == 0)
			(*(int *)&g_videoMode) = named(b.value, sizes, 7);
		else if (n == 1)
			g_videoDepth = !strcmp(b.value, (const char *)STR(0x4b22d4, "32"));
		else if (n == 2)
			g_highDetail = !strcmp(b.value, (const char *)STR(0x4b22cc, "HIGH"));
		else
			g_cfgSwitches[n - 3] = IS_ON(b.value);
	}
	crt_fgets(b.line, 0x50, f);
}

/* the binding a key line is read into: the lines run in the menu's order (cfg_writeKeyBindings' table), and the last
   line (help, second key) goes to the binding before it, 62, so binding 63 is never read back */
static int read_binding(int line)
{
	if (line >= 26 && line <= 33)
		return line + 4;
	if (line >= 34 && line <= 37)
		return line - 8;
	return line == 63 ? 62 : line;
}

/* 0x42e730: the key bindings read back: 64 lines of key names (each looked up among the 256 at g_keyNames, the last
   match kept; none leaves the binding as it was) into the bindings (g_keyForward), then the mouse: convert and smooth
   (ON; g_mouseInvert, g_mouseSmooth), the sensitivity and the crosshairs (g_mouseSensitivity, g_crosshairSetting); then one more line */
void (cfg_readKeyBindings)(void *f)
{
	const char *const *key_name = (const char *const *)OBJ(g_keyNames);
	CfgBuf b;
	__asm__("" : "=m"(b));
	for (int n = 0; n < 0x44; n++) {
		read_into(f, &b, 0);
		if (n == 0x40 || n == 0x41)
			GAME_VAR(int, OBJ(g_mouseSettings) + (n - 0x40) * 4) = IS_ON(b.value);   /* g_mouseSettings[n - 0x40] */
		else if (n == 0x42 || n == 0x43)
			GAME_VAR(int, OBJ(g_mouseSettings) + 8 + (n - 0x42) * 4) = crt_atoi(b.value);   /* g_mouseSettings[2 + n - 0x42]: sensitivity, crosshair */
		else
			for (int k = 0; k < 256; k++)
				if (!strcmp(b.value, key_name[k]))
					g_controls[read_binding(n)] = k;
	}
	crt_fgets(b.line, 0x50, f);
}
#undef IS_ON

/* 0x42eca0: axis.cfg read from the data folder (g_dataDir) when its first line is the
   header (0x4b0f50): the player, server, sound, graphics and key binding sections. Without the file or with another
   header, the defaults (the player PLAYER, the server AXIS ARENA with 8 players, sound at 100 / 100, the switches and
   graphics settings) and the default key bindings, then axis.cfg written with them. The player's name and the
   server's (32 bytes each) are cleared first either way.
   The line is cut at its last character; with an empty file fgets leaves the buffer as it was, and the cut lands
   wherever the old bytes end: the original's buffer is followed by the path, so this one is too. (A first line
   starting with a NUL byte makes the original clear the top byte of its caller's saved ebx, which is not
   reproduced) */
void (cfg_init)(void)
{
	struct { char line[0x84]; char path[0x184]; } s;
	strcpy(s.path, g_dataDir);
	strcat(s.path, (const char *)STR(0x4b2198, "\\axis.cfg"));
	memset((void *)OBJ(g_cfgPlayerName), 0, 32);
	memset((void *)OBJ(g_arenaName), 0, 32);
	void *f = crt_fopen(s.path, (const char *)STR(0x4ad5e0, "rt"));
	if (f) {
		__asm__("" : "=m"(s.line));   /* (left as the stack holds it until fgets writes it) */
		crt_fgets(s.line, 0x50, f);
		size_t length = strlen((const char *)&s);
		if (length)
			((char *)&s)[length - 1] = '\0';
		if (!strcmp(s.line, (const char *)STR(0x4b0f50, "AXIS CONFIGURATION FILE Master ver 1...."))) {
			cfg_readPlayer(f);
			cfg_readServer(f);
			cfg_readSound(f);
			cfg_readGraphics(f);
			cfg_readKeyBindings(f);
			fclose(f);
			return;
		}
		fclose(f);
	}
	g_stereoReverse = 0;
	g_videoDepth = 0;
	(*(int *)&g_videoMode) = 0;
	g_showFps = 0;
	g_cfgSimpleMenu = 0;
	strcpy(g_cfgPlayerName, (const char *)STR(0x4ad4b0, "PLAYER"));
	g_playerCorporation = 0;
	g_playerCustomize = 0;
	strcpy(g_arenaName, (const char *)STR(0x4ad4a4, "AXIS ARENA"));
	g_soundVolume = 100;
	g_musicVolume = 100;
	static const u8 server[6] = { 0, 8, 0, 0, 0, 0 };   /* 0x4ded40 (g_arenaMap ..): map 0, 8 players (numofplayer), the rest 0 */
	memcpy((void *)ADDR(g_arenaMap), server, 6);
	g_sound3D = 1;
	g_highDetail = 1;
	(*(int *)&g_cfgMipmaps) = 1;
	(*(int *)&g_cfgLinearFilter) = 1;
	input_setDefaultBindings();
	cfg_writeAxisCfg();
}

/* 0x4460d0: the pilot profiles found in the save folder ("save"; when it cannot be entered: "axisuser.dat" deleted
   from the data folder g_dataDir, back up, nothing more; the folder is NOT made here): each *.axs file's name
   (g_saveFileNames, 0x40 apart) and its header (0x104 bytes at 20000, unscrambled, into g_profileHeader); one with
   the right header (0x4b0fa0) becomes the next profile (0x48 bytes from g_profiles: its number, its name less ".axs"
   and its pilot, the header's last word), any other file is deleted. No *.axs at all: back up and axisuser.dat
   rewritten empty (profile_writeCleared(0)). Then back up, profile_readHeader, axisuser.dat rewritten with the valid
   count (profile_writeCleared) and the profile named g_profileName (among as many as there were files) chosen into
   g_currentProfile. The original leaves eax to callers that ignore it */
void (profile_scanSaves)(void)
{
	if (crt_chdir((const char *)STR(0x4b2adc, "save"))) {
		crt_chdir(g_dataDir);
		DeleteFileA((const char *)STR(0x4b2acc, "axisuser.dat"));   /* DeleteFileA("axisuser.dat") */
		crt_chdir((const char *)STR(0x4b2a80, ".."));
		return;
	}
	struct { u32 attrib, created, accessed, written, size; char name[260]; } found;   /* _finddata_t */
	int search = crt_findfirst((const char *)STR(0x4b2ac4, "*.axs"), &found);   /* "*.axs" */
	if (search < 0) {
		crt_chdir((const char *)STR(0x4b2a80, ".."));
		profile_writeCleared(0);
		return;
	}
	char (*files)[0x40] = (char (*)[0x40])OBJ(g_saveFileNames);
	strcpy(files[0], found.name);
	int count = 1;
	while (!crt_findnext(search, &found))
		strcpy(files[count++], found.name);
	crt_findclose(search);
	int valid = 0;
	for (int i = 0; i < count; i++) {
		u8 header[0x104];
		void *f = crt_fopen(files[i], (const char *)STR(0x4ad170, "rb"));
		crt_fseek(f, 20000, 0);
		crt_fread(header, 0x104, 1, f);
		fclose(f);
		crypt_record104(header, 0x7e);
		memcpy((void *)OBJ(g_profileHeader), header, 0x104);
		char name[32] = { 0 };
		memcpy(name, files[i], strlen(files[i]) - 4);
		if (strcmp((const char *)OBJ(g_profileHeader), (const char *)STR(0x4b0fa0, "AXIS USER PROFILE DATA Master ver 1.0..."))) {
			DeleteFileA(files[i]);   /* DeleteFileA */
			continue;
		}
		u8 *profile = g_profiles + valid * 0x48;
		strcpy((char *)profile + 4, name);
		*(u32 *)(profile + 0x44) = *(const u32 *)(header + 0x100);   /* the pilot */
		*(int *)profile = valid++;
	}
	crt_chdir((const char *)STR(0x4b2a80, ".."));
	profile_readHeader();
	profile_writeCleared(valid);
	for (int i = 0; i < count; i++)
		if (!strcmp(g_profileNames + i * 0x48, g_profileName)) {
			g_currentProfile = i;
			return;
		}
}

/* 0x473780 (thiscall on the stage): the component catalogue from path (a failed open or a version
   other than 0x1204 is a fatal message): six tables, each logged, its count then its records read unscrambled (heads,
   chests, arms, legs, boosters, items: headTypes .. actorItems). Returns 1 */
u32 THISCALL (catalogue_loadComponents)(u8 *stage, const char *path)
{
	static const u32 tables[6][4] = {   /* log message, count, records, record size */
		{ STR(0x4c755c, "read ActorHeadInfo"), offsetof(Stage, headTypeCount), offsetof(Stage, headTypes), sizeof(HeadType) }, { STR(0x4c7548, "read ActorChestInfo"), offsetof(Stage, chestTypeCount), offsetof(Stage, chestTypes), sizeof(ChestType) },
		{ STR(0x4c7534, "read ActorArmInfo"), offsetof(Stage, armTypeCount), offsetof(Stage, armTypes), sizeof(ArmType) }, { STR(0x4c7520, "read ActorLegInfo"), offsetof(Stage, legTypeCount), offsetof(Stage, legTypes), sizeof(LegType) },
		{ STR(0x4c7508, "read ActorBoosterInfo"), offsetof(Stage, boosterTypeCount), offsetof(Stage, boosterTypes), sizeof(BoosterType) }, { STR(0x4c74f4, "read ActorItemInfo"), offsetof(Stage, actorItemCount), offsetof(Stage, actorItems), sizeof(ActorItem) } };
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c75bc, "can't open file %s - loadActorCompone..."), (int)path);
	int version;
	crt_fread(&version, 4, 1, f);   /* fread */
	if (version != 0x1204)
		sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c7570, "incorrect file version, remove the fi..."), (int)path);
	for (int k = 0; k < 6; k++) {
		log_message((int)stage, 0, 0, (const char *)RELOC(tables[k][0]));
		fread_scrambled(stage + tables[k][1], 4, 1, f);
		fread_scrambled(stage + tables[k][2], tables[k][3], FIELD(u32, stage, tables[k][1]), f);
	}
	fclose(f);
	return 1;
}

/* 0x487cb0 (thiscall on the scene): a recording started (one going is stopped first: replay_closeRecording): the file
   AutoPlay\name.ape, or without a name the first of AutoPlay000 .. AutoPlay999 not there yet (the name kept at
   recordName; none free, or the file not made: nothing more). Recording (recording 1, the clock recordTime 0), the
   header written: version 0x1201, the settings (g_matchMode, g_mapIndex, the 32 bytes at g_gameTitle, g_mapRotation), the map
   (gameMode), g_fragLimit and g_timeLimit. Every player in use (net_playerInUse) is flagged to be sent (sendFlags[][2],
   sendFlags[][3]), the shown one (localPlayer) too (sendFlags[][1], sendFlags, its playerRecords[].flagSent cleared). Its caller ignores
   the eax it leaves */
void THISCALL (replay_startRecording)(u8 *s, const char *name)
{
	Scene *sc = (Scene *)s;
	char *kept = sc->recordName, path[0x100];
	if (sc->recording == 1)
		replay_closeRecording(sc);
	if (name) {
		strcpy(kept, name);
		sprintf(path, (const char *)STR(0x4c7cc8, "AutoPlay\\%s.ape"), kept);
	} else {
		int i = 0;
		for (;; i++) {
			sprintf(kept, (const char *)STR(0x4c7cb8, "AutoPlay%03d"), i);
			sprintf(path, (const char *)STR(0x4c7cc8, "AutoPlay\\%s.ape"), kept);
			if (!file_existsf(path))
				break;
			if (i == 999)
				return;
		}
	}
	void *f = sc->replayFile = crt_fopen(path, (const char *)STR(0x4b2ab0, "wb"));
	if (!f)
		return;
	sc->recording = 1;
	(*(int *)&sc->recordTime) = 0;
	int value = 0x1201;
	file_writeScrambled(&value, 4, 1, sc->replayFile);
	file_writeScrambled((void *)ADDR(g_matchMode), 4, 1, sc->replayFile);
	file_writeScrambled((void *)ADDR(g_mapIndex), 4, 1, sc->replayFile);
	file_writeScrambled((void *)OBJ(g_gameTitle), 1, 0x20, sc->replayFile);
	file_writeScrambled((void *)ADDR(g_mapRotation), 4, 1, sc->replayFile);
	value = sc->gameMode;
	file_writeScrambled(&value, 4, 1, sc->replayFile);
	file_writeScrambled((void *)ADDR(g_fragLimit), 4, 1, sc->replayFile);
	file_writeScrambled((void *)ADDR(g_timeLimit), 4, 1, sc->replayFile);
	for (int i = 0; i < 16; i++)
		if (net_playerInUse(i) == 1) {
			sc->sendFlags[i][2] = 1;
			sc->sendFlags[i][3] = 1;
		}
	sc->sendFlags[sc->localPlayer][1] = 1;
	sc->playerRecords[sc->localPlayer].flagSent = 0;
	sc->sendFlags[sc->localPlayer][0] = 1;
}

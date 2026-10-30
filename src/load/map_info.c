/* map_info.c: sections of a map's mission file read: a count and that many records, each record linked to its run
   in a shared table (the runs follow each other; the total must match the table's own count, else a fatal message). */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))
#define fatal4(format, a, b) GAME_CDECL(0x46c710, void, char *, const char *, int, int)((char *)0xae2eb8, (const char *)(format), a, b)

/* 0x48b4a0 (thiscall on the scene): the way points: their count (+0xe3b034) and 0x14-byte records (+0xe36214), each
   given its run of 0x30-byte points (+0x10: from +0xdc0f10; +0xc: its length); the points' total against +0xe36210.
   Its caller ignores the eax it leaves */
void THISCALL (map_loadWayPointInfoFrom)(u8 *scene, void *f)
{
	int *count = (int *)(scene + 0xe3b034);
	fread_scrambled(count, 4, 1, f);
	fread_scrambled(scene + 0xe36214, 0x14, *count, f);
	int total = 0;
	for (int i = 0; i < *count; i++) {
		u8 *r = scene + 0xe36214 + i * 0x14;
		FIELD(u8 *, r, 0x10) = scene + 0xdc0f10 + total * 0x30;
		total += FIELD(int, r, 0xc);
	}
	if (total != FIELD(int, scene, 0xe36210))
		fatal4(0x4c7d24, total, FIELD(int, scene, 0xe36210));
}

/* 0x48b530: the triggers: their count (+0xe3c938) and 0x1c-byte records (+0xe3b038), each given its run of way points
   (+4: from +0xe36214, 0x14 bytes each; +0: its length) and its radius squared, scaled (+0x14 x itself x 0x4a9708);
   the total against the way points' count (+0xe3b034) */
void THISCALL (map_loadTriggerInfoFrom)(u8 *scene, void *f)
{
	int *count = (int *)(scene + 0xe3c938);
	fread_scrambled(count, 4, 1, f);
	fread_scrambled(scene + 0xe3b038, 0x1c, *count, f);
	int total = 0;
	for (int i = 0; i < *count; i++) {
		u8 *r = scene + 0xe3b038 + i * 0x1c;
		long double radius = FIELD(float, r, 0x14);
		FIELD(u8 *, r, 4) = scene + 0xe36214 + total * 0x14;
		total += FIELD(int, r, 0);
		FIELD(float, r, 0x14) = (float)(radius * radius * GAME_VAR(float, 0x4a9708));
	}
	if (total != FIELD(int, scene, 0xe3b034))
		fatal4(0x4c7d74, total, FIELD(int, scene, 0xe3b034));
}

/* 0x4875d0 (thiscall on the scene): the item file: its version (0x1201, else a fatal message; no file one too), the
   items' count (+0x20f3adc) and 0x90-byte records (+0x20f3ae0); each item named (its first byte set) given its shape
   (+0x8c: shape_getByName on the scene's shapes, +0x19e188c, by its name at +0x4c), the others none. Returns 1 */
int THISCALL (map_loadItemInfoFrom)(u8 *scene, const char *path)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		GAME_CDECL(0x46c710, void, char *, const char *, const char *)((char *)0xae2eb8, (const char *)0x4c7bd4, path);
	u32 version;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		GAME_CDECL(0x46c710, void, char *, const char *, const char *)((char *)0xae2eb8, (const char *)0x4c7b94, path);
	int *count = (int *)(scene + 0x20f3adc);
	fread_scrambled(count, 4, 1, f);
	fread_scrambled(scene + 0x20f3ae0, 0x90, *count, f);
	fclose(f);
	for (int i = 0; i < *count; i++) {
		u8 *item = scene + 0x20f3ae0 + i * 0x90;
		FIELD(u32, item, 0x8c) = item[0] ? shape_getByName(scene + 0x19e188c, (const char *)(item + 0x4c), 1) : 0;
	}
	return 1;
#undef crt_fread
}

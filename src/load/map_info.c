/* map_info.c: sections of a map's mission file read: a count and that many records, each record linked to its run
   in a shared table (the runs follow each other; the total must match the table's own count, else a fatal message). */
#include "../game.h"
#include <string.h>

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

/* 0x48b5c0 (thiscall on the scene): the map's mission file (its name from +0x108 and name by 0x4c77f0; none: a fatal
   message): its version (0x1201, else a fatal message), two sections skipped (each a scrambled size, then that many
   bytes), a third size read, then the sections read in turn, each announced to the log first: 0x48b460's, the way
   points and the triggers. Its caller ignores the eax it leaves */
void THISCALL (map_loadMissionInfoFrom)(u8 *scene, const char *name)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	char path[0x100];
	sprintf(path, (const char *)0x4c77f0, scene + 0x108, name);
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7dec, (int)path);
	log_message((int)scene, 0, 0, (const char *)0x4c77b4);
	u32 version, skip;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	for (int k = 0; k < 2; k++) {
		fread_scrambled(&skip, 4, 1, f);
		crt_fseek(f, skip, 1);   /* SEEK_CUR */
	}
	fread_scrambled(&skip, 4, 1, f);
	log_message((int)scene, 0, 0, (const char *)0x4c7ddc);
	load_48b460(scene, f);
	log_message((int)scene, 0, 0, (const char *)0x4c7dcc);
	map_loadWayPointInfoFrom(scene, f);
	log_message((int)scene, 0, 0, (const char *)0x4c7dbc);
	map_loadTriggerInfoFrom(scene, f);
	fclose(f);
#undef crt_fread
}

/* 0x48b710 (thiscall on the scene): the map's objects. The caches emptied (+0xe3c93c shapes, +0x13016d0 skeletons,
   the object list: load_490d10), the shading not loaded (+0x13016cc 0). Mode 0: the shading file (named by 0x4c7e90
   from +0x108 and the name's base, load_46cad0) read when there (a count, +0x13016c8, then that many dwords at
   +0xf30dc8; the count cleared, +0x13016cc 1). The objects file (by 0x4c77f0; none: a fatal message): version
   0x1201 (else a fatal message), a dword, the count, then the 0xb0-byte object types in blocks of 56, each added
   (object_addObjectBy) until one fails; every second one logged. Mode 1 without shading loaded: the shading file
   written. Its caller ignores the eax it leaves */
void THISCALL (map_loadObjectInfoFrom)(u8 *scene, const char *name, int mode)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	char path[0x100], base[0x100];
	u8 objects[56][0xb0];
	FIELD(int, scene, 0x131ae40) = 0;
	ShapeManager_releaseModels(scene + 0xe3c93c);
	SkeletonManager_releaseSkeletons(scene + 0x13016d0);
	load_490d10(scene);
	FIELD(int, scene, 0x13016cc) = 0;
	if (mode == 0) {
		load_46cad0(name, base);
		sprintf(path, (const char *)0x4c7e90, scene + 0x108, base);
		void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
		if (f) {
			log_message((int)scene, 0, 0, (const char *)0x4c7e74);
			fread_scrambled(scene + 0x13016c8, 4, 1, f);
			fread_scrambled(scene + 0xf30dc8, 4, FIELD(u32, scene, 0x13016c8), f);
			fclose(f);
			FIELD(int, scene, 0x13016c8) = 0;
			FIELD(int, scene, 0x13016cc) = 1;
		}
	}
	sprintf(path, (const char *)0x4c77f0, scene + 0x108, name);
	void *f = crt_fopen(path, (const char *)0x4ad170);
	if (!f)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7e48, (int)path);
	log_message((int)scene, 0, 0, (const char *)0x4c77b4);
	int version, value, count;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	fread_scrambled(&value, 4, 1, f);
	fread_scrambled(&count, 4, 1, f);
	for (int i = 0; i < count; i++) {
		if (i % 2 == 0)
			log_message((int)scene, 0, i, (const char *)0x4c7e38, i);
		unsigned k = (unsigned)i % 56;
		if (k == 0)
			fread_scrambled(objects, 0xb0, 56, f);
		if (object_addObjectBy(scene, objects[k]) < 0)
			break;
	}
	fclose(f);
	load_46cad0(name, base);
	sprintf(path, (const char *)0x4c7e90, scene + 0x108, base);
	if (mode == 1 && FIELD(int, scene, 0x13016cc) == 0) {
		f = crt_fopen(path, (const char *)0x4b2ab0);   /* "wb" */
		if (f) {
			log_message((int)scene, 0, 0, (const char *)0x4c7e1c);
			file_writeScrambled(scene + 0x13016c8, 4, 1, f);
			file_writeScrambled(scene + 0xf30dc8, 4, FIELD(u32, scene, 0x13016c8), f);
			fclose(f);
		}
	}
#undef crt_fread
}

/* an item point's kind changed by the game's options (+0x20f3ac0 .. +0x20f3ad0, each on at 1): the kinds 0 .. 9 to 0,
   2, 3, 5 or none (-1); with the first, 10 .. 19 and 0x1e, 0x1f, 0x25 none too; with the third 15 .. 19 to 10 .. 14 */
static void remap_item(u8 *scene, int *kind)
{
	if (FIELD(int, scene, 0x20f3ac0) == 1) {
		if (*kind / 10 == 0)
			*kind = 0;
		else if (*kind / 10 == 1 || *kind == 0x1e || *kind == 0x1f || *kind == 0x25)
			*kind = -1;
	}
	if (FIELD(int, scene, 0x20f3ac4) == 1 && *kind / 10 == 0)
		*kind = 2;
	if (FIELD(int, scene, 0x20f3ac8) == 1) {
		if (*kind / 10 == 0)
			*kind = 3;
		else if (*kind >= 15 && *kind <= 19)
			*kind -= 5;
	}
	if (FIELD(int, scene, 0x20f3acc) == 1 && *kind / 10 == 0)
		*kind = 5;
	if (FIELD(int, scene, 0x20f3ad0) == 1 && *kind / 10 == 0)
		*kind = -1;
}

/* 0x4876b0 (thiscall on the scene): the map's play file (by 0x4c77f0 from +0x108 and name; none: a fatal message):
   version 0x1201 (else a fatal message), the first section skipped (a scrambled size), a dword, then the count and
   the 0x24-byte records (read scrambled 0x71c at a time): kind 0 the player start (+0x20fab60, its two angles x
   0x4a9418 at +0x20fab6c), 1 a multiplayer start (0x14 bytes from +0x20fab74, at most 32: +0x20fadf4), 2 an item
   point (0x28 bytes from +0x20fadf8, at most 200: +0x20fcd38; its kind remapped by the options). The start is the
   default (0xa0e7a8) until then, +0x20fcd3c -1. Its caller ignores the eax it leaves */
void THISCALL (map_loadPlayInfoFrom)(u8 *scene, const char *name)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	const float *scale = (const float *)0x4a9418;
	memcpy(scene + 0x20fab60, (const void *)0xa0e7a8, 12);
	FIELD(int, scene, 0x20fab6c) = 0;
	FIELD(int, scene, 0x20fab70) = 0;
	FIELD(int, scene, 0x20fadf4) = 0;
	FIELD(int, scene, 0x20fcd38) = 0;
	FIELD(int, scene, 0x20fcd3c) = -1;
	char path[0x100];
	sprintf(path, (const char *)0x4c77f0, scene + 0x108, name);
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7c8c, (int)path);
	log_message((int)scene, 0, 0, (const char *)0x4c77b4);
	int version, value, count;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	fread_scrambled(&value, 4, 1, f);
	crt_fseek(f, value, 1);   /* SEEK_CUR */
	fread_scrambled(&value, 4, 1, f);
	log_message((int)scene, 0, 0, (const char *)0x4c7c7c);
	fread_scrambled(&count, 4, 1, f);
	u32 records[0x71c][9];
	for (int i = 0; i < count; i++) {
		unsigned k = (unsigned)i % 0x71c;
		if (k == 0)
			fread_scrambled(records, 0x24, 0x71c, f);
		u32 *r = records[k];
		float *rf = (float *)r;
		if (r[0] == 0) {
			FIELD(float, scene, 0x20fab6c) = f32(fmul_m(fld_m(&rf[7]), scale));
			FIELD(float, scene, 0x20fab70) = f32(fmul_m(fld_m(&rf[8]), scale));
			memcpy(scene + 0x20fab60, &r[4], 12);
		} else if (r[0] == 1) {
			if (FIELD(int, scene, 0x20fadf4) >= 32)
				sys_fatalError((char *)0xae2eb8, (const char *)0x4c7c00, 0x20);
			u8 *start = scene + 0x20fab74 + FIELD(int, scene, 0x20fadf4) * 0x14;
			memcpy(start, &r[4], 12);
			FIELD(float, start, 0xc) = f32(fmul_m(fld_m(&rf[7]), scale));
			FIELD(float, start, 0x10) = f32(fmul_m(fld_m(&rf[8]), scale));
			FIELD(int, scene, 0x20fadf4)++;
		} else if (r[0] == 2) {
			if (FIELD(int, scene, 0x20fcd38) >= 200)
				sys_fatalError((char *)0xae2eb8, (const char *)0x4c7c44, 0x20);
			u8 *item = scene + 0x20fadf8 + FIELD(int, scene, 0x20fcd38) * 0x28;
			FIELD(u32, item, 0) = r[1];
			remap_item(scene, (int *)item);
			FIELD(u32, item, 4) = r[2];
			FIELD(u32, item, 8) = r[3];
			memcpy(item + 0xc, &r[4], 12);
			FIELD(float, item, 0x18) = f32(fmul_m(fld_m(&rf[7]), scale));
			FIELD(float, item, 0x1c) = f32(fmul_m(fld_m(&rf[8]), scale));
			FIELD(int, item, 0x20) = 0;
			FIELD(int, item, 0x24) = 0;
			FIELD(int, scene, 0x20fcd38)++;
		}
	}
	fclose(f);
#undef crt_fread
}

/* the ten colour schemes of the map's players: hue, saturation and value of a part's two colours (as float bits) */
static const u32 k_schemeHue[10][2] = {
	{ 0x43700000, 0x42200000 }, { 0, 0 }, { 0x42b40000, 0x43660000 }, { 0x43820000, 0x42340000 }, { 0x42340000, 0x42340000 },
	{ 0x42c80000, 0x41200000 }, { 0x435c0000, 0x43390000 }, { 0x435c0000, 0x435c0000 }, { 0x43870000, 0x43af0000 }, { 0, 0 } };
static const u32 k_schemeSat[10][2] = {
	{ 0x3f4ccccd, 0x3f4ccccd }, { 0x3f4ccccd, 0x3f4ccccd }, { 0x3f000000, 0x3f000000 }, { 0x3f000000, 0x3f000000 },
	{ 0x3f4ccccd, 0x3f4ccccd }, { 0x3f147ae1, 0x3f19999a }, { 0x3f147ae1, 0x3f19999a }, { 0x3f07ae15, 0x3f4ccccd },
	{ 0x3f4ccccd, 0x3f4ccccd }, { 0, 0 } };
static const u32 k_schemeVal[10][2] = {
	{ 0x3f000000, 0x3f000000 }, { 0x3f000000, 0x3f000000 }, { 0x3f000000, 0x3f000000 }, { 0x3f4ccccd, 0x3f147ae1 },
	{ 0x3e99999a, 0x3e4ccccd }, { 0x3e7fffff, 0x3e7fffff }, { 0x3f000000, 0x3f19999a }, { 0x3e99999a, 0x3f000000 },
	{ 0x3f07ae15, 0x3f4ccccd }, { 0, 0 } };

/* 0x474550 (thiscall on the scene): the map's players and actors (file by 0x4c77f0 from +0x108 and name; none, or a
   version other than 0x1201, a fatal message): three sections skipped, a dword, then the player count (+0x1cd6fb0)
   and their 0x58-byte records (+0x1cd6a30), the actor count (+0x1cd93a4) and their 0x5c-byte records (+0x1cd6fb4).
   Every player but the first: its colour scheme (+4, now less one; when not negative) gives all five parts their
   colours, the game type (2 .. 11, by pairs) fixes its first item (3, 5, 0x24, 0x19, 0x16; the last pair the second
   too, 0x17), the other items but the fifth emptied (-1), and it is set up (load_4742f0). The player count also at
   +0x19e1888, every actor but the first active (+0x18), the clan texture (by 0x4c7724 from +0x908) looked up into
   +0x2104fe4, and each player's type record given +0x47fc6 1 and +0x47fce 0x180. Its caller ignores the eax it
   leaves */
void THISCALL (map_loadActorInfoFrom)(u8 *scene, const char *name)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define setPartColor(p, part, s) GAME_THISCALL(0x474b50, void, void *, int, int, u32, u32, u32, u32, u32, u32)(scene, p, part, \
	k_schemeHue[s][0], k_schemeSat[s][0], k_schemeVal[s][0], k_schemeHue[s][1], k_schemeSat[s][1], k_schemeVal[s][1])
	static const int fixed[5] = { 3, 5, 0x24, 0x19, 0x16 };
	char path[0x100];
	sprintf(path, (const char *)0x4c77f0, scene + 0x108, name);
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c77c4, (int)path);
	log_message((int)scene, 0, 0, (const char *)0x4c77b4);
	int version, value;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	for (int k = 0; k < 3; k++) {
		fread_scrambled(&value, 4, 1, f);
		crt_fseek(f, value, 1);   /* SEEK_CUR */
	}
	fread_scrambled(&value, 4, 1, f);
	log_message((int)scene, 0, 0, (const char *)0x4c774c);
	fread_scrambled(scene + 0x1cd6fb0, 4, 1, f);
	fread_scrambled(scene + 0x1cd6a30, 0x58, FIELD(u32, scene, 0x1cd6fb0), f);
	log_message((int)scene, 0, 0, (const char *)0x4c7734);
	fread_scrambled(scene + 0x1cd93a4, 4, 1, f);
	fread_scrambled(scene + 0x1cd6fb4, 0x5c, FIELD(u32, scene, 0x1cd93a4), f);
	fclose(f);
	for (int p = 1; p < FIELD(int, scene, 0x1cd6fb0); p++) {
		u8 *rec = scene + 0x1cd6a30 + p * 0x58;
		if (--FIELD(int, rec, 4) >= 0)
			for (int part = 0; part < 5; part++)
				setPartColor(p, part, FIELD(int, rec, 4));
		int *items = (int *)(rec + 0x40);
		unsigned mode = FIELD(int, scene, 0x20f3ab8) - 2;
		if (mode <= 9) {
			items[0] = fixed[mode / 2];
			for (int k = 1; k < 6; k++)
				items[k] = -1;
			if (mode / 2 == 4)
				items[1] = 0x17;
		}
		for (int k = 1; k < 6; k++)
			if (k != 4)
				items[k] = -1;
		load_4742f0(scene, p, rec);
	}
	FIELD(int, scene, 0x19e1888) = FIELD(int, scene, 0x1cd6fb0);
	for (int i = 1; i < FIELD(int, scene, 0x1cd93a4); i++)
		FIELD(int, scene, 0x1cd6fb4 + i * 0x5c + 0x18) = 1;
	sprintf(path, (const char *)0x4c7724, scene + 0x908);
	FIELD(int, scene, 0x2104fe4) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), path, 0, 0, 0, 0, 0, 0, 0);
	for (int p = 0; p < FIELD(int, scene, 0x1cd6fb0); p++) {
		FIELD(int, scene, 0x15a9b2e + p * 0x47fd2) = 1;
		FIELD(int, scene, 0x15a9b36 + p * 0x47fd2) = 0x180;
	}
#undef crt_fread
#undef setPartColor
}

#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define POOL_MAX 4000000

/* the next n bytes of the layers' pool (+0x9ef940, +0xdc0240 used of 4,000,000: past it a fatal message); the
   caller adds n once the block is filled */
static u8 *pool_take(u8 *s, int n)
{
	int used = GAME_VAR(int, s + 0xdc0240);
	if (used + n > POOL_MAX)
		sys_fatalErrorN((char *)0xae2eb8, (const char *)0x4c7eb4, used + n, POOL_MAX);
	return s + 0x9ef940 + GAME_VAR(int, s + 0xdc0240);
}

/* texture id of "<dir>/<what>" (with an optional number) */
static u32 ground_tex(const char *dir, u32 fmt, int n, char *name)
{
	sprintf(name, (const char *)fmt, dir, n);
	return tex_getIdByName(GAME_VAR(void *, 0xa0e010), name, 0, 0, 0, 0, 0, 0, 0);
}

/* the grey value of a height-map pixel (r = g = b), or -1 */
static int grey(const u8 *px)
{
	return px[0] == px[1] && px[0] == px[2] ? px[0] : -1;
}

/* 0x48b9d0 (thiscall on the stage): the map's ground file name (under the map directory +0x108). No file or a
   version other than 0x1201 is fatal; then, scrambled, four blocks skipped, the map's directory (0x100), the view
   range (+0xa08), the lights (load_483d70), the clear colour and fog (+0x9ee030 ..), the background modes (sphere
   +0x9ee064, sky +0x9eee48, sides +0x9ef0b0, floor +0x9ef30c) and their textures, the area limits (+0x9ef904 ..),
   and the layers (+0xdc0a74; 0x20c-byte records from +0xdc0244: rows +0x1c, columns +0x20, origin +4, cell +0x24,
   height scale +0x28, texture size +0x2c): each its texture "<dir>/Ground<i>Map" and a 256 x 256 RGB height map
   (grey pixels are heights) giving, in the pool, its heights (+0x38), flat cells (+0x3c), vertices (+0x40), normals
   (+0x44: the four triangles about each inner vertex, flipped by +0 1; the border the default 0xa0e7d8), light map
   (+0x48, load_4728e0), texture coordinates (+0x50), index (+0x54 / +0x58) and primitive (+0x60 / +0x64) heaps;
   last the layer meshes (load_497a90). Returns 1 */
int THISCALL (map_loadGroundInfoFrom)(u8 *s, const char *name)
{
	u8 image[0x30000];   /* (on the stack, as the original's: the file reads log its address) */
	char path[0x100], dir[0x100], tex[0x100];
	u32 n;
	sprintf(path, (const char *)0x4c77f0, (const char *)s + 0x108, name);
	void *f = crt_fopen(path, (const char *)0x4ad170);
	if (!f)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c806c, (int)path);
	log_message((int)s, 0, 0, (const char *)0x4c77b4);
	crt_fread(&n, 4, 1, f);
	if (n != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	for (int k = 0; k < 4; k++) {
		fread_scrambled(&n, 4, 1, f);
		crt_fseek(f, n, 1);
	}
	fread_scrambled(dir, 1, 0x100, f);
	log_message((int)s, 0, 0, (const char *)0x4c804c);
	fread_scrambled(s + 0xa08, 4, 1, f);
	log_message((int)s, 0, 0, (const char *)0x4c8040);
	load_483d70(s + 0x9ccffc, f);
	log_message((int)s, 0, 0, (const char *)0x4c802c);
	fread_scrambled(s + 0x9ee030, 4, 1, f);
	fread_scrambled(s + 0x9ee034, 0x10, 1, f);
	log_message((int)s, 0, 0, (const char *)0x4c801c);
	fread_scrambled(s + 0x9ee044, 4, 1, f);
	fread_scrambled(s + 0x9ee048, 0x10, 1, f);
	static const u32 fog_and_modes[] = { 0x9ee058, 0x9ee05c, 0x9ee060, 0x9ee064, 0x9eee48, 0x9ef0b0, 0x9ef30c };
	for (int k = 0; k < 7; k++)
		fread_scrambled(s + fog_and_modes[k], 4, 1, f);
	log_message((int)s, 0, 0, (const char *)0x4c8004);
	int mode = GAME_VAR(int, s + 0x9ee064);
	if (mode == 1 || mode == 2) {
		if (mode == 2)
			GAME_VAR(u32, s + 0x9ee07c) = ground_tex(dir, 0x4c7ff4, 0, tex);   /* SphereFloor */
		static const u32 sphere[5] = { 0x4c7fe0, 0x4c7fd0, 0x4c7fc0, 0x4c7fb0, 0x4c7fa0 };   /* ceiling, east, south, west, north */
		for (int k = 0; k < 5; k++)
			GAME_VAR(u32, s + 0x9ee068 + k * 4) = ground_tex(dir, sphere[k], 0, tex);
	}
	log_message((int)s, 0, 0, (const char *)0x4c7f8c);
	mode = GAME_VAR(int, s + 0x9eee48);
	if (mode == 1 || mode == 2) {
		if (mode == 2)
			GAME_VAR(u32, s + 0x9eee50) = ground_tex(dir, 0x4c7f78, 0, tex);   /* SkyInnerLayer */
		GAME_VAR(u32, s + 0x9eee4c) = ground_tex(dir, 0x4c7f64, 0, tex);       /* SkyOuterLayer */
	}
	log_message((int)s, 0, 0, (const char *)0x4c7f4c);
	if (GAME_VAR(int, s + 0x9ef0b0) > 0 && GAME_VAR(int, s + 0x9ef0b0) <= 2)
		for (int k = 0; k < 6; k++)
			GAME_VAR(u32, s + 0x9ef0b4 + k * 4) = ground_tex(dir, 0x4c7f3c, k + 1, tex);   /* SideLayer<n> */
	log_message((int)s, 0, 0, (const char *)0x4c7f24);
	if (GAME_VAR(int, s + 0x9ef30c) > 0 && GAME_VAR(int, s + 0x9ef30c) <= 2)
		for (int k = 0; k < 16; k++)
			GAME_VAR(u32, s + 0x9ef310 + k * 4) = ground_tex(dir, 0x4c7f14, k + 1, tex);   /* FloorAni<nn> */
	log_message((int)s, 0, 0, (const char *)0x4c7f04);
	static const u8 limits[7][2] = { { 0x04, 0xc }, { 0x10, 0xc }, { 0x1c, 0xc }, { 0x28, 0xc }, { 0x34, 4 }, { 0x38, 4 }, { 0x3c, 4 } };
	for (int k = 0; k < 7; k++)
		fread_scrambled(s + 0x9ef900 + limits[k][0], limits[k][1], 1, f);
	fread_scrambled(s + 0xdc0a74, 4, 1, f);
	GAME_VAR(int, s + 0xdc0240) = 0;
	for (int i = 0; i < GAME_VAR(int, s + 0xdc0a74); i++) {
		u8 *l = s + 0xdc0244 + i * 0x20c;
		log_message((int)s, 0, i, (const char *)0x4c7ef4, i);
		fread_scrambled(l, 0x20c, 1, f);
		GAME_VAR(u32, l + 0x34) = ground_tex(dir, 0x4c7ee4, i, tex);
		fread_scrambled(image, 0x300, 0x100, f);
		int rows = GAME_VAR(int, l + 0x1c), cols = GAME_VAR(int, l + 0x20), w = cols + 1;
		int count = w * (rows + 1);
		u8 *heights = GAME_VAR(u8 *, l + 0x38) = pool_take(s, count);
		for (int r = 0; r <= GAME_VAR(int, l + 0x1c); r++)
			for (int c = 0; c <= GAME_VAR(int, l + 0x20); c++) {
				int g = grey(image + r * 0x300 + c * 3);
				heights[(GAME_VAR(int, l + 0x20) + 1) * r + c] = g < 0 ? 0 : (u8)g;
			}
		GAME_VAR(int, s + 0xdc0240) += count;
		int cells = GAME_VAR(int, l + 0x20) * GAME_VAR(int, l + 0x1c);
		u8 *flat = GAME_VAR(u8 *, l + 0x3c) = pool_take(s, cells);
		for (int r = 0; r < GAME_VAR(int, l + 0x1c); r++)
			for (int c = 0; c < GAME_VAR(int, l + 0x20); c++) {
				const u8 *px = image + r * 0x300 + c * 3;
				flat[GAME_VAR(int, l + 0x20) * r + c] = grey(px) >= 0 && grey(px + 0x300) >= 0 && grey(px + 0x303) >= 0 && grey(px + 3) >= 0;
			}
		GAME_VAR(int, s + 0xdc0240) += cells;
		int size = (GAME_VAR(int, l + 0x20) + 1) * (GAME_VAR(int, l + 0x1c) + 1) * 12;
		float *v = GAME_VAR(float *, l + 0x40) = (float *)pool_take(s, size);
		const float *origin = (const float *)(l + 4), *cell = (const float *)(l + 0x24), *hs = (const float *)(l + 0x28);
		for (int r = 0; r <= GAME_VAR(int, l + 0x1c); r++)
			for (int c = 0; c <= GAME_VAR(int, l + 0x20); c++) {
				int at = (GAME_VAR(int, l + 0x20) + 1) * r + c;
				float *p = v + at * 3;
				long double z = fadd_m(fmul_m((long double)r, cell), &origin[2]);
				long double y = fadd_m(fmul_m((long double)heights[at], hs), &origin[1]);
				p[0] = f32(fadd_m(fmul_m((long double)c, cell), &origin[0]));
				p[1] = f32(y);
				p[2] = f32(z);
			}
		GAME_VAR(int, s + 0xdc0240) += size;
		size = (GAME_VAR(int, l + 0x20) + 1) * (GAME_VAR(int, l + 0x1c) + 1) * 12;
		u8 *normals = GAME_VAR(u8 *, l + 0x44) = pool_take(s, size);
		w = GAME_VAR(int, l + 0x20) + 1;
		for (int r = 0; r <= GAME_VAR(int, l + 0x1c); r++) {
			memcpy(normals + (w * r) * 12, (const void *)0xa0e7d8, 12);
			memcpy(normals + (w * r + GAME_VAR(int, l + 0x20)) * 12, (const void *)0xa0e7d8, 12);
		}
		for (int c = 1; c < GAME_VAR(int, l + 0x20); c++) {
			memcpy(normals + c * 12, (const void *)0xa0e7d8, 12);
			memcpy(normals + ((GAME_VAR(int, l + 0x20) + 1) * GAME_VAR(int, l + 0x1c) + c) * 12, (const void *)0xa0e7d8, 12);
		}
		for (int r = 1; r < GAME_VAR(int, l + 0x1c); r++)
			for (int c = 1; c < GAME_VAR(int, l + 0x20); c++) {
				w = GAME_VAR(int, l + 0x20) + 1;
				const float *vs = GAME_VAR(const float *, l + 0x40);
				const float *p = vs + (w * r + c) * 3, *up = vs + (w * (r - 1) + c) * 3, *down = vs + (w * (r + 1) + c) * 3;
				const float *right = p + 3, *left = p - 3;
				float t[3], n1[3], n2[3], n3[3], n4[3];
				memcpy(n1, math_triangleNormal(t, left, p, up), 12);
				memcpy(n2, math_triangleNormal(t, up, p, right), 12);
				memcpy(n3, math_triangleNormal(t, right, p, down), 12);
				memcpy(n4, math_triangleNormal(t, down, p, left), 12);
				float *out = (float *)(GAME_VAR(u8 *, l + 0x44) + (w * r + c) * 12);
				for (int k = 0; k < 3; k++)
					out[k] = f32(fadd_m(fadd_m(fadd_m(fld_m(&n4[k]), &n3[k]), &n2[k]), &n1[k]));
				if (GAME_VAR(int, l) == 1)
					for (int k = 0; k < 3; k++)
						out[k] = f32(-fld_m(&out[k]));
			}
		GAME_VAR(int, s + 0xdc0240) += size;
		size = (GAME_VAR(int, l + 0x20) + 1) * (GAME_VAR(int, l + 0x1c) + 1) * 4;
		GAME_VAR(u8 *, l + 0x48) = pool_take(s, size);
		load_4728e0(s, l);
		GAME_VAR(int, s + 0xdc0240) += size;
		size = (GAME_VAR(int, l + 0x20) + 1) * (GAME_VAR(int, l + 0x1c) + 1) * 8;
		float *uv = GAME_VAR(float *, l + 0x50) = (float *)pool_take(s, size);
		for (int r = 0; r <= GAME_VAR(int, l + 0x1c); r++)
			for (int c = 0; c <= GAME_VAR(int, l + 0x20); c++) {
				int at = (GAME_VAR(int, l + 0x20) + 1) * r + c;
				const float *p = GAME_VAR(const float *, l + 0x40) + at * 3;
				long double tz = fdiv_m(fld_m(&p[2]), (const float *)(l + 0x2c));
				uv[at * 2] = f32(fdiv_m(fld_m(&p[0]), (const float *)(l + 0x2c)));
				uv[at * 2 + 1] = f32(tz);
			}
		GAME_VAR(int, s + 0xdc0240) += size;
		int indices = (GAME_VAR(int, l + 0x20) + 200) * GAME_VAR(int, l + 0x1c) * 2;
		u8 *heap = pool_take(s, indices * 4);
		GAME_VAR(int, l + 0x54) = indices;
		GAME_VAR(u8 *, l + 0x58) = heap;
		GAME_VAR(int, s + 0xdc0240) += indices * 4;
		int prims = GAME_VAR(int, l + 0x1c) * 200 + 4;
		heap = pool_take(s, prims * 12);
		GAME_VAR(int, l + 0x60) = prims;
		GAME_VAR(u8 *, l + 0x64) = heap;
		GAME_VAR(int, s + 0xdc0240) += prims * 12;
	}
	load_497a90(s);
	fclose(f);
	return 1;
}
#undef crt_fread
#undef POOL_MAX

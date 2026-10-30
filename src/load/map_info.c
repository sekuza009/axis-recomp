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
	FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c77b4);
	u32 version, skip;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	for (int k = 0; k < 2; k++) {
		fread_scrambled(&skip, 4, 1, f);
		crt_fseek(f, skip, 1);   /* SEEK_CUR */
	}
	fread_scrambled(&skip, 4, 1, f);
	FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c7ddc);
	load_48b460(scene, f);
	FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c7dcc);
	map_loadWayPointInfoFrom(scene, f);
	FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c7dbc);
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
	FUN_00467520(scene + 0xe3c93c);
	FUN_0046b7f0(scene + 0x13016d0);
	load_490d10(scene);
	FIELD(int, scene, 0x13016cc) = 0;
	if (mode == 0) {
		load_46cad0(name, base);
		sprintf(path, (const char *)0x4c7e90, scene + 0x108, base);
		void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
		if (f) {
			FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c7e74);
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
	FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c77b4);
	int version, value, count;
	crt_fread(&version, 4, 1, f);
	if (version != 0x1201)
		sys_fatalError((char *)0xae2eb8, (const char *)0x4c7768, (int)name);
	fread_scrambled(&value, 4, 1, f);
	fread_scrambled(&count, 4, 1, f);
	for (int i = 0; i < count; i++) {
		if (i % 2 == 0)
			FUN_00470fc0((int)scene, 0, i, (const char *)0x4c7e38, i);
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
			FUN_00470fc0((int)scene, 0, 0, (const char *)0x4c7e1c);
			FUN_0046cc30(scene + 0x13016c8, 4, 1, f);
			FUN_0046cc30(scene + 0xf30dc8, 4, FIELD(u32, scene, 0x13016c8), f);
			fclose(f);
		}
	}
#undef crt_fread
}

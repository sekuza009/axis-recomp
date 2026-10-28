/* armc_parts.c: the ARM CENTER's part-info records (0x80 bytes): what the screen shows of an actor type picked as
   a part or a weapon: its folder's last name, six values copied from its ActorInfo, eight scaled. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* ActorInfo offsets copied as they are (record offset, ActorInfo offset) */
static const short copied[6][2] = { { 0x40, 0x2dbc }, { 0x44, 0x2dc0 }, { 0x48, 0x2dc4 }, { 0x4c, 0x2dc8 },
                                    { 0x50, 0x2ddc }, { 0x54, 0x2de0 } };

/* and those scaled by a constant of the game (record offset, ActorInfo offset, constant's address) */
static const struct { short dst, src; u32 scale; } scaled[8] = {
	{ 0x58, 0x2de4, 0x4a9420 }, { 0x5c, 0x2de8, 0x4a9420 }, { 0x60, 0x2dec, 0x4a93ec }, { 0x64, 0x2df0, 0x4a9420 },
	{ 0x68, 0x2df4, 0x4a9420 }, { 0x70, 0x2e08, 0x4a94bc }, { 0x74, 0x2e0c, 0x4a93ec }, { 0x78, 0x2e10, 0x4a94bc } };

/* record rec for actor type idx; idx -1: the record emptied (its +0x40 -1) */
static void part_info(u8 *rec, int idx)
{
	if (idx == -1) {
		memset(rec, 0, 64);
		FIELD(int, rec, 0x40) = -1;
		memset(rec + 0x44, 0, 0x3c);
		return;
	}
	ActorInfo *info = &g_scene->actorInfo[idx];

	/* the name: the folder path's part after its last slash */
	char path[128] = { 0 };
	strcpy(path, info->name);
	int n = (int)strlen(path), i = n - 1;
	while (i >= 0 && path[i] != '\\' && path[i] != '/')
		i--;
	memset(rec, 0, 64);
	if (i + 1 < n)
		memcpy(rec, path + i + 1, n - (i + 1));

	for (int k = 0; k < 6; k++)
		FIELD(int, rec, copied[k][0]) = FIELD(int, info, copied[k][1]);
	for (int k = 0; k < 8; k++) {
		if (k == 5)
			FIELD(int, rec, 0x6c) = FIELD(int, info, 0x2df8);
		FIELD(float, rec, scaled[k].dst) =
			(float)((long double)FIELD(float, info, scaled[k].src) * GAME_VAR(float, scaled[k].scale));
	}
	FIELD(int, rec, 0x7c) = FIELD(int, info, 0x2db8);
}

/* 0x41ca50: the record of weapon slot slot (0x4dbe50, 0x80 apart) */
void (armc_41ca50)(int slot, int idx) { part_info((u8 *)0x4dbe50 + slot * 0x80, idx); }

/* 0x41cca0: the record of the part being looked at (0x4dc150); the first type picked is kept in 0x4dc198 */
void (armc_41cca0)(int idx)
{
	part_info((u8 *)0x4dc150, idx);
	if (idx != -1 && GAME_VAR(int, 0x4dc194) == -1)
		GAME_VAR(int, 0x4dc198) = idx;
}

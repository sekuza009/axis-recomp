/* net_tables.c: the network code's fixed tables: the 200 session values (8-byte records at 0xa0b470: in use,
   value; the last index in 0xa0b41c) and the sixteen player slot records (0x410 bytes from 0x9f9840). */
#include "../game.h"
#include <string.h>

/* 0x454110: the first free session record, -1 when all 200 are used */
int (FUN_00454110)(void)
{
	int i = 0;
	for (u32 p = 0xa0b470; p < 0xa0bab0; p += 8, i++)
		if (GAME_VAR(u32, p) == 0)
			return i;
	return -1;
}

/* 0x4532b0: session i's value, 0 when out of range or unused */
int (arena_4532b0)(int i)
{
	if (i > -1 && i <= GAME_VAR(int, 0xa0b41c) && GAME_VAR(int, 0xa0b470 + i * 8))
		return GAME_VAR(int, 0xa0b474 + i * 8);
	return 0;
}

/* 0x4514a0: player slot (its low byte) taken by player id: the shorts at +0x10 .. +0x22 reset (two of them -1),
   +0x32 the current value of 0xa0b428 */
void (arena_4514a0)(u32 slot, int id)
{
	static const short init[10] = { 0, 0, 0, 0, 0, -1, 0, 0, -1, 0 };
	u32 r = 0x9f9840 + (slot & 0xff) * 0x410;
	GAME_VAR(int, r) = 1;
	GAME_VAR(int, r + 4) = id;
	memcpy((void *)(r + 0x10), init, sizeof init);
	GAME_VAR(short, r + 0x32) = GAME_VAR(short, 0xa0b428);
}

/* 0x4515a0: all slots freed (and the 0x40 bytes at 0x9f93d8 cleared) */
void (arena_4515a0)(void)
{
	memset((void *)0x9f93d8, 0, 0x40);
	for (u32 r = 0x9f9840; r < 0x9fd940; r += 0x410)
		memset((void *)r, 0, 16);
}

/* 0x451450: a free player slot claimed (its flag in the sixteen at 0x9f93d8 set); 0xff when none is free */
u8 (FUN_00451450)(void)
{
	for (u8 i = 0; i < 0x10; i++)
		if (GAME_VAR(int, 0x9f93d8 + i * 4) == 0) {
			GAME_VAR(int, 0x9f93d8 + i * 4) = 1;
			return i;
		}
	return 0xff;
}

/* 0x451410: a slot claimed for the local player (id 0xa0b424) when the session is up; 1 when done */
int (arena_451410)(void)
{
	if (!GAME_VAR(int, 0xa0baf8))
		return 0;
	u8 slot = FUN_00451450();
	arena_4514a0(slot, GAME_VAR(int, 0xa0b424));
	GAME_VAR(u8, 0x9fd954) = slot;
	GAME_VAR(int, 0x9f9838) = 1;
	return 1;
}

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

/* 0x454130: with a session list (0xa0b384), every used session record (8 bytes from 0xa0b470: used, a malloc'd copy)
   freed and the list emptied (count 0xa0b41c). Returns the count, or 0 without a list */
u32 (arena_454130)(void)
{
	if (!GAME_VAR(int, 0xa0b384))
		return 0;
	for (int i = 0; i < GAME_VAR(int, 0xa0b41c); i++) {
		u32 *rec = (u32 *)(0xa0b470 + i * 8);
		if (rec[0] != 1)
			continue;
		rec[0] = 0;
		if (rec[1])
			crt_free((void *)rec[1]);
		rec[0] = 0;
		rec[1] = 0;
	}
	u32 r = GAME_VAR(u32, 0xa0b41c);
	GAME_VAR(int, 0xa0b41c) = 0;
	return r;
}

/* 0x4542a0: the address typed as "a.b.c.d" (0xa0b43c, cut up in place by strtok) as (a << 24) | b << 16 | c << 8 | d
   (a not masked). Each part goes into a 4-byte slot of a zeroed 20-byte buffer (a longer part runs into the next
   slot); more than four parts would overrun the original's stack, and a string with none makes it copy from NULL */
int (arena_4542a0)(void)
{
	char buf[20];
	memset(buf, 0, sizeof buf);
	char *part = crt_strtok((char *)0xa0b43c, (const char *)0x4b1304);   /* "." */
	strcpy(buf, part);
	if (part)
		for (char *slot = buf + 4; (part = crt_strtok(NULL, (const char *)0x4b3e68)) != NULL; slot += 4)
			strcpy(slot, part);
	int a = crt_atoi(buf), b = crt_atoi(buf + 4), c = crt_atoi(buf + 8), d = crt_atoi(buf + 12);
	return ((((a << 8) | (b & 0xff)) << 8 | (c & 0xff)) << 8) | (d & 0xff);
}

/* 0x454390: the address as "a.b.c.d" (bytes high to low) into 0xa0b460; returns its length + 1 */
int (dplay_formatSessionEntry)(u32 address)
{
	char text[16], part[4];
	itoa((int)(address >> 24), part, 10);
	strcpy(text, part);
	for (int shift = 16; shift >= 0; shift -= 8) {
		strcat(text, (const char *)0x4b1304);
		itoa((int)((address >> shift) & 0xff), part, 10);
		strcat(text, part);
	}
	strcpy((char *)0xa0b460, text);
	return (int)strlen(text) + 1;
}

/* a DirectPlay session description as the enumeration callback gets it, by value */
typedef struct { u8 b[0x85]; } SessionDesc;

/* 0x4540b0: a session found: unless it is the game's own (its GUID, bytes 4 .. 19, the one at 0x4aae70), a copy
   (malloc'd) kept in the first free slot of the table at 0xa0b470, the count up. Returns the copy, 0 for the game's
   own, or -1 when the table is full */
u32 (FUN_004540b0)(SessionDesc d)
{
	if (!memcmp(d.b + 4, (const void *)0x4aae70, 16))
		return 0;
	int i = FUN_00454110();
	if (i < 0)
		return (u32)i;
	void *copy = crt_malloc(0x85);
	GAME_VAR(void *, 0xa0b474 + i * 8) = copy;
	GAME_VAR(int, 0xa0b470 + i * 8) = 1;
	memcpy(GAME_VAR(void *, 0xa0b474 + i * 8), d.b, 0x85);
	GAME_VAR(int, 0xa0b41c) += 1;
	return (u32)copy;
}

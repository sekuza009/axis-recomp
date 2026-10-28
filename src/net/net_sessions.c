/* net_sessions.c: the network games received (DirectPlay's session enumeration) merged into the session list the
   arena lobby and the game room show: 0x4a-byte entries from 0x9087c4, their count in 0x67ef30. */
#include "../game.h"
#include <string.h>

#define g_sessionCount GAME_VAR(int, 0x67ef30)
#define SESSION(k) ((u8 *)0x9087c4 + (k) * 0x4a)

/* one screen's received games: flag says new ones arrived; records of stride bytes from base (s = a record's key
   byte: its name at s + nameOff, its flags around s, a second string at s + str2Off); total sums the entries'
   player counts; the three words of clear are cleared when nothing more is coming (0xa0d7a0 0) */
typedef struct {
	u32 flag, base;
	int stride, nameOff, str2Off;
	u32 total;
	u32 clear[3];
} Received;

static void merge(const Received *g)
{
	if (GAME_VAR(int, g->flag)) {
		for (int i = 0; i < GAME_VAR(int, 0xa0d79c); i++) {
			if (GAME_VAR(int, 0xa0bb14 + i * 4) != 1)   /* not new */
				continue;
			const u8 *s = (const u8 *)(g->base + i * g->stride);
			int players = GAME_VAR(int, 0xa0d384 + i * 4);
			if (players > 0) {
				int k = g_sessionCount;
				u8 *e = SESSION(k);
				memset(e, 0, 32);
				strcpy((char *)e, (const char *)s + g->nameOff);
				u8 b6 = s[-6];
				e[0x20] = s[0];
				e[0x21] = b6;
				e[0x28] = s[-3];
				e[0x22] = s[-5];
				e[0x23] = s[-4];
				e[0x29] = s[-2];
				e[0x2a] = s[-1];
				GAME_VAR(int, e + 0x24) = players;
				e[0x43] = s[9];
				GAME_VAR(int, e + 0x3b) = 0;
				GAME_VAR(int, e + 0x3f) = 0;
				strcpy((char *)e + 0x3b, (const char *)s + 0xa);
				memset(e + 0x2b, 0, 16);
				strcpy((char *)e + 0x2b, (const char *)s + g->str2Off);
				GAME_VAR(int, g->total) += (signed char)e[0x23];
				g_sessionCount = k + 1;
				arena_4065e0();   /* the list sorted again */
			}
			GAME_VAR(int, 0xa0bb14 + i * 4) = 0;
			GAME_VAR(int, 0x680bb8)++;
		}
		if (!GAME_VAR(int, 0xa0d7a0))
			return;
	}
	for (int k = 0; k < 3; k++)
		GAME_VAR(int, g->clear[k]) = 0;
}

/* 0x434ff0: the game room's (0x79-byte records) */
void (room_434ff0)(void)
{
	static const Received room = { 0xa0b358, 0x9fd9c7, 0x79, -0x66, -0x34, 0x9dd840, { 0x9dd6a0, 0x9da498, 0x9dd3fc } };
	merge(&room);
}

/* 0x406640: the arena lobby's (0x5b-byte records) */
void (arena_406640)(void)
{
	static const Received arena = { 0xa0b368, 0xa05791, 0x5b, -0x48, -0x16, 0x4dba8c, { 0x4db858, 0x4df018, 0x4db8b8 } };
	merge(&arena);
}

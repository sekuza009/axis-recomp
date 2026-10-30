/* factors.c: the factor pool's records built and added (factor_addFactorBy): a 0x2c-byte record of which only the
   kind (+8), the value (+0xc) and the kind's own fields are set; the rest is left as the stack holds it, as the
   originals leave it (they add the whole record). Also a layer's lighting. */
#include "../game.h"

typedef struct { u8 bytes[0x2c]; } FactorRecord;
#define REC(type, offset) (*(type *)(r.bytes + (offset)))

/* 0x483e90 (thiscall on the pool): a kind 0 factor of the value *a. Its callers ignore the eax it leaves */
void THISCALL (load_483e90)(void *pool, const u32 *a)
{
	FactorRecord r;
	__asm__("" : "=m"(r));   /* (left as the stack holds it) */
	REC(int, 8) = 0;
	REC(u32, 0xc) = *a;
	factor_addFactorBy(pool, &r);
}

/* 0x483ec0: a kind 1 factor of the value *a at the point p (+0x1c) */
void THISCALL (load_483ec0)(void *pool, const u32 *a, const u32 *p)
{
	FactorRecord r;
	__asm__("" : "=m"(r));
	REC(int, 8) = 1;
	REC(u32, 0xc) = *a;
	for (int i = 0; i < 3; i++)
		REC(u32, 0x1c + i * 4) = p[i];
	factor_addFactorBy(pool, &r);
}

/* 0x483f00: a kind 2 factor of the value *a towards p (+0x10) with x (+0x28) */
void THISCALL (match_483f00)(void *pool, const u32 *a, u32 x, const u32 *p)
{
	FactorRecord r;
	__asm__("" : "=m"(r));
	REC(int, 8) = 2;
	REC(u32, 0xc) = *a;
	for (int i = 0; i < 3; i++)
		REC(u32, 0x10 + i * 4) = p[i];
	REC(u32, 0x28) = x;
	factor_addFactorBy(pool, &r);
}
#undef REC

/* 0x4728e0 (thiscall on the scene): the layer's lighting computed over its vertices (+0x48), rows (+0x1c) and
   columns (+0x20). Its caller ignores the eax it leaves */
void THISCALL (load_4728e0)(void *scene, const u8 *layer)
{
	light_computeLayerLightBy(scene, layer, GAME_VAR(u32, layer + 0x48), 1, 0, 0, GAME_VAR(int, layer + 0x1c), GAME_VAR(int, layer + 0x20));
}

/* 0x483dd0 (thiscall on the pool): the record copied into the next free slot (+0xb008; 0x2c-byte slots from +4,
   +0xb004 of them, a slot added when that is the count; from 0x400 on a fatal message), given its index (+0) and
   marked used (+4); the next free one after it found; the pool marked changed (+0xb00c). Its callers ignore the eax
   it leaves */
void THISCALL (factor_addFactorBy)(u8 *pool, const u32 *record)
{
#define COUNT GAME_VAR(int, pool + 0xb004)
#define NEXT GAME_VAR(int, pool + 0xb008)
#define SLOT(k) ((u32 *)(pool + 4 + (k) * 0x2c))
	if (NEXT >= 0x400)
		sys_fatalError((char *)0xae2ee8, (const char *)0x4c7ae0, NEXT);
	if (NEXT == COUNT) {
		COUNT++;
		SLOT(COUNT)[1] = 0;
	}
	u32 *slot = SLOT(NEXT);
	for (int i = 0; i < 11; i++)
		slot[i] = record[i];
	slot[0] = NEXT;
	slot[1] = 1;
	for (int k = NEXT + 1; k <= COUNT; k++)
		if (SLOT(k)[1] == 0) {
			NEXT = k;
			break;
		}
	GAME_VAR(int, pool + 0xb00c) = 1;
#undef COUNT
#undef NEXT
#undef SLOT
}

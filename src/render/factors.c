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

/* factors.c: the factor pool's records built and added (factor_addFactorBy): a 0x2c-byte record of which only the
   kind (+8), the value (+0xc) and the kind's own fields are set; the rest is left as the stack holds it, as the
   originals leave it (they add the whole record). Also a layer's lighting. */
#include "../game.h"

typedef struct { u8 bytes[0x2c]; } FactorRecord;
#define REC(type, offset) (*(type *)(r.bytes + (offset)))

/* 0x483e90 (thiscall on the pool): a kind 0 factor of the value *a. Its callers ignore the eax it leaves */
void THISCALL (factors_addConstant)(void *pool, const u32 *a)
{
	FactorRecord r;
	__asm__("" : "=m"(r));   /* (left as the stack holds it) */
	REC(int, 8) = 0;
	REC(u32, 0xc) = *a;
	factor_addFactorBy(pool, &r);
}

/* 0x483ec0: a kind 1 factor of the value *a at the point p (+0x1c) */
void THISCALL (factors_addPoint)(void *pool, const u32 *a, const u32 *p)
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
void THISCALL (factors_addDirected)(void *pool, const u32 *a, u32 x, const u32 *p)
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
void THISCALL (ground_computeLighting)(void *scene, const u8 *layer)
{
	light_computeLayerLightBy(scene, layer, GAME_VAR(u32, layer + 0x48), 1, 0, 0, GAME_VAR(int, layer + 0x1c), GAME_VAR(int, layer + 0x20));
}

/* 0x483dd0 (thiscall on the pool): the record copied into the next free slot (+0xb008; 0x2c-byte slots from +4,
   +0xb004 of them, a slot added when that is the count; from 0x400 on a fatal message), given its index (+0) and
   marked used (+4); the next free one after it found; the pool marked changed (+0xb00c). Its callers ignore the eax
   it leaves */
void THISCALL (factor_addFactorBy)(u8 *pool, const u32 *record)
{
#define COUNT (((LightFactors *)pool)->count)
#define NEXT (((LightFactors *)pool)->nextFree)
#define SLOT(k) ((u32 *)(pool + 4 + (k) * 0x2c))
	if (NEXT >= 0x400)
		sys_fatalError((char *)OBJ(g_logLight), (const char *)STR(0x4c7ae0, "factorPool overflow(%d) - addFactorBy()"), NEXT);
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

/* 0x484050 (thiscall on a view volume): sized for its six tables (a x 0x1c, b x 0x40, c x 4, d x 0x68, e x 0x64,
   f x 0x24 bytes; the counts at +0x9030, +0x903c, +0x9048, +0x9054, +0x9068, +0x9084) in one block (+8, its size +4;
   allocated and owned, +0xc 1, without memory given, else the memory given, the caller's size checked: fatal
   messages), the tables' starts laid out (+0x9034 ..; d's and e's each in parts), then reset (ViewVolume_clearDrawCounts). Its
   caller ignores the eax it leaves */
void THISCALL (factor_initBy)(u8 *view, int a, int b, int c, int d, int e, int f, void *mem, int size)
{
#define FIELD(type, offset) GAME_VAR(type, view + (offset))
#define VV ((ViewVolume *)view)   /* the same by its fields (src/scene.fields) */
	gfx_initVertexArrayExt(view);
	VV->colourLimit = c;
	VV->entryLimit = a;
	VV->matrixLimit = b;
	VV->triangleLimit = d;
	VV->quadLimit = e;
	VV->segmentLimit = f;
	int need = FIELD(int, 4) = a * 0x1c + b * 0x40 + c * 4 + d * 0x68 + e * 0x64 + f * 0x24;
	if (!mem) {
		FIELD(void *, 8) = operator_new(need);
		if (!FIELD(void *, 8))
			sys_fatalError((char *)OBJ(g_logViewVolume), (const char *)STR(0x4c4cec, "insufficient memory for dataMemory(%d..."), FIELD(int, 4));
		FIELD(int, 0xc) = 1;
	} else {
		if (size < need)
			sys_fatalErrorN((char *)OBJ(g_logViewVolume), (const char *)STR(0x4c4cbc, "reserved dataMemory overflow(%d/%d) -..."), need, size);
		FIELD(void *, 8) = mem;
	}
	u8 *block = FIELD(u8 *, 8);
	VV->entries = block;
	int at = VV->entryLimit * 0x1c;
	VV->matrices = block + at;
	at += VV->matrixLimit * 0x40;
	VV->colours = block + at;
	at += VV->colourLimit * 4;
	VV->triangles = block + at;
	VV->triangleOrder = block + at + VV->triangleLimit * 0x60;
	at += VV->triangleLimit * 0x68;
	VV->quads = block + at;
	int count = VV->quadLimit;
	VV->quadOrderA = block + at + count * 0x5c;
	VV->quadOrderB = block + at + count * 0x64;
	VV->segments = block + at + count * 0x6c;
	ViewVolume_clearDrawCounts(view);
#undef FIELD
}

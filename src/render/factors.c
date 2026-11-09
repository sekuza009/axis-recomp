/* factors.c: the light factor pools' records built and added (factor_addFactorBy: a 0x2c-byte record of which only
   the kind, the colour and the kind's own fields are set; the rest is left as the stack holds it, as the originals
   leave it); a ground layer's lighting; a view volume sized (ViewVolume_initBy). */
#include "../game.h"

typedef struct { u8 bytes[0x2c]; } FactorRecord;

/* 0x483e90 (thiscall on the pool): an ambient light (kind 0) of the colour *colour. Its callers ignore the eax it leaves */
void THISCALL (factors_addAmbient)(void *pool, const u32 *colour)
{
	Factor r;
	__asm__("" : "=m"(r));   /* (left as the stack holds it) */
	r.kind = 0;
	r.colour = *colour;
	factor_addFactorBy(pool, &r);
}

/* 0x483ec0: a directional light (kind 1) of the colour *colour along the direction dir */
void THISCALL (factors_addDirectional)(void *pool, const u32 *colour, const u32 *dir)
{
	Factor r;
	__asm__("" : "=m"(r));
	r.kind = 1;
	r.colour = *colour;
	for (int i = 0; i < 3; i++)
		BITS(r.dir[i]) = dir[i];
	factor_addFactorBy(pool, &r);
}

/* 0x483f00: a point light (kind 2) of the colour *colour at pos, reaching the radius radius */
void THISCALL (factors_addPointLight)(void *pool, const u32 *colour, u32 radius, const u32 *pos)
{
	Factor r;
	__asm__("" : "=m"(r));
	r.kind = 2;
	r.colour = *colour;
	for (int i = 0; i < 3; i++)
		BITS(r.pos[i]) = pos[i];
	BITS(r.radius) = radius;
	factor_addFactorBy(pool, &r);
}

/* 0x4728e0 (thiscall on the stage): the layer's lighting computed into its colours over all its vertices
   (light_computeLayerLightBy, rows 0 .. rows, columns 0 .. cols, first 1). Its caller ignores the eax it leaves */
void THISCALL (ground_computeLighting)(void *stage, const GroundLayer *layer)
{
	light_computeLayerLightBy(stage, (const u8 *)layer, (u32)layer->colours, 1, 0, 0, layer->rows, layer->cols);
}

/* 0x483dd0 (thiscall on the pool): the record copied into the next free slot (nextFree; 0x2c-byte slots from +4,
   count of them, a slot added when that is the count; from 0x400 on a fatal message), given its index (+0) and
   marked used (+4); the next free one after it found; the pool marked in use (enabled). Its callers ignore the eax
   it leaves */
void THISCALL (factor_addFactorBy)(LightFactors *pool, const u32 *record)
{
#define COUNT (pool->count)
#define NEXT (pool->nextFree)
#define SLOT(k) ((u32 *)&pool->records[k])
	if (NEXT >= 0x400)
		sys_fatalError(AP(char, OBJ(g_logLight)), AP(const char, STR(0x4c7ae0, "factorPool overflow(%d) - addFactorBy()")), NEXT);
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
	pool->enabled = 1;
#undef COUNT
#undef NEXT
#undef SLOT
}

/* 0x484050 (thiscall on a view volume): sized for its six tables (entries x 0x1c, matrices x 0x40, colours x 4,
   triangles x 0x68, quads x 0x64, segments x 0x24 bytes; the counts at entryLimit, matrixLimit, colourLimit, triangleLimit, quadLimit, segmentLimit) in one block (+8, its size +4;
   allocated and owned, ownsBlock 1, without memory given, else the memory given, the caller's size checked: fatal
   messages), the tables' starts laid out (entries ..; the triangles' and quads' each in parts), then reset (ViewVolume_clearDrawCounts). Its
   caller ignores the eax it leaves. As in the original, the quads' part is sized quads x 0x64 but quadOrderB starts at
   + quadLimit x 0x64 and the segments at + quadLimit x 0x6c, so the segment table ends quadLimit x 8 bytes (3200 for
   Console_ctor's 400) past the size checked: harmless only because viewMemory (2,000,000) is larger than the
   1,240,000 asked */
void THISCALL (ViewVolume_initBy)(u8 *view, int entries, int matrices, int colours, int triangles, int quads, int segments, void *mem, int size)
{
#define VV ((ViewVolume *)view)   /* the same by its fields (src/scene.fields) */
	ViewVolume_release(view);
	VV->colourLimit = colours;
	VV->entryLimit = entries;
	VV->matrixLimit = matrices;
	VV->triangleLimit = triangles;
	VV->quadLimit = quads;
	VV->segmentLimit = segments;
	int need = VV->blockSize = entries * 0x1c + matrices * 0x40 + colours * 4 + triangles * 0x68 + quads * 0x64 + segments * 0x24;
	if (!mem) {
		VV->block = AREF(operator_new(need));
		if (!VV->block)
			sys_fatalError(AP(char, OBJ(g_logViewVolume)), AP(const char, STR(0x4c4cec, "insufficient memory for dataMemory(%d...")), VV->blockSize);
		VV->ownsBlock = 1;
	} else {
		if (size < need)
			sys_fatalErrorN(AP(char, OBJ(g_logViewVolume)), AP(const char, STR(0x4c4cbc, "reserved dataMemory overflow(%d/%d) -...")), need, size);
		VV->block = AREF(mem);
	}
	u8 *block = AP(u8, VV->block);
	VV->entries = AREF(block);
	int at = VV->entryLimit * 0x1c;
	VV->matrices = AREF(block + at);
	at += VV->matrixLimit * 0x40;
	VV->colours = AREF(block + at);
	at += VV->colourLimit * 4;
	VV->triangles = AREF(block + at);
	VV->triangleOrder = AREF(block + at + VV->triangleLimit * 0x60);
	at += VV->triangleLimit * 0x68;
	VV->quads = AREF(block + at);
	int count = VV->quadLimit;
	VV->quadOrderA = AREF(block + at + count * 0x5c);
	VV->quadOrderB = AREF(block + at + count * 0x64);
	VV->segments = AREF(block + at + count * 0x6c);
	ViewVolume_clearDrawCounts(view);
}

/* space_pools.c: the collision space's pools of planes, nodes and blocks. A pool is a count, an array of records
   and a free list (head, then a used count, at +8 / +0xc from the count); emptying it clears every record, links
   them both ways (prev, then next, at the same offset in each) and puts the whole array on the free list. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

typedef int (THISCALL *Clear)(void *record);

/* the pool whose count is at +count: records of stride bytes, their links at +link. Returns what the original
   leaves in eax: (count - 1) * stride when there are at least two records, else the count */
static int reset_pool(void *space, int count, int stride, Clear clear, int link)
{
	for (int i = 0; i < FIELD(int, space, count); i++)
		clear(FIELD(u8 *, space, count + 4) + i * stride);
	for (int i = 1; i < FIELD(int, space, count); i++) {
		u8 *e = FIELD(u8 *, space, count + 4) + i * stride;
		FIELD(u8 *, e, link) = e - stride;
	}
	int r = FIELD(int, space, count);
	if (FIELD(int, space, count) - 1 > 0) {
		int i;
		for (i = 0; i < FIELD(int, space, count) - 1; i++) {
			u8 *a = FIELD(u8 *, space, count + 4);
			FIELD(u8 *, a + i * stride, link + 4) = a + (i + 1) * stride;
		}
		r = i * stride;
	}
	FIELD(int, space, count + 0xc) = 0;
	FIELD(u8 *, space, count + 8) = FIELD(u8 *, space, count + 4);
	return r;
}

static int THISCALL clear_plane(void *r) { return load_47db50(r); }
static int THISCALL clear_node(void *r) { return load_480430(r); }
static int THISCALL clear_block(void *r) { return load_4804a0(r); }

/* 0x481520: the planes (0xac bytes each) */
int THISCALL (space_resetPlanes)(void *space) { return reset_pool(space, 0x10, 0xac, clear_plane, 0xa0); }
/* 0x481630: the nodes (0x10 bytes) */
int THISCALL (space_resetNodes)(void *space) { return reset_pool(space, 0x20, 0x10, clear_node, 8); }
/* 0x481860: the blocks (0x50 bytes) */
int THISCALL (space_resetBlocks)(void *space) { return reset_pool(space, 0x40, 0x50, clear_block, 0x48); }

/* ---- a record taken from a pool's free list (its head at +head, a record's next and previous at +next / +prev):
   the head moves on, the pool's used count (+count) goes up, the record is cleared. An empty free list is a fatal
   error reporting all the pools' sizes (format at format) ---- */
static void *take_free(u8 *space, int head, int next, int prev, int count, Clear clear, u32 format)
{
	u8 *r = FIELD(u8 *, space, head);
	if (!r) {
		GAME_CDECL(0x46c710, void, void *, const char *, int, int, int, int, int, int, int, int)(   /* sys_fatalError */
			(void *)0xae2ed0, (const char *)format, FIELD(int, space, 0x1c), FIELD(int, space, 0x10), FIELD(int, space, 0x2c),
			FIELD(int, space, 0x20), FIELD(int, space, 0x3c), FIELD(int, space, 0x30), FIELD(int, space, 0x4c),
			FIELD(int, space, 0x40));
		return 0;
	}
	u8 *after = FIELD(u8 *, r, next);
	if (after) {
		FIELD(u8 *, space, head) = after;
		FIELD(u8 *, after, prev) = 0;
	} else
		FIELD(u8 *, space, head) = 0;
	FIELD(int, space, count)++;
	clear(r);
	return r;
}
static int THISCALL clear_unit(void *r) { load_480440(r); return 0; }

/* 0x4815c0, 0x4816c0, 0x4817f0: a free plane, node or unit */
void *THISCALL (space_getNextFreePlanePtr)(void *space) { return take_free(space, 0x18, 0xa4, 0xa0, 0x1c, clear_plane, 0x4c7818); }
void *THISCALL (space_getNextFreeNodePtr)(void *space) { return take_free(space, 0x28, 0xc, 8, 0x2c, clear_node, 0x4c7874); }
void *THISCALL (space_getNextFreeUnitPtr)(void *space) { return take_free(space, 0x38, 0x10, 0xc, 0x3c, clear_unit, 0x4c78cc); }

/* 0x4818e0 (thiscall on the space): a block taken from the free list (+0x48; its next at +0x4c, the new head's back
   link +0x48 cleared), counted (+0x4c), reset (load_4804a0) and given the bounds mn / mx (three dwords each);
   returns it. With none free, a fatal message with the pools' sizes and 0 */
void *THISCALL (space_getNextFreeBlockPtrBy)(u8 *space, const u32 *mn, const u32 *mx)
{
#define FIELD(type, offset) GAME_VAR(type, space + (offset))
	u32 *block = FIELD(u32 *, 0x48);
	if (!block) {
		GAME_CDECL(0x46c710, void, char *, const char *, int, int, int, int, int, int, int, int)((char *)0xae2ed0, (const char *)0x4c7924,
			FIELD(int, 0x1c), FIELD(int, 0x10), FIELD(int, 0x2c), FIELD(int, 0x20), FIELD(int, 0x3c), FIELD(int, 0x30), FIELD(int, 0x4c), FIELD(int, 0x40));
		return 0;
	}
	u32 *next = (u32 *)block[0x4c / 4];
	if (next) {
		FIELD(u32 *, 0x48) = next;
		next[0x48 / 4] = 0;
	} else
		FIELD(u32 *, 0x48) = 0;
	FIELD(int, 0x4c)++;
	load_4804a0(block);
	for (int i = 0; i < 3; i++)
		block[i] = mn[i];
	for (int i = 0; i < 3; i++)
		block[3 + i] = mx[i];
	return block;
#undef FIELD
}

/* 0x482320 (thiscall on the space): a unit's planes built (space_buildPlanes) and, when there are any, linked at the
   end of the owner's list (owner +4 its last; +0xa0 / +0xa4 next / previous) and given a node (space_getNextFreeNode
   Ptr: +0 the planes, +8 / +0xc next / previous; owner +8 its last node). Its callers ignore the eax it leaves */
void THISCALL (load_482320)(void *space, u32 id, u8 *owner, u32 part, u32 i0, u32 i1, u32 i2, u32 v0, u32 v1, u32 v2)
{
#define AT(type, p, offset) GAME_VAR(type, (u8 *)(p) + (offset))
	u8 *planes = space_buildPlanes(space, id, v0, v1, v2, owner, part, i0, i1, i2);
	if (!planes)
		return;
	u8 *last = AT(u8 *, owner, 4);
	if (last) {
		AT(u8 *, last, 0xa0) = planes;
		AT(u8 *, planes, 0xa4) = AT(u8 *, owner, 4);
	}
	AT(u8 *, owner, 4) = planes;
	u8 **node = space_getNextFreeNodePtr(space);
	node[0] = planes;
	u8 **last_node = AT(u8 **, owner, 8);
	if (last_node) {
		AT(u8 *, last_node[0], 0xa0) = planes;
		AT(u8 *, node[0], 0xa4) = AT(u8 **, owner, 8)[0];
		AT(u8 **, AT(u8 **, owner, 8), 8) = node;
		AT(u8 **, node, 0xc) = AT(u8 **, owner, 8);
	}
	AT(u8 **, owner, 8) = node;
#undef AT
}

/* 0x4819b0 (thiscall on the space): the space emptied (planes, nodes, units, blocks) and laid out: its bounds mn / mx
   (+0x5c, +0x68), a grid of nx x ny x nz cells (+0x74 .., +0x58 their number: none, or more than its +0x50 cells, a
   fatal message), each cell's size (+0x80 .. +0x88: z, x, y over nx, ny, nz, as the original pairs them), a / b (+0x8c,
   +0x90) and the depth (+0x94; over 8 a fatal message); the cells' table (+0x54, two bytes each) all 0xff. Its callers
   ignore the eax it leaves */
void THISCALL (space_setBy)(u8 *space, const u32 *mn, const u32 *mx, int nx, int ny, int nz, u32 a, u32 b, int depth)
{
#define FIELD(type, offset) GAME_VAR(type, space + (offset))
	space_resetPlanes(space);
	space_resetNodes(space);
	space_resetUnits(space);
	space_resetBlocks(space);
	for (int i = 0; i < 3; i++)
		FIELD(u32, 0x5c + i * 4) = mn[i];
	FIELD(u32, 0x68) = mx[0];
	FIELD(u32, 0x6c) = mx[1];
	FIELD(int, 0x78) = ny;
	FIELD(u32, 0x70) = mx[2];
	FIELD(int, 0x74) = nx;
	FIELD(int, 0x7c) = nz;
	int cells = FIELD(int, 0x58) = nx * ny * nz;
	if (cells <= 0)
		sys_fatalErrorN((char *)0xae2ed0, (const char *)0x4c79f4, nx, ny, nz);
	else if (cells > FIELD(int, 0x50))
		sys_fatalErrorN((char *)0xae2ed0, (const char *)0x4c79bc, nx, ny, nz, cells, FIELD(int, 0x50));
	FIELD(u32, 0x90) = b;
	FIELD(u32, 0x8c) = a;
	FIELD(int, 0x94) = depth;
	FIELD(float, 0x80) = (float)(((long double)FIELD(float, 0x70) - FIELD(float, 0x64)) / FIELD(int, 0x74));
	FIELD(float, 0x84) = (float)(((long double)FIELD(float, 0x68) - FIELD(float, 0x5c)) / FIELD(int, 0x78));
	FIELD(float, 0x88) = (float)(((long double)FIELD(float, 0x6c) - FIELD(float, 0x60)) / FIELD(int, 0x7c));
	if (depth > 8)
		sys_fatalErrorN((char *)0xae2ed0, (const char *)0x4c7980, depth, 8);
	memset(FIELD(void *, 0x54), 0xff, FIELD(u32, 0x50) * 2);
#undef FIELD
}

/* 0x4813e0 (thiscall on the space): sized for the pools: planes (0xac bytes each, +0x10 of them), nodes (0x10, +0x20),
   units (0x14, +0x30), blocks (0x50, +0x40) and the cells' table (2 bytes, +0x50) laid out in that order in one block
   (+8, its size +4; allocated and owned, +0xc 1, without memory given, else the memory given, the caller's size checked:
   fatal messages); each pool's start kept twice (+0x14 / +0x18, +0x24 / +0x28, +0x34 / +0x38, +0x44 / +0x48), the
   table's (+0x54) filled with 0xff, then the pools emptied. Its caller ignores the eax it leaves */
void THISCALL (space_initBy)(u8 *space, int planes, int nodes, int units, int blocks, int cells, void *mem, int size)
{
#define FIELD(type, offset) GAME_VAR(type, space + (offset))
	load_4813b0(space);
	FIELD(int, 0x30) = units;
	FIELD(int, 0x40) = blocks;
	FIELD(int, 0x10) = planes;
	FIELD(int, 0x20) = nodes;
	FIELD(int, 0x50) = cells;
	int need = FIELD(int, 4) = planes * 0xac + nodes * 0x10 + units * 0x14 + blocks * 0x50 + cells * 2;
	if (!mem) {
		FIELD(void *, 8) = operator_new(need);
		if (!FIELD(void *, 8))
			sys_fatalError((char *)0xae2ed0, (const char *)0x4c4cec, FIELD(int, 4));
		FIELD(int, 0xc) = 1;
	} else {
		if (size < need)
			sys_fatalErrorN((char *)0xae2ed0, (const char *)0x4c4cbc, need, size);
		FIELD(void *, 8) = mem;
	}
	u8 *block = FIELD(u8 *, 8);
	FIELD(u8 *, 0x14) = FIELD(u8 *, 0x18) = block;
	int at = FIELD(int, 0x10) * 0xac;
	FIELD(u8 *, 0x24) = block + at;
	at += FIELD(int, 0x20) * 0x10;
	FIELD(u8 *, 0x28) = FIELD(u8 *, 0x24);
	FIELD(u8 *, 0x34) = block + at;
	at += FIELD(int, 0x30) * 0x14;
	FIELD(u8 *, 0x38) = FIELD(u8 *, 0x34);
	FIELD(u8 *, 0x44) = FIELD(u8 *, 0x48) = block + at;
	FIELD(u8 *, 0x54) = block + FIELD(int, 0x40) * 0x50 + at;
	memset(FIELD(void *, 0x54), 0xff, FIELD(u32, 0x50) * 2);
	space_resetPlanes(space);
	space_resetNodes(space);
	space_resetUnits(space);
	space_resetBlocks(space);
#undef FIELD
}

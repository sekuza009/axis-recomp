/* space_pools.c: the collision space's pools of planes, nodes and blocks. A pool is a count, an array of records
   and a free list (head, then a used count, at +8 / +0xc from the count); emptying it clears every record, links
   them both ways (prev, then next, at the same offset in each) and puts the whole array on the free list. */
#include "../game.h"

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

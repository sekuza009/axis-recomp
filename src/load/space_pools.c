/* space_pools.c: the collision space's pools of planes, nodes and blocks. A pool is a count, an array of records
   and a free list (head, then a used count, at +8 / +0xc from the count); emptying it clears every record, links
   them both ways (prev, then next, at the same offset in each) and puts the whole array on the free list. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

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

static int THISCALL clear_plane(void *r) { return collisionPlane_clear(r); }
static int THISCALL clear_node(void *r) { return spaceNode_clear(r); }
static int THISCALL clear_block(void *r) { return spaceBlock_clear(r); }

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
		GAME_FN(sys_fatalError, 0x46c710, void, void *, const char *, int, int, int, int, int, int, int, int)(   /* sys_fatalError */
			(void *)OBJ(g_logCollisionVolume), (const char *)RELOC(format), FIELD(int, space, 0x1c), FIELD(int, space, 0x10), FIELD(int, space, 0x2c),
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
static int THISCALL clear_unit(void *r) { spaceSlot_clear(r); return 0; }

/* 0x4815c0, 0x4816c0, 0x4817f0: a free plane, node or unit */
void *THISCALL (space_getNextFreePlanePtr)(void *space) { return take_free(space, 0x18, 0xa4, 0xa0, 0x1c, clear_plane, STR(0x4c7818, "not enoush free plane-getNextFreePlan...")); }
void *THISCALL (space_getNextFreeNodePtr)(void *space) { return take_free(space, 0x28, 0xc, 8, 0x2c, clear_node, STR(0x4c7874, "not enoush free node-getNextFreeNodeP...")); }
void *THISCALL (space_getNextFreeUnitPtr)(void *space) { return take_free(space, 0x38, 0x10, 0xc, 0x3c, clear_unit, STR(0x4c78cc, "not enoush free unit-getNextFreeUnitP...")); }

/* 0x4818e0 (thiscall on the space): a block taken from the free list (+0x48; its next at +0x4c, the new head's back
   link +0x48 cleared), counted (+0x4c), reset (spaceBlock_clear) and given the bounds mn / mx (three dwords each);
   returns it. With none free, a fatal message with the pools' sizes and 0 */
void *THISCALL (space_getNextFreeBlockPtrBy)(u8 *space, const u32 *mn, const u32 *mx)
{
#define FIELD(type, offset) GAME_VAR(type, space + (offset))
	u32 *block = FIELD(u32 *, 0x48);
	if (!block) {
		GAME_FN(sys_fatalError, 0x46c710, void, char *, const char *, int, int, int, int, int, int, int, int)((char *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c7924, "not enoush free block-getNextFreeBloc..."),
			FIELD(int, 0x1c), FIELD(int, 0x10), FIELD(int, 0x2c), FIELD(int, 0x20), FIELD(int, 0x3c), FIELD(int, 0x30), FIELD(int, 0x4c), FIELD(int, 0x40));
		return 0;
	}
	u32 *next = (u32 *)RELOC(block[0x4c / 4]);
	if (next) {
		FIELD(u32 *, 0x48) = next;
		next[0x48 / 4] = 0;
	} else
		FIELD(u32 *, 0x48) = 0;
	FIELD(int, 0x4c)++;
	spaceBlock_clear(block);
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
void THISCALL (space_addUnitPlanes)(void *space, u32 id, u8 *owner, u32 part, u32 i0, u32 i1, u32 i2, u32 v0, u32 v1, u32 v2)
{
#define AT(type, p, offset) GAME_VAR(type, (u8 *)RELOC(p) + (offset))
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
		sys_fatalErrorN((char *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c79f4, "non-zero size required(%dx%dx%d)-setBy()"), nx, ny, nz);
	else if (cells > FIELD(int, 0x50))
		sys_fatalErrorN((char *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c79bc, "blockIndexTable overflow((%dx%dx%d=%d..."), nx, ny, nz, cells, FIELD(int, 0x50));
	FIELD(u32, 0x90) = b;
	FIELD(u32, 0x8c) = a;
	FIELD(int, 0x94) = depth;
	FIELD(float, 0x80) = (float)(((long double)FIELD(float, 0x70) - FIELD(float, 0x64)) / FIELD(int, 0x74));
	FIELD(float, 0x84) = (float)(((long double)FIELD(float, 0x68) - FIELD(float, 0x5c)) / FIELD(int, 0x78));
	FIELD(float, 0x88) = (float)(((long double)FIELD(float, 0x6c) - FIELD(float, 0x60)) / FIELD(int, 0x7c));
	if (depth > 8)
		sys_fatalErrorN((char *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c7980, "blockRecursionLimit overflow(%d/%d)-s..."), depth, 8);
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
	CollisionVolume_release(space);
	FIELD(int, 0x30) = units;
	FIELD(int, 0x40) = blocks;
	FIELD(int, 0x10) = planes;
	FIELD(int, 0x20) = nodes;
	FIELD(int, 0x50) = cells;
	int need = FIELD(int, 4) = planes * 0xac + nodes * 0x10 + units * 0x14 + blocks * 0x50 + cells * 2;
	if (!mem) {
		FIELD(void *, 8) = operator_new(need);
		if (!FIELD(void *, 8))
			sys_fatalError((char *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c4cec, "insufficient memory for dataMemory(%d..."), FIELD(int, 4));
		FIELD(int, 0xc) = 1;
	} else {
		if (size < need)
			sys_fatalErrorN((char *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c4cbc, "reserved dataMemory overflow(%d/%d) -..."), need, size);
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

/* 0x482e30 (thiscall on the collision space): a sphere of radius r swept from pos along vel in whole steps of length
   step (n = |vel| / step; the walk down the nodes, space_collideAt, from pos + i steps, i = 0 .. n - 1), then
   from pos + n steps over what is left of vel. 1 at the first hit, else what the last walk found (1 or 0); the
   outputs are the walks' */
int THISCALL (space_testSphere)(void *grid, u32 r, const float *pos, const float *vel, float step, u32 k, u32 outPos,
                                u32 outVel, u32 outDist, u32 outPlane, u32 axis, u32 subs, u32 nsubs)
{
	float dir[3], d[3], p[3];
	memcpy(dir, vel, sizeof dir);
	int n = ftol(fdiv_m(Vec3_normalize(dir), &step));
	for (int c = 0; c < 3; c++)
		d[c] = f32(fmul_m(fld_m(&dir[c]), &step));
	for (int i = 0; i < n; i++) {
		long double li = i;
		float x = f32(fld_m(&d[0]) * li), y = f32(fld_m(&d[1]) * li);
		p[0] = f32(fadd_m(fld_m(&x), &pos[0]));
		p[1] = f32(fadd_m(fld_m(&y), &pos[1]));
		p[2] = f32(fadd_m(fmul_m(li, &d[2]), &pos[2]));
		if (space_collideAt(grid, r, p, d, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) == 1)
			return 1;
	}
	long double ln = n;
	float x = f32(fmul_m(ln, &d[0])), y = f32(fld_m(&d[1]) * ln);
	p[0] = f32(fadd_m(fld_m(&x), &pos[0]));
	p[1] = f32(fadd_m(fld_m(&y), &pos[1]));
	p[2] = f32(fadd_m(fmul_m(ln, &d[2]), &pos[2]));
	float rest[3];
	rest[0] = f32(fsub_m(fld_m(&vel[0]), &x));
	rest[1] = f32(fsub_m(fld_m(&vel[1]), &y));
	rest[2] = f32(fld_m(&vel[2]) - fmul_m(ln, &d[2]));
	return space_collideAt(grid, r, p, rest, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) == 1;
}

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* 0x482aa0 (thiscall on the collision space): the leaf of the space's octrees at pos + vel (written to outPos) has its
   triangles tested (space_collideUnit, its answer also kept at +0x98). The end point must be inside the space's box
   (+0x5c low, +0x68 high) widened by the margin (+0x8c); its cell (z, x, y: sizes +0x80, +0x84, +0x88; +0x74, +0x78,
   +0x7c of them, each index at most the last) names a root node (shorts at +0x54; 0xffff none) among the 0x50-byte
   nodes (+0x44). From the cell's box the walk goes down into the eighth (children +0x28 .., x upper +4, z upper +8,
   y upper +0x10) holding the point until a leaf (+0x24 0). 0 when there is none. The x middle is compared at full
   precision, the others as floats, as the original has them */
int THISCALL (space_collideAt)(u8 *grid, u32 r, const float *pos, const float *vel, u32 k, float *outPos,
                                      u32 outVel, u32 outDist, u32 outPlane, u32 axis, u32 subs, u32 nsubs)
{
	if (FIELD(int, grid, 0x74) <= 0 || FIELD(int, grid, 0x78) <= 0 || FIELD(int, grid, 0x7c) <= 0)
		return 0;
	float to[3];
	for (int c = 0; c < 3; c++)
		to[c] = f32(fadd_m(fld_m(&pos[c]), &vel[c]));
	memcpy(outPos, to, sizeof to);
	const float *low = (const float *)(grid + 0x5c), *high = (const float *)(grid + 0x68);
	const float *margin = (const float *)(grid + 0x8c);
	const float *size_z = (const float *)(grid + 0x80), *size_x = (const float *)(grid + 0x84), *size_y = (const float *)(grid + 0x88);
	for (int c = 0; c < 3; c++)
		if (fsub_m(fld_m(&low[c]), margin) >= outPos[c])
			return 0;
	for (int c = 0; c < 3; c++)
		if (!(fadd_m(fld_m(&high[c]), margin) > outPos[c]))
			return 0;
	int nz = FIELD(int, grid, 0x74), nx = FIELD(int, grid, 0x78), ny = FIELD(int, grid, 0x7c);
	int cz = ftol(fdiv_m(fsub_m(fld_m(&outPos[2]), &low[2]), size_z));
	if (cz > nz - 1)
		cz = nz - 1;
	int cx = ftol(fdiv_m(fsub_m(fld_m(&outPos[0]), &low[0]), size_x));
	if (cx > nx - 1)
		cx = nx - 1;
	int cy = ftol(fdiv_m(fsub_m(fld_m(&outPos[1]), &low[1]), size_y));
	if (cy > ny - 1)
		cy = ny - 1;
	u16 root = FIELD(u16 *, grid, 0x54)[(nz * cy + cz) * nx + cx];
	if (root == 0xffff)
		return 0;
	u8 *node = (u8 *)array_recordAt(root, FIELD(int, grid, 0x44), 0x50);
	float box[6];   /* low x, y, z, then high */
	float by = f32(fmul_m((long double)cy, size_y)), bz = f32(fmul_m((long double)cz, size_z));
	box[0] = f32(fadd_m(fmul_m((long double)cx, size_x), &low[0]));
	box[1] = f32(fadd_m(fld_m(&by), &low[1]));
	box[2] = f32(fadd_m(fld_m(&bz), &low[2]));
	box[3] = f32(fadd_m(fld_m(&box[0]), size_x));
	box[4] = f32(fadd_m(fld_m(&box[1]), size_y));
	box[5] = f32(fadd_m(fld_m(&box[2]), size_z));
	const float *half = (const float *)ADDR(k_0_5f);
	while (node) {
		if (!FIELD(int, node, 0x24))
			return FIELD(int, grid, 0x98) = space_collideUnit(node, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs);
		long double mx = fmul_m(fadd_m(fld_m(&box[3]), &box[0]), half);
		float my = f32(fmul_m(fadd_m(fld_m(&box[4]), &box[1]), half));
		float mz = f32(fmul_m(fadd_m(fld_m(&box[5]), &box[2]), half));
		int xu = !(mx > outPos[0]), yu = outPos[1] >= my, zu = outPos[2] >= mz;
		node = FIELD(u8 *, node, 0x28 + xu * 4 + zu * 8 + yu * 0x10);
		box[xu ? 0 : 3] = f32(mx);
		box[yu ? 1 : 4] = my;
		box[zu ? 2 : 5] = mz;
	}
	return 0;
}

/* a new block for octant i of the box low .. high (x by bit 0, z by bit 1, y by bit 2), sized as the original works
   it out (the x half kept at full precision) */
static u8 *make_octant(u8 *space, const float *low, const float *high, int i)
{
	const float *half = (const float *)ADDR(k_0_5f);
	int bx = i % 2, by = i / 4, bz = i / 2 % 2;
	float box[6];
	box[0] = f32(fadd_m(fmul_m(fsub_m(fld_m(&high[0]), &low[0]) * bx, half), &low[0]));
	box[1] = f32(fadd_m(fmul_m(fsub_m(fld_m(&high[1]), &low[1]) * by, half), &low[1]));
	box[2] = f32(fadd_m(fmul_m(fsub_m(fld_m(&high[2]), &low[2]) * bz, half), &low[2]));
	long double dx = fsub_m(fld_m(&high[0]), &low[0]);
	float dy = f32(fsub_m(fld_m(&high[1]), &low[1])), dz = f32(fsub_m(fld_m(&high[2]), &low[2]));
	float hy = f32(fmul_m(fld_m(&dy), half)), hz = f32(fmul_m(fld_m(&dz), half));
	box[3] = f32(fadd_m(fmul_m(dx, half), &box[0]));
	box[4] = f32(fadd_m(fld_m(&box[1]), &hy));
	box[5] = f32(fadd_m(fld_m(&box[2]), &hz));
	return space_getNextFreeBlockPtrBy(space, box, box + 3);
}

/* a child block that ended up with no items and no children given back (space_freeBlock) and forgotten */
static void drop_if_empty(u8 *space, u8 **child)
{
	if (FIELD(int, *child, 0x1c) <= 0 && FIELD(int, *child, 0x24) == 0) {
		space_freeBlock(space, *child);
		*child = NULL;
	}
}

/* 0x481ae0 (thiscall on the collision space): item put into block's part of the octree, depth levels more allowed.
   Nothing (0) when it misses the block's box (space_itemMeetsBox, widened by the margin +0x8c) or is already first in its
   list. A leaf (+0x24 0) gets a node for it (item, block; linked in first at +0x18, +0x1c counting them); holding more
   than +0x90 with depth left it splits: eight child blocks (+0x28 ..), every item put into each of them a level
   down, its nodes freed (space_freeNode), the children left empty dropped. An inner block puts the item into each
   child (made when missing) a level down, dropping those left empty. Otherwise 1 */
int THISCALL (space_insertItem)(u8 *space, u8 *block, u8 *item, int depth)
{
	const float *low = (const float *)block, *high = (const float *)(block + 0xc);
	if (!space_itemMeetsBox(item, low, high, FIELD(u32, space, 0x8c)))
		return 0;
	u32 *first = FIELD(u32 *, block, 0x18);
	if (first && first[0] == (u32)item)
		return 0;
	u8 **child = (u8 **)(block + 0x28);
	if (FIELD(int, block, 0x24)) {
		for (int i = 0; i < 8; i++) {
			if (!child[i])
				child[i] = make_octant(space, low, high, i);
			space_insertItem(space, child[i], item, depth - 1);
			drop_if_empty(space, &child[i]);
		}
		return 1;
	}
	u32 *node = space_getNextFreeNodePtr(space);
	node[0] = (u32)item;
	node[1] = (u32)block;
	node[3] = FIELD(u32, block, 0x18);
	if (FIELD(u32 *, block, 0x18))
		FIELD(u32 *, block, 0x18)[2] = (u32)node;
	FIELD(u32 *, block, 0x18) = node;
	if (++FIELD(int, block, 0x1c) <= FIELD(int, space, 0x90) || depth <= 0)
		return 1;
	for (int i = 0; i < 8; i++) {
		child[i] = make_octant(space, low, high, i);
		FIELD(int, block, 0x24) = 1;
	}
	for (u32 *n = FIELD(u32 *, block, 0x18); n;) {
		for (int j = 0; j < 8; j++)
			space_insertItem(space, child[j], (void *)RELOC(n[0]), depth - 1);
		u32 *next = (u32 *)RELOC(n[3]);
		space_freeNode(space, n);
		n = next;
	}
	FIELD(u32, block, 0x18) = 0;
	FIELD(int, block, 0x1c) = 0;
	for (int j = 0; j < 8; j++)
		drop_if_empty(space, &child[j]);
	return 1;
}

/* 0x481eb0 (thiscall on the collision space): a triangle (v0, v1, v2) of a unit put into the space: nothing (0) when
   its box misses the space's (+0x5c .. +0x70, widened by the margin +0x8c). Else a plane record (from the pool, set up
   by collisionTri_setup), and every grid cell its widened box covers (z, x, y as in space_collideAt) that the
   triangle really meets (space_itemMeetsBox) gets it into its octree (space_insertItem, depth +0x94; the cell's root block made
   when it has none). Returns the plane */
u8 *THISCALL (space_buildPlanes)(u8 *space, u32 id, const float *v0, const float *v1, const float *v2, u32 unit, u32 part,
                                 u32 i0, u32 i1, u32 i2)
{
	float low[3], high[3];
	memcpy(low, v0, sizeof low);
	memcpy(high, v0, sizeof high);
	const float *others[2] = { v1, v2 };
	for (int k = 0; k < 2; k++)
		for (int c = 0; c < 3; c++) {
			if (others[k][c] > high[c])
				((u32 *)high)[c] = ((const u32 *)others[k])[c];
			if (!(others[k][c] >= low[c]))
				((u32 *)low)[c] = ((const u32 *)others[k])[c];
		}
	const float *grid_low = (const float *)(space + 0x5c), *grid_high = (const float *)(space + 0x68);
	const float *margin = (const float *)(space + 0x8c);
	const float *size_z = (const float *)(space + 0x80), *size_x = (const float *)(space + 0x84), *size_y = (const float *)(space + 0x88);
	for (int c = 0; c < 3; c++)
		if (!(fadd_m(fld_m(&grid_high[c]), margin) > low[c]))
			return 0;
	for (int c = 0; c < 3; c++)
		if (fsub_m(fld_m(&grid_low[c]), margin) >= high[c])
			return 0;
	u8 *plane = space_getNextFreePlanePtr(space);
	collisionTri_setup(plane, id, v0, v1, v2, unit, part, i0, i1, i2);
	int z0 = ftol(fdiv_m(fsub_m(fsub_m(fld_m(&low[2]), margin), &grid_low[2]), size_z));
	if (z0 < 0)
		z0 = 0;
	int z1 = ftol(fdiv_m(fsub_m(fadd_m(fld_m(&high[2]), margin), &grid_low[2]), size_z));
	if (z1 > FIELD(int, space, 0x74) - 1)
		z1 = FIELD(int, space, 0x74) - 1;
	int x0 = ftol(fdiv_m(fsub_m(fsub_m(fld_m(&low[0]), margin), &grid_low[0]), size_x));
	if (x0 < 0)
		x0 = 0;
	int x1 = ftol(fdiv_m(fsub_m(fadd_m(fld_m(&high[0]), margin), &grid_low[0]), size_x));
	if (x1 > FIELD(int, space, 0x78) - 1)
		x1 = FIELD(int, space, 0x78) - 1;
	int y0 = ftol(fdiv_m(fsub_m(fsub_m(fld_m(&low[1]), margin), &grid_low[1]), size_y));
	if (y0 < 0)
		y0 = 0;
	int y1 = ftol(fdiv_m(fsub_m(fadd_m(fld_m(&high[1]), margin), &grid_low[1]), size_y));
	if (y1 > FIELD(int, space, 0x7c) - 1)
		y1 = FIELD(int, space, 0x7c) - 1;
	for (int y = y0; y <= y1; y++)
		for (int z = z0; z <= z1; z++) {
			float fy = f32(y), fz = f32(z);   /* (the original keeps these two as floats) */
			for (int x = x0; x <= x1; x++) {
				float box[6];
				box[0] = f32(fadd_m(fmul_m(x, size_x), &grid_low[0]));
				box[1] = f32(fadd_m(fmul_m(fld_m(&fy), size_y), &grid_low[1]));
				box[2] = f32(fadd_m(fmul_m(fld_m(&fz), size_z), &grid_low[2]));
				box[3] = f32(fadd_m(fld_m(&box[0]), size_x));
				box[4] = f32(fadd_m(fld_m(&box[1]), size_y));
				box[5] = f32(fadd_m(fld_m(&box[2]), size_z));
				if (space_itemMeetsBox(plane, box, box + 3, *(const u32 *)margin) != 1)
					continue;
				int cell = (FIELD(int, space, 0x74) * y + z) * FIELD(int, space, 0x78) + x;
				if (FIELD(u16 *, space, 0x54)[cell] == 0xffff) {
					u8 *block = space_getNextFreeBlockPtrBy(space, box, box + 3);
					FIELD(u16 *, space, 0x54)[cell] = (u16)array_indexOf(block, FIELD(int, space, 0x44), 0x50);
				}
				space_insertItem(space, FIELD(u8 *, space, 0x44) + FIELD(u16 *, space, 0x54)[cell] * 0x50, plane, FIELD(int, space, 0x94));
			}
		}
	return plane;
}

/* How the original works out a vertex through the unit's matrix (column-major): each row is three products summed
   in turn, then the translation, and each product loads one operand and multiplies by the other from memory. The
   order differs from one place to the next, so each is written out: per row the three products, each as the operand
   loaded and the one multiplied by (0 .. 15: the matrix element; V0 .. V2: the vertex's x, y, z) */
#define V0 16
#define V1 17
#define V2 18
typedef const u8 Rows[3][3][2];
static Rows k_fanFirst  = { { { V2, 8 }, { 4, V1 }, { V0, 0 } }, { { V2, 9 }, { V1, 5 }, { V0, 1 } }, { { V2, 10 }, { V1, 6 }, { 2, V0 } } };
static Rows k_evenFirst = { { { 4, V1 }, { V0, 0 }, { V2, 8 } }, { { V0, 1 }, { V2, 9 }, { V1, 5 } }, { { 10, V2 }, { 6, V1 }, { 2, V0 } } };
static Rows k_evenNext  = { { { V0, 0 }, { 4, V1 }, { V2, 8 } }, { { V2, 9 }, { V1, 5 }, { V0, 1 } }, { { V2, 10 }, { V1, 6 }, { V0, 2 } } };
static Rows k_evenLast  = { { { 4, V1 }, { 0, V0 }, { V2, 8 } }, { { 1, V0 }, { V2, 9 }, { V1, 5 } }, { { 10, V2 }, { 6, V1 }, { 2, V0 } } };
static Rows k_oddFirst  = { { { 4, V1 }, { V2, 8 }, { 0, V0 } }, { { 1, V0 }, { V2, 9 }, { V1, 5 } }, { { V2, 10 }, { V1, 6 }, { 2, V0 } } };
static Rows k_oddNext   = { { { 4, V1 }, { V2, 8 }, { 0, V0 } }, { { V2, 9 }, { V1, 5 }, { V0, 1 } }, { { 2, V0 }, { V2, 10 }, { V1, 6 } } };
static Rows k_oddLast   = { { { 4, V1 }, { 0, V0 }, { V2, 8 } }, { { V0, 1 }, { V2, 9 }, { V1, 5 } }, { { 10, V2 }, { 6, V1 }, { 2, V0 } } };
static Rows k_listFirst = { { { 4, V1 }, { 0, V0 }, { V2, 8 } }, { { 1, V0 }, { V2, 9 }, { V1, 5 } }, { { 10, V2 }, { 6, V1 }, { 2, V0 } } };
static Rows k_listNext  = { { { 4, V1 }, { V2, 8 }, { 0, V0 } }, { { 1, V0 }, { V2, 9 }, { V1, 5 } }, { { V2, 10 }, { V1, 6 }, { 2, V0 } } };
static Rows k_listLast  = { { { V2, 8 }, { 4, V1 }, { 0, V0 } }, { { V0, 1 }, { V2, 9 }, { V1, 5 } }, { { 2, V0 }, { 10, V2 }, { 6, V1 } } };

static void through(float *out, const float *m, const float *v, Rows rows)
{
	for (int r = 0; r < 3; r++) {
		long double sum = 0;
		for (int t = 0; t < 3; t++) {
			const float *a = rows[r][t][0] >= V0 ? &v[rows[r][t][0] - V0] : &m[rows[r][t][0]];
			const float *b = rows[r][t][1] >= V0 ? &v[rows[r][t][1] - V0] : &m[rows[r][t][1]];
			long double p = fmul_m(fld_m(a), b);
			sum = t ? sum + p : p;
		}
		out[r] = f32(fadd_m(sum, &m[12 + r]));
	}
}
#undef V0
#undef V1
#undef V2

/* 0x4823c0 (thiscall on the collision space): a unit for shape (from the pool, its id first) with every part not
   flagged 0x20 (flag 1: its triangles' id 0x10, else 0) turned into triangles: its primitives (12 bytes: type, index
   count, indices) as lists (4), strips (5) or fans (6) of its vertices (+0x50) through the matrix (the current GL
   modelview when none is given), each added with space_addUnitPlanes. Returns the unit */
u32 *THISCALL (space_buildUnits)(u8 *space, u32 id, u8 *shape, const float *matrix)
{
	float own[16];
	if (!matrix) {
		glGetFloatv(0xba6, own);   /* GL_MODELVIEW_MATRIX */
		matrix = own;
	}
	u32 *unit = space_getNextFreeUnitPtr(space);
	unit[0] = id;
	for (int i = 0; i < FIELD(int, shape, 0x10); i++) {
		u8 *part = FIELD(u8 *, shape, 0x14) + i * 0x80;
		if (part[0] & 0x20)
			continue;
		u32 kind = part[0] & 1 ? 0x10 : 0;
		const float *verts = FIELD(const float *, part, 0x50);
		for (int j = 0; j < FIELD(int, part, 0x60); j++) {
			u8 *prim = FIELD(u8 *, part, 0x64) + j * 0xc;
			int n = FIELD(int, prim, 4);
#define IDX(k) FIELD(u32, FIELD(u8 *, prim, 8), (k) * 4)
#define VERT(k) (FIELD(const float *, part, 0x50) + IDX(k) * 3)
			float a[3], b[3], c[3];
			switch (FIELD(int, prim, 0)) {
			case 6:   /* a fan */
				for (int k = 2; k < n; k++) {
					u32 i0 = IDX(0);
					through(a, matrix, verts + i0 * 3, k_fanFirst);
					u32 i1 = IDX(k - 1);
					space_transformPoint(b, matrix, VERT(k - 1));
					u32 i2 = IDX(k);
					space_transformPoint(c, matrix, VERT(k));
					space_addUnitPlanes(space, kind, unit, i, i0, i1, i2, a, b, c);
				}
				break;
			case 5:   /* a strip */
				for (int k = 2; k < n; k++) {
					u32 i0 = IDX(k - 2), i1, i2;
					if (k % 2 == 0) {
						through(a, matrix, VERT(k - 2), k_evenFirst);
						i1 = IDX(k - 1);
						through(b, matrix, VERT(k - 1), k_evenNext);
						i2 = IDX(k);
						through(c, matrix, VERT(k), k_evenLast);
					} else {
						through(a, matrix, VERT(k - 2), k_oddFirst);
						i2 = IDX(k);
						through(c, matrix, VERT(k), k_oddLast);
						i1 = IDX(k - 1);
						through(b, matrix, VERT(k - 1), k_oddNext);
					}
					space_addUnitPlanes(space, kind, unit, i, i0, i1, i2, a, b, c);
				}
				break;
			case 4:   /* a list */
				for (int k = 0; k < n; k += 3) {
					u32 i0 = IDX(k);
					through(a, matrix, VERT(k), k_listFirst);
					u32 i1 = IDX(k + 1);
					through(b, matrix, VERT(k + 1), k_listNext);
					u32 i2 = IDX(k + 2);
					through(c, matrix, VERT(k + 2), k_listLast);
					space_addUnitPlanes(space, kind, unit, i, i0, i1, i2, a, b, c);
				}
				break;
			}
#undef IDX
#undef VERT
		}
	}
	return unit;
}

/* a coordinate's cell along one axis (from the space's low corner, by the cell size), kept within 0 .. n - 1 */
static int cell_of(const float *p, const float *low, const float *size, int n)
{
	int c = ftol(fdiv_m(fsub_m(fld_m(p), low), size));
	return c < 0 ? 0 : c > n - 1 ? n - 1 : c;
}

/* the boundary between cells c - 1 and c along an axis: c x size + low, at full precision */
static long double cell_edge(int c, const float *size, const float *low)
{
	return fadd_m(fmul_m((long double)c, size), low);
}

/* 0x483060 (thiscall on the collision space): the segment p0 .. p1 through the grid's cells (z, x, y: sizes +0x80,
   +0x84, +0x88; +0x74, +0x78, +0x7c of them), cell by cell from p0's towards p1's: y slabs, within each the z slabs,
   within those the x cells, the segment clipped to each (the y and x clips through a parameter rounded to a float,
   the z clip at full precision, as the original has them). Each cell with a root node (shorts at +0x54; 0xffff none)
   has its octree traced (space_traceUnit, the 0x50-byte nodes at +0x44); the first that reports a hit is the
   answer. 0 when nothing is hit */
int THISCALL (space_traceNodes)(u8 *space, const float *p0, const float *p1, u32 hit, u32 subs, u32 nsubs)
{
	int nz = FIELD(int, space, 0x74), nx = FIELD(int, space, 0x78), ny = FIELD(int, space, 0x7c);
	if (nz <= 0 || nx <= 0 || ny <= 0)
		return 0;
	const float *low = (const float *)(space + 0x5c);
	const float *size_z = (const float *)(space + 0x80), *size_x = (const float *)(space + 0x84), *size_y = (const float *)(space + 0x88);
	int z0 = cell_of(&p0[2], &low[2], size_z, nz), x0 = cell_of(&p0[0], &low[0], size_x, nx), y0 = cell_of(&p0[1], &low[1], size_y, ny);
	int z1 = cell_of(&p1[2], &low[2], size_z, nz), x1 = cell_of(&p1[0], &low[0], size_x, nx), y1 = cell_of(&p1[1], &low[1], size_y, ny);
	int step_y = y0 > y1 ? -1 : 1, step_z = z0 > z1 ? -1 : 1, step_x = x0 > x1 ? -1 : 1;
	float d[3];
	for (int c = 0; c < 3; c++)
		d[c] = f32(fsub_m(fld_m(&p1[c]), &p0[c]));
	for (int cy = y0;; cy += step_y) {
		float a[3], e[3], da[3];   /* the y slab's part of the segment */
		for (int end = 0; end < 2; end++) {
			float *q = end ? e : a;
			if (cy == (end ? y1 : y0))
				memcpy(q, end ? p1 : p0, 12);
			else {
				long double b = cell_edge((step_y > 0) == end ? cy + 1 : cy, size_y, &low[1]);
				float t = f32(fdiv_m(fsub_m(b, &p0[1]), &d[1]));
				q[0] = f32(fadd_m(fmul_m(fld_m(&d[0]), &t), &p0[0]));
				q[1] = f32(b);
				q[2] = f32(fadd_m(fmul_m(fld_m(&d[2]), &t), &p0[2]));
			}
		}
		for (int c = 0; c < 3; c++)
			da[c] = f32(fsub_m(fld_m(&e[c]), &a[c]));
		for (int cz = z0;; cz += step_z) {
			float a2[3], e2[3], db[3];   /* the z slab's part of that */
			for (int end = 0; end < 2; end++) {
				float *q = end ? e2 : a2;
				if (cz == (end ? z1 : z0))
					memcpy(q, end ? e : a, 12);
				else {
					long double b = cell_edge((step_z > 0) == end ? cz + 1 : cz, size_z, &low[2]);
					long double t = fdiv_m(fsub_m(b, &a[2]), &da[2]);
					q[0] = f32(fadd_m(fld_m(&da[0]) * t, &a[0]));
					q[1] = f32(fadd_m(fld_m(&da[1]) * t, &a[1]));
					q[2] = f32(b);
				}
			}
			for (int c = 0; c < 3; c++)
				db[c] = f32(fsub_m(fld_m(&e2[c]), &a2[c]));
			for (int cx = x0;; cx += step_x) {
				float a3[3], e3[3], dist;   /* the cell's part */
				for (int end = 0; end < 2; end++) {
					float *q = end ? e3 : a3;
					if (cx == (end ? x1 : x0))
						memcpy(q, end ? e2 : a2, 12);
					else {
						long double b = cell_edge((step_x > 0) == end ? cx + 1 : cx, size_x, &low[0]);
						float t = f32(fdiv_m(fsub_m(b, &a2[0]), &db[0]));
						q[0] = f32(b);
						q[1] = f32(fadd_m(fmul_m(fld_m(&db[1]), &t), &a2[1]));
						q[2] = f32(fadd_m(fmul_m(fld_m(&db[2]), &t), &a2[2]));
					}
				}
				u16 root = FIELD(u16 *, space, 0x54)[(cy * FIELD(int, space, 0x74) + cz) * FIELD(int, space, 0x78) + cx];
				if (root != 0xffff) {
					int r = space_traceUnit(FIELD(u8 *, space, 0x44) + root * 0x50, a3, e3, hit, &dist, subs, nsubs);
					if (r)
						return r;
				}
				if (cx == x1)
					break;
			}
			if (cz == z1)
				break;
		}
		if (cy == y1)
			return 0;
	}
}

/* which half of the node (0 or 1) coordinate p falls in along an axis */
static int half_of(const float *p, const float *low, const float *half)
{
	int i = ftol(fdiv_m(fsub_m(fld_m(p), low), half));
	return i < 0 ? 0 : i > 1 ? 1 : i;
}

/* where the segment from + d t meets the plane (n halves along the axis from low): the other two coordinates as
   (d t) + from, t rounded to a float or not as the original keeps it */
static void cut_at(float *out, const float *from, const float *d, int n, const float *half, const float *low, int axis, int round_t)
{
	long double plane = fadd_m(fmul_m((long double)n, half), low);
	long double t = fdiv_m(fsub_m(plane, &from[axis]), &d[axis]);
	float tf = f32(t);
	for (int a = 0; a < 3; a++)
		if (a != axis)
			out[a] = f32(fadd_m(round_t ? fmul_m(fld_m(&d[a]), &tf) : fld_m(&d[a]) * t, &from[a]));
	out[axis] = f32(plane);
}

/* p through the 4 x 3 part of m: per row the y and z terms first, or (rows 1 and 2 with yx set) y and x, the last
   term then, then the translation */
static void through_m(float *out, const float *m, const float *p, int yx)
{
	for (int r = 0; r < 3; r++) {
		long double tx = fmul_m(fld_m(&m[r]), &p[0]), ty = fmul_m(fld_m(&m[4 + r]), &p[1]), tz = fmul_m(fld_m(&m[8 + r]), &p[2]);
		out[r] = f32(fadd_m(yx && r ? (ty + tx) + tz : (ty + tz) + tx, &m[12 + r]));
	}
}

/* 0x4809f0 (thiscall on an octree node: box low +0, high +0xc): the segment from -> to traced for the furthest hit
   (by the t collisionTri_traceSegment gives, from -FLT_MAX in dist; the hit point to hit). A split node (+0x24 1) walks
   its eight children (+0x28, x by 1, z by 2, y by 4) the segment passes through in order, cut at each child's
   boundary planes (the z planes spaced by the x half and the x planes by the z half: the original's slip, harmless
   on cubes), and returns the first child's hit. A leaf traces its list (+0x18; nodes: record +0, next +0xc; records
   flagged 1 skipped) and then each of nsubs sub-model lists (subs: 3 dwords each, the list, the matrix out, the
   matrix in; the segment taken in, a hit taken back out). Returns the hit record or 0 */
u32 THISCALL (space_traceUnit)(u8 *unit, const float *from, const float *to, float *hit, float *dist, const u32 *subs, int nsubs)
{
	const float *low = (const float *)RELOC(unit), *k = (const float *)ADDR(k_0_5f);
	if (GAME_VAR(int, unit + 0x24) == 1) {
		float half[3], d[3];
		for (int a = 0; a < 3; a++) {
			float ext = f32(fsub_m(fld_m(&low[3 + a]), &low[a]));
			half[a] = f32(fmul_m(fld_m(&ext), k));
		}
		int z0 = half_of(&from[2], &low[2], &half[2]), x0 = half_of(&from[0], &low[0], &half[0]), y0 = half_of(&from[1], &low[1], &half[1]);
		int z1 = half_of(&to[2], &low[2], &half[2]), x1 = half_of(&to[0], &low[0], &half[0]), y1 = half_of(&to[1], &low[1], &half[1]);
		int sy = y0 > y1 ? -1 : 1, sz = z0 > z1 ? -1 : 1, sx = x0 > x1 ? -1 : 1;
		for (int a = 0; a < 3; a++)
			d[a] = f32(fsub_m(fld_m(&to[a]), &from[a]));
		for (int y = y0;; y += sy) {
			float p0[3], p1[3], dp[3];
			if (y == y0)
				memcpy(p0, from, 12);
			else
				cut_at(p0, from, d, sy > 0 ? y : y + 1, &half[1], &low[1], 1, 1);
			if (y == y1)
				memcpy(p1, to, 12);
			else
				cut_at(p1, from, d, sy > 0 ? y + 1 : y, &half[1], &low[1], 1, 1);
			for (int a = 0; a < 3; a++)
				dp[a] = f32(fsub_m(fld_m(&p1[a]), &p0[a]));
			for (int z = z0;; z += sz) {
				float q0[3], q1[3], dq[3];
				if (z == z0)
					memcpy(q0, p0, 12);
				else
					cut_at(q0, p0, dp, sz > 0 ? z : z + 1, &half[0], &low[2], 2, 0);
				if (z == z1)
					memcpy(q1, p1, 12);
				else
					cut_at(q1, p0, dp, sz > 0 ? z + 1 : z, &half[0], &low[2], 2, 0);
				for (int a = 0; a < 3; a++)
					dq[a] = f32(fsub_m(fld_m(&q1[a]), &q0[a]));
				for (int x = x0;; x += sx) {
					float r0[3], r1[3];
					if (x == x0)
						memcpy(r0, q0, 12);
					else
						cut_at(r0, q0, dq, sx > 0 ? x : x + 1, &half[2], &low[0], 0, 1);
					if (x == x1)
						memcpy(r1, q1, 12);
					else
						cut_at(r1, q0, dq, sx > 0 ? x + 1 : x, &half[2], &low[0], 0, 1);
					u8 *child = GAME_VAR(u8 *, unit + 0x28 + (x + 2 * z + 4 * y) * 4);
					if (child) {
						u32 r = space_traceUnit(child, r0, r1, (u32)hit, dist, (u32)subs, (u32)nsubs);
						if (r)
							return r;
					}
					if (x == x1)
						break;
				}
				if (z == z1)
					break;
			}
			if (y == y1)
				return 0;
		}
	}
	u32 *node = GAME_VAR(u32 *, unit + 0x18);
	if (!node)
		return 0;
	GAME_VAR(u32, dist) = 0xff7fffff;
	float f[3], t[3];
	memcpy(f, from, 12);
	memcpy(t, to, 12);
	u32 found = 0;
	const u32 *sub = NULL;
	for (int s = -1;;) {
		u8 *rec = (u8 *)RELOC(node[0]);
		if (s >= 0 || !(rec[0] & 1)) {
			float at[3], tt;
			if (collisionTri_traceSegment(rec, f, t, at, &tt) == 1 && tt > *dist) {
				if (s < 0)
					memcpy(hit, at, 12);
				else {
					const float *m = (const float *)RELOC(sub[1]);
					for (int r = 0; r < 3; r++)
						hit[r] = f32(fadd_m(fmul_m(fld_m(&at[2]), &m[8 + r]) + fmul_m(fld_m(&at[1]), &m[4 + r]) +
						                    fmul_m(fld_m(&at[0]), &m[r]), &m[12 + r]));
				}
				*dist = tt;
				found = node[0];
			}
		}
		node = (u32 *)RELOC(node[3]);
		if (!node) {
			if (++s >= nsubs)
				return found;
			sub = subs + s * 3;
			node = (u32 *)RELOC(sub[0]);
			through_m(f, (const float *)RELOC(sub[2]), from, 0);
			through_m(t, (const float *)RELOC(sub[2]), to, 1);
		}
	}
}

/* where v lies against lo .. hi: bit when not above lo, bit << 4 when not below hi (a NaN counts as below lo) */
static u32 side(float v, float lo, float hi, u32 bit)
{
	return !(v > lo) ? bit : !(v < hi) ? bit << 4 : 0;
}

/* the segment's direction b - a, rounded as the original's Vec3 constructor takes it */
static void direction(float *d, const float *a, const float *b)
{
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(&b[k]), &a[k]));
}

/* the segment's start a moved along d onto the plane at *plane across axis k (0 or 1): its x and y as
   f32(f32(t d) / d[k]) + a, its z with t d2 / d[k] rounded or not as the original has it; then d = b - a */
static void clip_start(float *a, const float *b, float *d, const float *plane, int k, int round_z)
{
	long double t = fsub_m(fld_m(plane), &a[k]);
	float e0 = f32(fmul_m(t, &d[0])), e1 = f32(fmul_m(t, &d[1]));
	float n0 = f32(fdiv_m(fld_m(&e0), &d[k])), n1 = f32(fdiv_m(fld_m(&e1), &d[k]));
	long double z = fdiv_m(fmul_m(t, &d[2]), &d[k]);
	if (round_z)
		z = f32(z);
	a[0] = f32(fadd_m(fld_m(&n0), &a[0]));
	a[1] = f32(fadd_m(fld_m(&n1), &a[1]));
	a[2] = f32(fadd_m(z, &a[2]));
	direction(d, a, b);
}

/* the segment's end b moved back along d onto the plane across axis k: b - f32(f32(t d) / d[k]) (inline: the z
   unrounded, f32(t d2) / d[k] kept whole) */
static void clip_end(const float *a, float *b, float *d, const float *plane, int k, int inline_z)
{
	long double t = fsub_m(fld_m(plane), &b[k]);
	float v[3], w[3];
	for (int i = 0; i < 2; i++) {
		v[i] = f32(fmul_m(t, &d[i]));
		w[i] = f32(fdiv_m(fld_m(&v[i]), &d[k]));
	}
	if (inline_z)
		b[2] = f32(fld_m(&b[2]) - fdiv_m(fmul_m(t, &d[2]), &d[k]));
	else {
		v[2] = f32(fmul_m(t, &d[2]));
		w[2] = f32(fdiv_m(fld_m(&v[2]), &d[k]));
		b[2] = f32(fsub_m(fld_m(&b[2]), &w[2]));
	}
	b[0] = f32(fsub_m(fld_m(&b[0]), &w[0]));
	b[1] = f32(fsub_m(fld_m(&b[1]), &w[1]));
	(void)a;
}

/* 0x471740 (thiscall on the scene): the line of sight p0 -> p1 through the level. Every active scene object (0x2cc
   bytes from +0x131ae44, +0x13c9b24 of them: +4 1, its unit +0x28c with a list and enabled +0x290) takes the segment
   into its frame (the inverse +0x134); unless both ends lie beyond one side of its model's box (+0x27c: +0x34 low,
   +0x40 high), clipped to the box in x then y (the original's own rounding at every step), it becomes a sub-model
   (+0x9ca0f4: its list, its matrices +0x1f4 / +0x234). Then the level grid (+0xa10) is traced with them
   (space_traceNodes). Returns its hit record or 0 */
u32 THISCALL (collision_rayTrace)(u8 *s, const float *p0, const float *p1, void *hit)
{
	int n = 0;
	for (int i = 0; i < GAME_VAR(int, s + 0x13c9b24); i++) {
		u8 *o = s + 0x131ae44 + i * 0x2cc;
		if (GAME_VAR(int, o + 4) != 1 || GAME_VAR(int, o + 0x290) != 1 || !GAME_VAR(u32, GAME_VAR(u8 *, o + 0x28c) + 8))
			continue;
		const float *m = (const float *)(o + 0x134);
		const float *lo = (const float *)(GAME_VAR(u8 *, o + 0x27c) + 0x34), *hi = lo + 3;
		float a[3], b[3], d[3];
		for (int r = 0; r < 3; r++)
			a[r] = f32(fadd_m(fmul_m(fld_m(&p0[2]), &m[8 + r]) + fmul_m(fld_m(&p0[r ? 1 : 0]), &m[r ? 4 + r : 0]) +
			                  fmul_m(fld_m(&p0[r ? 0 : 1]), &m[r ? r : 4]), &m[12 + r]));
		b[0] = f32(fadd_m(fmul_m(fld_m(&p1[0]), &m[0]) + fmul_m(fld_m(&p1[1]), &m[4]) + fmul_m(fld_m(&m[8]), &p1[2]), &m[12]));
		b[1] = f32(fadd_m(fmul_m(fld_m(&p1[1]), &m[5]) + fmul_m(fld_m(&p1[0]), &m[1]) + fmul_m(fld_m(&m[9]), &p1[2]), &m[13]));
		long double b2 = fadd_m(fmul_m(fld_m(&p1[1]), &m[6]) + fmul_m(fld_m(&p1[0]), &m[2]) + fmul_m(fld_m(&m[10]), &p1[2]), &m[14]);
		b[2] = f32(b2);
		d[0] = f32(fsub_m(fld_m(&b[0]), &a[0]));
		d[1] = f32(fsub_m(fld_m(&b[1]), &a[1]));
		d[2] = f32(fsub_m(b2, &a[2]));
		u32 ca = side(a[0], lo[0], hi[0], 1) | side(a[1], lo[1], hi[1], 0x100) | side(a[2], lo[2], hi[2], 0x10000);
		u32 cb = side(b[0], lo[0], hi[0], 1) | side(b[1], lo[1], hi[1], 0x100) | side(b[2], lo[2], hi[2], 0x10000);
		if (ca & cb)
			continue;
		if (ca & 1)
			clip_start(a, b, d, &lo[0], 0, 0);
		else if (ca & 0x10)
			clip_start(a, b, d, &hi[0], 0, 0);
		if (cb & 1) {
			clip_end(a, b, d, &lo[0], 0, 1);
			direction(d, a, b);
		} else if (cb & 0x10) {
			clip_end(a, b, d, &hi[0], 0, 0);
			direction(d, a, b);
		}
		ca = side(a[1], lo[1], hi[1], 0x100);
		cb = side(b[1], lo[1], hi[1], 0x100);
		if (ca & cb)
			continue;
		if (ca & 0x100)
			clip_start(a, b, d, &lo[1], 1, 0);
		else if (ca & 0x1000)
			clip_start(a, b, d, &hi[1], 1, 1);
		if (cb & 0x100)
			clip_end(a, b, d, &lo[1], 1, 0);
		else if (cb & 0x1000)
			clip_end(a, b, d, &hi[1], 1, 0);
		if (side(a[2], lo[2], hi[2], 0x10000) & side(b[2], lo[2], hi[2], 0x10000))
			continue;
		u32 *sub = (u32 *)(RELOC(s) + 0x9ca0f4) + n * 3;
		sub[0] = GAME_VAR(u32, GAME_VAR(u8 *, o + 0x28c) + 8);
		sub[1] = (u32)(o + 0x1f4);
		sub[2] = (u32)(o + 0x234);
		n++;
	}
	return space_traceNodes(s + 0xa10, p0, p1, hit, s + 0x9ca0f4, n);
}

/* batch 61: pool / data initialisers (lifted/grp8.c, lifted in batch 60) */
/* 0x4813e0 (thiscall) space_initBy(planes, nodes, units, blocks, indices, mem, memSize): size the space object's
   pools (planes 0xb0 bytes, nodes 0x10, units, blocks 0x50, a block index table of shorts), take the memory from
   mem (memSize must suffice) or allocate it, lay the pools out, set the index table to -1 and reset the free lists */
static THISCALL DWORD space_initBy(char *sp, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f, DWORD g)
{
	DWORD v[7] = { a, b, c, d, e, f, g };
	return run_lifted(lift_4813e0, (DWORD)sp, 7, v);
}
/* 0x4819b0 (thiscall) space_setBy(min, max, nx, ny, nz, a, b, depth): reset the pools, set the grid bounds and cell
   counts (nx * ny * nz cells, at most the index table's size; at least 1), cell sizes, recursion depth (at most 8),
   clear the index table */
static THISCALL DWORD space_setBy(char *sp, DWORD mn, DWORD mx, DWORD nx, DWORD ny, DWORD nz, DWORD a, DWORD b, DWORD depth)
{
	DWORD v[8] = { mn, mx, nx, ny, nz, a, b, depth };
	return run_lifted(lift_4819b0, (DWORD)sp, 8, v);
}
/* 0x471010 (thiscall) load_471010: the scene's level grid (scene + 0xa10) as one cell over the level bounds */
static THISCALL DWORD load_471010(char *scene) { return run_lifted(lift_471010, (DWORD)scene, 0, NULL); }
/* 0x484050 (thiscall) factor_initBy(items, matrices, a, b, c, d, mem, memSize): the view volume's pools (render
   items, matrices and four more lists), memory from mem or allocated, laid out one after the other */
static THISCALL DWORD factor_initBy(char *vv, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f, DWORD g, DWORD h)
{
	DWORD v[8] = { a, b, c, d, e, f, g, h };
	return run_lifted(lift_484050, (DWORD)vv, 8, v);
}
/* 0x4569d0 (thiscall) texSmall_initBy(t64, t128x64, t256x64, t128, t256x128, t256): keep six texture images,
   each checked for its size (a wrong one is fatal) */
static THISCALL DWORD texSmall_initBy(char *self, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f)
{
	DWORD v[6] = { a, b, c, d, e, f };
	return run_lifted(lift_4569d0, (DWORD)self, 6, v);
}
/* 0x46aa10 (thiscall) skel_loadFrom_46aa10(f, mem, memSize): an animation: 0x24-byte header into the object
   (size +4, count +0x10), the memory from mem or allocated, then count 0x70-byte tracks, each followed by its
   position keys (0x20 bytes) and rotation keys (0x28 bytes); the track's key pointers are linked in */
static THISCALL DWORD skel_loadFrom_46aa10(char *self, DWORD f, DWORD mem, DWORD size)
{
	DWORD v[3] = { f, mem, size };
	return run_lifted(lift_46aa10, (DWORD)self, 3, v);
}

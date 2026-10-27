/* batch 67 (lifted/grp14.c) */
#include "lifted/grp14.c"
/* 0x481eb0 (thiscall) space_buildPlanes(id, v0, v1, v2, a..e): a collision triangle for the space object: nothing (0)
   if its box misses the grid's bounds (+0x5c / +0x68, widened by the margin +0x8c); else a plane record from the
   pool (load_47db60), then for every grid cell its box overlaps (cell sizes +0x84 / +0x88 / +0x80, dims +0x78 / +0x7c /
   +0x74) that load_47fce0 confirms: the cell's block (index table +0x54, -1 = make one from the block pool) gets the
   triangle (load_481ae0, depth +0x94). Returns the plane */
static THISCALL DWORD space_buildPlanes(char *sp, DWORD id, DWORD v0, DWORD v1, DWORD v2, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	DWORD v[9] = { id, v0, v1, v2, a, b, c, d, e };
	return run_lifted(lift_481eb0, (DWORD)sp, 9, v);
}
/* 0x482320 (thiscall) load_482320(id, unit, part, i0, i1, i2, v0, v1, v2): space_buildPlanes for one of a unit's
   triangles; a made plane is linked into the unit's plane list (+4, planes +0xa0 / +0xa4) and gets a node in its node
   list (+8) */
static THISCALL DWORD load_482320(char *sp, DWORD id, DWORD unit, DWORD part, DWORD i0, DWORD i1, DWORD i2, DWORD v0, DWORD v1, DWORD v2)
{
	DWORD v[9] = { id, unit, part, i0, i1, i2, v0, v1, v2 };
	return run_lifted(lift_482320, (DWORD)sp, 9, v);
}
/* 0x4823c0 (thiscall) space_buildUnits(id, shape, matrix): a unit (pool) for a shape: every part not flagged 0x20
   (flag 1 -> id 0x10) has its primitives' triangles (type 4 lists, 5 strips with alternating winding, 6 fans)
   transformed by the matrix (the GL modelview one if none is given) and added with load_482320. Returns the unit */
static THISCALL DWORD space_buildUnits(char *sp, DWORD id, DWORD shape, DWORD mat)
{
	DWORD v[3] = { id, shape, mat };
	return run_lifted(lift_4823c0, (DWORD)sp, 3, v);
}

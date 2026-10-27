/* batch 75 (lifted/grp22.c) */
#include "lifted/grp22.c"
/* 0x464db0 (thiscall) model_loadObjFormatFrom(f, mem, memSize): a shape from a Wavefront OBJ text file in three
   passes: count the parts (usemtl), positions (v), normals (vn), texture coordinates (vt) and the triangles of the
   faces (f with 3 or 4 v/vt/vn corners, a 4-corner face is two triangles; a lone "\" continues the face on the next
   line; fewer corners are fatal); take the data memory (allocated with three temporary arrays, or given: too small
   is fatal) and lay out each part's vertex, normal, colour and texture arrays and its one triangle-list primitive;
   then read the values (y and z kept as written), name the parts after the last "_" piece of the material name, and
   expand the faces into per-corner vertices; finally the parts' bounds (shape_relocate) */
static THISCALL DWORD model_loadObjFormatFrom(char *shape, DWORD f, DWORD mem, DWORD size)
{
	DWORD v[3] = { f, mem, size };
	return run_lifted(lift_464db0, (DWORD)shape, 3, v);
}

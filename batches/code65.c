/* batch 64 (lifted/grp11.c) */
#include "lifted/grp11.c"
/* 0x470ad0 (thiscall) scene_reset: reset the scene's subsystems (lists, effects, actors, particles, scripts, the
   level grid), the view to identity, start/item point counts to 0, the id tables to -1 */
static THISCALL DWORD scene_reset(char *scene) { return run_lifted(lift_470ad0, (DWORD)scene, 0, NULL); }
/* 0x466120 (thiscall) shape_read(f, mem, memSize): release the old data, read the 0x34-byte header (data size +4,
   part count +0x10, version +0x30; an old version has 0x68-byte part records, 0x18 less each), the data memory from
   mem or allocated, the part records (0x80 apart), then per part its vertices, normals, colours, texture
   coordinates, polygons and their index lists; old files get their bounds computed (shape_relocate); the overall
   box from the parts' boxes */
static THISCALL DWORD shape_read(char *self, DWORD f, DWORD mem, DWORD size)
{
	DWORD v[3] = { f, mem, size };
	return run_lifted(lift_466120, (DWORD)self, 3, v);
}

/* batch 108 (lifted/grp54.c) */
#include "lifted/grp54.c"
/* 0x485af0 (thiscall on a view volume) render_drawObjects(mode, b): draw what ViewVolume_projectObject queued. The
   projection / modelview are loaded from +0x90b0 / +0x90f0 and fog follows GL's fog state (glGetBooleanv; the
   fog range then maps through the projection, +0x90d8..). Per material (count +0x3024, ids +0x20; 0 none, else the
   texture id + 1 bound unless mode 2) its item chain (+0x3028 + id * 4; mesh, colours, factors, flag, matrix, -,
   next): each mesh's vertex colours come from the item's colour buffer, or are lit into the colour buffer +0x904c
   (shape_getShadingColorBufferBy / FUN_00464a70; up to +0x9048 vertices, the largest kept in +0x9050) through the
   inverse of the item's matrix, then drawn from vertex arrays (+0x50 positions, the colours, +0x5c texture
   coordinates) by its polygons (+0x60 count, +0x64 list of { mode, count, indices }); mode 1 draws wireframe. Then
   the transparent triangles (+0x9058, count +0x905c) and billboards (+0x906c, count +0x9070) are depth-sorted
   (+0x9060 / +0x9074 / +0x907c) and drawn back to front; the counters +0x90a4.. are updated */
static THISCALL DWORD render_drawObjects(char *vv, DWORD mode, DWORD b) { DWORD v[2] = { mode, b }; return run_lifted(lift_485af0, (DWORD)vv, 2, v); }

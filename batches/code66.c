/* batch 65 (lifted/grp12.c) */
#include "lifted/grp12.c"
/* 0x472400 (thiscall) light_computeLayerLightBy(layer, colours, first, row0, col0, row1, col1): a terrain layer's
   vertex colours over rows row0..row1, columns col0..col1 (grid (+0x20 + 1) wide): for each directional light
   factor (scene +0x9cd008, 0x2c apart, count +0x9d8000) the intensity (1 - normal . direction) * 128 (at least 0)
   times the factor's colour / 256, written (first) or added and clamped to 255, alpha 255; a layer with sky colours
   (+0x30 == 1) also gets the light straight down in its 12 colours at +0xfc. A type-2 layer only clears its light
   map (+0x48) and sky colours */
static THISCALL DWORD light_computeLayerLightBy(char *scene, DWORD layer, DWORD cols, DWORD first, DWORD r0, DWORD c0, DWORD r1, DWORD c1)
{
	DWORD v[7] = { layer, cols, first, r0, c0, r1, c1 };
	return run_lifted(lift_472400, (DWORD)scene, 7, v);
}
/* 0x497d20 (thiscall) render_processRenderingBy(vv, h): per terrain layer (scene +0xdc0248, 0x20c apart, count
   +0xdc0a74) the cells of its bitmap (bit 0) within the view distance (+0xa08) of the camera (+0x20f3970 / +0x20f3978)
   as triangle strips (type 5) of grid indices, into the layer's primitive buffer and index heap (overflow is
   fatal); a water layer (+0x2c == 1) also gets its 4 + 6 surface vertices and texture coordinates around the
   camera; then both terrain objects (+0xdc0cc4, +0xdc0a78) go to vv's queue (ViewVolume_projectObject) */
static THISCALL DWORD render_processRenderingBy(char *scene, DWORD vv, DWORD h)
{
	DWORD v[2] = { vv, h };
	return run_lifted(lift_497d20, (DWORD)scene, 2, v);
}

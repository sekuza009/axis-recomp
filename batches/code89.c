/* batch 88 (lifted/grp34.c) */
#include "lifted/grp34.c"
/* 0x46f4e0 (thiscall) data_loadFrom_46f4e0(shapeCache, skelCache, nShapes, shapeNames, nSkels, skelNames, lit,
   factors, pixelLights, mem, memSize): an object list (released first, FUN_0046f4b0): the shapes by name (0x44 apart,
   an int at +0x40 each; the first 64 looked up once, later ones again when filled in) with their element counts
   summed (+0x18), the data memory (100 bytes per shape, 4 per skeleton, with lit == 1 the colour buffers too) from
   mem (too small is fatal) or operator new (none is fatal), then per shape its entry (shape, the int, colour
   buffer when lit), the skeletons by name (0x40 apart) after them, and with lit == 1 the colours (data_46f7a0) */
static THISCALL DWORD data_loadFrom_46f4e0(char *list, DWORD sc, DWORD kc, DWORD ns, DWORD names, DWORD nk, DWORD knames,
                                           DWORD lit, DWORD fac, DWORD px, DWORD mem, DWORD size)
{
	DWORD v[11] = { sc, kc, ns, names, nk, knames, lit, fac, px, mem, size };
	return run_lifted(lift_46f4e0, (DWORD)list, 11, v);
}

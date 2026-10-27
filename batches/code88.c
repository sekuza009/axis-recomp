/* batch 87 (lifted/grp33.c) */
#include "lifted/grp33.c"
/* 0x48b710 (thiscall) map_loadObjectInfoFrom(name, mode): a map's objects. Releases the shape and skeleton caches
   and the object pool; mode 0 first tries "dir/Temp-<name without extension>-objectShadingInfo.dat" (scrambled count
   + element colours into the pool at +0xf30dc8; read: no shading pass, +0x13016cc = 1). Then "dir/name" (dir +0x108;
   no file is fatal): version 0x1201 (else fatal), scrambled count and one more value, then the 0xb0-byte object
   types in scrambled blocks of 56, each added with object_addObjectBy until one fails. Mode 1 without a shading
   file writes one ("wb", scrambled) */
static THISCALL DWORD map_loadObjectInfoFrom(char *scene, DWORD name, DWORD mode)
{
	DWORD v[2] = { name, mode };
	return run_lifted(lift_48b710, (DWORD)scene, 2, v);
}

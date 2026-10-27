/* batch 73 (lifted/grp20.c) */
#include "lifted/grp20.c"
/* 0x469b90 (thiscall) skel_loadAseFrom(f, mem, memSize): a skeleton from a 3ds Max ASE text file. Pass 1 counts
   GEOMOBJECTs (bones, 0x70 bytes), TCB/Bezier position keys (0x20) and TCB rotation keys (0x28) and takes the data
   memory (allocated, or given: too small is fatal); pass 2 (fseek to 0) reads SCENE_LASTFRAME / FRAMESPEED /
   TICKSPERFRAME (key times = tick / ticksPerFrame * 1000 / frameSpeed), and per bone its NODE_NAME, NODE_PARENT
   (looked up among the earlier bones; missing is fatal), TM_POS / TM_ROTAXIS / TM_ROTANGLE (y and z swapped, z and
   the angle negated) and its key lists (rotation keys accumulated onto the previous one); then the bones' matrices */
static THISCALL DWORD skel_loadAseFrom(char *sk, DWORD f, DWORD mem, DWORD size)
{
	DWORD v[3] = { f, mem, size };
	return run_lifted(lift_469b90, (DWORD)sk, 3, v);
}

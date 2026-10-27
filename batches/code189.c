/* batch 188 (lifted/grp143.c, grp144.c: split, bullet_spawn calls bullet_init): bullets */
#include "lifted/grp143.c"
#include "lifted/grp144.c"
/* the bullets (thiscall on the scene, BUF in the tests): 400 slots of 0x4e8 bytes from +0x202ef34 (used flag +4),
   the next free +0x20a99b8, the highest used +0x20a99b4, a serial +0x20a99bc.
   0x47ce50 bullet_spawn(a1, a2, a3, shot, a5) (ret 0x14): -1 for a shot without a weapon (+4 < 0) or with all slots
   in use, else the first free slot set up by bullet_init; returns the slot */
static THISCALL DWORD bullet_spawn(char *s, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5)
{
	DWORD v[5] = { a1, a2, a3, a4, a5 };
	return run_lifted(lift_47ce50, (DWORD)s, 5, v);
}
/* 0x479b40 bullet_init(slot, id, owner, a4, shot, a6) (ret 0x18): the slot from the shot (weapon +4: its record at
   +0x14d1ab4, origin and direction), the owner actor's muzzle and team, the id (or the next serial), its matrix,
   the firing sound and muzzle particles (stubbed) */
static THISCALL DWORD bullet_init(char *s, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6)
{
	DWORD v[6] = { a1, a2, a3, a4, a5, a6 };
	return run_lifted(lift_479b40, (DWORD)s, 6, v);
}

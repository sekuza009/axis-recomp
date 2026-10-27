/* batch 86 (lifted/grp32.c) */
#include "lifted/grp32.c"
/* 0x490c50 (thiscall) object_addObjectBy(type): add a map object of this type in the first free slot (+0x13c9b28;
   past the highest used one, +0x13c9b24, that one grows and its slot is cleared) with object_initObjectBy, then move
   the free slot on to the next unused object (+0x131ae48 == 0) up to the highest. Returns the slot; with 1000 in
   use, a message (sys_errorMessage) and -1 */
static THISCALL DWORD object_addObjectBy(char *scene, DWORD type)
{
	DWORD v[1] = { type };
	return run_lifted(lift_490c50, (DWORD)scene, 1, v);
}
/* 0x48ec20 (thiscall) effect_initTextures(): the effect shapes from the shape cache at +0x19e188c, each bound:
   "Effect\PlasmaThrust-0..7", "IonThrust-0..7", "GravityThrust-0..7" (+0x20f2dac, +0x20f2dcc, +0x20f2dec) and
   eight shots / muzzle flashes (+0x20f2e74..+0x20f2e90); clears +0x20f2f3c first */
static THISCALL DWORD effect_initTextures(char *self) { return run_lifted(lift_48ec20, (DWORD)self, 0, NULL); }

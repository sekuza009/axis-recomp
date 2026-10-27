/* batch 78 */
/* 0x490df0 (thiscall) object_setAnimation(i, name, period, mode): script command 0x1c. No name or mode 0 stops object
   i's animation (rate 0); otherwise its skeleton comes from the scene's cache (+0x13016d0), its collision unit is
   disabled, and the rate is 1 / period (+-1 for a period within 1e-8 of 0, -1 also for a NaN) */
static THISCALL void object_setAnimation(char *self, int i, DWORD name, float period, int mode)
{
	char *o = OBJ(self, i) + 0x131ae44;
	if (!name || !mode) { S32(o, 0x29c) = 0; return; }
	S32(o, 0x294) = (int)skel_getSkeletonPtrBy(self + 0x13016d0, name);
	if (S32(o, 0x28c)) space_disableUnit((char *)S32(o, 0x28c));
	S32(o, 0x290) = 1;
	S32(o, 0x2a0) = mode;
	if (fabsf(period) > 1e-8f) SF(o, 0x29c) = (float)(1.0L / (long double)period);
	else SF(o, 0x29c) = period >= 0.0f ? 1.0f : -1.0f;
}

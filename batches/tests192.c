/* batch 191 */
/* the frame loops: bullets_setup's / particles_setup's slots (in use or not, the highest used), paused or not, dt; the
   per-slot update stubbed (thiscall, ret 8) */
static const DWORD g_stubBulletLoop[] = { 0x47a2d0, 2 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubPartLoop[] = { 0x476410, 2 | CS_POP | CS_THIS, 0 };
static void frameloop_setup(int bullets)
{
	if (bullets) bullets_setup(g_stubBulletLoop); else particles_setup(g_stubPartLoop);
	S32(BUF, 0x2149308) = irnd(0, 1); S32(BUF, 0x214930c) = irnd(0, 2);
	GF(&g_a[0]) = (float)irnd(1, 100) / 1000.0f;
}
ST(bullet_updateAll, frameloop_setup(1);, (TC(void, 0x47d000, char *, int)(BUF, g_a[0]), 0), (bullet_updateAll(BUF, (DWORD)g_a[0]), 0))
ST(match_479a90, frameloop_setup(0);, (TC(void, 0x479a90, char *, int)(BUF, g_a[0]), 0), (match_479a90(BUF, (DWORD)g_a[0]), 0))

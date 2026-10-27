/* batch 107 */
/* hudicon_setup's HUD object (texture id also at +0xbc06b4) and a rectangle in 640 x 480 units */
static void hudpanel_setup(void)
{
	hudicon_setup();
	S32(BUF, 0xbc06b4) = S32(BUF, 0xbc06b0);
	g_a[0] = irnd(-50, 700); g_a[1] = irnd(-50, 500); g_a[2] = irnd(-20, 400); g_a[3] = irnd(-20, 300);
}
ST(hud_495ed0, hudpanel_setup();, (TC(void, 0x495ed0, char *, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3]), 0),
   (hud_495ed0(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3]), 0))

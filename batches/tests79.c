/* batch 78 */
/* object i of 0..999 with the skeleton cache test's scene cache, a unit list or none; no name / mode 0 sometimes;
   periods of every size, tiny, +-0, NaN */
static void setanim_setup(void)
{
	skelcache_setup(BUF + 0x13016d0);
	int nm = g_a[0], i = irnd(0, 999);
	char *o = OBJ(BUF, i) + 0x131ae44;
	fill(o + 0x28c, 0x18);
	units_setup();
	S32(o, 0x28c) = irnd(0, 2) ? (int)BUF : 0;
	float p; int c = irnd(0, 9);
	if (c < 5) p = (float)irnd(-100000, 100000) / 1000.0f;
	else if (c < 7) p = (float)irnd(-200, 200) * 1e-10f;
	else if (c == 7) p = irnd(0, 1) ? 0.0f : -0.0f;
	else if (c == 8) fill(&p, 4);
	else { DWORD q = 0x7fc00000u | (irnd(0, 1) ? 0x80000000u : 0); memcpy(&p, &q, 4); }
	g_a[0] = i; g_a[1] = irnd(0, 9) ? nm : 0; memcpy(&g_a[2], &p, 4); g_a[3] = irnd(0, 9) ? irnd(1, 3) : 0;
}
ST(object_setAnimation, setanim_setup();,
   (TC(void, 0x490df0, char *, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3]), 0),
   (object_setAnimation(BUF, g_a[0], (DWORD)g_a[1], *(float *)&g_a[2], g_a[3]), 0))

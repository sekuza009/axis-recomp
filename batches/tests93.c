/* batch 92 */
/* tex_getIdByName's texture set at 0xa0e010 (its test manager in one slot); a texture id there that owns a GL slot
   (just bound) or texture i (loaded from its files); menu coordinates. (A negative id would index outside the set;
   no caller passes one) */
static int menutex_setup(void)
{
	texset_setup();
	G32(0xa0e010) = (int)(BUF + 0x400000);
	int k = 0, i = S32(BUF, 0xcd128), c = irnd(0, 9);
	while (S32(BUF + 0x400000, 4 + k * 4) != (int)BUF) k++;
	S32(BUF, 0xcd128) = 21;
	for (int a = 0; a < 4; a++) g_a[a] = irnd(-100, 800);
	return c < 6 ? k * 512 + S32((char *)S32(BUF, 0xcd134), 4) : k * 512 + i;
}
ST(menu_drawTexturedRect_427a90, g_a[4] = menutex_setup();, (CD(void, 0x427a90, int, int, int, int, int)(g_a[0], g_a[1], g_a[2], g_a[3], g_a[4]), 0),
   (menu_drawTexturedRect_427a90(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], 0, 0, 0), 0))
ST(menu_drawTexturedRect_427b60, g_a[4] = menutex_setup();, (CD(void, 0x427b60, int, int, int, int, int)(g_a[0], g_a[1], g_a[2], g_a[3], g_a[4]), 0),
   (menu_drawTexturedRect_427b60(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], 0, 0, 0), 0))
ST(menu_drawTexturedRect_428a00, G32(0x4deb4c) = menutex_setup();, (CD(void, 0x428a00, int, int, int, int)(g_a[0], g_a[1], g_a[2], g_a[3]), 0),
   (menu_drawTexturedRect_428a00(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], 0, 0, 0, 0), 0))
ST(menu_drawTexturedRect_428b50, G32(0x4deb4c) = menutex_setup();, (CD(void, 0x428b50, int, int, int)(g_a[0], g_a[1], g_a[2]), 0),
   (menu_drawTexturedRect_428b50(0, 0, 0, g_a[0], g_a[1], g_a[2], 0, 0, 0, 0, 0), 0))

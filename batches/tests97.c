/* batch 96 */
/* the font texture name in the texture dat index (texpath_index), the already-initialised flag now and then; the
   glyph tables cleared to random bytes first */
static void pen_setup(void)
{
	char *nm = BUF + 0x87fe00;
	strcpy(nm, irnd(0, 1) ? "Texture/HudFont" : "pen");
	texpath_index(nm);
	fill((void *)0xa0f150, 0xa106b0 - 0xa0f150);
	G32(0xa106a8) = irnd(0, 9) ? 0 : 1;
	g_a[0] = (int)nm;
}
ST(pen_init, pen_setup();, CD(int, 0x46b950, char *)((char *)g_a[0]), pen_init(0, 0, 0, (DWORD)g_a[0], 0, 0, 0))

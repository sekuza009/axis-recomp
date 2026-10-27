/* batch 102 */
/* the clan texture's path in the texture index (texpath_index), every part table and item record ready (as
   wholeplayer_setup), and the actor file as the second VFS content ("M1.act"): version 0x1201 (rarely not), three
   blocks of 0..20 bytes to skip, 1..5 players (colour scheme 0..10, name, team, parts 0..3, items -1..3) and 0..6
   actors, scrambled. The scene's dir (+0x108) is the texture manager's dat count here (see batch 87) */
static void actorfile_setup(void)
{
	char stage[16]; fill_str(stage, 8, 'A', 'Z');
	char path[64]; sprintf(path, "Stage\\%s\\Clan", stage);
	texpath_index(path);
	strcpy(BUF + 0x908, stage);
	setitem_setup();
	S32(BUF, 0x20f3ab8) = irnd(0, 3) ? 0 : irnd(0, 13);
	for (int k = 0; k < 5; k++) {
		const PartType *t = &g_partTypes[k];
		S32(BUF, t->countOff) = 4;
		for (int ty = 0; ty < 4; ty++) part_record(BUF + t->base + ty * t->stride, t->stride, 0x40, t->kcOff, t->maxNames);
	}
	BYTE *d = (BYTE *)(BUF + 0x880000); int len = 0, np = irnd(1, 5), na = irnd(0, 6);
	*(DWORD *)d = irnd(0, 19) ? 0x1201 : 0x1200; len = 4;
	for (int b = 0; b < 3; b++) { int n = irnd(0, 20); scrambled_count((char *)d + len, (DWORD)n); len += 4; fill(d + len, n); len += n; }
	scrambled_count((char *)d + len, (DWORD)irnd(0, 9)); len += 4;
	scrambled_count((char *)d + len, (DWORD)np); len += 4;
	for (int i = 0; i < np; i++) {
		char *r = (char *)d + len; fill(r, 0x58);
		S32(r, 4) = irnd(0, 10); fill_str(r + 8, 20, 'A', 'Z'); S32(r, 0x28) = irnd(-1, 3);
		for (int k = 0; k < 5; k++) S32(r, 0x2c + k * 4) = irnd(0, 3);
		for (int k = 0; k < 6; k++) S32(r, 0x40 + k * 4) = irnd(-1, 3);
		for (int b = 0; b < 0x58; b++) { BYTE c = (BYTE)r[b]; r[b] = (char)(((c >> 1) | (c << 7)) ^ 0x59); }
		len += 0x58;
	}
	scrambled_count((char *)d + len, (DWORD)na); len += 4;
	fill(d + len, na * 0x5c); len += na * 0x5c;
	g_vfsAltName = "M1.act"; g_vfsAltData = d; g_vfsAltSize = (DWORD)len;
	g_vfsOpenFail = 0; g_vfsFailMask = !irnd(0, 29) ? 1 : 0;
	strcpy(BUF + 0x87ff00, "M1.act");
	fill(BUF + 0x1cd6a30, 6 * 0x58); fill(BUF + 0x2104fe4, 4);
	g_a[0] = (int)(BUF + 0x87ff00);
}
static int g_actorFileDone;
static DWORD actorfile_orig(void) { TC(void, 0x474550, char *, char *)(BUF, (char *)g_a[0]); g_actorFileDone++; return 0; }
ST(map_loadActorInfoFrom, actorfile_setup();, actorfile_orig(),
   (map_loadActorInfoFrom(BUF, (DWORD)g_a[0]), 0))

/* batch 95 */
/* texture paths: tex_getIdByName's set (0xa0e010) with its manager in format 0 and no dir, and the dat index holding
   the path the function builds (upper-cased, '/' -> '\') between decoys most of the time (else "can't find" is
   fatal); a new texture is bound at once now and then, loaded from texture i's PTX */
static void texpath_index(const char *path)
{
	char up[0x80], names[4][0x80]; int n = 0;
	strcpy(up, path);
	for (char *c = up; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
	texset_setup();
	G32(0xa0e010) = (int)(BUF + 0x400000);
	S32(BUF, 0xc0114) = 0; BUF[8] = 0;
	if (irnd(0, 9)) strcpy(names[n++], up);
	strcpy(names[n++], "A0"); strcpy(names[n++], "ACTOR\\ITEM\\Z"); strcpy(names[n++], "ZZ");
	for (int a = 0; a < n; a++) for (int b = a + 1; b < n; b++)
		if (strcmp(names[b], names[a]) < 0) { char x[0x80]; strcpy(x, names[a]); strcpy(names[a], names[b]); strcpy(names[b], x); }
	for (int k = 0; k < n; k++) { memset(BUF + 0x200 + k * 0x44, 0, 0x44); strncpy(BUF + 0x200 + k * 0x44, names[k], 0x3f); }
	strcpy(BUF + 0x200 + n * 0x44, "\x7f");
	S32(BUF, 0x108) = n;
}
static void snapshot_setup(void)
{
	int i = irnd(0, 7);
	char *nm = (char *)0x4dbe50 + i * 0x80, path[0x100];
	if (irnd(0, 7)) fill_str(nm, 12, 'a', 'z'); else fill_str(nm, 1, 'a', 'z');
	sprintf(path, "Actor/item/%s/snapshot", nm);
	texpath_index(path);
	fill((void *)0x4dcc64, 4); fill((void *)(0x4dcc70 + i * 4), 4);
	g_a[0] = i;
}
ST(armc_snapshot, snapshot_setup();, (CD(void, 0x419000, int)(g_a[0]), 0), (armc_snapshot(0, 0, 0, (DWORD)g_a[0], 0, 0, 0), 0))
static void mappreview_setup(DWORD idxp)
{
	int k = irnd(0, 15);
	char *dir = (char *)0x680bc4, *nm = (char *)0x907b30 + k * 0x20, path[0x100];
	strcpy(dir, irnd(0, 1) ? "Map/" : "Data/Map/"); fill_str(nm, 10, 'A', 'z');
	*(signed char *)idxp = (signed char)k;
	sprintf(path, "%s%s/%s", dir, nm, nm);
	texpath_index(path);
	fill((void *)0x9da324, 4); fill((void *)0x680cd0, 4);
}
static int g_previewFound;
static DWORD preview_orig(void) { CD(void, 0x40b420, void)(); g_previewFound += G32(0x9da324) >= 0; return 0; }   /* counts found textures */
ST(arena_40b420, mappreview_setup(0x4db548);, preview_orig(), (arena_40b420(0, 0, 0, 0, 0, 0, 0), 0))
ST(room_43bcb0, mappreview_setup(0x4df9e8);, (CD(void, 0x43bcb0, void)(), 0), (room_43bcb0(0, 0, 0, 0, 0, 0, 0), 0))

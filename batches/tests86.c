/* batch 85 */
/* the scene (BUF) with shape_getByName's test cache at +0xe3c93c and a type record (BUF + 0xe50000) naming the
   cache's name (never an empty or "." one: the original would read through the null shape); 0..5 known types
   (the record's name among them half the time); shading (+0x13016cc == 0) only for names already in the cache,
   whose shapes have shade_setup's parts (a loaded shape's parts come from random file data) */
static void objinit_setup(void)
{
	char *sc = BUF, *self = BUF + 0xe3c93c, *rec = BUF + 0xe50000;
	shapecache_setup(self);
	char *nm = (char *)g_a[0];
	if (!nm[0] || nm[0] == '.') strcpy(nm, "MECH");
	fill(rec, 0xb0); strcpy(rec, nm);
	if (irnd(0, 1)) rec[0x4c] = 0; else strcpy(rec + 0x4c, irnd(0, 1) ? "ROCKS" : "b2");
	for (int k = 0; k < 3; k++) { SF(rec, 0x8c + k * 4) = (float)irnd(-5000, 5000) / 10.0f; SF(rec, 0x98 + k * 4) = (float)irnd(-314, 314) / 100.0f; }
	strcpy(sc + 0x908, irnd(0, 1) ? "MAPS" : "M1");
	int nt = irnd(0, 5);
	S32(sc, 0x131ae40) = irnd(0, 49) ? nt : 1000;
	for (int t = 0; t < nt; t++) fill_str(sc + 0x130b440 + t * 0x40, 8, 'A', 'Z');
	if (nt && irnd(0, 1)) strcpy(sc + 0x130b440 + irnd(0, nt - 1) * 0x40, rec);
	fill(sc + 0x130b440 + nt * 0x40, 0x40);
	int i = irnd(0, 999);
	fill(sc + 0x131ae44 + i * 0x2cc, 0x2cc);
	S32(sc, 0x13c9b2c) = irnd(0, 500); S32(sc, 0x13016c8) = irnd(0, 49) ? irnd(0, 1000) : 999990;
	/* a cached name (upper-cased, '/' -> '\') is found in the tree: only then shade */
	char u[0x40]; int hit = 0;
	strcpy(u, rec); for (char *c = u; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
	for (int n = 0; n < S32(self, 0x120); n++) hit |= !strcmp(u, (char *)S32(self, 0x118) + n * 0x4c);
	S32(sc, 0x13016cc) = hit && irnd(0, 2) ? 0 : 1;
	fill(sc + 0xf30dc8 + S32(sc, 0x13016c8) * 4, 0x100);
	char *f = sc + 0x9ccffc; int nf = irnd(0, 9) ? irnd(1, 4) : 0;       /* shade_setup's factors */
	S32(f, 0xb004) = nf;
	for (int k = 0; k < 4; k++) {
		char *r = f + 4 + k * 0x2c; fill(r, 0x2c);
		S32(r, 8) = irnd(0, 3);
		for (int j = 0x10; j < 0x28; j += 4) SF(r, j) = shade_f(-800, 800);
		SF(r, 0x28) = (float)irnd(0, 1200) / 100.0f;
	}
	g_a[0] = i; g_a[1] = (int)rec;
}
ST(object_initObjectBy, objinit_setup();, (TC(void, 0x48fee0, char *, int, char *)(BUF, g_a[0], (char *)g_a[1]), 0),
   (object_initObjectBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))

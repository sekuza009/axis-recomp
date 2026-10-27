/* batch 108 */
/* a view volume (BUF + 0x100000) with 0..3 materials (no texture, or a GL slot owner of menutex_setup's set + 1),
   each with a chain of 1..3 items over 4 meshes (shade_setup-like parts with positions, normals, colours, texture
   coordinates and 0..3 polygons { mode 4 / 5 / 6, count, in-range indices }); items with their own colours or lit
   (factors as shade_setup's), invertible matrices; buffers for the colour pass and the sort lists, room for
   transparent triangles, 0..4 billboards; the matrices, fog on or off; modes 0..2 */
static void drawobj_setup(void)
{
	int t0 = menutex_setup(), k = t0 - t0 % 512;
	char *vv = BUF + 0x100000, *items = BUF + 0x130000, *mats = BUF + 0x138000, *mesh = BUF + 0x140000, *data = BUF + 0x150000;
	memset(vv, 0, 0x9200);
	/* meshes */
	for (int m = 0; m < 4; m++) {
		char *e = mesh + m * 0x80, *d = data + m * 0x2000; int nv = irnd(1, 12), np = irnd(0, 3);
		fill(e, 0x80);
		S32(e, 0) = irnd(0, 31) & (m < 2 ? ~1 : ~0); S32(e, 0x48) = 0; S32(e, 0x4c) = nv;   /* flags: 1 transparent (not meshes 0 / 1), 2 unlit, 4 / 8 culling, 0x10 */
		S32(e, 0x50) = (int)d; S32(e, 0x54) = (int)(d + 0x200); S32(e, 0x58) = (int)(d + 0x400); S32(e, 0x5c) = (int)(d + 0x600);
		S32(e, 0x60) = np; S32(e, 0x64) = (int)(d + 0x800);
		for (int i = 0; i < nv * 3; i++) { SF(d, 4 * i) = (float)irnd(-500, 500) / 1000.0f; SF(d + 0x200, 4 * i) = shade_f(-100, 100); }   /* small: inside the clip volume */
		fill(d + 0x400, nv * 4);
		for (int i = 0; i < nv * 2; i++) SF(d + 0x600, 4 * i) = (float)irnd(0, 100) / 100.0f;
		for (int j = 0; j < 3; j++) { SF(e, 0x68 + 4 * j) = -5.0f; SF(e, 0x74 + 4 * j) = 5.0f; }
		for (int p = 0; p < np; p++) {
			char *pg = d + 0x800 + p * 12; int c = irnd(0, 8);
			S32(pg, 0) = 4 + irnd(0, 2); S32(pg, 4) = c; S32(pg, 8) = (int)(d + 0xa00 + p * 0x40);
			for (int i = 0; i < c; i++) S32(d + 0xa00 + p * 0x40, 4 * i) = irnd(0, nv - 1);
		}
	}
	/* factors (shade_setup's) and the items' matrices */
	char *f = BUF + 0x180000; int nf = irnd(0, 9) ? irnd(1, 4) : 0;
	S32(f, 0xb004) = nf;
	for (int q = 0; q < 4; q++) {
		char *r = f + 4 + q * 0x2c; fill(r, 0x2c);
		S32(r, 8) = irnd(0, 3);
		for (int j = 0x10; j < 0x28; j += 4) SF(r, j) = shade_f(-800, 800);
		SF(r, 0x28) = (float)irnd(0, 1200) / 100.0f;
	}
	for (int i = 0; i < 12; i++) {
		float *mt = (float *)(mats + i * 64), a = (float)irnd(-314, 314) / 100.0f;
		memset(mt, 0, 64); mt[0] = mt[5] = cosf(a); mt[1] = sinf(a); mt[4] = -mt[1]; mt[10] = mt[15] = 1.0f;
		for (int j = 12; j < 15; j++) mt[j] = (float)irnd(-30, 30) / 100.0f;
	}
	/* the queue */
	int nm = irnd(0, 3), it = 0;
	S32(vv, 0x3024) = nm;
	for (int i = 0; i < nm; i++) {
		int id = 0;                                       /* 0: no texture; else a GL slot owner's id + 1 */
		if (i > 0 || irnd(0, 2)) { char *sl = (char *)S32(BUF, 0xcd134); for (int m = irnd(0, 5); m; m--) sl = (char *)S32(sl, 0xc); id = 1 + k + S32(sl, 4); }
		for (int j = 0; j < i; j++) if (S32(vv, 0x20 + j * 4) == id) id = 0;
		S32(vv, 0x20 + i * 4) = id;
		int n = irnd(1, 3); char *prev = 0;
		for (int j = 0; j < n; j++, it++) {
			char *e = items + it * 0x1c;
			S32(e, 0) = (int)(mesh + irnd(0, id ? 3 : 1) * 0x80);   /* untextured items stay opaque: a transparent one crashes the original (null texture coordinates) */
			S32(e, 4) = irnd(0, 2) ? 0 : (int)(BUF + 0x188000 + it * 0x40);
			S32(e, 8) = irnd(0, 2) ? (int)f : 0; S32(e, 0xc) = irnd(0, 1) ? (int)(BUF + 0x18c000 + it * 4) : 0;   /* an RGBA tint or none */ S32(e, 0x10) = (int)(mats + irnd(0, 11) * 64);
			S32(e, 0x14) = !id || irnd(0, 2) ? 0 : (int)(mats + irnd(0, 11) * 64); S32(e, 0x18) = 0;   /* a second matrix or none */
			if (prev) S32(prev, 0x18) = (int)e; else S32(vv, 0x3028 + id * 4) = (int)e;
			prev = e;
		}
	}
	fill(BUF + 0x188000, 12 * 0x40); fill(BUF + 0x18c000, 12 * 4);
	/* the view volume's buffers and state */
	S32(vv, 0x9048) = 64;   /* the colour buffer's capacity: a mesh that never fits is retried forever (the game's is large) */ S32(vv, 0x904c) = (int)(BUF + 0x190000); S32(vv, 0x9050) = irnd(0, 5);
	S32(vv, 0x9058) = (int)(BUF + 0x198000); S32(vv, 0x905c) = 0; S32(vv, 0x9054) = irnd(0, 3) ? 64 : irnd(0, 3);   /* transparent triangles: room */ S32(vv, 0x9060) = (int)(BUF + 0x1a0000);
	S32(vv, 0x906c) = (int)(BUF + 0x1a8000); S32(vv, 0x9070) = 0; S32(vv, 0x9074) = (int)(BUF + 0x1b0000); S32(vv, 0x907c) = (int)(BUF + 0x1b8000);
	for (int i = 0; i < 16; i++) SF(vv, 0x9130 + i * 4) = (i % 5 == 0) ? 1.0f : (float)irnd(-30, 30) / 100.0f;   /* the view matrix (culls transparent triangles) */
	for (int i = 0; i < 32; i++) SF(vv, 0x90b0 + 4 * i) = unit_rnd() * 2.0f;
	SF(vv, 0x90bc) = 0; SF(vv, 0x90cc) = 0; SF(vv, 0x90dc) = -1.0f; SF(vv, 0x90ec) = 0.5f + unit_rnd();
	S32(vv, 0x9088) = (int)(BUF + 0x1c0000); S32(vv, 0x908c) = irnd(0, 4); fill(BUF + 0x1c0000, 0x1000); fill(vv + 0x90a4, 12);   /* the line list */
	/* 0..4 billboards queued the game's way (hud_4848e0, rebuilt and bit-exact): types 2 / 3 (the two depth lists)
	   or another, a GL slot owner's texture or none (-1), a colour, four points near the view */
	S32(vv, 0x9068) = 8; S32(vv, 0x9070) = 0;
	for (int q = irnd(0, 4); q > 0; q--) {
		DWORD uv0[2], uv1[2], col; float pts[12]; char *sl = (char *)S32(BUF, 0xcd134);
		for (int m = irnd(0, 5); m; m--) sl = (char *)S32(sl, 0xc);
		fill(uv0, 8); fill(uv1, 8); fill(&col, 4);
		for (int c = 0; c < 12; c++) pts[c] = (float)irnd(-500, 500) / 1000.0f;
		hud_4848e0(vv, irnd(0, 3) ? k + S32(sl, 4) : -1, uv0, uv1, &col, pts, irnd(0, 4) ? irnd(2, 3) : 1, irnd(0, 1));
	}
	g_mockGlBool = irnd(0, 1);
	for (int i = 0; i < 16; i++) g_glFloats[i] = (DWORD)irnd(-0x3f800000, 0x3f800000) & 0xbfffffffu;
	g_a[0] = irnd(0, 2); g_a[1] = irnd(0, 1);
	g_paintStacks = 1;
}
static int g_drawSorted, g_drawRuns;
static DWORD drawobj_orig(void)   /* counts runs whose transparent pass had triangles to sort */
{
	TC(void, 0x485af0, char *, int, int)(BUF + 0x100000, g_a[0], g_a[1]);
	g_drawRuns++; g_drawSorted += S32(BUF + 0x100000, 0x9064) > 0;
	return 0;
}
ST(render_drawObjects, drawobj_setup();, drawobj_orig(),
   (render_drawObjects(BUF + 0x100000, (DWORD)g_a[0], (DWORD)g_a[1]), 0))

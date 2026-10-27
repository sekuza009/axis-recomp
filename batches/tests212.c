/* batch 211 */
/* the text passes: a point on or off the 640 x 480 screen, a printable text (0..40 characters), a width, the colour
   and the font textures' ids; the texture set's table zero (the bind stub records a null object); every callee
   stubbed (the last pass goes through the patch DLL's wrapper when installed, to the same stub) */
static const DWORD g_stubTxt5[] = { 0x403060, 3, 0x41ef90, 1, 0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubTxt8[] = { 0x401870, 3, 0x401aa0, 3, 0x402010, 3, 0x41ef90, 1, 0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubTxt16[] = { 0x401870, 3, 0x401aa0, 3, 0x402210, 3, 0x41ef90, 1, 0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubTxt32[] = { 0x401ce0, 3, 0x401e70, 3, 0x402420, 3, 0x41ef90, 1, 0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubBox16[] = { 0x401870, 3, 0x401aa0, 3, 0x402210, 3, 0x402590, 1, 0x41ef90, 1,
	0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubBox32[] = { 0x401ce0, 3, 0x401e70, 3, 0x402420, 3, 0x402590, 1, 0x41ef90, 1,
	0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static void txtpass_setup(const DWORD *stubs)
{
	callee_stubs(stubs, 0);
	G32(0xa0e010) = (int)(BUF + 0x1000);
	static const DWORD ids[] = { 0x9dae1c, 0x76d360, 0x76d448, 0x9dad90 };
	for (int k = 0; k < 4; k++) G32(ids[k]) = irnd(0, 0x7ff);
	for (int k = 0; k < 4; k++) GF(0x76d438 + 4 * k) = csu_fr(0, 100);
	fill_str(BUF + 0x100, 40, 32, 126);
	g_a[0] = irnd(-20, 660); g_a[1] = irnd(-20, 500); g_a[2] = (int)(BUF + 0x100); g_a[3] = irnd(0, 300); g_a[4] = 8;
}
/* the four-argument passes take (x1, y, x2, text) */
static void txtbox_setup(const DWORD *stubs) { txtpass_setup(stubs); g_a[3] = g_a[2]; g_a[2] = g_a[0] + irnd(-20, 400); }
T_PLAIN(text_draw5, 0x403170, txtpass_setup(g_stubTxt5);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(text_draw8, 0x402620, txtpass_setup(g_stubTxt8);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(text_draw16, 0x4028b0, txtpass_setup(g_stubTxt16);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(text_draw32, 0x402c90, txtpass_setup(g_stubTxt32);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(text_draw8b, 0x402740, txtbox_setup(g_stubTxt8);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(text_drawBox16, 0x4029d0, txtbox_setup(g_stubBox16);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(hud_403210, 0x403210, txtbox_setup(g_stubTxt5);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(hud_402db0, 0x402db0, txtbox_setup(g_stubBox32);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* the menu pointer: on or off the screen, blink and click flash states, the frame time; the vertex helper, the
   projection and the bind stubbed (the right-hand corners go through the patch DLL's cursor_vtx when installed) */
static const DWORD g_stubCursor[] = { 0x41ef60, 2, 0x41ef90, 1, 0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static void cursor_setup(void)
{
	callee_stubs(g_stubCursor, 0);
	G32(0xa0e010) = (int)(BUF + 0x1000);
	G32(0x4ded68) = irnd(-50, 700); G32(0x4ded6c) = irnd(-50, 530); GF(0x4df910) = csu_fr(-100, 300);
	G32(0x4df03c) = irnd(0, 3); G32(0x4e152c) = irnd(0, 0x7ff); GF(0x4b071c) = csu_fr(0, 10);
}
T_PLAIN(menu_drawCursor, 0x429bc0, cursor_setup();, 0, 0, 0, 0, 0)
/* the size dispatchers: sizes among the fonts' and others; the passes stubbed */
static const DWORD g_stubSized[] = { 0x402620, 3, 0x4028b0, 3, 0x402c90, 3, 0x403170, 3, 0 };
static const DWORD g_stubSized2[] = { 0x402740, 4, 0x4029d0, 4, 0x402db0, 4, 0x403210, 4, 0 };
static void sized_setup(const DWORD *stubs)
{
	static const int sz[] = { 5, 8, 16, 32, 0, 7, 12, 64 };
	callee_stubs(stubs, 0);
	fill_str(BUF + 0x100, 40, 32, 126);
	g_a[0] = irnd(-20, 660); g_a[1] = irnd(-20, 500); g_a[2] = (int)(BUF + 0x100); g_a[3] = sz[irnd(0, 7)];
	g_a[4] = irnd(-20, 660);
}
T_PLAIN(text_drawSized, 0x44ad60, sized_setup(g_stubSized);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
ST(hud_44ae10, sized_setup(g_stubSized2); g_a[5] = g_a[3]; g_a[3] = g_a[2]; g_a[2] = g_a[4];,
	(((void (*)(int, int, int, int, int))0x44ae10)(g_a[0], g_a[1], g_a[2], g_a[3], g_a[5]), 0),
	(hud_44ae10(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[5], 0, 0, 0), 0))
/* the scaled box: corners on and off the 640 x 480 screen, the screen size; the fill stubbed */
static const DWORD g_stubBox[] = { 0x4685b0, 0, 0x4685c0, 0, 0x46bd60, 1, 0 };
static void hudbox_setup(void)
{
	static const int w[] = { 640, 800, 1024, 1920 }, h[] = { 480, 600, 768, 1080 };
	int k = irnd(0, 3);
	callee_stubs(g_stubBox, 0); callee_ret(0x4685b0, w[k]); callee_ret(0x4685c0, h[k]);
	for (int i = 0; i < 4; i++) g_a[i] = irnd(-20, 660);
}
T_PLAIN(hud_4950a0, 0x4950a0, hudbox_setup();, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* the title / menu frame end: the title counter near its limit, the version texts; the background, the transition
   (through the patch DLL's trans_wrap when installed), the colour and the text pass stubbed */
static const DWORD g_stubVersion[] = { 0x403170, 3, 0x41f0e0, 5, 0x429170, 0, 0x441740, 0, 0 };
static void version_setup(void)
{
	callee_stubs(g_stubVersion, 0);
	G32(0x4df01c) = irnd(0, 1); G32(0x4e0458) = irnd(10, 20); G32(0x76d3e8) = irnd(0, 3) * 100; GF(0x9da434) = csu_fr(0, 500);
}
T_PLAIN(menu_drawVersion, 0x41f8d0, version_setup();, 0, 0, 0, 0, 0)

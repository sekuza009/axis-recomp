/* batch 177: generated tests (tools/gentests.py, gen_setup from batch 172) plus two by hand */
static const DWORD g_gs_434e70[] = { 0x41ee40, 0, 0x452fe0, 0, 0x453180, 4, 0x457310, 0, 0 };
static const DWORD g_gi_434e70[] = { 0x5b1b54, 0x5b1b55, 0x4db708, 0x4db710, 0x4db8b4, 0x4dbb10, 0x4dbb78, 0x4dbbf8, 0x4df8e8, 0x67ef04, 0x67ef14, 0x76d368, 0x76d408, 0x9da3e0, 0x9dad94, 0x9dce48, 0 };
static const DWORD g_gb_434e70[] = { 0x67fb44, 0x9dd570, 0 };
T_PLAIN(app_onClose, 0x434e70, gen_setup(g_gs_434e70, g_gi_434e70, g_gb_434e70); /* 0x4dbbf8: the session record */ fill(BUF + 0x5000, 0x40); G32(0x4dbbf8) = (int)(BUF + 0x5000);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4062b0[] = { 0x41ee40, 1, 0x451e60, 0, 0x452fe0, 0, 0x453180, 4, 0x457310, 0, 0 };
static const DWORD g_gi_4062b0[] = { 0x4ded44, 0x4ded45, 0x9dae44, 0x9dae45, 0x9dae4c, 0x9dae4d, 0x9dae4e, 0x4db708, 0x4db710, 0x4db8b4, 0x4dbb10, 0x4dbb3c, 0x4dbb78, 0x4dbbf8, 0x4dedd0, 0x4df8e8, 0x67ef04, 0x67ef14, 0x76d368, 0x76d408, 0x9da3e0, 0x9dad94, 0x9dae20, 0 };
static const DWORD g_gb_4062b0[] = { 0x4dedb0, 0x67fb44, 0x9dae24, 0 };
T_PLAIN(app_shutdown, 0x4062b0, gen_setup(g_gs_4062b0, g_gi_4062b0, g_gb_4062b0); /* 0x4dbbf8: the session record */ fill(BUF + 0x5000, 0x40); G32(0x4dbbf8) = (int)(BUF + 0x5000);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_41f540[] = { 0x41e730, 2, 0x41ef60, 2, 0x41ef90, 1, 0x41f0e0, 5, 0x41f100, 0, 0x430bf0, 0, 0x430ca0, 0, 0x4411e0, 0, 0x4566c0, 1 | CS_POP, 0x457150, 1, 0x48b420, 0, 0 };
static const DWORD g_gi_41f540[] = { 0x4dd080, 0x4dd084, 0x4dd0a8, 0x4dd0ac, 0x4dd0c8, 0x4dd0cc, 0x4dd560, 0x4dd564, 0x4dda34, 0x4dda48, 0x4ded68, 0x4ded6c, 0x4deda8, 0x4df010, 0x4df01c, 0x4df03c, 0x4df8e0, 0x4df910, 0x4e0458, 0x4e14fc, 0x67ef0c, 0x680370, 0x76d350, 0x76d354, 0x76d358, 0x76d35c, 0x76d3e8, 0x76d3f0, 0x76d480, 0x9db978, 0xa0e010, 0 };
static const DWORD g_gb_41f540[] = { 0x76d438, 0 };
T_PLAIN(menuState100_intro, 0x41f540, gen_setup(g_gs_41f540, g_gi_41f540, g_gb_41f540); /* an inlined texture lookup: the set 0xa0e010 and the logo texture 0x76d3f0 from it */ G32(0x76d3f0) = menutex_fonts(menutex_setup());, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* the chat edit's subclass (stdcall: hwnd, msg, wparam, lparam): a key down (codes 9 .. 0x25: Enter sends the line,
   Esc, Tab, the arrows ...), the two room timers (0x29a, 0x115c) or another message, the original proc and the
   room / typing flags, the shift state; every callee stubbed. The 3D sound: sound 0..15 (the table 0xa0e02c), a
   source and a listener position (vectors in BUF), two values, the listener's ear vector, sound on or off */
static const DWORD g_stubChatEdit[] = { 0x431600, 1, 0x4521c0, 2, 0 };
static const DWORD g_stubSound3d[] = { 0x467db0, 2, 0x467dd0, 3, 0 };   /* Vec3_normalize real: it returns the length in ST0 */
static void chatedit_setup(void)
{
	static const DWORD msgs[] = { 0x100, 0x100, 0x100, 0x113, 0x102, 0x10 };
	static const DWORD ints[] = { 0x4dbbf4, 0x4ded18, 0x76d3e8, 0x9dc428, 0x9dd84c, 0x9dd868, 0x9dd888, 0x9dd900, 0 };
	for (const DWORD *p = ints; *p; p++) G32(*p) = irnd(0, 3);
	GF(0x9da434) = (float)irnd(-2, 4); fill_str((char *)0x9dc92c, 40, 32, 126);
	g_a[0] = 0x10010; g_a[1] = (int)msgs[irnd(0, 5)];
	g_a[2] = g_a[1] == 0x113 ? (irnd(0, 1) ? 0x29a : 0x115c) : irnd(0, 9) ? irnd(8, 0x26) : irnd(0, 255);
	g_a[3] = irnd(0, 0x7fffffff);
	g_mockKeyState = irnd(0, 1) ? 0x8000 : 0; g_mockWndRet = (DWORD)irnd(0, 5);
	callee_stubs(g_stubChatEdit, 0);
}
static void sound3d_setup(void)
{
	G32(0xa0e80c) = irnd(0, 3) ? 1 : 0; G32(0xa0e66c) = irnd(-10000, 0); G32(0x4e0c9c) = irnd(0, 100);
	for (int k = 0; k < 16; k++) G32(0xa0e02c + 4 * k) = irnd(0, 3) ? 0x1000 + k : 0;
	for (int k = 0; k < 6; k++) GF(BUF + 0x10 + 4 * k) = (float)irnd(-5000, 5000) / 10.0f;
	for (int k = 0; k < 3; k++) GF(0xa0e7d8 + 4 * k) = (float)irnd(-100, 100) / 100.0f;
	g_a[0] = irnd(0, 15); g_a[1] = (int)(BUF + 0x10); g_a[2] = (int)(BUF + 0x1c);
	g_a[3] = irnd(-10, 120); g_a[4] = irnd(0, 3) ? irnd(0, 100) : irnd(-50, 5000);
	callee_stubs(g_stubSound3d, 0);
}
ST(chat_editSubclass, chatedit_setup();, ((LONG (WINAPI *)(DWORD, DWORD, DWORD, DWORD))0x440840)(g_a[0], g_a[1], g_a[2], g_a[3]),
   chat_editSubclass(g_a[0], g_a[1], g_a[2], g_a[3]))
ST(sound_play3D, sound3d_setup();, ((DWORD (__cdecl *)(int, void *, void *, int, int))0x456ed0)(g_a[0], (void *)g_a[1], (void *)g_a[2], g_a[3], g_a[4]),
   sound_play3D(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], 0, 0, 0))

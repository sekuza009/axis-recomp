/* batch 204 */
/* the start-up load: the CD flag, 0x76d410, every check passing mostly (one time in eight not), the GL state answer,
   the scene's allocation given (a pointer only: its constructor is stubbed) or failing, the texture sizes, screen
   size and 0x4e0c90 random; every callee stubbed */
static const DWORD g_stubStartLoad[] = { 0x401000, 0, 0x401410, 2, 0x401780, 0, 0x4017b0, 1, 0x4017c0, 1, 0x41e550, 0,
	0x41e5b0, 0, 0x41e610, 0, 0x41e670, 0, 0x41e6d0, 0, 0x41edf0, 1, 0x41f0e0, 5, 0x42b590, 0, 0x42b830, 0, 0x42ba40, 0,
	0x42bc00, 0, 0x42bd40, 0, 0x42bde0, 0, 0x42bee0, 0, 0x42f940, 0, 0x42fb40, 0, 0x4302d0, 0, 0x430390, 0, 0x431680, 0,
	0x4460d0, 0, 0x4515d0, 0, 0x455080, 7 | CS_POP | CS_THIS, 0x4569d0, 6 | CS_POP | CS_THIS, 0x456be0, 8 | CS_POP | CS_THIS,
	0x456d10, 2, 0x460570, 0 | CS_THIS, 0x466c00, 0, 0x467a50, 1, 0x46afe0, 0, 0x46b950, 1, 0x46c270, 0, 0 };
static void startload_setup(void)
{
	callee_stubs(g_stubStartLoad, 0);
	static const DWORD chk[] = { 0x401000, 0x401410, 0x41e550, 0x41e5b0, 0x41e610, 0x41e670, 0x41e6d0 };
	for (int i = 0; i < 7; i++) callee_ret(chk[i], irnd(0, 7) ? 1 : 0);
	callee_ret(0x467a50, irnd(0, 1)); callee_ret(0x456be0, irnd(0, 100)); callee_ret(0x460570, 0x1234);
	g_mockBigAlloc = irnd(0, 3) ? (DWORD)BUF + 0x1000 : 0;
	G32(0x9dbf0c) = irnd(0, 1); G32(0x76d410) = irnd(0, 1);
	static const int w[] = { 640, 800, 1024, 1280, 1920 }, h[] = { 480, 600, 768, 960, 1080 };
	int k = irnd(0, 4); G32(0x5b1998) = w[k]; G32(0x4e045c) = h[k];
	G32(0x4e0c90) = irnd(0, 400); G32(0x83a9cc) = irnd(0, 3); G32(0x83a9d0) = irnd(0, 3);
	G32(0x4ded18) = 0x10010; g_a[0] = 0x400000;
}
T_PLAIN(app_checkCdAndLoad, 0x430400, startload_setup();, 0, g_a[0], 0, 0, 0)

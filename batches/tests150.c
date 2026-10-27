/* batch 149 */
/* a console at BUF (it fits: its stage at +0x1f36c8 ends below the mock heap): ownership flags inside the stage as
   Stage_dtor's test sets them (up to the stage's last fields, +0x2149330), the view volume at +0x74 as vvext_setup
   sets it, the delete flag 0..3 */
static void console_dtor_setup(void)
{
	char *vv = BUF + 0x74;
	owned_bits(BUF + 0x1f36c8 + 0x100, 0x2148000, irnd(0, 12));
	fill(vv, 0x40); S32(vv, 0xc) = irnd(0, 1); S32(vv, 8) = (int)(BUF + 0x3000);
	g_mockGlExt = (DWORD)irnd(0, 2); g_a[0] = irnd(0, 3);
}
ST(Console_ctor, console_dtor_setup();, (TC(void, 0x460c40, char *)(BUF), 0), (Console_ctor(BUF), 0))
ST(Console_deletingDtor, console_dtor_setup();, TC(DWORD, 0x460c20, char *, int)(BUF, g_a[0]), Console_deletingDtor(BUF, (DWORD)g_a[0]))

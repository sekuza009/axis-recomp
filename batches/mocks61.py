p = 'recomp.c'
s = open(p, encoding='utf-8-sig').read()

def rep(a, b):
    global s
    assert s.count(a) == 1, a[:70]
    s = s.replace(a, b)

rep("static void WINAPI mstub_glPixelStorei(DWORD p, DWORD v) { mock_rec(0x4a9268, 2, p, v, 0, 0); }",
    r"""static void WINAPI mstub_glPixelStorei(DWORD p, DWORD v) { mock_rec(0x4a9268, 2, p, v, 0, 0); }
/* window / font creation, registry key creation, texture names */
static DWORD WINAPI mstub_CreateFontIndirectA(const BYTE *lf) { mock_rec(0x4a9038, 1, mock_hash(lf, 60), 0, 0, 0); return 0xf0f0; }
static DWORD WINAPI mstub_SendMessageA(DWORD w, DWORD msg, DWORD wp, DWORD lp) { mock_rec(0x4a92ec, 4, w, msg, wp, lp); return 0; }
static DWORD WINAPI mstub_CreateWindowExA(DWORD ex, const char *cls, const char *name, DWORD style, int x, int y, int w, int h,
                                          DWORD parent, DWORD menu, DWORD inst, DWORD param)
{
	mock_rec(0x4a9350, 4, mock_hashstr(cls) ^ mock_hashstr(name), style ^ ex, (DWORD)x << 16 ^ (DWORD)y ^ (DWORD)w << 8 ^ (DWORD)h << 24, parent ^ menu ^ param);
	(void)inst;
	return 0xe0e0;
}
static LONG WINAPI mstub_SetWindowLongA(DWORD w, int i, LONG v) { mock_rec(0x4a9354, 3, w, (DWORD)i, (DWORD)v, 0); return 0x1234; }
static DWORD WINAPI mstub_SetFocus(DWORD w) { mock_rec(0x4a935c, 1, w, 0, 0, 0); return 0; }
static LONG WINAPI mstub_RegCreateKeyExA(DWORD key, const char *sub, DWORD res, char *cls, DWORD opt, DWORD sam, void *sa, DWORD *out, DWORD *disp)
{
	mock_rec(0x4a9010, 3, key, mock_hashstr(sub), opt ^ sam, 0);
	(void)res; (void)cls; (void)sa;
	if (g_mockRegFail) return 2;
	if (out) *out = 0x5000; if (disp) *disp = 2;
	return 0;
}
static void WINAPI mstub_glGenTextures(int n, DWORD *t) { mock_rec(0x4a925c, 1, (DWORD)n, 0, 0, 0); for (int i = 0; i < n && i < 64; i++) t[i] = 100 + i; }""")
rep("	{ 0x4a9050, (void *)mstub_gluOrtho2D }, { 0x4a9044, (void *)mstub_gluBuild2DMipmaps },",
    """	{ 0x4a9050, (void *)mstub_gluOrtho2D }, { 0x4a9044, (void *)mstub_gluBuild2DMipmaps },
	{ 0x4a9038, (void *)mstub_CreateFontIndirectA }, { 0x4a92ec, (void *)mstub_SendMessageA }, { 0x4a9350, (void *)mstub_CreateWindowExA },
	{ 0x4a9354, (void *)mstub_SetWindowLongA }, { 0x4a935c, (void *)mstub_SetFocus }, { 0x4a9010, (void *)mstub_RegCreateKeyExA },
	{ 0x4a925c, (void *)mstub_glGenTextures },""")
open(p, 'w', encoding='utf-8-sig').write(s)
print('ok')

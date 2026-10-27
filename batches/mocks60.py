p = 'recomp.c'
s = open(p, encoding='utf-8-sig').read()

def rep(a, b):
    global s
    assert s.count(a) == 1, a[:70]
    s = s.replace(a, b)

rep("static DWORD g_mockTick, g_mockRecvRet, g_mockGlExt;",
    "static DWORD g_mockTick, g_mockRecvRet, g_mockGlExt, g_mockDispRet, g_mockCaps, g_mockTimeMs;")
rep("static void WINAPI mstub_Sleep(DWORD ms) { mock_rec(0x4a9110, 1, ms, 0, 0, 0); }   /* tests must not wait */",
    r"""static void WINAPI mstub_Sleep(DWORD ms) { mock_rec(0x4a9110, 1, ms, 0, 0, 0); }   /* tests must not wait */
/* display mode, device caps, time, texture upload: scripted results; pixel data logged as size + hash */
static LONG WINAPI mstub_ChangeDisplaySettingsA(const BYTE *dm, DWORD fl) { mock_rec(0x4a9314, 2, dm ? mock_hash(dm, 0x9c) : 0, fl, 0, 0); return (LONG)g_mockDispRet; }
static int WINAPI mstub_GetDeviceCaps(DWORD dc, int idx) { mock_rec(0x4a9034, 2, dc, (DWORD)idx, 0, 0); return (int)(g_mockCaps + (DWORD)idx); }
static DWORD WINAPI mstub_GetDC(DWORD wnd) { mock_rec(0x4a9318, 1, wnd, 0, 0, 0); return 0xdc0; }
static void WINAPI mstub_GetSystemTime(WORD *t) { mock_rec(0x4a910c, 0, 0, 0, 0, 0); memcpy(t, g_mockTime, 16); }
static DWORD WINAPI mstub_timeGetTime(void) { mock_rec(0x4a9364, 0, 0, 0, 0, 0); g_mockTimeMs += 16; return g_mockTimeMs - 16; }
static DWORD pixels_hash(const void *px, int w, int h, DWORD fmt) { int bpp = fmt == 0x1908 ? 4 : fmt == 0x1907 ? 3 : 1; return px && w > 0 && h > 0 && w <= 2048 && h <= 2048 ? mock_hash(px, (DWORD)(w * h * bpp)) : 0; }
static void WINAPI mstub_glTexImage2D(DWORD tg, DWORD lv, DWORD ifmt, int w, int h, DWORD border, DWORD fmt, DWORD type, const void *px)
{ mock_rec(0x4a91e4, 4, tg ^ lv << 8 ^ ifmt << 16 ^ border << 24, (DWORD)w << 16 ^ (DWORD)h, fmt ^ type << 16, pixels_hash(px, w, h, fmt)); }
static void WINAPI mstub_glTexParameterf(DWORD tg, DWORD p, DWORD v) { mock_rec(0x4a9260, 3, tg, p, v, 0); }
static void WINAPI mstub_glBindTexture(DWORD tg, DWORD t) { mock_rec(0x4a9264, 2, tg, t, 0, 0); }
static void WINAPI mstub_glPixelStorei(DWORD p, DWORD v) { mock_rec(0x4a9268, 2, p, v, 0, 0); }
static void WINAPI mstub_gluOrtho2D(DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7)
{ DWORD v[8] = { a0, a1, a2, a3, a4, a5, a6, a7 }; mock_rec(0x4a9050, 1, mock_hash(v, 32), 0, 0, 0); }
static int WINAPI mstub_gluBuild2DMipmaps(DWORD tg, DWORD comp, int w, int h, DWORD fmt, DWORD type, const void *px)
{ mock_rec(0x4a9044, 4, tg ^ comp << 16, (DWORD)w << 16 ^ (DWORD)h, fmt ^ type << 16, pixels_hash(px, w, h, fmt)); return 0; }""")
rep("	{ 0x4a9110, (void *)mstub_Sleep }, { 0x4a9394, (void *)mstub_send },",
    """	{ 0x4a9110, (void *)mstub_Sleep }, { 0x4a9394, (void *)mstub_send },
	{ 0x4a9314, (void *)mstub_ChangeDisplaySettingsA }, { 0x4a9034, (void *)mstub_GetDeviceCaps }, { 0x4a9318, (void *)mstub_GetDC },
	{ 0x4a910c, (void *)mstub_GetSystemTime }, { 0x4a9364, (void *)mstub_timeGetTime }, { 0x4a91e4, (void *)mstub_glTexImage2D },
	{ 0x4a9260, (void *)mstub_glTexParameterf }, { 0x4a9264, (void *)mstub_glBindTexture }, { 0x4a9268, (void *)mstub_glPixelStorei },
	{ 0x4a9050, (void *)mstub_gluOrtho2D }, { 0x4a9044, (void *)mstub_gluBuild2DMipmaps },""")
rep("	g_mockTick = 100000; g_mockRecvRet = 0; g_mockGlExt = 1;",
    "	g_mockTick = 100000; g_mockRecvRet = 0; g_mockGlExt = 1; g_mockDispRet = 0; g_mockCaps = 32; g_mockTimeMs = 5000;")
open(p, 'w', encoding='utf-8-sig').write(s)
print('ok')

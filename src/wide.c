/* wide.c: the patch DLL's widescreen state as the rebuilds see it (wide.h). Until the patch DLL hands over its
   table, and for good without one, everything reads 0: no fix, the original's drawing. */
#include "wide.h"

static const int off;
static int unused;
static void CDECL no_fullScreen(int on) { (void)on; }

static int no_mousePressed(int key) { (void)key; return 0; }
static int no_latch[3];
static void CDECL no_cursorClamp(void) {}
static const float *const no_float;
static void **const no_slot;
static const Wide none = { sizeof(Wide), &off, &off, &off, &off, &off, &off, &off, &unused, no_fullScreen,
                           0, 0, &off, no_mousePressed, no_latch, &off, no_cursorClamp, &off, &unused, NULL,
                           &off, &no_float, &no_slot, NULL };
const Wide *g_wide = &none;

/* called by the patch DLL (test build) right after it loads recomp.dll */
__declspec(dllexport) void recomp_setWide(const Wide *wide)
{
	if (wide && wide->size == (int)sizeof(Wide))
		g_wide = wide;
}

void *wide_callSite(u32 site)
{
	if (g_wide->callSite)
		return g_wide->callSite(site);
	return (void *)(RELOC(site) + 5 + *(const i32 *)(RELOC(site) + 1));   /* (the call instruction's target) */
}

int wide_callAdded(u32 site, u32 at, const char *pattern)
{
	return g_wide->callSite ? g_wide->callSite(site) != NULL : code_matches(at, pattern);
}

/* for the harness: the patch DLL handed its table over, and it put in its own menu_vertex / menu_drawRect */
int wide_menuFix(void) { return g_wide != &none && *g_wide->menuFix; }
int wide_present(void) { return g_wide != &none; }

/* for the harness's tests: the menu cursor's state as the patch DLL's cursor_draw sets it while it draws (on, the
   viewport's left edge and width), so menu_vertex is compared with the patch DLL's own version on the cursor too */
void wide_testCursor(int on, int x, int w)
{
	if (g_wide == &none)
		return;
	*(volatile int *)g_wide->cursorX = x;
	*(volatile int *)g_wide->cursorW = w;
	*(volatile int *)g_wide->cursorOn = on;
}

int wide_carries(u32 addr)
{
#ifdef AXIS_DIRECT
	const int entryJumps = 1;   /* (AxisRC.exe: the patch layer's flags say it all; it rewrites no game code) */
#else
	const u8 *p = (const u8 *)RELOC(addr);
	const int entryJumps = p[0] == 0xE9;
#endif
	switch (addr) {
	case 0x41ef60: case 0x427970:   /* menu_vertex, menu_drawRect: replaced by the patch DLL's own versions */
		return wide_menuFix() && entryJumps;
	case 0x401600:                  /* input_justPressed: its entry jumps to the mouse-button latch */
		return *g_wide->pressedFix && entryJumps;
	case 0x445c60:                  /* input_updateMouse: the mouse read's call retargeted (followed live), the
	                                   clamp replaced (cursorClampFix): both carried */
		return 1;
	case 0x461850:                  /* armc_drawPreview3D: four instructions of the turn (rotFix) */
		return 1;
	}
	return 0;
}

/* for the harness: the patch DLL's writable data (NULL without its table) */
u8 *wide_state(u32 *size)
{
	*size = g_wide->stateSize;
	return g_wide->stateSize ? g_wide->state : NULL;
}

/* for the harness's tests: the patch DLL's latch for mouse button i (input_justPressed) */
void wide_testMouseLatch(int i, int on)
{
	g_wide->mouseLatch[i] = on;
}

/* for the harness's log: which of the patch DLL's in-memory changes are installed */
int wide_fixes(void)
{
	return wide_menuFix() | *g_wide->pressedFix << 1 | *g_wide->cursorClampFix << 2 | *g_wide->rotFix << 3;
}

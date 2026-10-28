/* wide.c: the patch DLL's widescreen state as the rebuilds see it (wide.h). Until the patch DLL hands over its
   table, and for good without one, everything reads 0: no fix, the original's drawing. */
#include "wide.h"

static const int off;
static int unused;
static void CDECL no_fullScreen(int on) { (void)on; }

static const Wide none = { sizeof(Wide), &off, &off, &off, &off, &off, &off, &off, &unused, no_fullScreen };
const Wide *g_wide = &none;

/* called by the patch DLL (test build) right after it loads recomp.dll */
__declspec(dllexport) void recomp_setWide(const Wide *wide)
{
	if (wide && wide->size == (int)sizeof(Wide))
		g_wide = wide;
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

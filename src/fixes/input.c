/* fixes/input.c (native build, AXIS_NATIVE): the patch layer's input fixes as the game's own code. Each was done
   from outside before (axisnet_recomp.c: mouse_pressed, input_read, menu_mouse, cursor_clamp, menu_nav,
   label_halfw); they are called from the functions they change. */
#ifdef AXIS_NATIVE
#include "../game.h"
#include "fixes.h"
#include <string.h>

/* ---- the mouse buttons in key bindings latch like keys (input_justPressed). The original answered a button's
   one-frame click pulse only when a flag that flips on every call was 0, so with one test per frame (the Esc
   menu's select) about every other click was lost. ---- */
static int g_buttonLatch[3];

int fix_mousePressed(int key)
{
	int i = key - 0xfa;
	if (!g_mouseClicked[i]) {
		g_buttonLatch[i] = 0;
		return 0;
	}
	if (g_buttonLatch[i])
		return 0;
	g_buttonLatch[i] = 1;
	return 1;
}

/* the menus' box on the screen: its width in pixels (a centred 4:3 box, or 16:9 with [hud] menu43=0) */
static int menu_boxWidth(int w, int h)
{
	if (g_settings.menu43)
		return w * 3 > h * 4 ? h * 4 / 3 : w;
	return w * 9 > h * 16 ? h * 16 / 9 : w;
}

/* ---- the mouse read (input_updateMouse's input_readMouse) ----
   Buttons: the window stays visible after alt-tab, so a click on it brings the game back and the exclusive mouse
   is acquired while that button is down; its release could be missed and the button stayed held. Back in the
   foreground, each button now counts only once it has been seen released.
   Menu pointer speed: the read's counts move the pointer in 640 x 480 units, one count a pixel at 640 x 480 but
   box / 640 pixels on a big screen (4.5 at 4K) - far faster than the Windows pointer. In the menus the counts are
   scaled to about one screen pixel each (per axis) times the Windows pointer speed and [input] menusens; the
   fraction carries to the next frame. In a match the pointer is centred every frame and its offset is the turn
   rate, so aiming is untouched. */
static u8 g_buttonsAwaitingRelease;
static float g_carryX, g_carryY;

static void menu_pointerSpeed(int *move)
{
	if (g_settings.menuSens <= 0 || g_screen == 0x270f) {
		g_carryX = g_carryY = 0;
		return;
	}
	int w = g_screenW, h = g_screenH;
	if (w <= 0 || h <= 0)
		return;
	int boxW = menu_boxWidth(w, h);
	float k = platform_pointerSpeed() * g_settings.menuSens;
	float fx = move[0] * k * 640.0f / boxW + g_carryX, fy = move[1] * k * 480.0f / h + g_carryY;
	move[0] = (int)fx;   /* (toward 0; the rest carried) */
	move[1] = (int)fy;
	g_carryX = fx - move[0];
	g_carryY = fy - move[1];
}

int fix_readMouse(void)
{
	int r = ((int (CDECL *)(void))(void *)FN_input_readMouse)();
	u8 *buttons = (u8 *)g_mouseState + 0xc;   /* DIMOUSESTATE.rgbButtons */
	if (g_mainWindow && !platform_isForeground(AP(void, g_mainWindow)))
		g_buttonsAwaitingRelease = 0x0f;
	else {
		platform_mouseButtons((buttons[0] >> 7) | (buttons[1] >> 7 << 1) | (buttons[2] >> 7 << 2));
		for (int i = 0; i < 4; i++) {
			if (!(buttons[i] & 0x80))
				g_buttonsAwaitingRelease &= ~(1 << i);
			else if (g_buttonsAwaitingRelease & (1 << i))
				buttons[i] = 0;
		}
	}
	menu_pointerSpeed(g_mouseState);   /* DIMOUSESTATE.lX / lY */
	if (g_mainWindow)
		platform_watchWindow(AP(void, g_mainWindow), AP(void *, ADDR(g_hEditField)), AP(void *, ADDR(g_mouse)));
	return r;
}

/* ---- the menu pointer's clamp (input_updateMouse): the whole width of a wide screen, not 0 .. 630 of the box ---- */
void fix_cursorClamp(void)
{
	int lo = 0, hi = 630, w = g_screenW, h = g_screenH;
	if (w > 0 && h > 0) {
		int boxW = menu_boxWidth(w, h);
		if (boxW > 0 && boxW < w) {
			int boxX = (w - boxW) / 2;
			lo = -(boxX * 640 / boxW);
			hi = (w - boxX) * 640 / boxW - 10;
		}
	}
	if (g_mouseX > hi) g_mouseX = hi;
	if (g_mouseY > 474) g_mouseY = 474;
	if (g_mouseX < lo) g_mouseX = lo;
	if (g_mouseY < 0) g_mouseY = 0;
}

/* ---- the Esc menu in a match, by mouse (match_readInput). The original turned any frame's offset over 50 into a step
   up or down: built for 30 fps and 400 dpi mice, at 120 fps a gentle slide raced through the items. Now the travel
   adds up along the page's own direction - up and down on the main page's column, left and right on the side by side
   pairs (the team's RED / BLUE, RETRY's and QUIT's YES / NO), the other direction ignored - and each step takes a
   quarter of the screen's height of movement at the Windows pointer speed (divided by [input] escmenusens). ---- */
static float g_menuTravel;
static unsigned g_menuTick;
static int g_menuPage;

void fix_escMenuNav(Scene *scene)
{
	unsigned now = platform_ticks();
	int page = scene->escPage, across = page == 1 || page == 3 || page == 4;
	if (now - g_menuTick > 250 || page != g_menuPage)   /* the menu just (re)opened, or another page */
		g_menuTravel = 0;
	g_menuTick = now;
	g_menuPage = page;
	int s = g_mouseSensitivity, h = g_screenH;
	float f = ((s * 0.02f) * (s * 0.02f) + 1) * 0.5f, d;   /* (the offsets back to the raw counts) */
	if (across)
		d = scene->mouseDx / f;   /* (right: the second item) */
	else {
		d = scene->mouseDy / f;
		if (g_mouseInvert)   /* (the menu follows the hand) */
			d = -d;
	}
	if (d * g_menuTravel < 0)   /* turned round */
		g_menuTravel = 0;
	g_menuTravel += d;
	float sens = platform_pointerSpeed() * g_settings.menuSens * (g_settings.escMenuSens > 0 ? g_settings.escMenuSens : 1);
	float step = (h > 0 ? h : 480) / 4.0f / sens;
	if (g_menuTravel <= -step) {
		scene->menuKeys[0] = 1;
		g_menuTravel = 0;
	} else if (g_menuTravel >= step) {
		scene->menuKeys[1] = 1;
		g_menuTravel = 0;
	}
}

/* ---- a player's name label (hud_drawPlayerMarkers): the icon left of it ended at x - (len / 2) * 8, but the text
   starts at x - 4 * (len - 5 * colour codes), so for odd-length names the icon covered half the first letter. Half
   the text's own width instead. ---- */
int fix_labelHalfWidth(const char *name)
{
	int len = (int)strlen(name), codes = 0;
	for (int i = 0; i < len; i++)
		if (name[i] == '$' && name[i + 1] == '[' && name[i + 3] == ']' && name[i + 5])
			codes++;
	return 4 * (len - 5 * codes);
}
#endif

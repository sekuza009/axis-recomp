/* profile_misc.c: small pieces of the pilot profiles: the save files' byte scrambling, name checks, and a profile's
   colour record loaded for the preview. */
#include "../game.h"
#include <string.h>
#include "key_repeat.h"

/* the bytes xored with a key that counts up by one (from key); the reset of the key is dead code in the original
   (a signed byte is never above 0xa5) */
static void crypt_bytes(u8 *p, int n, u8 key)
{
	for (int i = 0; i < n; i++) {
		p[i] ^= key;
		key++;
		if ((int)(signed char)key > 0xa5)
			key = 0x7e;
	}
}

/* 0x445f10, 0x445f40: a 0x104-byte and a 0x80-byte record scrambled (or unscrambled: the same xor) */
void (crypt_record104)(u8 *p, u8 key) { crypt_bytes(p, 0x104, key); }
void (crypt_record80)(u8 *p, u8 key) { crypt_bytes(p, 0x80, key); }

/* 1 if any character of s is one of bad */
static int has_any(const char *s, const char *bad)
{
	int n = 0;
	while (s[n] != '\0')
		n++;
	for (int i = 0; i < n; i++)
		for (const char *b = bad; *b != '\0'; b++)
			if (s[i] == *b)
				return 1;
	return 0;
}

/* 0x434400: a room name with a character the network messages cannot carry; 0x44b7e0: a pilot name that cannot be
   a file name */
int (room_nameHasBadChar)(const char *s) { return has_any(s, "`\"',/\\|~?"); }
int (profile_nameHasBadChar)(const char *s) { return has_any(s, "\\/:*?\"<>|"); }

/* profile colour record i (nine ints, 76 bytes a record from 0x9f9068) into the preview's floats, each plus the
   constant at 0x4a9560; the preview reset (distance 40, -1, not turning) */
static void load_colour(int i)
{
	(*(u32 *)&g_profileFrameAlpha) = 0x42200000;   /* 40.0 */
	g_profileFrameStep = 0xbf800000;   /* -1.0 */
	g_emblemMoved = 0;
	for (int k = 0; k < 9; k++)
		GAME_VAR(float, 0x9f8ec0 + k * 4) =
			(float)((long double)GAME_VAR(int, 0x9f9068 + i * 76 + k * 4) + k_50f);
}

/* 0x44bc50: the selected profile's colours; 0x44bd20: those of the pilot under the list cursor */
void (profile_loadSelectedColours)(void) { load_colour(g_emblemCursor); }
void (profile_loadCursorColours)(void) { load_colour(GAME_VAR(int, 0x9f688c + g_pilotChosen * 72)); }

/* 0x445ee0: a whole 0x3ac-byte profile record scrambled */
void (save_cryptRecord)(u8 *rec, u8 key) { crypt_bytes(rec, 0x3ac, key); }

/* 0x42b3c0: a 0x4c-byte record scrambled with a key that just counts up (no reset); returns the count */
int (crypt_countingKey)(u8 *p, u8 key)
{
	int i;
	for (i = 0; i < 0x4c; i++)
		p[i] ^= key++;
	return i;
}

/* 0x42b390: every byte of s inverted in place; its length */
int (str_invert)(char *s)
{
	int n = (int)strlen(s);
	for (int i = 0; i < n; i++)
		s[i] = ~s[i];
	return n > 0 ? n : 0;
}

/* 0x4343b0: 1 when a name is blank (only spaces and control characters) */
int (name_isBlank)(const char *name)
{
	int n = (int)strlen(name);
	for (int i = 0; i < n; i++)
		if (name[i] < 0 || name[i] > 0x20)
			return 0;
	return 1;
}

/* 0x44b2e0: 1 when (x, y) is in the dialog box rectangle at 0x9f9010 (left, top, right, bottom), else -1 */
int (profile_inDialogBox)(int x, int y)
{
	const int *r = (const int *)IMG(0x9f9010);
	return x >= r[0] && x <= r[2] && y >= r[1] && y <= r[3] ? 1 : -1;
}

/* 0x44b7a0: the colour preview reset: no colours, distance 40, -1, turning */
void (profile_resetPreview)(void)
{
	memset((void *)IMG(0x9f8ec0), 0, 36);
	memset((void *)IMG(0x9f8d34), 0, 36);
	g_emblemMoved = 1;
	(*(u32 *)&g_profileFrameAlpha) = 0x42200000;   /* 40.0 */
	g_profileFrameStep = 0xbf800000;   /* -1.0 */
}

/* 0x44b750: the same, and no profile selected */
void (profile_resetSelection)(void)
{
	profile_resetPreview();
	g_emblemCursor = 0;
	g_profile9f8ee4 = 0;
	g_profile9f6828 = 0;
}

/* 0x44bc00: the profile screen's camera put to its start (distance 80, speed 0.1) */
void (profile_resetCamera)(void)
{
	g_profileIntroState = 0;
	g_profileIntro = 1;
	g_unusedProfileCameraWord = -1;
	(*(u32 *)&g_profileIntroZoom) = 0x42a00000;   /* 80.0 */
	g_profileIntroTime = 0;
	(*(u32 *)&g_profileIntroSpeed) = 0x3dcccccd;   /* 0.1 */
	g_profilePage = 1;
}

/* 0x44b870: does a profile with the typed name (0x9dc92c) exist, ignoring case? (The original's trailing-space trim
   can't run: it is skipped whenever the length is >= 0. Its compare buffer keeps the tail of a longer earlier
   name, as here.) */
int (profile_nameExists)(void)
{
	char typed[1024], name[1024];
	memset(name, 0, sizeof name);
	memset(typed, 0, sizeof typed);
	const char *s = (const char *)IMG(0x9dc92c);
	for (int i = 0, n = (int)strlen(s); i < n; i++)
		typed[i] = s[i] >= 'A' && s[i] <= 'Z' ? s[i] + 0x20 : s[i];
	for (int e = 0; e < g_profileCount; e++) {
		const char *p = (const char *)(IMG(0x9f684c) + e * 0x48);
		for (int i = 0, n = (int)strlen(p); i < n; i++)
			name[i] = p[i] >= 'A' && p[i] <= 'Z' ? p[i] + 0x20 : p[i];
		if (!strcmp(typed, name))
			return 1;
	}
	return 0;
}

/* ---- the profile screen's confirmation dialogs: a click on the first button does the thing (with the menu sound),
   the second (or a right click) closes the dialog (0x9f8f10). Both return the right click state (the original's eax) */
/* 0x44c390: "delete this profile?" */
int (profile_openDeleteQuestion)(void)
{
	(*(int *)&g_cursorBlink) = 0;
	if (g_mouseClick) {
		int button = deleteDialog_hitTest(g_mouseX, g_mouseY);   /* the dialog's hit test */
		if (button == 0) {
			sound_playMenu(0);
			profile_deleteFiles();
			g_profilePage = 1;
		} else if (button == 1) {
			sound_playMenu(0);
			g_profilePage = 1;
		}
	}
	if (g_keyEnter)
		g_profilePage = 1;
	return g_keyEnter;
}

/* 0x44c400: the second dialog: its first button runs profile_resetCamera, the second closes it (and clears 0x76d42c) */
int (profile_secondDialogClicks)(void)
{
	(*(int *)&g_cursorBlink) = 0;
	if (g_mouseClick) {
		int button = secondDialog_hitTest(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_resetCamera();
		} else if (button == 1) {
			sound_playMenu(0);
			g_profilePage = 1;
			g_highlightShown = 0;
		}
	}
	if (g_keyEnter)
		g_profilePage = 1;
	return g_keyEnter;
}

/* 0x44f6c0: logging in with the selected profile (when 0x9f6840): the profile saved, the main menu (state 300), the
   profile's name as the player's (0x20 bytes), then axis.cfg loaded. Returns what the original leaves in eax */
u32 (profile_logIn)(void)
{
	if (!g_profileDialogOpen)
		return 0;
	g_lobbyReply = 0;
	if (g_startedFromLobby == 1)
		g_lobbyReply = 0x65;
	GAME_FN(profile_save, 0x446a10, void, void)();   /* profile_save */
	g_menuState = 300;
	g_nextScreen = 300;
	g_keysBlocked = 2;
	g_unusedMenuReturnWord = 0;
	GAME_CDECL(0x49ea80, char *, char *, const char *, u32)((char *)IMG(0x4dedb0),
	                                                        (const char *)(IMG(0x9f684c) + g_currentProfile * 0x48), 0x20);   /* strncpy */
	return GAME_FN(cfg_loadAxisCfg, 0x42d730, u32, void)();   /* cfg_loadAxisCfg */
}

#define CALL(addr) GAME_CDECL(addr, u32, void)()

/* 0x44f410: the profile screen's frame: the message's timer (0x9f8f18, to 0x4a944c; then the message goes), the
   dialog's frame and its page (0x44b600) while open, else the screen (an entry being edited first), the page shown.
   Returns what the original leaves in eax */
u32 (profile_frame)(void)
{
	if (g_profileRowClicked) {
		long double t = fadd_m(fld_m(&g_frameTime), (const float *)ADDR(g_profileMessageTime));
		g_profileMessageTime = (float)t;
		if (t > k_20f) {
			g_profileRowClicked = 0;
			(*(int *)&g_profileMessageTime) = 0;
		}
	}
	if (g_dialogOpen) {
		menu_drawFrame(g_profilePageLeft, g_profilePageTop, g_profilePageRight, g_profilePageBottom);
		if (g_dialogOpen)
			return (u32)g_dialogOpen;
		if (!g_profileScreenReady)
			return 0;
		return GAME_FN(profile_typeNewName, 0x44b600, u32, void)();
	}
	if (g_emblemMoved)
		GAME_FN(profile_loadCursorColours, 0x44bd20, u32, void)();
	g_profilePage = 1;
	return GAME_FN(mainmenu_drawScreen, 0x44d720, u32, void)();
}

/* 0x44c560: the profile screen's input: while its intro plays (0x9f6838) a click skips it (to state 5, the panel
   sliding in from 100 at 0.05); else, with no dialog, by page (0x9f8f10): 1 the list, 2 the new profile, 3 and 5 the
   dialogs, 6 the profile list's clicks. Returns what the original leaves in eax */
u32 (profile_processInput)(void)
{
	int intro = g_profileIntro;
	if (intro && g_profileIntroState != 5) {
		u32 r = g_mouseClick ? (u32)g_mouseClick : (*(u32 *)&g_keyEnter);
		if (r) {
			g_profileIntroState = 5;
			g_profileIntroTime = 0;
			(*(u32 *)&g_profileIntroZoom) = 0x42c80000;   /* 100 */
			(*(u32 *)&g_profileIntroSpeed) = 0x3d4ccccd;   /* 0.05 */
		}
		return r;
	}
	if (g_dialogOpen || intro)
		return (u32)intro;
	u32 page = (*(u32 *)&g_profilePage) - 1;
	switch (page) {
	case 0: return GAME_FN(profileList_mouse, 0x44be00, u32, void)();
	case 1: return GAME_FN(profile_newNameDialog, 0x44c190, u32, void)();
	case 2: return GAME_FN(profile_openDeleteQuestion, 0x44c390, u32, void)();   /* profile_openDeleteQuestion */
	case 4: return GAME_FN(profile_secondDialogClicks, 0x44c400, u32, void)();   /* profile_secondDialogClicks */
	case 5: return GAME_FN(profileList_clicks, 0x44c480, u32, void)();   /* profileList_clicks */
	}
	return page;
}

/* 0x44c480: the profile list's clicks: rows 0 .. 8 select a profile (with sound 2, its pilot panel reset), 9 logs in
   with the typed name (profile_selectAndLoad), 10 cancels; a right click closes the page. Returns the right click
   state (the original's eax) */
int (profileList_clicks)(void)
{
	(*(int *)&g_cursorBlink) = 0;
	if (g_mouseClick) {
		u32 row = GAME_FN(pilotSelect_hitTest, 0x44b3e0, u32, int, int)(g_mouseX, g_mouseY);   /* the list's hit test */
		if (row <= 8) {
			if ((*(u32 *)&g_emblemCursor) != row) {
				(*(u32 *)&g_emblemCursor) = row;
				g_emblemMoved = 1;
				sound_playMenu(2);
				g_profile9f8ee4 = 0;
				g_profile9f6828 = 0;
			}
		} else if (row == 9) {
			sound_playMenu(0);
			GAME_FN(profile_selectAndLoad, 0x44b990, u32, void)();   /* profile_selectAndLoad */
			g_profilePage = 1;
		} else if (row == 10) {
			sound_playMenu(0);
			g_profilePage = 1;
			g_highlightShown = 0;
		}
	}
	if (g_keyEnter)
		g_profilePage = 1;
	return g_keyEnter;
}

#define chdir_(path) GAME_CDECL(0x49f8a6, int, const char *)(path)
#define mkdir_(path) GAME_CDECL(0x49f94a, int, const char *)(path)

/* 0x44b990: a new profile made from the typed name: it goes into the next slot (with the chosen pilot, 0x9f8d30), the
   save folder is made if missing, the list scrolls to show it (13 rows), it is saved (profile_load) and the screen
   updated. Returns what that leaves in eax */
u32 (profile_selectAndLoad)(void)
{
	int n = g_profileCount;
	strcpy((char *)(IMG(0x9f684c) + n * 0x48), (const char *)IMG(0x9dc92c));
	GAME_VAR(int, 0x9f688c + n * 0x48) = g_emblemCursor;
	if (chdir_((const char *)STR(0x4b2adc, "save"))) {
		mkdir_((const char *)STR(0x4b2adc, "save"));
		chdir_((const char *)STR(0x4b2adc, "save"));
	}
	chdir_((const char *)STR(0x4b2a80, ".."));
	int count = n + 1;
	g_profileCount = count;
	if (count <= 0xd) {
		g_profileListRow = count - 1;
		g_pilotChosen = g_profileListTop + count - 1;
	} else {
		g_profileListRow = 0xc;
		g_profileListTop = count - 0xd;
		g_pilotChosen = count - 1;
	}
	GAME_FN(profile_load, 0x446590, u32, void)();         /* profile_load (it writes the profile) */
	return GAME_FN(profile_resetPreview, 0x44b7a0, u32, void)();  /* profile_resetPreview */
}

/* a profile screen page with a panel: while the pointer glides (0x76d42c) it is pulled towards its target (0x67ef34,
   0x67fb38) by the frame time times rate, until the glide's timer (0x680bc0) runs out; the screen drawn, then the
   dialog's frame (at frame: x0, y0, x1, y1) if one is open, else the panel. Returns what the original leaves in eax */
static u32 glide_page(const float *rate, const u32 *frame, u32 panel)
{
	if (g_highlightShown) {
		int step = ftol(fmul_m(fmul_m((long double)(g_highlightX - g_mouseX), &g_frameTime), rate));
		g_mouseX += step;
		step = ftol(fmul_m(fmul_m((long double)(g_highlightY - g_mouseY), &g_frameTime), rate));
		g_mouseY += step;
		long double t = fsub_m(fld_m((const float *)IMG(0x680bc0)), &g_frameTime);
		g_highlightSize = (float)t;
		if (!(t >= k_0f))
			g_highlightShown = 0;
	}
	GAME_FN(mainmenu_drawScreen, 0x44d720, u32, void)();   /* mainmenu_drawScreen */
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(GAME_VAR(int, frame[0]), GAME_VAR(int, frame[1]),
		                                                     GAME_VAR(int, frame[2]), GAME_VAR(int, frame[3]));   /* menu_drawFrame */
	return CALL(panel);
}
/* 0x44f5f0: the pilot panel's page (profile_drawDeleteQuestion) */
u32 (profile_pilotPanelPage)(void)
{
	static const u32 frame[4] = { IMG(0x9f8f1c), IMG(0x9f8f0c), IMG(0x9f8f2c), IMG(0x9f8f28) };
	return glide_page((const float *)ADDR(k_0_25f), frame, FN_ADDR(profile_drawDeleteQuestion, 0x44e180));
}
/* 0x44f740: the second panel's page (profile_drawSecondDialog), gliding at its own rate */
u32 (profile_secondPanelPage)(void)
{
	static const u32 frame[4] = { IMG(0x9f6834), IMG(0x9f683c), IMG(0x9f93bc), IMG(0x9f93c0) };
	return glide_page((const float *)ADDR(k_0_2f), frame, FN_ADDR(profile_drawSecondDialog, 0x44e3e0));
}

/* 0x44ce90: the profile list's names drawn (13 rows from the top entry 0x9f8c4c, 20 units apart in the panel at
   0x9f8e48): grey-blue, the selected one brighter; dimmer while a dialog page is up (page other than 1). Returns the
   last text call's eax */
u32 (profileList_drawNames)(void)
{
	u32 r = 0;
	for (int i = 0; i < 13 && i < g_profileCount; i++) {
		int page1 = g_profilePage == 1;
		u32 shade = page1 ? 0x3f000000 : 0x3e99999a;   /* 0.5 / 0.3 */
		GAME_FN(Color4_set, 0x41f0e0, void, void *, u32, u32, u32, u32)((void *)IMG(0x76d438), 0, shade, shade, 0x3f800000);
		if (g_profileListTop + i == g_pilotChosen) {
			shade = g_profilePage == 1 ? 0x3f800000 : 0x3f000000;   /* 1 / 0.5 */
			GAME_FN(Color4_set, 0x41f0e0, void, void *, u32, u32, u32, u32)((void *)IMG(0x76d438), 0, shade, shade, 0x3f800000);
		}
		r = GAME_FN(text_draw8, 0x402620, u32, int, int, const char *)(g_profilePageLeft + 0x28, g_profilePageTop + 0x24 + i * 0x14,
		                                                      (const char *)(IMG(0x9f684c) + (g_profileListTop + i) * 0x48));   /* text_draw8 */
	}
	return r;
}

/* 0x44f4b0: the profile screen's name entry step (after 0x44d720): with a dialog open its frame is drawn
   (0x428c30); while a profile is being made (0x9f8f34) 0x44dc60; once the typed name (0x9dc92c) is in (the keyboard
   back): empty cancels, an existing name (name_isBlank) or a bad one (profile_nameHasBadChar, message 0x81) is refused
   with sound 6, otherwise the profile is made (profile_nameExists; failing that state 6 and 0x44b750). Returns the
   last call's eax */
u32 (profile_nameEntryStep)(void)
{
	const char *typed = (const char *)IMG(0x9dc92c);
	GAME_FN(mainmenu_drawScreen, 0x44d720, void, void)();
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(g_newNameDialogLeft, g_newNameDialogTop,
		                                                     g_newNameDialogRight, g_newNameDialogBottom);
	if (g_profileMessage)
		return GAME_FN(profile_drawMessageWindow, 0x44dc60, u32, void)();
	if (g_paused)
		return GAME_FN(profile_drawNewDialog, 0x44de00, u32, void)();
	if (!strlen(typed)) {
		g_dialogOpen = 0;
		g_profileMessage = 0;
		g_profilePage = 1;
		return GAME_FN(profile_drawNewDialog, 0x44de00, u32, void)();
	}
	if (GAME_FN(name_isBlank, 0x4343b0, int, const char *)(typed) == 1) {   /* name_isBlank */
		u32 r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(6);              /* sound_playMenu */
		g_profilePage = 1;
		g_dialogOpen = 0;
		g_profileMessage = 0;
		return r;
	}
	if (GAME_FN(profile_nameHasBadChar, 0x44b7e0, int, const char *)(typed) == 1) {   /* profile_nameHasBadChar */
		sound_playMenu(6);
		g_dialogOpen = 0;
		g_profileMessage = 0;
		g_profilePage = 1;
		return GAME_FN(menu_showMessage, 0x41ee40, u32, int)(0x81);             /* the message */
	}
	if (GAME_FN(profile_nameExists, 0x44b870, int, void)()) {                     /* profile_nameExists */
		sound_playMenu(6);
		g_profileMessage = 1;
		g_dialogOpen = 1;
		return GAME_FN(profile_drawNewDialog, 0x44de00, u32, void)();
	}
	g_profilePage = 6;
	GAME_FN(profile_resetSelection, 0x44b750, void, void)();
	return GAME_FN(profile_drawNewDialog, 0x44de00, u32, void)();
}

/* 0x44ba60: the current profile (0x9f8d74) deleted: its save file ("save\<name>.axs") removed (DeleteFileA, tried
   twice), the later profiles moved down a slot and the freed last slot cleared (colour -1), the count lowered.
   With none left everything is reset and the list written (profile_delete); otherwise, if the current one was the
   last, the selection steps back (the scrolled row 0x9f8c5c, else the list's top 0x9f8c4c), then the list is
   written and shown again (profile_resetPreview). Returns the last call's eax */
u32 (profile_deleteFiles)(void)
{
	int current = g_pilotChosen;
	u8 *records = (u8 *)IMG(0x9f6848);   /* 0x48 bytes each: +0 a word, +4 the name, +0x44 the colour */
	if (GAME_CDECL(0x49f8a6, int, const char *)((const char *)STR(0x4b2adc, "save")) == 0) {   /* chdir("save") */
		char path[0x80];
		memset(path, 0, sizeof path);
		strcpy(path, (const char *)(records + current * 0x48 + 4));
		strcat(path, (const char *)STR(0x4b2afc, ".axs"));
		if (!IMPORT(0x4a9104, int, const char *)(path))   /* DeleteFileA */
			IMPORT(0x4a9104, int, const char *)(path);
		GAME_CDECL(0x49f8a6, int, const char *)((const char *)STR(0x4b2a80, ".."));   /* chdir("..") */
	}
	int count = g_profileCount - 1, last = current;
	for (; last < count; last++)
		memcpy(records + last * 0x48, records + (last + 1) * 0x48, 0x48);
	u8 *freed = records + last * 0x48;
	memset(freed + 4, 0, 0x40);
	*(int *)freed = 0;
	*(int *)(freed + 0x44) = -1;
	g_profileCount = count;
	if (g_pilotChosen >= count) {
		if (count <= 0) {
			g_profileListRow = 0;
			g_profileListTop = 0;
			g_pilotChosen = 0;
			g_profileCount = 0;
			return GAME_FN(profile_delete, 0x447320, u32, void)();   /* profile_delete: the list written */
		}
		if (g_profileListRow > 0)
			g_profileListRow--;
		else
			g_profileListTop--;
		g_pilotChosen = g_profileListTop + g_profileListRow;
	}
	GAME_FN(profile_delete, 0x447320, u32, void)();
	return GAME_FN(profile_resetPreview, 0x44b7a0, u32, void)();   /* profile_resetPreview */
}

/* typing over: the key state reset (input_resetKeys) and the keyboard taken again; returns input_initKeyboard's eax */
static u32 keyboard_back(void)
{
	input_resetKeys();
	return GAME_FN(input_initKeyboard, 0x401310, u32, void *)(g_mainWindow);   /* input_initKeyboard */
}

/* the typed line emptied (its length 0x9dcd30) */
static void line_wipe(void)
{
	int n = g_typedLength;
	if (n > 0)
		memset((void *)IMG(0x9dc92c), 0, n);
}

/* 0x44c190: the new pilot's name dialog. Before typing (0x9f8f34): a click on the name field (profile_inDialogBox) or
   Enter starts it (profile_typeNewName). While typing: OK (button 0) refuses a blank name (sound 6), refuses a bad one
   (message 0x81, the dialog shut) or takes it (profile_nameExists; when that fails the dialog stays for another go),
   cancel (1) empties the line; Enter (0x4ded8c) leaves typing with the line emptied. Returns what the original
   leaves in eax */
u32 (profile_newNameDialog)(void)
{
	const char *typed = (const char *)IMG(0x9dc92c);
	g_cursorBlink = 0.0f;
	u32 r = 0;
	if (g_profileMessage) {
		if (g_mouseClick &&
		    GAME_FN(profile_inDialogBox, 0x44b2e0, int, int, int)(g_mouseX, g_mouseY)) {   /* profile_inDialogBox */
			sound_playMenu(0);
			g_profileMessage = 0;
			g_paused = 1;
			r = GAME_FN(profile_typeNewName, 0x44b600, u32, void)();   /* profile_typeNewName: typing starts */
		}
		if (!g_keyEnter)
			return r;
		g_profileMessage = 0;
		r = GAME_FN(profile_typeNewName, 0x44b600, u32, void)();
		g_paused = 1;
		return r;
	}
	if (g_mouseClick) {
		u32 button = GAME_FN(newNameDialog_hitTest, 0x44b2a0, u32, int, int)(g_mouseX, g_mouseY);   /* newNameDialog_hitTest */
		r = button - 1;
		if (button == 0) {
			if (GAME_FN(name_isBlank, 0x4343b0, int, const char *)(typed) == 1)   /* name_isBlank: blank */
				return GAME_FN(sound_playMenu, 0x41e760, u32, int)(6);
			if (GAME_FN(profile_nameHasBadChar, 0x44b7e0, int, const char *)(typed) == 1) {   /* profile_nameHasBadChar: a bad character */
				sound_playMenu(6);
				g_dialogOpen = 0;
				g_profileMessage = 0;
				g_profilePage = 1;
				menu_showMessage(0x81);
				g_paused = 0;
				return keyboard_back();
			}
			if (GAME_FN(profile_nameExists, 0x44b870, int, void)()) {   /* profile_nameExists: taken */
				sound_playMenu(6);
				g_profileMessage = 1;
				g_dialogOpen = 1;
			} else
				sound_playMenu(0);
			g_paused = 0;
			r = keyboard_back();
		} else if (button == 1) {
			sound_playMenu(0);
			g_paused = 0;
			line_wipe();
			r = keyboard_back();
		}
	}
	if (!g_keyEnter)
		return r;
	g_profilePage = 1;
	g_paused = 0;
	line_wipe();
	return keyboard_back();
}

/* ---- the profile list's keys (page 1): 13 rows shown from 0x9f8c4c, the cursor 0x9f8c5c on them, the profile
   chosen (0x9f8d74) the one under it; there are 0x9f9008 profiles ---- */
#define g_listTop g_profileListTop
#define g_listRow g_profileListRow

static void list_moved(void)
{
	g_pilotChosen = g_listTop + g_listRow;
	g_emblemMoved = 1;
	sound_playMenu(2);
}

/* the cursor a row up (the list scrolled at the top); 0 when already at the first */
static int list_up(void)
{
	if (g_listRow > 0)
		g_listRow--;
	else if (g_listTop > 0)
		g_listTop--;
	else
		return 0;
	list_moved();
	return 1;
}

/* a row down (scrolled once the cursor is on the 13th row); 0 at the last profile */
static int list_down(void)
{
	if (g_listTop + g_listRow >= g_profileCount - 1)
		return 0;
	if (g_listRow < 12)
		g_listRow++;
	else
		g_listTop++;
	list_moved();
	return 1;
}

static void key_up(void) { list_up(); }
static void key_down(void) { list_down(); }

/* 0x44c600: the profile list's keys: up / down held (with the menu's key repeat) move the cursor, scrolling the list
   at its ends (sound 2); Enter (0x4e150c) takes the profile (profile_typeNewName); 0x4e0ce0 / 0x76d414 delete it
   (profile_askDelete) when there is one; 0x4e14f4 opens the new-profile dialog (0x9f6840, page 4), or takes the
   profile when there are none; OK / the second cancel key copy it (profile_askSecond). The original leaves eax to
   callers that ignore it */
void (profileList_keys)(void)
{
	if (key_repeat(g_keyUp, &g_repeatUp, key_up) || key_repeat(g_keyDown, &g_repeatDown, key_down))
		return;
	if (input_justPressed(g_dikN) == 1) {
		sound_playMenu(0);
		g_cursorBlink = 0;
		profile_typeNewName();
		return;
	}
	if ((input_justPressed(g_dikD) == 1 || input_justPressed(g_dikDelete) == 1)
	    && g_profileCount > 0)
		GAME_FN(profile_askDelete, 0x44b670, void, void)();   /* profile_askDelete */
	if (input_justPressed(g_dikI) == 1) {
		sound_playMenu(0);
		g_cursorBlink = 0;
		if (g_profileCount <= 0) {
			profile_typeNewName();
			return;
		}
		g_profileDialogOpen = 1;
		g_profilePage = 4;
	}
	if (input_justPressed(g_keyOk) == 1 || input_justPressed(g_keyCancel2))
		GAME_FN(profile_askSecond, 0x44b6e0, void, void)();   /* profile_askSecond */
}
/* 0x44be00: the profile list's mouse: a click (0x4ded88) on the page's buttons (profilePage_hitTest): 0 takes the profile
   (profile_typeNewName), 1 deletes it (profile_askDelete) when there is one, 2 opens the new-profile dialog (or takes the
   profile when there are none), 3 copies it (profile_askSecond), 4 the list: a row (profileList_hitTest) chosen, or the
   chosen row clicked again (0x9f900c) opens the dialog; 5 / 6 a row up / down. Then with the button held
   (0x4ded94) on the arrows they step again once the blink clock (0x4dda44) reaches 5. The original leaves eax to
   callers that ignore it */
void (profileList_mouse)(void)
{
#define g_mouseX GAME_VAR(int, 0x4ded68)
#define g_mouseY GAME_VAR(int, 0x4ded6c)
	if (g_mouseClick) {
		g_cursorBlink = 0;
		switch (GAME_FN(profilePage_hitTest, 0x44b260, int, int, int)(g_mouseX, g_mouseY)) {   /* profilePage_hitTest */
		case 0:
			sound_playMenu(0);
			profile_typeNewName();
			break;
		case 1:
			if (g_profileCount > 0)
				GAME_FN(profile_askDelete, 0x44b670, void, void)();   /* profile_askDelete */
			break;
		case 2:
			sound_playMenu(0);
			g_cursorBlink = 0;
			if (g_profileCount <= 0) {
				profile_typeNewName();
				return;
			}
			g_profileDialogOpen = 1;
			g_profilePage = 4;
			break;
		case 3:
			GAME_FN(profile_askSecond, 0x44b6e0, void, void)();   /* profile_askSecond */
			break;
		case 4: {
			sound_playMenu(2);
			int row = GAME_FN(profileList_hitTest, 0x44b3a0, int, int, int)(g_mouseX, g_mouseY);   /* profileList_hitTest */
			if (row == -1 || g_listTop + row >= g_profileCount)
				return;
			if (row == g_listRow && g_profileRowClicked) {
				g_cursorBlink = 0;
				g_profileDialogOpen = 1;
				g_profilePage = 4;
				g_profileRowClicked = 0;
				(*(int *)&g_profileMessageTime) = 0;
				break;
			}
			g_listRow = row;
			g_profileRowClicked = 1;
			(*(int *)&g_profileMessageTime) = 0;
			if (g_pilotChosen != g_listTop + row) {
				g_pilotChosen = g_listTop + row;
				g_emblemMoved = 1;
			}
			break;
		}
		case 5:
			list_up();
			break;
		case 6:
			if (!list_down())
				return;
			break;
		}
	}
	if (!g_mouseHeld)
		return;
	int held = GAME_FN(profilePage_hitTest, 0x44b260, int, int, int)(g_mouseX, g_mouseY);   /* profilePage_hitTest */
	if (held != 5 && held != 6)
		return;
	if (!(g_cursorBlink >= k_5f))   /* 5 */
		return;
	if (held == 5)
		list_up();
	else if (!list_down())
		return;
	g_cursorBlink = 0;
#undef g_mouseX
#undef g_mouseY
}

#undef g_listRow
#undef g_listTop

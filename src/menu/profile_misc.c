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

/* 0x434400: a Ladder account field (ID, password, e-mail) with a character the server's messages cannot carry
   (`"',/\|~?); profile_nameHasBadChar (0x44b7e0): a pilot name that cannot be a file name (\/:*?"<>|) */
int (account_hasBadChar)(const char *s) { return has_any(s, "`\"',/\\|~?"); }
int (profile_nameHasBadChar)(const char *s) { return has_any(s, "\\/:*?\"<>|"); }

/* the stat bars' targets (g_statBarTargets) from pilot character i's nine stats, each plus k_50f; the frame's pulse
   restarted (g_profileFrameAlpha 40, falling) and the bars no longer stale (g_statBarsStale) */
static void load_stat_bars(int i)
{
	(*(u32 *)&g_profileFrameAlpha) = 0x42200000;   /* 40.0 */
	(*(u32 *)&g_profileFrameStep) = 0xbf800000;   /* -1.0 */
	g_statBarsStale = 0;
	for (int k = 0; k < 9; k++)
		g_statBarTargets[k] =
			(float)((long double)((CharacterProfile *)g_characterProfiles)[i].stats[k] + k_50f);
}

/* 0x44bc50: the stat bars for the pilot under CHARACTER SELECT's cursor; profile_loadPilotStats: for the pilot of the
   profile chosen in the list */
void (pilotSelect_loadStats)(void) { load_stat_bars(g_pilotSelectCursor); }
void (profile_loadPilotStats)(void) { load_stat_bars(g_profileRecords[(u32)g_profileChosen].pilot); }

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

/* 0x44b2e0: 1 when (x, y) is in the dialog box rectangle at g_profileMessageClickBox (left, top, right, bottom), else -1 */
int (profile_inDialogBox)(int x, int y)
{
	const int *r = g_profileMessageClickBox;
	return x >= r[0] && x <= r[2] && y >= r[1] && y <= r[3] ? 1 : -1;
}

/* 0x44b7a0: the stat bars reset: their targets (g_statBarTargets) and drawn values (g_statBars) cleared and marked to
   be loaded again (g_statBarsStale), the frame's pulse restarted (g_profileFrameAlpha 40, g_profileFrameStep -1) */
void (profile_resetStatBars)(void)
{
	memset((void *)OBJ(g_statBarTargets), 0, 36);
	memset((void *)OBJ(g_statBars), 0, 36);
	g_statBarsStale = 1;
	(*(u32 *)&g_profileFrameAlpha) = 0x42200000;   /* 40.0 */
	(*(u32 *)&g_profileFrameStep) = 0xbf800000;   /* -1.0 */
}

/* 0x44b750: the stat bars reset (profile_resetStatBars), the pilot grid's cursor on the first pilot
   (g_pilotSelectCursor 0) and its portrait growth stopped (g_profileReveal, g_profileRevealClock 0) */
void (pilotSelect_reset)(void)
{
	profile_resetStatBars();
	g_pilotSelectCursor = 0;
	(*(int *)&g_profileRevealClock) = 0;
	g_profileReveal = 0;
}

/* 0x44bc00: the log-out question answered yes (profile_logOutClicks button 0, profile_keys.c): g_profileQuitting set
   (the next frame menuState210_frame quits: app_quitGame), g_profileQuitSkip 0, the unused camera words set (-1, zoom
   80, time 0, speed 0.1), page 1 */
void (profile_quitGame)(void)
{
	g_profileQuitSkip = 0;
	g_profileQuitting = 1;
	g_unusedProfileCameraWord = -1;
	(*(u32 *)&g_unusedProfileCameraZoom) = 0x42a00000;   /* 80.0 */
	g_unusedProfileCameraTime = 0;
	(*(u32 *)&g_unusedProfileCameraSpeed) = 0x3dcccccd;   /* 0.1 */
	g_profilePage = 1;
}

/* 0x44b870: does a profile with the typed name (g_inputLine) exist, ignoring case? (The original's trailing-space trim
   can't run: it is skipped whenever the length is >= 0. Its compare buffer keeps the tail of a longer earlier
   name, as here.) */
int (profile_nameExists)(void)
{
	char typed[1024], name[1024];
	memset(name, 0, sizeof name);
	memset(typed, 0, sizeof typed);
	const char *s = g_inputLine;
	for (int i = 0, n = (int)strlen(s); i < n; i++)
		typed[i] = s[i] >= 'A' && s[i] <= 'Z' ? s[i] + 0x20 : s[i];
	for (int e = 0; e < g_profileCount; e++) {
		const char *p = (const char *)(OBJ(g_profileNames) + e * 0x48);
		for (int i = 0, n = (int)strlen(p); i < n; i++)
			name[i] = p[i] >= 'A' && p[i] <= 'Z' ? p[i] + 0x20 : p[i];
		if (!strcmp(typed, name))
			return 1;
	}
	return 0;
}

/* ---- the profile screen's confirmation dialogs: a click on the first button does the thing (with the menu sound),
   the second (or a right click) closes the dialog (g_profilePage). Both return the right click state (the original's eax) */
/* 0x44c390: "delete this profile?" */
int (profile_deleteClicks)(void)
{
	(*(int *)&g_menuRepeatClock) = 0;
	if (g_mouseClick) {
		int button = deleteDialog_hitTest(g_mouseX, g_mouseY);   /* the dialog's hit test */
		if (button == 0) {
			sound_playMenu(0);
			profile_deleteChosen();
			g_profilePage = 1;
		} else if (button == 1) {
			sound_playMenu(0);
			g_profilePage = 1;
		}
	}
	if (g_rightClick)
		g_profilePage = 1;
	return g_rightClick;
}

/* 0x44c400: the log-out question: its first button runs profile_quitGame, the second closes it (and clears g_pointerGliding) */
int (profile_logOutClicks)(void)
{
	(*(int *)&g_menuRepeatClock) = 0;
	if (g_mouseClick) {
		int button = logOutDialog_hitTest(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_quitGame();
		} else if (button == 1) {
			sound_playMenu(0);
			g_profilePage = 1;
			g_pointerGliding = 0;
		}
	}
	if (g_rightClick)
		g_profilePage = 1;
	return g_rightClick;
}

/* 0x44f6c0: the profile screen's page 4 (menuState210_frame's table): logging in with the chosen profile (only when
   g_profileLogInAsked): it is made current (profile_makeCurrent: axisuser.dat written, the pilot's save read), the
   main menu (state 300), the profile's name as the player's (0x20 bytes, g_cfgPlayerName), then axis.cfg written
   (cfg_writeAxisCfg). Returns its eax */
u32 (profile_logIn)(void)
{
	if (!g_profileLogInAsked)
		return 0;
	g_launchStartStep = 0;
	if (g_launchedForNetGame == 1)
		g_launchStartStep = 0x65;
	profile_makeCurrent();   /* profile_makeCurrent */
	g_menuState = 300;
	g_nextScreen = 300;
	g_menuCameraMove = 2;
	g_unusedMenuReturnWord = 0;
	crt_strncpy(g_cfgPlayerName,
	                                                        (const char *)(OBJ(g_profileNames) + g_currentProfile * 0x48), 0x20);   /* strncpy */
	return cfg_writeAxisCfg();   /* cfg_writeAxisCfg */
}

#define CALL(addr) GAME_CDECL(addr, u32, void)()

/* 0x44f410: the profile screen's page 1, the list (menuState210_frame's table, with profile_newNamePage /
   profile_deletePage / profile_logIn / profile_logOutPage / pilotSelect_page): the row click's timer
   (g_profileRowClickTime, to k_20f; then g_profileRowClicked clears); while a dialog frame opens, its frame
   (menu_drawFrameOpening) and, entered with no profiles (g_profileNoneAtEntry), the new-name typing (profile_typeNewName);
   else the stat bars loaded when stale and the management window drawn. Returns what the original leaves in eax */
u32 (profile_listPage)(void)
{
	if (g_profileRowClicked) {
		long double t = fadd_m(fld_m(&g_frameTime), (const float *)ADDR(g_profileRowClickTime));
		g_profileRowClickTime = (float)t;
		if (t > k_20f) {
			g_profileRowClicked = 0;
			(*(int *)&g_profileRowClickTime) = 0;
		}
	}
	if (g_frameOpening) {
		menu_drawFrameOpening(g_profilePageLeft, g_profilePageTop, g_profilePageRight, g_profilePageBottom);
		if (g_frameOpening)
			return (u32)g_frameOpening;
		if (!g_profileNoneAtEntry)
			return 0;
		return profile_typeNewName();
	}
	if (g_statBarsStale)
		profile_loadPilotStats();
	g_profilePage = 1;
	return profile_drawManagementWindow();
}

/* 0x44c560: the profile screen's mouse (from menu_processMouse): once log-out was answered yes (g_profileQuitting)
   the first click or right click sets g_profileQuitSkip 5 and the unused camera words (zoom 100, speed 0.05; the game
   quits on the next frame anyway); else, with no dialog frame opening, by page (g_profilePage): 1 the list
   (profileList_mouse), 2 the new-name dialog, 3 delete, 5 log out, 6 the pilot grid (pilotSelect_clicks). Returns
   what the original leaves in eax */
u32 (profile_screenClicks)(void)
{
	int quitting = g_profileQuitting;
	if (quitting && g_profileQuitSkip != 5) {
		u32 r = g_mouseClick ? (u32)g_mouseClick : (*(u32 *)&g_rightClick);
		if (r) {
			g_profileQuitSkip = 5;
			g_unusedProfileCameraTime = 0;
			(*(u32 *)&g_unusedProfileCameraZoom) = 0x42c80000;   /* 100 */
			(*(u32 *)&g_unusedProfileCameraSpeed) = 0x3d4ccccd;   /* 0.05 */
		}
		return r;
	}
	if (g_frameOpening || quitting)
		return (u32)quitting;
	u32 page = (*(u32 *)&g_profilePage) - 1;
	switch (page) {
	case 0: return profileList_mouse();
	case 1: return newNameDialog_clicks();
	case 2: return profile_deleteClicks();   /* profile_deleteClicks */
	case 4: return profile_logOutClicks();   /* profile_logOutClicks */
	case 5: return pilotSelect_clicks();   /* pilotSelect_clicks */
	}
	return page;
}

/* 0x44c480: the pilot grid's clicks (page 6, pilotSelect_hitTest): rows 0 .. 8 pick a pilot (with sound 2, its pilot panel reset), 9 makes the profile
   with the typed name (profile_create), 10 cancels; a right click closes the page. Returns the right click
   state (the original's eax) */
int (pilotSelect_clicks)(void)
{
	(*(int *)&g_menuRepeatClock) = 0;
	if (g_mouseClick) {
		u32 row = ((u32)pilotSelect_hitTest(g_mouseX, g_mouseY));   /* the list's hit test */
		if (row <= 8) {
			if ((*(u32 *)&g_pilotSelectCursor) != row) {
				(*(u32 *)&g_pilotSelectCursor) = row;
				g_statBarsStale = 1;
				sound_playMenu(2);
				(*(int *)&g_profileRevealClock) = 0;
				g_profileReveal = 0;
			}
		} else if (row == 9) {
			sound_playMenu(0);
			profile_create();   /* profile_create */
			g_profilePage = 1;
		} else if (row == 10) {
			sound_playMenu(0);
			g_profilePage = 1;
			g_pointerGliding = 0;
		}
	}
	if (g_rightClick)
		g_profilePage = 1;
	return g_rightClick;
}

#define chdir_(path) GAME_CDECL(0x49f8a6, int, const char *)(path)
#define mkdir_(path) GAME_CDECL(0x49f94a, int, const char *)(path)

/* 0x44b990: a new profile made from the typed name: it goes into the next slot (with the pilot chosen in the grid), the
   save folder is made if missing, the list scrolls to show it (13 rows), it is saved (profile_newCampaign) and the screen
   updated. Returns what that leaves in eax */
u32 (profile_create)(void)
{
	int n = g_profileCount;
	strcpy((char *)(OBJ(g_profileNames) + n * 0x48), g_inputLine);
	g_profileRecords[(u32)n].pilot = g_pilotSelectCursor;
	if (chdir_((const char *)STR(0x4b2adc, "save"))) {
		mkdir_((const char *)STR(0x4b2adc, "save"));
		chdir_((const char *)STR(0x4b2adc, "save"));
	}
	chdir_((const char *)STR(0x4b2a80, ".."));
	int count = n + 1;
	g_profileCount = count;
	if (count <= 0xd) {
		g_profileListRow = count - 1;
		g_profileChosen = g_profileListTop + count - 1;
	} else {
		g_profileListRow = 0xc;
		g_profileListTop = count - 0xd;
		g_profileChosen = count - 1;
	}
	profile_newCampaign();         /* profile_newCampaign (it writes the profile) */
	return profile_resetStatBars();  /* profile_resetStatBars */
}

/* a profile screen page with a panel: while the pointer glides (g_pointerGliding) it is pulled towards its target (g_pointerGlideX,
   g_pointerGlideY) by the frame time times rate, until the glide's timer (g_pointerGlideTime) runs out; the screen drawn, then the
   dialog's frame (at frame: x0, y0, x1, y1) if one is open, else the panel. Returns what the original leaves in eax */
static u32 glide_page(const float *rate, const u32 *frame, u32 panel)
{
	if (g_pointerGliding) {
		int step = ftol(fmul_m(fmul_m((long double)(g_pointerGlideX - g_mouseX), &g_frameTime), rate));
		g_mouseX += step;
		step = ftol(fmul_m(fmul_m((long double)(g_pointerGlideY - g_mouseY), &g_frameTime), rate));
		g_mouseY += step;
		long double t = fsub_m(fld_m((const float *)ADDR(g_pointerGlideTime)), &g_frameTime);
		g_pointerGlideTime = (float)t;
		if (!(t >= k_0f))
			g_pointerGliding = 0;
	}
	profile_drawManagementWindow();   /* profile_drawManagementWindow */
	if (g_frameOpening)
		return menu_drawFrameOpening(GAME_VAR(int, frame[0]), GAME_VAR(int, frame[1]),
		                                                     GAME_VAR(int, frame[2]), GAME_VAR(int, frame[3]));   /* menu_drawFrameOpening */
	return CALL(panel);
}
/* 0x44f5f0: the delete question's page (profile_drawDeleteQuestion) */
u32 (profile_deletePage)(void)
{
	static const u32 frame[4] = { ADDR(g_deleteDialogX), ADDR(g_deleteDialogY), ADDR(g_deleteDialogRight), ADDR(g_deleteDialogBottom) };
	return glide_page((const float *)ADDR(k_0_25f), frame, FN_ADDR(profile_drawDeleteQuestion, 0x44e180));
}
/* 0x44f740: the log-out question's page (profile_drawLogOutQuestion), gliding at its own rate */
u32 (profile_logOutPage)(void)
{
	static const u32 frame[4] = { ADDR(g_logOutDialogX), ADDR(g_logOutDialogY), ADDR(g_logOutDialogRight), ADDR(g_logOutDialogBottom) };
	return glide_page((const float *)ADDR(k_0_2f), frame, FN_ADDR(profile_drawLogOutQuestion, 0x44e3e0));
}

/* 0x44ce90: the profile list's names drawn (13 rows from the top entry g_profileListTop, 20 units apart in the panel at
   g_profilePageLeft): grey-blue, the selected one brighter; dimmer while a dialog page is up (page other than 1). Returns the
   last text call's eax */
u32 (profileList_drawNames)(void)
{
	u32 r = 0;
	for (int i = 0; i < 13 && i < g_profileCount; i++) {
		int page1 = g_profilePage == 1;
		u32 shade = page1 ? 0x3f000000 : 0x3e99999a;   /* 0.5 / 0.3 */
		Color4_set_bits((void *)OBJ(g_textColour), 0, shade, shade, 0x3f800000);
		if (g_profileListTop + i == g_profileChosen) {
			shade = g_profilePage == 1 ? 0x3f800000 : 0x3f000000;   /* 1 / 0.5 */
			Color4_set_bits((void *)OBJ(g_textColour), 0, shade, shade, 0x3f800000);
		}
		r = text_draw8(g_profilePageLeft + 0x28, g_profilePageTop + 0x24 + i * 0x14,
		                                                      (const char *)(OBJ(g_profileNames) + (g_profileListTop + i) * 0x48));   /* text_draw8 */
	}
	return r;
}

/* 0x44f4b0: the new-name page: the management window (profile_drawManagementWindow), then while the dialog opens
   its frame (menu_drawFrameOpening), with the "NAME ALREADY REGISTRED" message up its window, while typing the name
   dialog; once the typed name (g_inputLine) is in: empty cancels, a blank one (name_isBlank) is refused with sound 6,
   one with a bad character (profile_nameHasBadChar) too with message 0x81, one that exists (profile_nameExists)
   brings up the message; any other goes on to the pilot grid (page 6, pilotSelect_reset). Returns the last
   call's eax */
u32 (profile_newNamePage)(void)
{
	const char *typed = g_inputLine;
	profile_drawManagementWindow();
	if (g_frameOpening)
		return menu_drawFrameOpening(g_newNameDialogLeft, g_newNameDialogTop,
		                                                     g_newNameDialogRight, g_newNameDialogBottom);
	if (g_profileMessage)
		return profile_drawMessageWindow();
	if (g_textFieldOpen)
		return profile_drawNewDialog();
	if (!strlen(typed)) {
		g_frameOpening = 0;
		g_profileMessage = 0;
		g_profilePage = 1;
		return profile_drawNewDialog();
	}
	if (name_isBlank(typed) == 1) {   /* name_isBlank */
		u32 r = sound_playMenu(6);              /* sound_playMenu */
		g_profilePage = 1;
		g_frameOpening = 0;
		g_profileMessage = 0;
		return r;
	}
	if (profile_nameHasBadChar(typed) == 1) {   /* profile_nameHasBadChar */
		sound_playMenu(6);
		g_frameOpening = 0;
		g_profileMessage = 0;
		g_profilePage = 1;
		return menu_showMessage(0x81);             /* the message */
	}
	if (profile_nameExists()) {                     /* profile_nameExists */
		sound_playMenu(6);
		g_profileMessage = 1;
		g_frameOpening = 1;
		return profile_drawNewDialog();
	}
	g_profilePage = 6;
	pilotSelect_reset();
	return profile_drawNewDialog();
}

/* 0x44ba60: the current profile (g_profileChosen) deleted: its save file ("save\<name>.axs") removed (DeleteFileA, tried
   twice), the later profiles moved down a slot and the freed last slot cleared (pilot -1), the count lowered.
   With none left everything is reset and the list written (profile_writeFile); otherwise, if the current one was the
   last, the selection steps back (the scrolled row g_profileListRow, else the list's top g_profileListTop), then the list is
   written and shown again (profile_resetStatBars). Returns the last call's eax */
u32 (profile_deleteChosen)(void)
{
	int chosen = g_profileChosen;
	u8 *records = g_profiles;   /* 0x48 bytes each: +0 the number (ProfileRecord.number), +4 the name, +0x44 the pilot */
	if (crt_chdir((const char *)STR(0x4b2adc, "save")) == 0) {   /* chdir("save") */
		char path[0x80];
		memset(path, 0, sizeof path);
		strcpy(path, (const char *)(records + chosen * 0x48 + 4));
		strcat(path, (const char *)STR(0x4b2afc, ".axs"));
		if (!((int)DeleteFileA(path)))   /* DeleteFileA */
			DeleteFileA(path);
		crt_chdir((const char *)STR(0x4b2a80, ".."));   /* chdir("..") */
	}
	int count = g_profileCount - 1, last = chosen;
	for (; last < count; last++)
		memcpy(records + last * 0x48, records + (last + 1) * 0x48, 0x48);
	u8 *freed = records + last * 0x48;
	memset(freed + 4, 0, 0x40);
	*(int *)freed = 0;
	*(int *)(freed + 0x44) = -1;
	g_profileCount = count;
	if (g_profileChosen >= count) {
		if (count <= 0) {
			g_profileListRow = 0;
			g_profileListTop = 0;
			g_profileChosen = 0;
			g_profileCount = 0;
			return profile_writeFile();   /* profile_writeFile: the list written */
		}
		if (g_profileListRow > 0)
			g_profileListRow--;
		else
			g_profileListTop--;
		g_profileChosen = g_profileListTop + g_profileListRow;
	}
	profile_writeFile();
	return profile_resetStatBars();   /* profile_resetStatBars */
}

/* typing over: the key state reset (input_resetKeys) and the keyboard taken again; returns input_initKeyboard's eax */
static u32 keyboard_back(void)
{
	input_resetKeys();
	return ((u32)input_initKeyboard(g_mainWindow));   /* input_initKeyboard */
}

/* the typed line emptied (its length g_lineMaxLength) */
static void line_wipe(void)
{
	int n = g_lineMaxLength;
	if (n > 0)
		memset((void *)OBJ(g_inputLine), 0, n);
}

/* 0x44c190: the new-name dialog's clicks (page 2). While the name-taken message is up (g_profileMessage): any click
   (profile_inDialogBox returns 1 or -1 and the original only tests for nonzero, so where the click lands does not
   matter) or a right click closes it and typing starts again (profile_typeNewName). Otherwise (newNameDialog_hitTest)
   OK (0) refuses a blank name (sound 6), refuses one with a bad character (message 0x81, the dialog shut), brings the
   message up when the name exists (profile_nameExists), else takes it (profile_newNamePage then goes on to the pilot
   grid); CANCEL (1) empties the line; a right click shuts the dialog with the line emptied. Returns what the original
   leaves in eax */
u32 (newNameDialog_clicks)(void)
{
	const char *typed = g_inputLine;
	g_menuRepeatClock = 0.0f;
	u32 r = 0;
	if (g_profileMessage) {
		if (g_mouseClick &&
		    profile_inDialogBox(g_mouseX, g_mouseY)) {   /* profile_inDialogBox */
			sound_playMenu(0);
			g_profileMessage = 0;
			g_textFieldOpen = 1;
			r = profile_typeNewName();   /* profile_typeNewName: typing starts */
		}
		if (!g_rightClick)
			return r;
		g_profileMessage = 0;
		r = profile_typeNewName();
		g_textFieldOpen = 1;
		return r;
	}
	if (g_mouseClick) {
		u32 button = ((u32)newNameDialog_hitTest(g_mouseX, g_mouseY));   /* newNameDialog_hitTest */
		r = button - 1;
		if (button == 0) {
			if (name_isBlank(typed) == 1)   /* name_isBlank: blank */
				return sound_playMenu(6);
			if (profile_nameHasBadChar(typed) == 1) {   /* profile_nameHasBadChar: a bad character */
				sound_playMenu(6);
				g_frameOpening = 0;
				g_profileMessage = 0;
				g_profilePage = 1;
				menu_showMessage(0x81);
				g_textFieldOpen = 0;
				return keyboard_back();
			}
			if (profile_nameExists()) {   /* profile_nameExists: taken */
				sound_playMenu(6);
				g_profileMessage = 1;
				g_frameOpening = 1;
			} else
				sound_playMenu(0);
			g_textFieldOpen = 0;
			r = keyboard_back();
		} else if (button == 1) {
			sound_playMenu(0);
			g_textFieldOpen = 0;
			line_wipe();
			r = keyboard_back();
		}
	}
	if (!g_rightClick)
		return r;
	g_profilePage = 1;
	g_textFieldOpen = 0;
	line_wipe();
	return keyboard_back();
}

/* ---- the profile list's keys (page 1): 13 rows shown from g_profileListTop, the cursor g_profileListRow on them, the profile
   chosen (g_profileChosen) the one under it; there are g_profileCount profiles ---- */
#define g_listTop g_profileListTop
#define g_listRow g_profileListRow

static void list_moved(void)
{
	g_profileChosen = g_listTop + g_listRow;
	g_statBarsStale = 1;
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
   at its ends (sound 2); N starts a new profile (profile_typeNewName); g_dikD / g_dikDelete delete it
   (profile_askDelete) when there is one; g_dikI logs in (g_profileLogInAsked, page 4: profile_logIn), or starts a new
   profile when there are none; OK / the second cancel key ask to log out (profile_askLogOut). The original leaves eax to
   callers that ignore it */
void (profileList_keys)(void)
{
	if (key_repeat(g_keyUp, &g_repeatUp, key_up) || key_repeat(g_keyDown, &g_repeatDown, key_down))
		return;
	if (input_justPressed(g_dikN) == 1) {
		sound_playMenu(0);
		g_menuRepeatClock = 0;
		profile_typeNewName();
		return;
	}
	if ((input_justPressed(g_dikD) == 1 || input_justPressed(g_dikDelete) == 1)
	    && g_profileCount > 0)
		profile_askDelete();   /* profile_askDelete */
	if (input_justPressed(g_dikI) == 1) {
		sound_playMenu(0);
		g_menuRepeatClock = 0;
		if (g_profileCount <= 0) {
			profile_typeNewName();
			return;
		}
		g_profileLogInAsked = 1;
		g_profilePage = 4;
	}
	if (input_justPressed(g_keyOk) == 1 || input_justPressed(g_keyCancel2))
		profile_askLogOut();   /* profile_askLogOut */
}
/* 0x44be00: the profile list's mouse: a click (g_mouseClicked) on the page's buttons (profilePage_hitTest): 0 NEW: a new name typed
   (profile_typeNewName), 1 DELETE asked (profile_askDelete) when there is one, 2 LOG IN: logs in (g_profileLogInAsked, page 4:
   profile_logIn; with no profiles a new name typed instead), 3 LOG OUT asked (profile_askLogOut), 4 the list: a row
   (profileList_hitTest) chosen, or the chosen row clicked again (g_profileRowClicked) logs in the same way; 5 / 6 a row up / down. Then with the button held
   (g_mouseButtonsHeld) on the arrows they step again once the blink clock (g_menuRepeatClock) reaches 5. The original leaves eax to
   callers that ignore it */
void (profileList_mouse)(void)
{
	if (g_mouseClick) {
		g_menuRepeatClock = 0;
		switch (profilePage_hitTest(g_mouseX, g_mouseY)) {   /* profilePage_hitTest */
		case 0:
			sound_playMenu(0);
			profile_typeNewName();
			break;
		case 1:
			if (g_profileCount > 0)
				profile_askDelete();   /* profile_askDelete */
			break;
		case 2:
			sound_playMenu(0);
			g_menuRepeatClock = 0;
			if (g_profileCount <= 0) {
				profile_typeNewName();
				return;
			}
			g_profileLogInAsked = 1;
			g_profilePage = 4;
			break;
		case 3:
			profile_askLogOut();   /* profile_askLogOut */
			break;
		case 4: {
			sound_playMenu(2);
			int row = profileList_hitTest(g_mouseX, g_mouseY);   /* profileList_hitTest */
			if (row == -1 || g_listTop + row >= g_profileCount)
				return;
			if (row == g_listRow && g_profileRowClicked) {
				g_menuRepeatClock = 0;
				g_profileLogInAsked = 1;
				g_profilePage = 4;
				g_profileRowClicked = 0;
				(*(int *)&g_profileRowClickTime) = 0;
				break;
			}
			g_listRow = row;
			g_profileRowClicked = 1;
			(*(int *)&g_profileRowClickTime) = 0;
			if (g_profileChosen != g_listTop + row) {
				g_profileChosen = g_listTop + row;
				g_statBarsStale = 1;
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
	int held = profilePage_hitTest(g_mouseX, g_mouseY);   /* profilePage_hitTest */
	if (held != 5 && held != 6)
		return;
	if (!(g_menuRepeatClock >= k_5f))   /* 5 */
		return;
	if (held == 5)
		list_up();
	else if (!list_down())
		return;
	g_menuRepeatClock = 0;
#undef g_mouseX
#undef g_mouseY
}

#undef g_listRow
#undef g_listTop

/* profile_misc.c: small pieces of the pilot profiles: the save files' byte scrambling, name checks, and a profile's
   colour record loaded for the preview. */
#include "../game.h"
#include <string.h>

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
void (profile_445f10)(u8 *p, u8 key) { crypt_bytes(p, 0x104, key); }
void (profile_445f40)(u8 *p, u8 key) { crypt_bytes(p, 0x80, key); }

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
int (room_434400)(const char *s) { return has_any(s, "`\"',/\\|~?"); }
int (profile_44b7e0)(const char *s) { return has_any(s, "\\/:*?\"<>|"); }

/* profile colour record i (nine ints, 76 bytes a record from 0x9f9068) into the preview's floats, each plus the
   constant at 0x4a9560; the preview reset (distance 40, -1, not turning) */
static void load_colour(int i)
{
	GAME_VAR(u32, 0x9f8f08) = 0x42200000;   /* 40.0 */
	GAME_VAR(u32, 0x9f8c48) = 0xbf800000;   /* -1.0 */
	GAME_VAR(int, 0x9f8d68) = 0;
	for (int k = 0; k < 9; k++)
		GAME_VAR(float, 0x9f8ec0 + k * 4) =
			(float)((long double)GAME_VAR(int, 0x9f9068 + i * 76 + k * 4) + GAME_VAR(float, 0x4a9560));
}

/* 0x44bc50: the selected profile's colours; 0x44bd20: those of the pilot under the list cursor */
void (profile_44bc50)(void) { load_colour(GAME_VAR(int, 0x9f8d30)); }
void (profile_44bd20)(void) { load_colour(GAME_VAR(int, 0x9f688c + GAME_VAR(int, 0x9f8d74) * 72)); }

/* 0x445ee0: a whole 0x3ac-byte profile record scrambled */
void (save_cryptRecord)(u8 *rec, u8 key) { crypt_bytes(rec, 0x3ac, key); }

/* 0x42b3c0: a 0x4c-byte record scrambled with a key that just counts up (no reset); returns the count */
int (profile_42b3c0)(u8 *p, u8 key)
{
	int i;
	for (i = 0; i < 0x4c; i++)
		p[i] ^= key++;
	return i;
}

/* 0x42b390: every byte of s inverted in place; its length */
int (data_42b390)(char *s)
{
	int n = (int)strlen(s);
	for (int i = 0; i < n; i++)
		s[i] = ~s[i];
	return n > 0 ? n : 0;
}

/* 0x4343b0: 1 when a name is blank (only spaces and control characters) */
int (profile_4343b0)(const char *name)
{
	int n = (int)strlen(name);
	for (int i = 0; i < n; i++)
		if (name[i] < 0 || name[i] > 0x20)
			return 0;
	return 1;
}

/* 0x44b2e0: 1 when (x, y) is in the dialog box rectangle at 0x9f9010 (left, top, right, bottom), else -1 */
int (profile_44b2e0)(int x, int y)
{
	const int *r = (const int *)0x9f9010;
	return x >= r[0] && x <= r[2] && y >= r[1] && y <= r[3] ? 1 : -1;
}

/* 0x44b7a0: the colour preview reset: no colours, distance 40, -1, turning */
void (profile_44b7a0)(void)
{
	memset((void *)0x9f8ec0, 0, 36);
	memset((void *)0x9f8d34, 0, 36);
	GAME_VAR(int, 0x9f8d68) = 1;
	GAME_VAR(u32, 0x9f8f08) = 0x42200000;   /* 40.0 */
	GAME_VAR(u32, 0x9f8c48) = 0xbf800000;   /* -1.0 */
}

/* 0x44b750: the same, and no profile selected */
void (profile_44b750)(void)
{
	profile_44b7a0();
	GAME_VAR(int, 0x9f8d30) = 0;
	GAME_VAR(int, 0x9f8ee4) = 0;
	GAME_VAR(int, 0x9f6828) = 0;
}

/* 0x44bc00: the profile screen's camera put to its start (distance 80, speed 0.1) */
void (profile_44bc00)(void)
{
	GAME_VAR(int, 0x9f8e54) = 0;
	GAME_VAR(int, 0x9f6838) = 1;
	GAME_VAR(int, 0x9f6800) = -1;
	GAME_VAR(u32, 0x9f8f14) = 0x42a00000;   /* 80.0 */
	GAME_VAR(int, 0x9f8f30) = 0;
	GAME_VAR(u32, 0x9f8e50) = 0x3dcccccd;   /* 0.1 */
	GAME_VAR(int, 0x9f8f10) = 1;
}

/* 0x44b870: does a profile with the typed name (0x9dc92c) exist, ignoring case? (The original's trailing-space trim
   can't run: it is skipped whenever the length is >= 0. Its compare buffer keeps the tail of a longer earlier
   name, as here.) */
int (profile_44b870)(void)
{
	char typed[1024], name[1024];
	memset(name, 0, sizeof name);
	memset(typed, 0, sizeof typed);
	const char *s = (const char *)0x9dc92c;
	for (int i = 0, n = (int)strlen(s); i < n; i++)
		typed[i] = s[i] >= 'A' && s[i] <= 'Z' ? s[i] + 0x20 : s[i];
	for (int e = 0; e < GAME_VAR(int, 0x9f9008); e++) {
		const char *p = (const char *)(0x9f684c + e * 0x48);
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
int (profile_44c390)(void)
{
	GAME_VAR(int, 0x4dda44) = 0;
	if (g_mouseClick) {
		int button = GAME_CDECL(0x44b320, int, int, int)(g_mouseX, g_mouseY);   /* the dialog's hit test */
		if (button == 0) {
			sound_playMenu(0);
			profile_deleteFiles();
			GAME_VAR(int, 0x9f8f10) = 1;
		} else if (button == 1) {
			sound_playMenu(0);
			GAME_VAR(int, 0x9f8f10) = 1;
		}
	}
	if (GAME_VAR(int, 0x4ded8c))
		GAME_VAR(int, 0x9f8f10) = 1;
	return GAME_VAR(int, 0x4ded8c);
}

/* 0x44c400: the second dialog: its first button runs profile_44bc00, the second closes it (and clears 0x76d42c) */
int (profile_44c400)(void)
{
	GAME_VAR(int, 0x4dda44) = 0;
	if (g_mouseClick) {
		int button = GAME_CDECL(0x44b360, int, int, int)(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_44bc00();
		} else if (button == 1) {
			sound_playMenu(0);
			GAME_VAR(int, 0x9f8f10) = 1;
			GAME_VAR(int, 0x76d42c) = 0;
		}
	}
	if (GAME_VAR(int, 0x4ded8c))
		GAME_VAR(int, 0x9f8f10) = 1;
	return GAME_VAR(int, 0x4ded8c);
}

/* 0x44f6c0: logging in with the selected profile (when 0x9f6840): the profile saved, the main menu (state 300), the
   profile's name as the player's (0x20 bytes), then axis.cfg loaded. Returns what the original leaves in eax */
u32 (profile_44f6c0)(void)
{
	if (!GAME_VAR(int, 0x9f6840))
		return 0;
	GAME_VAR(int, 0x9da49c) = 0;
	if (GAME_VAR(int, 0x76d410) == 1)
		GAME_VAR(int, 0x9da49c) = 0x65;
	GAME_CDECL(0x446a10, void, void)();   /* profile_save */
	g_menuState = 300;
	GAME_VAR(int, 0x67ef20) = 300;
	GAME_VAR(int, 0x680370) = 2;
	GAME_VAR(int, 0x4df8e0) = 0;
	GAME_CDECL(0x49ea80, char *, char *, const char *, u32)((char *)0x4dedb0,
	                                                        (const char *)(0x9f684c + GAME_VAR(int, 0x9f8c58) * 0x48), 0x20);   /* strncpy */
	return GAME_CDECL(0x42d730, u32, void)();   /* cfg_loadAxisCfg */
}

#define CALL(addr) GAME_CDECL(addr, u32, void)()

/* 0x44f410: the profile screen's frame: the message's timer (0x9f8f18, to 0x4a944c; then the message goes), the
   dialog's frame and its page (0x44b600) while open, else the screen (an entry being edited first), the page shown.
   Returns what the original leaves in eax */
u32 (profile_44f410)(void)
{
	if (GAME_VAR(int, 0x9f900c)) {
		long double t = fadd_m(fld_m(&g_frameTime), (const float *)0x9f8f18);
		GAME_VAR(float, 0x9f8f18) = (float)t;
		if (t > GAME_VAR(float, 0x4a944c)) {
			GAME_VAR(int, 0x9f900c) = 0;
			GAME_VAR(int, 0x9f8f18) = 0;
		}
	}
	if (g_dialogOpen) {
		menu_drawFrame(GAME_VAR(int, 0x9f8e48), GAME_VAR(int, 0x9f8e4c), GAME_VAR(int, 0x9f8ea0), GAME_VAR(int, 0x9f8ea4));
		if (g_dialogOpen)
			return (u32)g_dialogOpen;
		if (!GAME_VAR(int, 0x9f8d70))
			return 0;
		return CALL(0x44b600);
	}
	if (GAME_VAR(int, 0x9f8d68))
		CALL(0x44bd20);
	GAME_VAR(int, 0x9f8f10) = 1;
	return CALL(0x44d720);
}

/* 0x44c560: the profile screen's input: while its intro plays (0x9f6838) a click skips it (to state 5, the panel
   sliding in from 100 at 0.05); else, with no dialog, by page (0x9f8f10): 1 the list, 2 the new profile, 3 and 5 the
   dialogs, 6 the profile list's clicks. Returns what the original leaves in eax */
u32 (profile_processInput)(void)
{
	int intro = GAME_VAR(int, 0x9f6838);
	if (intro && GAME_VAR(int, 0x9f8e54) != 5) {
		u32 r = g_mouseClick ? (u32)g_mouseClick : GAME_VAR(u32, 0x4ded8c);
		if (r) {
			GAME_VAR(int, 0x9f8e54) = 5;
			GAME_VAR(int, 0x9f8f30) = 0;
			GAME_VAR(u32, 0x9f8f14) = 0x42c80000;   /* 100 */
			GAME_VAR(u32, 0x9f8e50) = 0x3d4ccccd;   /* 0.05 */
		}
		return r;
	}
	if (g_dialogOpen || intro)
		return (u32)intro;
	u32 page = GAME_VAR(u32, 0x9f8f10) - 1;
	switch (page) {
	case 0: return CALL(0x44be00);
	case 1: return CALL(0x44c190);
	case 2: return CALL(0x44c390);   /* profile_44c390 */
	case 4: return CALL(0x44c400);   /* profile_44c400 */
	case 5: return CALL(0x44c480);   /* profile_44c480 */
	}
	return page;
}

/* 0x44c480: the profile list's clicks: rows 0 .. 8 select a profile (with sound 2, its pilot panel reset), 9 logs in
   with the typed name (profile_selectAndLoad), 10 cancels; a right click closes the page. Returns the right click
   state (the original's eax) */
int (profile_44c480)(void)
{
	GAME_VAR(int, 0x4dda44) = 0;
	if (g_mouseClick) {
		u32 row = GAME_CDECL(0x44b3e0, u32, int, int)(g_mouseX, g_mouseY);   /* the list's hit test */
		if (row <= 8) {
			if (GAME_VAR(u32, 0x9f8d30) != row) {
				GAME_VAR(u32, 0x9f8d30) = row;
				GAME_VAR(int, 0x9f8d68) = 1;
				sound_playMenu(2);
				GAME_VAR(int, 0x9f8ee4) = 0;
				GAME_VAR(int, 0x9f6828) = 0;
			}
		} else if (row == 9) {
			sound_playMenu(0);
			CALL(0x44b990);   /* profile_selectAndLoad */
			GAME_VAR(int, 0x9f8f10) = 1;
		} else if (row == 10) {
			sound_playMenu(0);
			GAME_VAR(int, 0x9f8f10) = 1;
			GAME_VAR(int, 0x76d42c) = 0;
		}
	}
	if (GAME_VAR(int, 0x4ded8c))
		GAME_VAR(int, 0x9f8f10) = 1;
	return GAME_VAR(int, 0x4ded8c);
}

#define chdir_(path) GAME_CDECL(0x49f8a6, int, const char *)(path)
#define mkdir_(path) GAME_CDECL(0x49f94a, int, const char *)(path)

/* 0x44b990: a new profile made from the typed name: it goes into the next slot (with the chosen pilot, 0x9f8d30), the
   save folder is made if missing, the list scrolls to show it (13 rows), it is saved (profile_load) and the screen
   updated. Returns what that leaves in eax */
u32 (profile_selectAndLoad)(void)
{
	int n = GAME_VAR(int, 0x9f9008);
	strcpy((char *)(0x9f684c + n * 0x48), (const char *)0x9dc92c);
	GAME_VAR(int, 0x9f688c + n * 0x48) = GAME_VAR(int, 0x9f8d30);
	if (chdir_((const char *)0x4b2adc)) {
		mkdir_((const char *)0x4b2adc);
		chdir_((const char *)0x4b2adc);
	}
	chdir_((const char *)0x4b2a80);
	int count = n + 1;
	GAME_VAR(int, 0x9f9008) = count;
	if (count <= 0xd) {
		GAME_VAR(int, 0x9f8c5c) = count - 1;
		GAME_VAR(int, 0x9f8d74) = GAME_VAR(int, 0x9f8c4c) + count - 1;
	} else {
		GAME_VAR(int, 0x9f8c5c) = 0xc;
		GAME_VAR(int, 0x9f8c4c) = count - 0xd;
		GAME_VAR(int, 0x9f8d74) = count - 1;
	}
	CALL(0x446590);         /* profile_load (it writes the profile) */
	return CALL(0x44b7a0);  /* profile_44b7a0 */
}

/* a profile screen page with a panel: while the pointer glides (0x76d42c) it is pulled towards its target (0x67ef34,
   0x67fb38) by the frame time times rate, until the glide's timer (0x680bc0) runs out; the screen drawn, then the
   dialog's frame (at frame: x0, y0, x1, y1) if one is open, else the panel. Returns what the original leaves in eax */
static u32 glide_page(const float *rate, const u32 *frame, u32 panel)
{
	if (GAME_VAR(int, 0x76d42c)) {
		int step = ftol(fmul_m(fmul_m((long double)(GAME_VAR(int, 0x67ef34) - g_mouseX), &g_frameTime), rate));
		g_mouseX += step;
		step = ftol(fmul_m(fmul_m((long double)(GAME_VAR(int, 0x67fb38) - g_mouseY), &g_frameTime), rate));
		g_mouseY += step;
		long double t = fsub_m(fld_m((const float *)0x680bc0), &g_frameTime);
		GAME_VAR(float, 0x680bc0) = (float)t;
		if (!(t >= GAME_VAR(float, 0x4a93e8)))
			GAME_VAR(int, 0x76d42c) = 0;
	}
	CALL(0x44d720);   /* mainmenu_drawScreen */
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, frame[0]), GAME_VAR(int, frame[1]),
		                                                     GAME_VAR(int, frame[2]), GAME_VAR(int, frame[3]));   /* menu_drawFrame */
	return CALL(panel);
}
/* 0x44f5f0: the pilot panel's page (profile_44e180) */
u32 (profile_44f5f0)(void)
{
	static const u32 frame[4] = { 0x9f8f1c, 0x9f8f0c, 0x9f8f2c, 0x9f8f28 };
	return glide_page((const float *)0x4a941c, frame, 0x44e180);
}
/* 0x44f740: the second panel's page (profile_44e3e0), gliding at its own rate */
u32 (profile_44f740)(void)
{
	static const u32 frame[4] = { 0x9f6834, 0x9f683c, 0x9f93bc, 0x9f93c0 };
	return glide_page((const float *)0x4a94f8, frame, 0x44e3e0);
}

/* 0x44ce90: the profile list's names drawn (13 rows from the top entry 0x9f8c4c, 20 units apart in the panel at
   0x9f8e48): grey-blue, the selected one brighter; dimmer while a dialog page is up (page other than 1). Returns the
   last text call's eax */
u32 (profile_44ce90)(void)
{
	u32 r = 0;
	for (int i = 0; i < 13 && i < GAME_VAR(int, 0x9f9008); i++) {
		int page1 = GAME_VAR(int, 0x9f8f10) == 1;
		u32 shade = page1 ? 0x3f000000 : 0x3e99999a;   /* 0.5 / 0.3 */
		GAME_CDECL(0x41f0e0, void, void *, u32, u32, u32, u32)((void *)0x76d438, 0, shade, shade, 0x3f800000);
		if (GAME_VAR(int, 0x9f8c4c) + i == GAME_VAR(int, 0x9f8d74)) {
			shade = GAME_VAR(int, 0x9f8f10) == 1 ? 0x3f800000 : 0x3f000000;   /* 1 / 0.5 */
			GAME_CDECL(0x41f0e0, void, void *, u32, u32, u32, u32)((void *)0x76d438, 0, shade, shade, 0x3f800000);
		}
		r = GAME_CDECL(0x402620, u32, int, int, const char *)(GAME_VAR(int, 0x9f8e48) + 0x28, GAME_VAR(int, 0x9f8e4c) + 0x24 + i * 0x14,
		                                                      (const char *)(0x9f684c + (GAME_VAR(int, 0x9f8c4c) + i) * 0x48));   /* text_draw8 */
	}
	return r;
}

/* 0x44f4b0: the profile screen's name entry step (after 0x44d720): with a dialog open its frame is drawn
   (0x428c30); while a profile is being made (0x9f8f34) 0x44dc60; once the typed name (0x9dc92c) is in (the keyboard
   back): empty cancels, an existing name (profile_4343b0) or a bad one (profile_44b7e0, message 0x81) is refused
   with sound 6, otherwise the profile is made (profile_44b870; failing that state 6 and 0x44b750). Returns the
   last call's eax */
u32 (profile_44f4b0)(void)
{
	const char *typed = (const char *)0x9dc92c;
	GAME_CDECL(0x44d720, void, void)();
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x9f8eac), GAME_VAR(int, 0x9f8ea8),
		                                                     GAME_VAR(int, 0x9f8f20), GAME_VAR(int, 0x9f8f24));
	if (GAME_VAR(int, 0x9f8f34))
		return GAME_CDECL(0x44dc60, u32, void)();
	if (GAME_VAR(int, 0x68039c))
		return GAME_CDECL(0x44de00, u32, void)();
	if (!strlen(typed)) {
		g_dialogOpen = 0;
		GAME_VAR(int, 0x9f8f34) = 0;
		GAME_VAR(int, 0x9f8f10) = 1;
		return GAME_CDECL(0x44de00, u32, void)();
	}
	if (GAME_CDECL(0x4343b0, int, const char *)(typed) == 1) {   /* profile_4343b0 */
		u32 r = GAME_CDECL(0x41e760, u32, int)(6);              /* sound_playMenu */
		GAME_VAR(int, 0x9f8f10) = 1;
		g_dialogOpen = 0;
		GAME_VAR(int, 0x9f8f34) = 0;
		return r;
	}
	if (GAME_CDECL(0x44b7e0, int, const char *)(typed) == 1) {   /* profile_44b7e0 */
		sound_playMenu(6);
		g_dialogOpen = 0;
		GAME_VAR(int, 0x9f8f34) = 0;
		GAME_VAR(int, 0x9f8f10) = 1;
		return GAME_CDECL(0x41ee40, u32, int)(0x81);             /* the message */
	}
	if (GAME_CDECL(0x44b870, int, void)()) {                     /* profile_44b870 */
		sound_playMenu(6);
		GAME_VAR(int, 0x9f8f34) = 1;
		g_dialogOpen = 1;
		return GAME_CDECL(0x44de00, u32, void)();
	}
	GAME_VAR(int, 0x9f8f10) = 6;
	GAME_CDECL(0x44b750, void, void)();
	return GAME_CDECL(0x44de00, u32, void)();
}

/* 0x44ba60: the current profile (0x9f8d74) deleted: its save file ("save\<name>.axs") removed (DeleteFileA, tried
   twice), the later profiles moved down a slot and the freed last slot cleared (colour -1), the count lowered.
   With none left everything is reset and the list written (profile_delete); otherwise, if the current one was the
   last, the selection steps back (the scrolled row 0x9f8c5c, else the list's top 0x9f8c4c), then the list is
   written and shown again (profile_44b7a0). Returns the last call's eax */
u32 (profile_deleteFiles)(void)
{
	int current = GAME_VAR(int, 0x9f8d74);
	u8 *records = (u8 *)0x9f6848;   /* 0x48 bytes each: +0 a word, +4 the name, +0x44 the colour */
	if (GAME_CDECL(0x49f8a6, int, const char *)((const char *)0x4b2adc) == 0) {   /* chdir("save") */
		char path[0x80];
		memset(path, 0, sizeof path);
		strcpy(path, (const char *)(records + current * 0x48 + 4));
		strcat(path, (const char *)0x4b2afc);   /* ".axs" */
		if (!IMPORT(0x4a9104, int, const char *)(path))   /* DeleteFileA */
			IMPORT(0x4a9104, int, const char *)(path);
		GAME_CDECL(0x49f8a6, int, const char *)((const char *)0x4b2a80);   /* chdir("..") */
	}
	int count = GAME_VAR(int, 0x9f9008) - 1, last = current;
	for (; last < count; last++)
		memcpy(records + last * 0x48, records + (last + 1) * 0x48, 0x48);
	u8 *freed = records + last * 0x48;
	memset(freed + 4, 0, 0x40);
	*(int *)freed = 0;
	*(int *)(freed + 0x44) = -1;
	GAME_VAR(int, 0x9f9008) = count;
	if (GAME_VAR(int, 0x9f8d74) >= count) {
		if (count <= 0) {
			GAME_VAR(int, 0x9f8c5c) = 0;
			GAME_VAR(int, 0x9f8c4c) = 0;
			GAME_VAR(int, 0x9f8d74) = 0;
			GAME_VAR(int, 0x9f9008) = 0;
			return GAME_CDECL(0x447320, u32, void)();   /* profile_delete: the list written */
		}
		if (GAME_VAR(int, 0x9f8c5c) > 0)
			GAME_VAR(int, 0x9f8c5c)--;
		else
			GAME_VAR(int, 0x9f8c4c)--;
		GAME_VAR(int, 0x9f8d74) = GAME_VAR(int, 0x9f8c4c) + GAME_VAR(int, 0x9f8c5c);
	}
	GAME_CDECL(0x447320, u32, void)();
	return GAME_CDECL(0x44b7a0, u32, void)();   /* profile_44b7a0 */
}

/* typing over: the key state reset (match_431590) and the keyboard taken again; returns input_initKeyboard's eax */
static u32 keyboard_back(void)
{
	GAME_CDECL(0x431590, void, void)();
	return GAME_CDECL(0x401310, u32, void *)(GAME_VAR(void *, 0x4ded18));   /* input_initKeyboard */
}

/* the typed line emptied (its length 0x9dcd30) */
static void line_wipe(void)
{
	int n = GAME_VAR(int, 0x9dcd30);
	if (n > 0)
		memset((void *)0x9dc92c, 0, n);
}

/* 0x44c190: the new pilot's name dialog. Before typing (0x9f8f34): a click on the name field (profile_44b2e0) or
   Enter starts it (profile_44b600). While typing: OK (button 0) refuses a blank name (sound 6), refuses a bad one
   (message 0x81, the dialog shut) or takes it (profile_44b870; when that fails the dialog stays for another go),
   cancel (1) empties the line; Enter (0x4ded8c) leaves typing with the line emptied. Returns what the original
   leaves in eax */
u32 (profile_44c190)(void)
{
	const char *typed = (const char *)0x9dc92c;
	GAME_VAR(float, 0x4dda44) = 0.0f;
	u32 r = 0;
	if (GAME_VAR(int, 0x9f8f34)) {
		if (GAME_VAR(int, 0x4ded88) &&
		    GAME_CDECL(0x44b2e0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c))) {   /* profile_44b2e0 */
			sound_playMenu(0);
			GAME_VAR(int, 0x9f8f34) = 0;
			g_paused = 1;
			r = GAME_CDECL(0x44b600, u32, void)();   /* profile_44b600: typing starts */
		}
		if (!GAME_VAR(int, 0x4ded8c))
			return r;
		GAME_VAR(int, 0x9f8f34) = 0;
		r = GAME_CDECL(0x44b600, u32, void)();
		g_paused = 1;
		return r;
	}
	if (GAME_VAR(int, 0x4ded88)) {
		u32 button = GAME_CDECL(0x44b2a0, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* profile_44b2a0 */
		r = button - 1;
		if (button == 0) {
			if (GAME_CDECL(0x4343b0, int, const char *)(typed) == 1)   /* profile_4343b0: blank */
				return GAME_CDECL(0x41e760, u32, int)(6);
			if (GAME_CDECL(0x44b7e0, int, const char *)(typed) == 1) {   /* profile_44b7e0: a bad character */
				sound_playMenu(6);
				g_dialogOpen = 0;
				GAME_VAR(int, 0x9f8f34) = 0;
				GAME_VAR(int, 0x9f8f10) = 1;
				GAME_CDECL(0x41ee40, void, int)(0x81);
				g_paused = 0;
				return keyboard_back();
			}
			if (GAME_CDECL(0x44b870, int, void)()) {   /* profile_44b870: taken */
				sound_playMenu(6);
				GAME_VAR(int, 0x9f8f34) = 1;
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
	if (!GAME_VAR(int, 0x4ded8c))
		return r;
	GAME_VAR(int, 0x9f8f10) = 1;
	g_paused = 0;
	line_wipe();
	return keyboard_back();
}

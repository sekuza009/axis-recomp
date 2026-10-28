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

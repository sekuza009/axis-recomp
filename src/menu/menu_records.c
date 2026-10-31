/* menu_records.c: the front end's small records: the lobby player name, the data paths, the chat input line and
   its history, the message box line, the session records of the arena list, the saved mech, and the paged lists
   of the room and skirmish screens. */
#include "../game.h"
#include <string.h>

/* a name field cleared, then the name copied in (the lobby and room code always do both) */
static void copy_name(u32 dst, int clear_bytes, const char *src)
{
	memset((void *)dst, 0, clear_bytes);
	strcpy((char *)dst, src);
}

/* ---- the lobby player record (0x4db560: name, two fields) ---- */
/* 0x4050f0: "PLAYER" (0x4ad4b0) and both fields 0 */
void (cfg_defaultPlayerName)(void)
{
	copy_name(0x4db560, 32, (const char *)0x4ad4b0);
	GAME_VAR(int, 0x4db580) = 0;
	GAME_VAR(int, 0x4db584) = 0;
}

/* 0x404930: the profile's name and fields (0x4dedb0) */
void (lobby_404930)(void)
{
	GAME_VAR(int, 0x4db584) = GAME_VAR(int, 0x4dedd4);
	copy_name(0x4db560, 32, (const char *)0x4dedb0);
	GAME_VAR(int, 0x4db580) = GAME_VAR(int, 0x4dedd0);
}

/* 0x43f5a0: "initdata/" (0x4b29bc) into both data path buffers, the stage path (0x4b0498) into the third */
void (app_setDataPaths)(void)
{
	copy_name(0x9dae7c, 0x105, (const char *)0x4b29bc);
	copy_name(0x4dedf8, 0x105, (const char *)0x4b29bc);
	copy_name(0x680bc4, 0x105, (const char *)0x4b0498);
}

/* ---- the chat input line (0x400 bytes at 0x9dc92c) and its three-line history ---- */
/* 0x431560: the line emptied, in input mode mode */
void (menu_clearInputBuffer)(int mode)
{
	memset((void *)0x9dc92c, 0, 0x400);
	GAME_VAR(int, 0x9dbf10) = 0;
	GAME_VAR(int, 0x9dcd30) = mode;
}

/* 0x4315c0: the line pushed onto the history (the oldest line dropped) */
void (room_4315c0)(void)
{
	memcpy((void *)0x67f738, (void *)0x67f338, 0x400);
	memcpy((void *)0x67f338, (void *)0x67ef38, 0x400);
	memcpy((void *)0x67ef38, (void *)0x9dc92c, 0x400);
}

/* 0x41ee40: message i of the 0x80-byte table at 0x74de24 shown in the message box */
void (menu_showMessage)(int i)
{
	GAME_VAR(int, 0x4df900) = 1;
	memset((void *)0x4df81c, 0, 0x50);
	GAME_VAR(int, 0x9da49c) = 0;
	strcpy((char *)0x4df81c, (const char *)(0x74de24 + i * 0x80));
}

/* ---- session records (0x4a bytes) ---- */
/* 0x4065a0: records a and b swapped */
void (arena_4065a0)(void *a, void *b)
{
	u8 t[0x4a];
	memcpy(t, a, 0x4a);
	memcpy(a, b, 0x4a);
	memcpy(b, t, 0x4a);
}

/* 0x4045e0: chat record 0x67ef30 (from 0x9087c4) cleared; the original does it 256 times over without moving on */
void (arena_4045e0)(void)
{
	u32 r = 0x9087c4 + GAME_VAR(int, 0x67ef30) * 0x4a;
	memset((void *)r, 0, 32);
	GAME_VAR(u8, r + 0x21) = 0;
	GAME_VAR(u8, r + 0x28) = 0;
	GAME_VAR(u8, r + 0x22) = 0;
	GAME_VAR(u8, r + 0x23) = 0;
	GAME_VAR(u8, r + 0x29) = 0;
	GAME_VAR(u8, r + 0x2a) = 0;
	GAME_VAR(int, r + 0x24) = 0;
}

/* ---- the saved mech (0x4dc878 parts, 0x4dcf18 weapons, 0x4dcfe0 colours) ---- */
/* 0x430390: the empty mech: no weapons, part 0, colour pairs (0,1,0) (0,1,0) */
void (app_430390)(void)
{
	static const float colour[6] = { 0, 1, 0, 0, 1, 0 };
	GAME_VAR(int, 0x4dcf24) = GAME_VAR(int, 0x4dcf28) = GAME_VAR(int, 0x4dcf2c) =
		GAME_VAR(int, 0x4dcf18) = GAME_VAR(int, 0x4dcf1c) = -1;
	GAME_VAR(int, 0x4dc878) = GAME_VAR(int, 0x4dc87c) = GAME_VAR(int, 0x4dc880) =
		GAME_VAR(int, 0x4dc884) = GAME_VAR(int, 0x4dc888) = 0;
	GAME_VAR(int, 0x4dcf20) = 0;
	for (u32 p = 0x4dcfe0; p < 0x4dd058; p += 24)
		memcpy((void *)p, colour, 24);
}

/* 0x40ddb0: the mech unpacked from the network / profile record at 0x9dd5f8 (signed bytes: five parts, the weapons,
   then the colours) */
void (mech_unpackFromRecord)(void)
{
	const signed char *rec = (const signed char *)0x9dd5f8;
	GAME_VAR(int, 0x4dc878) = rec[0];
	GAME_VAR(int, 0x4dc87c) = rec[1];
	GAME_VAR(int, 0x4dc880) = rec[2];
	GAME_VAR(int, 0x4dc884) = rec[3];
	GAME_VAR(int, 0x4dc888) = rec[4];
	for (int i = 0; i < 4; i++)
		GAME_VAR(int, 0x4dcf20 + i * 4) = rec[7 + i];
	GAME_VAR(int, 0x4dcf1c) = rec[6];
	GAME_VAR(int, 0x4dcf18) = rec[5];
	memcpy((void *)0x4dcfe0, (void *)0x9dd603, 0x90);
}

/* 0x4463a0: the mech loaded from the profile record (0x9f19f8 ..): the parts, the weapons, the six colour pairs (a
   negative or NaN chroma or value becomes 0 in the record first) */
void (mech_loadFromProfile)(void)
{
	GAME_VAR(int, 0x4dc87c) = GAME_VAR(int, 0x9f19fc);
	GAME_VAR(int, 0x4dc878) = GAME_VAR(int, 0x9f19f8);
	GAME_VAR(int, 0x4dc880) = GAME_VAR(int, 0x9f1a00);
	GAME_VAR(int, 0x4dc888) = GAME_VAR(int, 0x9f1a08);
	GAME_VAR(int, 0x4dc884) = GAME_VAR(int, 0x9f1a04);
	GAME_VAR(int, 0x4dcf20) = GAME_VAR(int, 0x9f1a1c);
	GAME_VAR(int, 0x4dcf28) = GAME_VAR(int, 0x9f1a24);
	GAME_VAR(int, 0x4dcf24) = GAME_VAR(int, 0x9f1a20);
	GAME_VAR(int, 0x4dcf2c) = GAME_VAR(int, 0x9f1a28);
	GAME_VAR(int, 0x4dcf18) = GAME_VAR(int, 0x9f1a14);
	GAME_VAR(int, 0x4dcf1c) = GAME_VAR(int, 0x9f1a18);
	for (int o = 0; o < 0x90; o += 0x18) {
		if (!(GAME_VAR(float, 0x9f1a38 + o) >= 0.0f))
			GAME_VAR(int, 0x9f1a38 + o) = 0;
		if (!(GAME_VAR(float, 0x9f1a3c + o) >= 0.0f))
			GAME_VAR(int, 0x9f1a3c + o) = 0;
		memcpy((void *)(0x4dcfe0 + o), (void *)(0x9f1a34 + o), 0x18);
	}
}

/* 0x4464b0: the mech stored into the profile record (the inverse of mech_loadFromProfile) */
void (match_4464b0)(void)
{
	GAME_VAR(int, 0x9f19f8) = GAME_VAR(int, 0x4dc878);
	GAME_VAR(int, 0x9f19fc) = GAME_VAR(int, 0x4dc87c);
	GAME_VAR(int, 0x9f1a04) = GAME_VAR(int, 0x4dc884);
	GAME_VAR(int, 0x9f1a00) = GAME_VAR(int, 0x4dc880);
	GAME_VAR(int, 0x9f1a08) = GAME_VAR(int, 0x4dc888);
	GAME_VAR(int, 0x9f1a20) = GAME_VAR(int, 0x4dcf24);
	GAME_VAR(int, 0x9f1a1c) = GAME_VAR(int, 0x4dcf20);
	GAME_VAR(int, 0x9f1a24) = GAME_VAR(int, 0x4dcf28);
	GAME_VAR(int, 0x9f1a18) = GAME_VAR(int, 0x4dcf1c);
	GAME_VAR(int, 0x9f1a28) = GAME_VAR(int, 0x4dcf2c);
	GAME_VAR(int, 0x9f1a14) = GAME_VAR(int, 0x4dcf18);
	memcpy((void *)0x9f1a34, (void *)0x4dcfe0, 0x90);
}

/* 0x447910: the menu camera put back (armc_40e670 without its flag) */
void (skirmish_447910)(void)
{
	GAME_VAR(int, 0x4df024) = GAME_VAR(int, 0x4df870);
	GAME_VAR(int, 0x4df028) = GAME_VAR(int, 0x4df874);
	GAME_VAR(int, 0x4df02c) = GAME_VAR(int, 0x4df878);
	GAME_VAR(int, 0x680378) = GAME_VAR(int, 0x76d388);
	GAME_VAR(int, 0x68037c) = GAME_VAR(int, 0x76d38c);
	GAME_VAR(int, 0x680380) = GAME_VAR(int, 0x76d390);
}

/* 0x445de0: a click (either button) starts the menu fade, once */
void (menu_445de0)(void)
{
	if ((GAME_VAR(int, 0x4ded88) || GAME_VAR(int, 0x4ded8c)) && !GAME_VAR(int, 0x4df01c)) {
		GAME_VAR(int, 0x4df01c) = 1;
		GAME_VAR(int, 0x4e0458) = 0;
	}
}

/* ---- the room list's pages: page 0x9dd6ac of 0x9dd4b8 (at most 99), the page before in 0x9dd1b4 ---- */
static void room_pageChanged(void)
{
	GAME_VAR(int, 0x9dd350) = 1;
	GAME_VAR(int, 0x9dd3b0) = 0;
	GAME_VAR(int, 0x76d40c) = 0;
	GAME_VAR(int, 0xa0b350) = 0;
	GAME_VAR(int, 0xa0b35c) = 0;
}

/* 0x435970, 0x4359b0: the previous and the next page */
void (room_435970)(void)
{
	int *page = &GAME_VAR(int, 0x9dd6ac);
	if (*page > 0) {
		GAME_VAR(int, 0x9dd1b4) = *page;
		(*page)--;
		room_pageChanged();
	}
}

void (room_4359b0)(void)
{
	int *page = &GAME_VAR(int, 0x9dd6ac);
	if (*page < GAME_VAR(int, 0x9dd4b8) && *page < 99) {
		GAME_VAR(int, 0x9dd1b4) = *page;
		(*page)++;
		room_pageChanged();
	}
}

/* 0x4359f0: the list's mode cycled 0 .. 2 (the one before kept in 0x9dd300), its distance limit back to 10,000,000 */
void (room_4359f0)(void)
{
	int mode = GAME_VAR(int, 0x9dd1d0);
	GAME_VAR(int, 0x9dd300) = mode;
	room_pageChanged();
	GAME_VAR(int, 0x9dd328) = 0;
	GAME_VAR(u32, 0x9dd384) = 0x4b189680;   /* 10000000.0f */
	GAME_VAR(int, 0x9dd1d0) = (mode + 1) % 3;
}

/* the value a row is ranked by in mode (0x9dd1d0): 0 a float at +0x3e, 1 an int at +0x2e, 2 an int at +0x26, 3 a
   float at +0x36; another mode keeps the one before (0: none) */
static int rank_value(const u8 *row, int mode, long double *value)
{
	if (mode == 0)
		*value = fld_m((const float *)(row + 0x3e));
	else if (mode == 1)
		*value = (long double)*(const int *)(row + 0x2e);
	else if (mode == 2)
		*value = (long double)*(const int *)(row + 0x26);
	else if (mode == 3)
		*value = fld_m((const float *)(row + 0x36));
	else
		return 0;
	return 1;
}

/* 0x435770: the room list's page of ten rows (0x44 bytes from 0x9dceec) filled from the players received (62-byte
   records from 0xa05330, up to the first without a name): each row its rank (page 0x9dd6ac * 10 + its place) or,
   when its value (rank_value) equals the row's before, that row's rank; the page before's last value and rank
   (0x9dd384, 0x9dd328) start the comparison, and this page's are kept there for the next */
void (room_435770)(void)
{
	static const u8 dst[7] = { 0x26, 0x3e, 0x36, 0x2a, 0x2e, 0x32, 0x3a }, src[7] = { 0x2e, 0x36, 0x3a, 0x22, 0x26, 0x2a, 0x32 };
	u8 *rows = (u8 *)0x9dceec;
	for (int i = 0; i < 10; i++) {
		u8 *row = rows + i * 0x44;
		*(int *)(row + 4) = 0;
		memset(row + 8, 0, 30);
		static const u8 cleared[5] = { 0x26, 0x2a, 0x2e, 0x32, 0x36 };   /* (+0x3e is left as it was) */
		for (int k = 0; k < 5; k++)
			*(int *)(row + cleared[k]) = 0;
		*(int *)(row + 0x3a) = 1;
	}
	long double value = fld_m((const float *)0x4a94ec);
	float before = 1000000.0f;
	int i;
	for (i = 0; i < 10; i++) {
		const u8 *player = (const u8 *)0xa05330 + i * 62;
		if (!*player)
			break;
		u8 *row = rows + i * 0x44;
		*(int *)(row + 4) = i + GAME_VAR(int, 0x9dd6ac) * 10 + 1;
		strcpy((char *)(row + 8), (const char *)player);
		for (int k = 0; k < 7; k++)
			*(u32 *)(row + dst[k]) = *(const u32 *)(player + src[k]);
		int mode = GAME_VAR(int, 0x9dd1d0), rank;
		if (i == 0) {
			before = GAME_VAR(float, 0x9dd384);
			rank = GAME_VAR(int, 0x9dd328);
		} else {
			long double v;
			rank = *(const int *)(row - 0x44 + 4);
			if (rank_value(row - 0x44, mode, &v))
				before = f32(v);
		}
		rank_value(row, mode, &value);
		if (!(value < before) && !(value > before))   /* (fcom: unordered counts as equal) */
			*(int *)(row + 4) = rank;
	}
	GAME_VAR(float, 0x9dd384) = f32(value);
	GAME_VAR(int, 0x9dd328) = *(const int *)(rows + (i - 1) * 0x44 + 4);
}

/* ---- the skirmish list: eight rows shown from entry top, the cursor on row; sel = top + row ---- */
#define sk_top GAME_VAR(int, 0x9f16bc)
#define sk_row GAME_VAR(int, 0x9f1058)
#define sk_sel GAME_VAR(int, 0x9f16a4)
#define sk_count GAME_VAR(int, 0x9ef2c0)

/* 0x443cd0: cursor up (the list scrolls at the top row) */
void (skirmish_443cd0)(void)
{
	if (sk_row > 0) {
		sk_row--;
		sk_sel = sk_top + sk_row;
		return;
	}
	if (sk_top > 0)
		sk_top--;
	sk_sel = sk_top + sk_row;
}

/* 0x443d10: cursor down (the list scrolls at the bottom row) */
void (skirmish_443d10)(void)
{
	if (sk_top + sk_row < sk_count - 1) {
		if (sk_row < 7)
			sk_row++;
		else
			sk_top++;
		sk_sel = sk_top + sk_row;
	}
}

/* 0x443d50: a click on row */
void (skirmish_443d50)(int row)
{
	if (sk_top + row < sk_count) {
		sk_row = row;
		sk_sel = sk_top + row;
	}
}

/* ---- the skirmish settings' undo stack: values at 0x9eeadc (depth 0x9f1060), the current one 0x9eeba4; the
   pending step 0x9ef1f4 and its flag 0x4d7348; each change clears the 400-dword work buffer at 0x9f1064 ---- */
#define undo_depth GAME_VAR(int, 0x9f1060)
#define undo_stack ((int *)0x9eeadc)
#define undo_value GAME_VAR(int, 0x9eeba4)
#define undo_step GAME_VAR(int, 0x9ef1f4)
#define undo_pending GAME_VAR(int, 0x4d7348)

/* 0x443d80: the pending step pushed (value = the top - 1 + step) */
void (undo_push)(void)
{
	if (undo_pending) {
		int d = undo_depth;
		undo_depth = d + 1;
		undo_value = undo_stack[d] - 1 + undo_step;
		undo_step = 0;
		undo_stack[d + 1] = undo_value;
		memset((void *)0x9f1064, 0, 1600);
		undo_pending = 0;
	}
}

/* 0x443de0: one step undone */
void (undo_pop)(void)
{
	if (undo_depth > 0) {
		undo_depth--;
		undo_value = undo_stack[undo_depth];
		memset((void *)0x9f1064, 0, 1600);
		undo_step = 0;
		undo_pending = 0;
		GAME_VAR(int, 0x9f105c) = 0;
	}
}

/* 0x443ea0: a click on the skirmish settings' arrows: 1 marks a change (0x9ef1f8 = 10, as a right click does), 2 adds
   the pending step, 3 undoes one */
void (menu_443ea0)(void)
{
	if (g_dialogOpen)
		return;
	if (!GAME_VAR(int, 0x4ded8c)) {
		if (!g_mouseClick)
			return;
		switch (skirmish_443910(g_mouseX, g_mouseY)) {
		case 1:
			break;
		case 2:
			undo_push();
			return;
		case 3:
			undo_pop();
			return;
		default:
			return;
		}
	}
	GAME_VAR(int, 0x9ef1f8) = 10;
}

/* ---- leaving the skirmish settings (0x443c80) or the mission settings (0x447960): the screen's state cleared, the
   view squeezed (aspect 0.1) to open out again, the camera to (?, 0, 1600) looking ahead, a sound, the menu camera
   put back. Both return what that leaves in eax ---- */
#define put_camera_back() GAME_CDECL(0x447910, u32, void)()   /* skirmish_447910 */
static u32 leave_settings(u32 state)
{
	GAME_VAR(int, state) = 0;
	GAME_VAR(u32, 0x4e1870) = 0x3dcccccd;   /* g_viewAspect = 0.1 */
	GAME_VAR(int, 0x4df028) = 0;
	GAME_VAR(u32, 0x4df02c) = 0x44c80000;   /* 1600 */
	GAME_VAR(int, 0x68037c) = 0;
	GAME_VAR(int, 0x680380) = 0;
	sound_playMenu(4);
	return put_camera_back();
}
u32 (skirmish_443c80)(void) { return leave_settings(0x9ef1f0); }
u32 (FUN_00447960)(void) { return leave_settings(0x9f62f8); }

/* 0x4370e0: the room's two keys: the first asks to leave (0x9dd6c4 = 1), the second to go back (2), each with the
   menu sound. Returns what the original leaves in eax */
u32 (menu_4370e0)(void)
{
	u32 r = input_justPressed(GAME_VAR(int, 0x4e1510));
	if (r == 1) {
		r = GAME_CDECL(0x41e760, u32, int)(0);   /* sound_playMenu */
		GAME_VAR(int, 0x9dd6c4) = 1;
		return r;
	}
	r = input_justPressed(GAME_VAR(int, 0x4e0cdc));
	if (r == 1) {
		r = GAME_CDECL(0x41e760, u32, int)(0);
		GAME_VAR(int, 0x9dd6c4) = 2;
	}
	return r;
}

/* 0x445be0: the skirmish settings screen drawn: the background (when 0x9eeba8), the map list unless closing (state
   2), the camera; then while open (state past 1) the dialog's frame if one is open, else the screen A (0x9ef1f8 10)
   or B (20). Returns what the original leaves in eax */
u32 (menuState900_skirmishSetup)(void)
{
	if (GAME_VAR(int, 0x9eeba8))
		menu_drawBackground();
	if (GAME_VAR(int, 0x9ef1f0) != 2)
		GAME_CDECL(0x4445a0, void, void)();   /* skirmish_4445a0 */
	GAME_CDECL(0x444130, void, void)();       /* skirmish_444130: the camera */
	int state = GAME_VAR(int, 0x9ef1f0);
	if (state == 1 || state == 0)
		return state;
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x9f16a8), GAME_VAR(int, 0x9f16ac),
		                                                     GAME_VAR(int, 0x9f16b0), GAME_VAR(int, 0x9f16b4));   /* menu_drawFrame */
	int screen = GAME_VAR(int, 0x9ef1f8);
	if (screen == 10)
		return GAME_CDECL(0x445bc0, u32, void)();   /* skirmish_drawScreenA */
	if (screen == 20)
		return GAME_CDECL(0x445bd0, u32, void)();   /* skirmish_drawScreenB */
	return screen;
}

/* 0x444070: the skirmish settings' keys: two keys (and a third) switch to screen A (0x9ef1f8 = 10), two step the
   settings forward and back. Returns what the original leaves in eax */
u32 (menu_444070)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)) == 1)
		return 1;
	if (input_justPressed(GAME_VAR(int, 0x4e0cdc)) == 1 || input_justPressed(GAME_VAR(int, 0x76d48c)) == 1) {
		GAME_VAR(int, 0x9ef1f8) = 10;
		return 1;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e150c)) == 1)
		return GAME_CDECL(0x443d80, u32, void)();   /* undo_push: the pending step pushed */
	u32 r = input_justPressed(GAME_VAR(int, 0x4e1514));
	if (r == 1)
		return GAME_CDECL(0x443de0, u32, void)();   /* undo_pop: one step undone */
	return r;
}

/* ---- the mission select (selection 0x9f63b4) ---- */
/* 0x4479d0: mission sel chosen: its 32-byte record (0x907b30) as the current one (0x67fb44), its three values from the
   0x5c-byte table at 0x9db9e4, the settings left, mission mode (0x67ef14 = 1, 0x5ae9c4 = 3) */
u32 (mission_4479d0)(void)
{
	int sel = GAME_VAR(int, 0x9f63b4);
	u32 t = (u32)sel * 0x5c;
	GAME_VAR(int, 0x9dad94) = sel;
	memcpy((void *)0x67fb44, (const void *)(0x907b30 + sel * 32), 32);
	int a = GAME_VAR(int, 0x9db9e4 + t), b = GAME_VAR(int, 0x9db9ec + t), c = GAME_VAR(int, 0x9db9e8 + t);
	GAME_VAR(int, 0x9da3e0) = 0;
	GAME_VAR(int, 0x76d368) = a;
	GAME_VAR(int, 0x4df8e8) = b;
	GAME_VAR(int, 0x76d408) = c;
	u32 r = GAME_CDECL(0x447960, u32, void)();   /* FUN_00447960: the settings left */
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x5ae9c4) = 3;
	return r;
}

/* 0x447a50: the mission select's clicks (no dialog open): a right click leaves; buttons 0 choose, 1 leave, 2 and 3
   step the selection down and up (within 0 .. the count 0x9f181c and 14). Returns what the original leaves in eax */
u32 (mission_447a50)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (GAME_VAR(int, 0x4ded8c))
		GAME_CDECL(0x447960, u32, void)();
	if (!g_mouseClick)
		return 0;
	u32 button = GAME_CDECL(0x447710, u32, int, int)(g_mouseX, g_mouseY);   /* the screen's hit test */
	int sel = GAME_VAR(int, 0x9f63b4);
	switch (button) {
	case 0:
		return GAME_CDECL(0x4479d0, u32, void)();   /* mission_4479d0 */
	case 1:
		return GAME_CDECL(0x447960, u32, void)();
	case 2:
		if (sel <= 0)
			return (u32)sel;
		GAME_VAR(int, 0x9f63b4) = --sel;
		return GAME_CDECL(0x4479b0, u32, int)(sel);   /* mission_4479b0 */
	case 3:
		if (sel >= GAME_VAR(int, 0x9f181c) || sel >= 0xe)
			return (u32)sel;
		GAME_VAR(int, 0x9f63b4) = ++sel;
		return GAME_CDECL(0x4479b0, u32, int)(sel);
	}
	return button;
}

/* 0x431600: the chat line closed: sent (into the history) when ok, else emptied; typing off, the keyboard taken again,
   the fade timer 10. Returns what the original leaves in eax */
u32 (room_431600)(int ok)
{
	u32 r;
	GAME_VAR(int, 0x68039c) = 0;
	if (ok) {
		GAME_CDECL(0x431590, void, void)();   /* match_431590 */
		input_initKeyboard(g_hWndMain);
		r = GAME_CDECL(0x4315c0, u32, void)();   /* room_4315c0: into the history */
	} else {
		if (GAME_VAR(int, 0x9dcd30) > 0)
			memset((void *)0x9dc92c, 0, GAME_VAR(int, 0x9dcd30));
		GAME_CDECL(0x431590, void, void)();
		r = (u32)input_initKeyboard(g_hWndMain);
	}
	GAME_VAR(int, 0x9dcd30) = 0;
	GAME_VAR(int, 0x9dbf10) = 0;
	GAME_VAR(u32, 0x9da434) = 0x41200000;   /* 10 */
	return r;
}

/* 0x431950: any of three keys closes the message box (0x4df900). Returns the last key's state */
u32 (menu_431950)(void)
{
	static const u32 keys[3] = { 0x9dae70, 0x5b1da8, 0x6803a0 };
	u32 r = 0;
	for (int k = 0; k < 3; k++) {
		r = input_justPressed(GAME_VAR(int, keys[k]));
		if (r == 1) {
			GAME_VAR(int, 0x4dda44) = 0;
			GAME_VAR(int, 0x4df900) = 0;
		}
	}
	return r;
}

/* 0x4318b0: any of three keys starts the menu's fade (0x4df01c, once; its timer 0x4e0458 from 0). Returns what the
   original leaves in eax */
u32 (menu_4318b0)(void)
{
	static const u32 keys[3] = { 0x9dae70, 0x5b1da8, 0x6803a0 };
	u32 r = 0;
	for (int k = 0; k < 3; k++) {
		r = input_justPressed(GAME_VAR(int, keys[k]));
		if (r == 1) {
			if (GAME_VAR(int, 0x4df01c))
				return GAME_VAR(u32, 0x4df01c);
			GAME_VAR(int, 0x4df01c) = 1;
			GAME_VAR(int, 0x4e0458) = 0;
		}
	}
	return r;
}

/* 0x442d10: the map list's visible names: up to 10 rows, 20 pixels apart, from the first shown (0x9dd92c) of the
   0x9dd928 maps (0x44-byte records from 0x9dda88): a flagged one (+0x40) on a red bar with yellow text, the others
   pale blue. Returns the last text_draw8's eax (0 with no rows) */
u32 (mainmenu_442d10)(void)
{
	u32 r = 0;
	for (int i = 0, dy = 0; i < GAME_VAR(int, 0x9dd928) && dy < 200; i++, dy += 20) {
		set_colour_bits((Colour *)0x76d438, 0x3f4ccccd, 0x3f4ccccd, 0x3f800000, 0x3f800000);   /* (0.8, 0.8, 1, 1) */
		int map = GAME_VAR(int, 0x9dd92c) + i;
		if (GAME_VAR(int, 0x9dda88 + map * 0x44 + 0x40)) {
			set_colour_bits((Colour *)0x9da480, 0x3f800000, 0x3dcccccd, 0x3e99999a, 0x3f000000);   /* (1, 0.1, 0.3, 0.5) */
			menu_drawRect(GAME_VAR(int, 0x9dd908) + 0x20, GAME_VAR(int, 0x9dd90c) + dy + 0x2b, GAME_VAR(int, 0x9dd910) - 0x50,
			              GAME_VAR(int, 0x9dd90c) + dy + 0x3d, 1);
			set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);   /* yellow */
		}
		map = GAME_VAR(int, 0x9dd92c) + i;
		r = GAME_CDECL(0x402620, u32, int, int, const char *)(GAME_VAR(int, 0x9dd908) + 0x28, GAME_VAR(int, 0x9dd90c) + dy + 0x2c,
		                                                      (const char *)(0x9dda88 + map * 0x44));   /* text_draw8 */
	}
	return r;
}

/* the game left for the launcher: the keys held (4), the camera pulled back (0x4deb48, next screen 210), the
   progress saved and 0x48b420. Returns its eax */
static u32 leave_game(void)
{
	set_680370_441250(4);
	GAME_VAR(int, 0x4deb48) = 1;
	GAME_VAR(int, 0x67ef20) = 210;
	GAME_CDECL(0x447010, void, void)();   /* profile_saveProgress */
	return GAME_CDECL(0x48b420, u32, void)();
}

/* main menu choice i (with its sound; 0x4dda44 cleared): 0 the campaign (menuState500_enter), 1 skirmish (next
   screen 400), 2 network play (net_connect, then 0x452170; messages 0x2a / 0x29 when they fail; next screen 800), 3
   the setup (600), 4 the armour centre (0x40ee20), 5 quit. The original's eax into *r; 1 when a failure ended the
   caller there */
static int menu_choice(int i, u32 *r)
{
	sound_playMenu(0);
	if (i)
		GAME_VAR(float, 0x4dda44) = 0.0f;
	int result;
	switch (i) {
	case 0:
		*r = GAME_CDECL(0x447750, u32, void)();   /* menuState500_enter */
		GAME_VAR(int, 0x4deb48) = 0;
		return 0;
	case 2:
		result = GAME_CDECL(0x451b80, int, int)(0x65);   /* net_connect */
		if (result == 2 || result == 0 || GAME_CDECL(0x452170, int, void *, int)(GAME_VAR(void *, 0x4ded18), 0x65) == 0) {
			sound_playMenu(6);
			*r = GAME_CDECL(0x41ee40, u32, int)(result == 2 ? 0x2a : 0x29);
			return 1;
		}
		/* fall through */
	case 1: case 3:
		*r = GAME_CDECL(0x441250, u32, int)(2);   /* set_680370_441250 */
		GAME_VAR(int, 0x4deb48) = 0;
		GAME_VAR(int, 0x67ef20) = i == 1 ? 400 : i == 2 ? 800 : 600;
		return 0;
	case 4:
		GAME_VAR(int, 0x4dc24c) = 1;
		*r = GAME_CDECL(0x40ee20, u32, void)();   /* menu_enterMenus: the armour centre */
		GAME_VAR(int, 0x4deb48) = 0;
		return 0;
	default:
		*r = leave_game();
		return 0;
	}
}

/* 0x4419d0: the main menu clicked (not while it is fading in (0x9db994 = 1); the map-select dialog first if open):
   its six buttons (outlines 0x2c bytes apart from 0x4deb80) as menu_choice. A right click quits too when the game
   was started from the launcher (0x9dae10). Returns what the original leaves in eax */
u32 (mainmenu_startNetGame)(void)
{
	if (GAME_VAR(int, 0x9db994) == 1)
		return 1;
	if (GAME_VAR(int, 0x9eeab4))
		return GAME_CDECL(0x441810, u32, void)();   /* mainmenu_441810: the map-select dialog */
	if (GAME_VAR(int, 0x4ded88)) {
		GAME_VAR(float, 0x4dda44) = 0.0f;
		const Outline *buttons = (const Outline *)0x4deb80;
		int i = 0;
		while (i < 6 && point_in_outline(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c), buttons[i]) != 1)
			i++;
		u32 r;
		if (i < 6 && menu_choice(i, &r))
			return r;
	}
	if (!GAME_VAR(int, 0x4ded8c))
		return 0;
	int launched = GAME_VAR(int, 0x9dae10);
	if (launched <= 0)
		return launched;
	GAME_VAR(float, 0x4dda44) = 0.0f;
	return leave_game();
}

/* 0x441e00: the main menu's keys (not while fading in; the map-select dialog's keys (mainmenu_441c00) when open):
   the six choices' keys as menu_choice, the back key quitting (without saving) when started from the launcher, and
   the map-select key (0x440d70, the dialog opened). Returns what the original leaves in eax */
u32 (mainmenu_processKeys)(void)
{
	static const u32 key[6] = { 0x4e1500, 0x4e1508, 0x4e1504, 0x4e1524, 0x4e0cd4, 0x4e153c };
	if (GAME_VAR(int, 0x9db994) == 1)
		return 1;
	if (GAME_VAR(int, 0x9eeab4))
		return GAME_CDECL(0x441c00, u32, void)();   /* mainmenu_441c00 */
	for (int i = 0; i < 6; i++)
		if (input_justPressed(GAME_VAR(int, key[i])) == 1) {
			u32 r;
			menu_choice(i, &r);
			return r;
		}
	if (input_justPressed(GAME_VAR(int, 0x76d48c)) && GAME_VAR(int, 0x9dae10) > 0) {
		GAME_VAR(float, 0x4dda44) = 0.0f;
		set_680370_441250(4);
		GAME_VAR(int, 0x4deb48) = 1;
		GAME_VAR(int, 0x67ef20) = 210;
		return GAME_CDECL(0x48b420, u32, void)();
	}
	u32 r = (u32)input_justPressed(GAME_VAR(int, 0x9da440));
	if (r != 1)
		return r;
	r = GAME_CDECL(0x440d70, u32, void)();
	GAME_VAR(int, 0x9eeab4) = 1;
	return r;
}

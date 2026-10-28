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
void (FUN_0041ee40)(int i)
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
void (FUN_0040ddb0)(void)
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
void (FUN_004463a0)(void)
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

/* 0x4464b0: the mech stored into the profile record (the inverse of FUN_004463a0) */
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
void (FUN_00443d80)(void)
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
void (FUN_00443de0)(void)
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
			FUN_00443d80();
			return;
		case 3:
			FUN_00443de0();
			return;
		default:
			return;
		}
	}
	GAME_VAR(int, 0x9ef1f8) = 10;
}

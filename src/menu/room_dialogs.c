/* room_dialogs.c: the room screen's dialogs opened and its state reset: each dialog a box (left, top, right,
   bottom), its fields cleared, the screen's sub-state (0x9dd834) set to the dialog's. */
#include "../game.h"
#include <string.h>

#define g_roomState GAME_VAR(int, 0x9dd834)   /* the room screen's sub-state: which dialog is up */

static void set_box(u32 box, int left, int top, int right, int bottom)
{
	GAME_VAR(int, box) = left;
	GAME_VAR(int, box + 4) = top;
	GAME_VAR(int, box + 8) = right;
	GAME_VAR(int, box + 12) = bottom;
}

/* the cursor, the picked field and the key repeat of a dialog cleared */
static void dialog_opened(int state)
{
	g_roomState = state;
	g_dialogOpen = 1;
	GAME_VAR(int, 0x9dd830) = 0;
	GAME_VAR(int, 0x9dd38c) = 0;
	GAME_VAR(int, 0x4e1868) = 0;
	GAME_VAR(int, 0x68039c) = 0;
}

/* 0x433980: dialog 0x58 */
void (room_433980)(void)
{
	set_box(0x9dd1a0, 0x50, 0x78, 0x230, 0x168);
	room_431c00();
	dialog_opened(0x58);
	GAME_VAR(int, 0x9dd6c4) = 0;
}

/* 0x4338c0: dialog 0x4d, its two 0x2a-byte name buffers emptied */
void (room_4338c0)(void)
{
	set_box(0x9dd6e8, 0x1e, 0x32, 0x262, 0x1ae);
	room_431b70();
	memset((void *)0x9dd1d8, 0, 0x54);
	dialog_opened(0x4d);
	GAME_VAR(int, 0x9dd4a0) = 1;
	GAME_VAR(int, 0x9dd850) = 0;
}

/* 0x434640: dialog 0x42, its name field filled from 0x9dd570 */
void (room_434640)(void)
{
	static const u32 cleared[] = { 0x9dd348, 0x9dd32c, 0x9dd3f8, 0x9dd564, 0x9dd6cc, 0x4e1868, 0x68039c };
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	memset((void *)0x9dd1d8, 0, 7 * 4 + 2 + 12);
	g_roomState = 0x42;
	GAME_VAR(int, 0x9dced0) = 1;
	strcpy((char *)0x9dd1d8, (const char *)0x9dd570);
}

/* 0x433590: the room screen's start: state 1, fade 0.7, 30 (0x5b1914), 999 (0x907b24), the rest cleared */
void (room_433590)(void)
{
	static const u32 cleared[] = { 0x9dd3fc, 0x9dd6a0, 0x9dd330, 0x9da498, 0x67ef30, 0x4dba80, 0x76d41c, 0x680bb0,
	                               0x4df818, 0x9dd4bc, 0x9dd56c, 0x9dd6c0, 0x9dd34c, 0x9dcd40, 0x9dd840 };
	GAME_VAR(u32, 0x9dd6bc) = 0x3f333333;   /* 0.7 */
	g_roomState = 1;
	GAME_VAR(int, 0x9dce48) = 1;
	GAME_VAR(int, 0x907b24) = 999;
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	GAME_VAR(int, 0x5b1914) = 30;
}

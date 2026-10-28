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

#define CALL(addr) GAME_CDECL(addr, u32, void)()
#define sound(id) GAME_CDECL(0x41e760, u32, int)(id)   /* sound_playMenu, its eax */

/* 0x4378e0: the game room's mouse, by state (0x9dd834): 0 .. 2, 4 and 99 while no dialog is open (0x9dd7d8; 2: the map
   list's keys when open), 66 and 88 (a message box 0x9dd850 first), 77. Returns what the handler leaves in eax */
u32 (menu_4378e0)(void)
{
	u32 state = GAME_VAR(u32, 0x9dd834);
	int dialog = GAME_VAR(int, 0x9dd7d8);
	switch (state) {
	case 0: return dialog ? (u32)dialog : CALL(0x437240);   /* menu_437240 */
	case 1: return dialog ? (u32)dialog : CALL(0x4372f0);
	case 2:
		if (dialog)
			return (u32)dialog;
		return GAME_VAR(int, 0x4db508) ? CALL(0x403870) : CALL(0x437630);
	case 4: return dialog ? (u32)dialog : CALL(0x437810);
	case 66: return GAME_VAR(int, 0x9dd850) == 1 ? CALL(0x436940) : CALL(0x436990);
	case 77: return CALL(0x436e10);
	case 88: return GAME_VAR(int, 0x9dd850) == 1 ? CALL(0x436940) : CALL(0x4370e0);
	case 99: return dialog ? (u32)dialog : CALL(0x437140);
	}
	return state;
}

/* 0x437240: the game room's keys (unless typing): with the confirm box up (0x9dd6d4) one key closes it; else the
   first key starts the game when ready (0x434b90), or plays the refusal sound and shows message 5; two more keys
   leave the screen (0x9dce48 = 0). Returns what the original leaves in eax */
u32 (menu_437240)(void)
{
	if (GAME_VAR(int, 0x68039c))
		return GAME_VAR(u32, 0x68039c);
	if (GAME_VAR(int, 0x9dd6d4) == 1) {
		if (!input_justPressed(GAME_VAR(int, 0x76d48c)))
			return 0;
	} else if (input_justPressed(GAME_VAR(int, 0x4e1510))) {
		if (CALL(0x434b90) != 1) {   /* not ready */
			sound(6);
			return GAME_CDECL(0x41ee40, u32, int)(5);   /* FUN_0041ee40: the message */
		}
	} else if (!input_justPressed(GAME_VAR(int, 0x4e0cdc)) && !input_justPressed(GAME_VAR(int, 0x76d48c)))
		return 0;
	u32 r = sound(0);
	GAME_VAR(int, 0x9dce48) = 0;
	return r;
}

/* 0x435c20: the game settings dialog's clicks: a right click (or button 5) closes it, buttons 0 .. 3 pick an option
   page, 4 applies. Returns what the original leaves in eax */
u32 (room_435c20)(void)
{
	if (GAME_VAR(int, 0x4ded8c)) {
		sound(0);
		return CALL(0x434640);   /* closed */
	}
	if (!g_mouseClick)
		return 0;
	u32 button = GAME_CDECL(0x432240, u32, int, int)(g_mouseX, g_mouseY);   /* the dialog's hit test */
	if (button <= 3) {
		CALL(0x433d30);
		return GAME_CDECL(0x433e60, u32, int)((int)button);
	}
	if (button == 4) {
		sound(0);
		return CALL(0x4346c0);   /* applied */
	}
	if (button == 5) {
		sound(0);
		return CALL(0x434640);
	}
	return button;
}

/* 0x434dd0: joining session i of the list: its DirectPlay connection (0x452ec0) and the join (arena_453260); a failure
   shows message 0x3f or 0x40 and stops the search; on success the join's wait starts (timer 0x378, 2 s, its id
   kept). Returns what the original leaves in eax */
u32 (room_434dd0)(int i)
{
	GAME_VAR(int, 0x9dd56c) = 0;
	if (!GAME_CDECL(0x452ec0, int, int, void *)(0, (void *)(0x9087ef + i * 0x4a))) {
		GAME_CDECL(0x41ee40, void, int)(0x3f);
		return CALL(0x452fe0);   /* arena_452fe0 */
	}
	GAME_VAR(int, 0x4db710) = i;
	if (!CALL(0x453260)) {        /* arena_453260 */
		GAME_CDECL(0x41ee40, void, int)(0x40);
		return CALL(0x452fe0);
	}
	GAME_VAR(int, 0x4dbb10) = 0;
	GAME_VAR(int, 0x4db8b4) = 1;
	GAME_VAR(int, 0x4dbb78) = 0;
	GAME_VAR(int, 0x4db708) = 0;
	u32 timer = IMPORT(0x4a9334, u32, void *, u32, u32, void *)(g_hWndMain, 0x378, 2000, NULL);   /* SetTimer */
	GAME_VAR(u32, 0xa0bad0) = timer;
	return timer;
}

/* 0x434d00: the game room's list opened: its state reset, the session list cleared, the request for the server's
   room list sent (message 0x13, 0x65 bytes), 30 seconds. Returns 1 */
int (room_434d00)(void)
{
	GAME_VAR(int, 0x4dba88) = 1;
	GAME_VAR(int, 0x4ded60) = 2;
	GAME_VAR(int, 0x9da498) = 0;
	GAME_VAR(int, 0x9dd3fc) = 0;
	GAME_VAR(int, 0x9dd6a0) = 1;
	GAME_VAR(int, 0xa0b34c) = 0;
	GAME_VAR(int, 0x9087b0) = 0;
	GAME_VAR(int, 0x67ef30) = 0;
	GAME_VAR(int, 0x9dd330) = 1;
	GAME_VAR(int, 0x76d41c) = 0;
	GAME_VAR(u32, 0x4dba80) = 0x447a0000;   /* 1000 */
	GAME_VAR(int, 0x680bb0) = 0;
	GAME_VAR(int, 0x4df818) = 0;
	CALL(0x4045e0);   /* arena_4045e0 */
	GAME_VAR(u32, GAME_VAR(u32, 0xa0b334)) = 0x180001;
	GAME_CDECL(0x4521c0, int, int, int)(0x13, 0x65);   /* net_send */
	GAME_VAR(int, 0x9dd840) = 0;
	GAME_VAR(int, 0x5b1914) = 0x1e;
	return 1;
}

/* 0x406200: joining arena i of the list (99999: the one typed in, 0x4dbbd4): the search stopped first if it runs,
   the connection made (0x452ec0; message 0x3f and the search stopped on a failure), the join (arena_453260, not
   checked), the join's wait (timer 0x378, 2 s). Returns what the original leaves in eax */
u32 (arena_406200)(int i)
{
	GAME_VAR(int, 0x4dbbec) = 0;
	GAME_VAR(int, 0x4dbbf0) = 0;
	if (GAME_VAR(int, 0x4dba84))
		CALL(0x452fe0);
	void *session = i == 99999 ? (void *)0x4dbbd4 : (void *)(0x9087ef + i * 0x4a);
	if (!GAME_CDECL(0x452ec0, int, int, void *)(0, session)) {
		GAME_CDECL(0x41ee40, void, int)(0x3f);
		return CALL(0x452fe0);
	}
	GAME_VAR(int, 0x4db710) = i;
	CALL(0x453260);
	GAME_VAR(int, 0x4dbb10) = 0;
	GAME_VAR(int, 0x4db8b4) = 1;
	GAME_VAR(int, 0x4dbb78) = 0;
	GAME_VAR(int, 0x4db708) = 0;
	u32 timer = IMPORT(0x4a9334, u32, void *, u32, u32, void *)(g_hWndMain, 0x378, 2000, NULL);   /* SetTimer */
	GAME_VAR(u32, 0xa0bad0) = timer;
	return timer;
}

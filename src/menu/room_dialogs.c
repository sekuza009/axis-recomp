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

/* 0x436800: the game room's keys, by state (0x9dd834): as menu_4378e0's mouse, with the room's own handlers (state 1:
   the join's wait while it runs, 0x4db8b4). Returns what the handler leaves in eax */
u32 (room_processKeys)(void)
{
	u32 state = GAME_VAR(u32, 0x9dd834);
	int dialog = GAME_VAR(int, 0x9dd7d8);
	switch (state) {
	case 0: return dialog ? (u32)dialog : CALL(0x435e70);   /* room_435e70 */
	case 1:
		if (dialog)
			return (u32)dialog;
		return GAME_VAR(int, 0x4db8b4) ? CALL(0x435f40) : CALL(0x435fc0);
	case 2:
		if (dialog)
			return (u32)dialog;
		return GAME_VAR(int, 0x4db508) ? CALL(0x4036c0) : CALL(0x436400);
	case 4: return dialog ? (u32)dialog : CALL(0x436620);
	case 66: return GAME_VAR(int, 0x9dd850) ? CALL(0x435ab0) : CALL(0x435b00);
	case 77: return CALL(0x435c20);   /* room_435c20 */
	case 88: return GAME_VAR(int, 0x9dd850) ? CALL(0x435ab0) : CALL(0x435ce0);
	case 99: return dialog ? (u32)dialog : CALL(0x435d30);
	}
	return state;
}

/* 0x435e70: the game room's clicks while it is open (0x9dce48 past 1; no confirm box, dialog or typing): buttons 0 .. 3
   edit the settings' fields, 4 starts the game when ready (else message 5 and the refusal sound), 5 (or a right click)
   leaves. Returns what the original leaves in eax */
u32 (room_435e70)(void)
{
	int mode = GAME_VAR(int, 0x9dce48);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x9dd6d4) == 1)
		return (u32)mode;
	if (g_dialogOpen)
		return (u32)g_dialogOpen;
	if (GAME_VAR(int, 0x68039c))
		return GAME_VAR(u32, 0x68039c);
	if (!GAME_VAR(int, 0x4ded8c)) {
		if (!g_mouseClick)
			return 0;
		u32 button = GAME_CDECL(0x4322c0, u32, int, int)(g_mouseX, g_mouseY);   /* the room's hit test */
		switch (button) {
		case 0: return CALL(0x434020);
		case 1: return CALL(0x4340e0);
		case 2: return CALL(0x4341a0);
		case 3: return CALL(0x434260);
		case 4:
			if (CALL(0x434b90) == 1)
				break;
			GAME_CDECL(0x41ee40, void, int)(5);
			return sound(6);
		case 5:
			break;
		default:
			return button;
		}
	}
	u32 r = sound(0);
	GAME_VAR(int, 0x9dce48) = 0;
	return r;
}

/* 0x43ed20: the game room drawn (its background first): while open and not leaving (state 99), the dialog's frame if
   one is open, else the room settings kept in range (players 0 .. 16 else 8, the frag limit at most 50 and the time
   at most 60 else 30, the map 0 .. 11 else 0), the settings panel, the map list when open, the options when shown.
   Returns what the original leaves in eax */
u32 (room_43ed20)(void)
{
	CALL(0x4388e0);   /* room_4388e0 */
	int mode = GAME_VAR(int, 0x9dce48);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x9dd834) == 0x63)
		return (u32)mode;
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x9dd1b8), GAME_VAR(int, 0x9dd1bc),
		                                                     GAME_VAR(int, 0x9dd1c0), GAME_VAR(int, 0x9dd1c4));   /* menu_drawFrame */
	signed char players = GAME_VAR(signed char, 0x5b1b51);
	if (players < 0 || players > 0x10)
		GAME_VAR(u8, 0x5b1b51) = 8;
	if (GAME_VAR(u8, 0x5b1b54) > 0x32)
		GAME_VAR(u8, 0x5b1b54) = 0x1e;
	if (GAME_VAR(u8, 0x5b1b55) > 0x3c)
		GAME_VAR(u8, 0x5b1b55) = 0x1e;
	signed char map = GAME_VAR(signed char, 0x5b1b53);
	if (map < 0 || map > 0xb)
		GAME_VAR(u8, 0x5b1b53) = 0;
	CALL(0x43bfe0);   /* room_drawGameSettings */
	if (GAME_VAR(int, 0x4db508) == 1)
		CALL(0x4038e0);   /* arena_4038e0: the map list */
	if (!GAME_VAR(int, 0x4dba88))
		return 0;
	return CALL(0x4355b0);   /* room_4355b0 */
}

/* 0x433c70: the chat edit control closed (the window focused again, the line sent): typed into the room's name
   (0x9dd1cc set: up to 30 bytes at 0x9dd1d8) or its password (0x9dd6b0: 12 bytes at 0x9dd1f6, the stars off).
   Returns what the original leaves in eax */
u32 (room_433c70)(void)
{
	IMPORT(0x4a9344, u32, void *)(GAME_VAR(void *, 0x9dd888));   /* DestroyWindow */
	IMPORT(0x4a935c, void *, void *)(g_hWndMain);               /* SetFocus */
	GAME_CDECL(0x431600, u32, int)(1);                           /* room_431600: the line sent */
	if (GAME_VAR(int, 0x9dd1cc) == 1) {
		memset((void *)0x9dd1d8, 0, 30);
		GAME_VAR(int, 0x9dd1cc) = 0;
		strcpy((char *)0x9dd1d8, (const char *)0x9dc92c);
		return 0;
	}
	if (GAME_VAR(int, 0x9dd6b0) == 1) {
		memset((void *)0x9dd1f6, 0, 12);
		GAME_VAR(int, 0x4e1868) = 0;
		strcpy((char *)0x9dd1f6, (const char *)0x9dc92c);
		GAME_VAR(int, 0x9dd6b0) = 0;
		return 0;
	}
	return GAME_VAR(u32, 0x9dd1cc);
}

/* 0x43e610: the game room's network events: a pending leave (0x9dd6c4: 1 leave now, 2 to state 0x4d), then the
   server's answer (0xa0b37c, when awaited: 0x9dd6a4): 33 accepted (the ladder game set up, the settings written, to
   state 99), 30 message 0x22, 42 a message box, anything else message 0x2a. Returns what the original leaves in eax */
u32 (room_43e610)(void)
{
	u32 r = GAME_VAR(u32, 0x9dd6c4) - 2;   /* (what the original's compare chain leaves) */
	if (GAME_VAR(int, 0x9dd6c4) == 1) {
		r = CALL(0x434820);   /* room_434820 */
		GAME_VAR(int, 0x9dd6c4) = 0;
	} else if (GAME_VAR(int, 0x9dd6c4) == 2) {
		r = 0;
		GAME_VAR(int, 0x9dd834) = 0x4d;
		GAME_VAR(int, 0x9dd6c4) = 0;
	}
	if (!GAME_VAR(int, 0x9dd6a4))
		return r;
	u32 answer = GAME_VAR(u32, 0xa0b37c);
	switch (answer) {
	case 0:
		return 0;
	case 33:
		GAME_VAR(int, 0x9dd834) = 0x63;
		GAME_VAR(int, 0x9dd838) = 0;
		CALL(0x432620);   /* lobby_ladderGameName */
		r = CALL(0x432400);   /* reg_writeCharacterSettings */
		GAME_VAR(int, 0xa0b37c) = 0;
		GAME_VAR(int, 0x9dd84c) = 1;
		return r;
	case 30:
		GAME_VAR(int, 0x9dd838) = 0;
		r = GAME_CDECL(0x41ee40, u32, int)(0x22);
		GAME_VAR(int, 0xa0b37c) = 0;
		return r;
	case 42:
		GAME_VAR(int, 0x9dd838) = 0;
		GAME_VAR(int, 0xa0b37c) = 0;
		GAME_VAR(int, 0x9dd850) = 1;
		return answer;
	}
	GAME_VAR(int, 0x9dd838) = 0;
	r = GAME_CDECL(0x41ee40, u32, int)(0x2a);
	GAME_VAR(int, 0xa0b37c) = 0;
	return r;
}

/* 0x437810: the room list's keys while its password box is up (0x9dd6b8): one key cancels it (the list's page and
   mode put back), another cancels it or, without it, leaves the screen; a third leaves the screen. Returns what the
   original leaves in eax */
u32 (menu_437810)(void)
{
	u32 r;
	if (input_justPressed(GAME_VAR(int, 0x4e1524))) {
		if (!GAME_VAR(int, 0x9dd6b8))
			return 0;
		r = sound(0);
		GAME_VAR(int, 0x9dd6b8) = 0;
		GAME_VAR(int, 0x76d40c) = 0;
		GAME_VAR(int, 0x9dd6ac) = GAME_VAR(int, 0x9dd1b4);
		GAME_VAR(int, 0x9dd1d0) = GAME_VAR(int, 0x9dd300);
		GAME_VAR(int, 0x9dd3b0) = 1;
		return r;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0cdc))) {
		if (GAME_VAR(int, 0x9dd6b8))
			return GAME_VAR(u32, 0x9dd6b8);
		r = sound(0);
		GAME_VAR(int, 0x9dd6b8) = 0;
		GAME_VAR(int, 0x9dd3b0) = 0;
		GAME_VAR(int, 0x76d40c) = 0;
		GAME_VAR(int, 0x9dce48) = 0;
		return r;
	}
	if (!input_justPressed(GAME_VAR(int, 0x76d48c)))
		return 0;
	if (GAME_VAR(int, 0x9dd6b8))
		return GAME_VAR(u32, 0x9dd6b8);
	r = sound(0);
	GAME_VAR(int, 0x9dce48) = 0;
	return r;
}

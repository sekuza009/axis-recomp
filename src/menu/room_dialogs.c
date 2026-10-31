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
			return GAME_CDECL(0x41ee40, u32, int)(5);   /* menu_showMessage: the message */
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

/* the dialog's button choice (g_dialogChoice) highlighted at (x, y) */
static void highlight_choice(int choice, int x, int y)
{
	g_dialogChoice = choice;
	g_highlightShown = 1;
	GAME_VAR(u32, 0x680bc0) = 0x41a00000;   /* g_highlightSize 20 */
	GAME_VAR(u32, 0x9da4a4) = 0x3ecccccd;   /* g_highlightAlpha 0.4 */
	g_highlightX = x;
	g_highlightY = y;
}

/* 0x43df80: the create-game dialog (its panel at 0x9dd358): a password to retype (0x9dced0: the settings back and
   the password opened again), the login to send (0x9dd198); once typing has ended (g_paused clear), the line taken
   into the game's name (0x9dd830; 30 bytes at 0x9dd1d8) or password (0x9dd38c; 12 at 0x9dd1f6) and the key that
   ended it (0x9dc428: 10 back, 20 on) moving to the other field or the dialog's buttons; else the server's answer
   to the request (0xa0b378, awaited: 0x9dd838): 33 accepted (state 99, the settings written and taken), 42 done
   (0x9dd850), 31 / 32 / 34 a message (31 / 32 / 35), anything else message 42 */
void (room_43df80)(void)
{
#define g_editKey GAME_VAR(int, 0x9dc428)
	if (GAME_VAR(int, 0x9dced0)) {
		room_432be0();
		room_433bb0();
		GAME_VAR(int, 0x9dced0) = 0;
		return;
	}
	if (GAME_VAR(int, 0x9dd198) == 1) {
		room_433c70();
		room_434490();
		GAME_VAR(int, 0x9dd198) = 0;
		return;
	}
	if (GAME_VAR(int, 0x9dd830)) {
		if (g_paused)
			return;
		GAME_VAR(int, 0x9dd830) = 0;
		memset((void *)0x9dd1d8, 0, 30);
		strcpy((char *)0x9dd1d8, g_chatLine);
		if (g_editKey == 10) {
			highlight_choice(3, GAME_VAR(int, 0x9dd358) + 0x1a2, GAME_VAR(int, 0x9dd364) - 0x30);
			GAME_VAR(int, 0x9dd1cc) = 0;
			g_editKey = 0;
		} else if (g_editKey == 20) {
			GAME_VAR(int, 0x9dd1cc) = 0;
			room_433bb0();
			GAME_VAR(int, 0x9dd6b0) = 1;
			g_chatFieldFlag = 1;
			g_editKey = 0;
		}
		return;
	}
	if (GAME_VAR(int, 0x9dd38c)) {
		if (g_paused)
			return;
		memset((void *)0x9dd1f6, 0, 12);
		GAME_VAR(int, 0x9dd38c) = 0;
		strcpy((char *)0x9dd1f6, g_chatLine);
		g_chatFieldFlag = 0;
		if (g_editKey == 10) {
			GAME_VAR(int, 0x9dd1cc) = 1;
			GAME_VAR(int, 0x9dd6b0) = 0;
			room_433b00();
			g_editKey = 0;
		} else if (g_editKey == 20) {
			highlight_choice(1, GAME_VAR(int, 0x9dd358) + 0x62, GAME_VAR(int, 0x9dd364) - 0x30);
			GAME_VAR(int, 0x9dd1cc) = 0;
			GAME_VAR(int, 0x9dd6b0) = 0;
			g_editKey = 0;
		}
		return;
	}
	if (!GAME_VAR(int, 0x9dd838))
		return;
	u32 answer = GAME_VAR(u32, 0xa0b378);
	if (answer == 0)
		return;
	GAME_VAR(int, 0x9dd838) = 0;
	if (answer == 0x21) {
		GAME_VAR(int, 0x9dd834) = 99;
		reg_writeCharacterSettings();
		room_432db0();
	} else if (answer == 0x2a)
		GAME_VAR(int, 0x9dd850) = 1;
	else if (answer == 0x1f || answer == 0x20)
		menu_showMessage(answer);
	else if (answer == 0x22)
		menu_showMessage(0x23);
	else
		menu_showMessage(0x2a);
	GAME_VAR(int, 0xa0b378) = 0;
	GAME_VAR(int, 0x9dd1c8) = 0;
#undef g_editKey
}

/* 0x43e290: the login form (its panel at 0x9dd6e8): the name opened when asked (0x9dd4a0); with no message box
   (0x4df900) and typing ended, the line taken into the field being typed in (the first of the four flagged 1) and
   the key that ended it (0x9dc428: 20 on, 10 back) moving to the next or previous field; on from the e-mail
   highlights the right button, back from the name the left one (the name's flag left set). Then the flagged field
   opened again for typing (the password's before the repeat's) */
void (room_43e290)(void)
{
	static const struct { u32 editing, text; int size; } field[4] = {
		{ 0x9dd348, 0x9dd1d8, 30 }, { 0x9dd3f8, 0x9dd1f6, 12 }, { 0x9dd564, 0x9dd202, 12 }, { 0x9dd6cc, 0x9dd20e, 50 } };
#define EDITING(k) GAME_VAR(int, field[k].editing)
	if (GAME_VAR(int, 0x9dd4a0)) {
		room_433e60(0);
		GAME_VAR(int, 0x9dd4a0) = 0;
		return;
	}
	if (GAME_VAR(int, 0x4df900) || g_paused)
		return;
	int key = GAME_VAR(int, 0x9dc428);
	if (key == 20 || key == 10) {
		int k = 0;
		while (k < 4 && EDITING(k) != 1)
			k++;
		if (k < 4) {
			memset((void *)field[k].text, 0, field[k].size);
			strcpy((char *)field[k].text, g_chatLine);
			if (key == 10 && k == 0)
				highlight_choice(2, GAME_VAR(int, 0x9dd6e8) + 0x172, GAME_VAR(int, 0x9dd6f4) - 0x2c);
			else {
				EDITING(k) = 0;
				if (key == 10)
					EDITING(k - 1) = 1;
				else if (k < 3)
					EDITING(k + 1) = 1;
				else {
					EDITING(0) = 0;
					highlight_choice(1, GAME_VAR(int, 0x9dd6e8) + 0xaa, GAME_VAR(int, 0x9dd6f4) - 0x2c);
				}
			}
		}
		GAME_VAR(int, 0x9dc428) = 0;
	}
	if (EDITING(0) == 1) {
		room_433e60(0);
		return;
	}
	if (EDITING(1) == 1)
		room_433e60(1);
	if (EDITING(2) == 1) {
		room_433e60(2);
		return;
	}
	if (EDITING(3) == 1)
		room_433e60(3);
#undef EDITING
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

/* 0x4334c0: the request to join the selected room sent: the room's password and state cleared, the room screen at
   state 0 (open, brightness 0.7), the room's name (0x9dd570, 30 bytes) as message 0x1d; then the confirm box up.
   Returns net_send's eax */
u32 (room_4334c0)(void)
{
	static const u32 cleared[] = { 0x9dd202, 0x9dd1f6, 0x9dd206, 0x9dd6d8, 0x9dd1fa, 0x9dd20a, 0x9dd6dc, 0x9dd834 };
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	GAME_VAR(int, 0x9dce48) = 1;
	GAME_VAR(u32, 0x9dd6bc) = 0x3f333333;
	static const u32 cleared2[] = { 0x9dd69c, 0x9dd37c, 0x9dd378, 0x9dd304, 0x9dd6d0, 0x9dd1fe, 0x9dd6e0 };
	for (unsigned k = 0; k < sizeof cleared2 / sizeof cleared2[0]; k++)
		GAME_VAR(int, cleared2[k]) = 0;
	char *message = GAME_VAR(char *, 0xa055e0);
	memset(message, 0, 30);
	strcpy(message, (const char *)0x9dd570);
	u32 r = GAME_CDECL(0x4521c0, u32, int, int)(0x1d, 0x65);   /* net_send */
	GAME_VAR(int, 0x9dd354) = 0;
	GAME_VAR(int, 0x9dd6d4) = 1;
	return r;
}

/* a password as stars: the buffer cleared (size bytes), then one '*' a character */
static void stars(char *out, int size, const char *password)
{
	int n = strlen(password);
	memset(out, 0, size);
	if (n > 0)
		memset(out, '*', n);
}

/* 0x4399c0: the server login dialog (0x9dd6e8 .. 0x9dd6f4; only its frame while a message box is open): the title
   0x7588a4, four labelled lines (0x758924, 0x80 apart) with underlines, the values (the name 0x9dd1d8, the two
   passwords 0x9dd1f6 / 0x9dd202 as stars, 0x9dd20e), each left out while its field is being typed in (0x9dd348 /
   0x9dd3f8 / 0x9dd564 / 0x9dd6cc, with the keys taken), the two buttons (the one under the pointer, 4 / 5 by
   FUN_00432240, bright) and the border. Returns the frame's or the border's eax */
u32 (room_4399c0)(void)
{
#define X0 GAME_VAR(int, 0x9dd6e8)
#define Y0 GAME_VAR(int, 0x9dd6ec)
#define X1 GAME_VAR(int, 0x9dd6f0)
#define Y1 GAME_VAR(int, 0x9dd6f4)
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the frame */
	const u32 *bright = (const u32 *)0x9dcec0, *dim = (const u32 *)0x9dd338;
	int hovered = GAME_CDECL(0x432240, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x40, Y0 + 0x10, (const char *)0x7588a4);
	set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
	for (int k = 0; k < 4; k++) {
		text_draw8(X0 + 0x30, Y0 + k * 0x30 + 0x3c, (const char *)(0x758924 + k * 0x80));
		menu_drawLine(X0 + 0x84, Y0 + k * 0x30 + 0x50, X0 + 0x200, Y0 + k * 0x30 + 0x50);
	}
	char hidden[64];   /* (30 bytes cleared, as the original's buffer) */
	if (!GAME_VAR(int, 0x9dd348) || !g_paused)
		text_draw8(X0 + 0x94, Y0 + 0x3c, (const char *)0x9dd1d8);
	if (!GAME_VAR(int, 0x9dd3f8) || !g_paused) {
		stars(hidden, sizeof hidden, (const char *)0x9dd1f6);
		text_draw8(X0 + 0x94, Y0 + 0x6c, hidden);
	}
	if (!GAME_VAR(int, 0x9dd564) || !g_paused) {
		stars(hidden, sizeof hidden, (const char *)0x9dd202);
		text_draw8(X0 + 0x94, Y0 + 0x9c, hidden);
	}
	if (!GAME_VAR(int, 0x9dd6cc) || !g_paused)
		text_draw8(X0 + 0x94, Y0 + 0xcc, (const char *)0x9dd20e);
	for (int k = 0; k < 2; k++) {
		int x = k * 0xc8;
		glEnable(GL_TEXTURE_2D);
		int texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		const u32 *colour = hovered == k + 4 ? bright : dim;
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k + 4 ? 1.0f : 0.4f);
		profile_4283e0(X0 + x + 0x5a, Y1 - 0x40, X0 + x + 0xfa, Y1 - 0x20, 1);
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(X0 + x + 0x5a, Y1 - 0x38, X0 + x + 0xfa, (const char *)(0x7517a4 + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_CDECL(0x428a00, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* the confirmation over a room dialog (0x9dd850): the screen dimmed, a box with two lines (0x74dfa4, 0x74e024) and
   its two buttons (0x7517a4; the one under the pointer, by room_4321c0, in cyan) */
static void confirm_box(void)
{
	int hovered = room_4321c0(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f000000);   /* 0.1, 0.1, 0.1, 0.5 */
	menu_drawRect(0, 0, 0x280, 0x1e0, 1);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f4ccccd);   /* 0.1, 0.1, 0.1, 0.8 */
	menu_drawRect(0x64, 0xb4, 0x21c, 0x140, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(0x68, 0xb8, 0x218, 0x13c, 0);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_drawBox16(0x64, 0xc8, 0x21c, (const char *)0x74dfa4);
	text_drawBox16(0x64, 0xdc, 0x21c, (const char *)0x74e024);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int x = 0xb4 + k * 0xa0;
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k ? 1.0f : 0.4f);
		menu_drawTexQuad_4282f0(x, 0x104, x + 0x78, 0x124, 1);
		if (hovered == k)
			set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		else
			set_colour_bits((Colour *)0x76d438, 0x3e99999a, 0x3f333333, 0x3f333333, 0x3f800000);   /* 0.3, 0.7, 0.7, 1 */
		text_drawBox16(x, 0x10c, x + 0x78, (const char *)(0x7517a4 + k * 0x80));
	}
}

/* 0x439e00: the room's server dialog (0x9dd1a0 .. 0x9dd1ac; only its frame while a message box is open): the title
   0x758da4, a rule, the server name 0x9dd1d8 in a green-framed box, the note 0x758e24, two buttons (0x758f24, 0x80
   apart; the one under the pointer by room_432280 bright), the confirmation (0x9dd850) and the border. Returns the
   frame's or the border's eax */
u32 (room_439e00)(void)
{
#define X0 GAME_VAR(int, 0x9dd1a0)
#define Y0 GAME_VAR(int, 0x9dd1a4)
#define X1 GAME_VAR(int, 0x9dd1a8)
#define Y1 GAME_VAR(int, 0x9dd1ac)
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* menu_drawFrame */
	const u32 *bright = (const u32 *)0x9dcec0, *dim = (const u32 *)0x9dd338;
	int hovered = room_432280(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427b60(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)0x758da4);
	set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x20, Y0 + 0x20, X1 - 0x20, Y0 + 0x20);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f800000);   /* 0.1, 0.1, 0.1, 1 */
	menu_drawRect(X0 + 0x30, Y0 + 0x40, X1 - 0x30, Y0 + 0x60, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0, 0x3f800000);
	menu_drawRect(X0 + 0x30, Y0 + 0x40, X1 - 0x30, Y0 + 0x60, 0);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);
	text_drawBox16(X0 + 0x30, Y0 + 0x48, X1 - 0x30, (const char *)0x9dd1d8);
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_drawBox16(X0, Y0 + 0x8c, X1, (const char *)0x758e24);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k ? 1.0f : 0.4f);
		int x = X0 + k * 0xb4;
		menu_drawTexQuad_4282f0(x + 0x64, Y1 - 0x40, x + 0xdc, Y1 - 0x20, 1);
		const u32 *colour = hovered == k ? bright : dim;
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x64, Y1 - 0x38, x + 0xdc, (const char *)(0x758f24 + k * 0x80));
	}
	if (GAME_VAR(int, 0x9dd850))
		confirm_box();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_CDECL(0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x4392c0: the room login dialog (0x9dd358 .. 0x9dd364; only its frame while a message box is open): the title
   0x7583a4 and its rule, two labelled dark boxes (0x758424, 0x80 apart) with the name 0x9dd1d8 and the password
   0x9dd1f6 as stars (each left out while it is being typed in: 0x9dd830 / 0x9dd38c), three buttons (0x758524; the
   one under the pointer, 2 .. 4 by room_432200, bright unless connecting), while connecting (0x9dd838) a box with
   two lines (0x74f6a4, 0x74f724), the confirmation (0x9dd850) and the border. Returns the frame's or the border's
   eax */
u32 (room_4392c0)(void)
{
#define X0 GAME_VAR(int, 0x9dd358)
#define Y0 GAME_VAR(int, 0x9dd35c)
#define X1 GAME_VAR(int, 0x9dd360)
#define Y1 GAME_VAR(int, 0x9dd364)
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* menu_drawFrame */
	const u32 *bright = (const u32 *)0x9dcec0, *dim = (const u32 *)0x9dd338;
	int hovered = GAME_CDECL(0x432200, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* room_432200 */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x40, Y0 + 0x10, (const char *)0x7583a4);
	set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
	menu_drawLine(X0 + 0x40, Y0 + 0x24, X1 - 0x40, Y0 + 0x24);
	for (int k = 0; k < 2; k++) {
		int y = Y0 + k * 0x30;
		text_draw16(X0 + 0x40, y + 0x58, (const char *)(0x758424 + k * 0x80));
		set_colour_bits(g_rectColour, 0, 0, 0, 0x3f000000);
		menu_drawRect(X0 + 0xb8, y + 0x50, X0 + 0x1a8, y + 0x70, 1);
		set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
		menu_drawRect(X0 + 0xb8, y + 0x50, X0 + 0x1a8, y + 0x70, 0);
	}
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	if (!GAME_VAR(int, 0x9dd830))
		text_draw8(X0 + 0xc8, Y0 + 0x58, (const char *)0x9dd1d8);
	if (!GAME_VAR(int, 0x9dd38c)) {
		char hidden[30];
		stars(hidden, sizeof hidden, (const char *)0x9dd1f6);
		text_draw8(X0 + 0xc8, Y0 + 0x88, hidden);
	}
	for (int k = 0; k < 3; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 2 && !GAME_VAR(int, 0x9dd838);
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0xa0;
		menu_drawTexQuad_4282f0(x + 0x30, Y1 - 0x40, x + 0xa8, Y1 - 0x20, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x30, Y1 - 0x38, x + 0xa8, (const char *)(0x758524 + k * 0x80));
	}
	if (GAME_VAR(int, 0x9dd838)) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
		menu_drawRect(0x64, 0xc8, 0x21c, 0x140, 1);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x69, 0xdc, 0x217, (const char *)0x74f6a4);
		text_drawBox16(0x69, 0xf4, 0x217, (const char *)0x74f724);
	}
	if (GAME_VAR(int, 0x9dd850))
		confirm_box();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_CDECL(0x428a00, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* a rank's badge (rank 1 .. : cell rank - 1 of the 10-wide grid of the font texture 0x76d448, bound) 24 x 16 at
   (x, y) */
static void rank_badge(int rank, int x, int y)
{
	const float *col_w = (const float *)0x4a9590, *row_h = (const float *)0x4a958c;
	int cell = rank - 1;
	float u0 = f32(fmul_m((long double)(cell % 10), col_w));
	float v0 = f32(fadd_m(fmul_m((long double)(cell / 10), row_h), (const float *)0x4a9588));
	glBegin(GL_QUADS);
	glTexCoord2f(u0, v0);
	menu_vertex(x, y);
	float u1 = f32(fadd_m(u0, col_w));
	glTexCoord2f(u1, v0);
	menu_vertex(x + 0x18, y);
	float v1 = f32(fadd_m(v0, row_h));
	glTexCoord2f(u1, v1);
	menu_vertex(x + 0x18, y + 0x10);
	glTexCoord2f(u0, v1);
	menu_vertex(x, y + 0x10);
	glEnd();
}

/* 0x43a420: the pilot's account panel (0x9dd368 .. 0x9dd374); while waiting for the server (0x9dd6d4 = 1) only a
   box with two lines (0x75b1a4, 0x74f724). The title 0x7592a4, five labels for the fields (0x759324, 0x80 apart) and
   seven for the record (0x7595a4); four dark boxes with the name 0x9dd1d8, three passwords as stars (0x9dd6d8,
   0x9dd1f6, 0x9dd202; each left out while it is being typed in: 0x9dd69c / 0x9dd37c / 0x9dd378) and 0x9dd20e (left
   out while 0x9dd304); the level 0x9dd5d8 with its rank badge (cell (level - 1) % 10, / 10 of the texture 0x76d448),
   the clan 0x9dd248 (0x759924 when none), two ratios ("%.2f": 0x9dd5e4, 0x9dd5f4) and three counts (0x9dd5ec,
   0x9dd5f0, 0x9dd5dc); two buttons (0x7517a4; 4 / 5 under the pointer by room_4322c0, lit unless 0x68039c), a
   rule and the border. The original leaves eax to callers that ignore it */
void (room_43a420)(void)
{
#define X0 GAME_VAR(int, 0x9dd368)
#define Y0 GAME_VAR(int, 0x9dd36c)
#define X1 GAME_VAR(int, 0x9dd370)
#define Y1 GAME_VAR(int, 0x9dd374)
#define K(addr) ((const float *)(addr))
	const u32 *bright = (const u32 *)0x9dcec0, *dim = (const u32 *)0x9dd338;
	int hovered = GAME_CDECL(0x4322c0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* room_4322c0 */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	if (GAME_VAR(int, 0x9dd6d4) == 1) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
		menu_drawRect(0x50, 0xc8, 0x230, 0x118, 1);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x50, 0xdc, 0x230, (const char *)0x75b1a4);
		text_drawBox16(0x50, 0xf0, 0x230, (const char *)0x74f724);
		return;
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)0x7592a4);
	for (int k = 0; k < 5; k++)
		text_draw8(X0 + 0x20, Y0 + k * 0x1c + 0x34, (const char *)(0x759324 + k * 0x80));
	for (int k = 0; k < 7; k++)
		text_draw8(X0 + 0x20, Y0 + k * 0x18 + 0xbe, (const char *)(0x7595a4 + k * 0x80));
	text_draw8(X0 + 0x98, Y0 + 0x38, (const char *)0x9dd1d8);
	for (int k = 0; k < 4; k++) {
		int y = Y0 + k * 0x1c;
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f800000);   /* 0.1, 0.1, 0.1, 1 */
		menu_drawRect(X0 + 0x8e, y + 0x4e, X1 - 0x20, y + 0x64, 1);
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0, 0x3f800000);
		menu_drawRect(X0 + 0x8e, y + 0x4e, X1 - 0x20, y + 0x64, 0);
	}
	char text[20];
	static const struct { u32 typing, password; int y; } hidden[3] = {
		{ 0x9dd69c, 0x9dd6d8, 0x50 }, { 0x9dd37c, 0x9dd1f6, 0x6c }, { 0x9dd378, 0x9dd202, 0x88 },
	};
	for (int k = 0; k < 3; k++)
		if (!GAME_VAR(int, hidden[k].typing)) {
			stars(text, sizeof text, (const char *)hidden[k].password);
			text_draw8(X0 + 0x98, Y0 + hidden[k].y, text);
		}
	if (!GAME_VAR(int, 0x9dd304))
		text_draw8(X0 + 0x98, Y0 + 0xa4, (const char *)0x9dd20e);
	itoa(GAME_VAR(int, 0x9dd5d8), text, 10);
	text_draw8(X0 + 0x98, Y0 + 0xbe, text);
	/* the rank badge */
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x76d448);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	rank_badge(GAME_VAR(int, 0x9dd5d8), X0 + 0xc0, Y0 + 0xbe);
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
	menu_drawRect(X0 + 0xc1, Y0 + 0xbe, X0 + 0xd8, Y0 + 0xce, 0);
	/* the record */
	if (!GAME_VAR(int, 0x9dd248))
		text_draw8(X0 + 0x98, Y0 + 0xd6, (const char *)0x759924);
	else {
		itoa(GAME_VAR(int, 0x9dd248), text, 10);
		text_draw8(X0 + 0x98, Y0 + 0xd6, text);
	}
	sprintf(text, (const char *)0x4b0268, (double)GAME_VAR(float, 0x9dd5e4));
	text_draw8(X0 + 0x98, Y0 + 0xee, text);
	sprintf(text, (const char *)0x4b0268, (double)GAME_VAR(float, 0x9dd5f4));
	text_draw8(X0 + 0x98, Y0 + 0x106, text);
	static const u32 counts[3] = { 0x9dd5ec, 0x9dd5f0, 0x9dd5dc };
	for (int k = 0; k < 3; k++) {
		itoa(GAME_VAR(int, counts[k]), text, 10);
		text_draw8(X0 + 0x98, Y0 + 0x11e + k * 0x18, text);
	}
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 4 && !GAME_VAR(int, 0x68039c);
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0xa0;
		menu_drawTexQuad_4282f0(x + 0x7d, Y1 - 0x30, x + 0xf5, Y1 - 0x10, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x7d, Y1 - 0x28, x + 0xf5, (const char *)(0x7517a4 + k * 0x80));
	}
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y1 - 0x40, X1 - 0x10, Y1 - 0x40);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(X0, Y0, X1, Y1);
#undef K
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x43d060: the ranking table (0x9dced8 .. 0x9dcee4): the title 0x75aba4; the page arrows (0 / 1 under the pointer,
   by room_4323c0, lit) about "first ~ last" of page 0x9dd6ac (stored in 0x9dd83c / 0x9dd7dc); the sort button
   (0x75ac24; 2) with the sorted column's name; two rules and the column heads (0x75aca4 .., the sorted one in
   yellow); when there is a list (0x9dd3b0) up to ten 0x44-byte rows (the name at 0x9dcef4, its rank at -4) until an
   empty name (which stores the page in 0x9dd4b8): rank, name, rank badge (+0x32) in a yellow frame, "%8.1f" (+0x36),
   "%3.2f" (+0x2e) and three counts (+0x26, +0x2a, +0x1e), the sorted value in yellow; a rule, two buttons
   (0x75b0a4; 3 / 4, the first dead until the list is loaded, 0x9dd6b8); while loading the blinking 0x75b1a4; the
   border. Returns the border's eax */
u32 (room_43d060)(void)
{
#define X0 GAME_VAR(int, 0x9dced8)
#define Y0 GAME_VAR(int, 0x9dcedc)
#define X1 GAME_VAR(int, 0x9dcee0)
#define Y1 GAME_VAR(int, 0x9dcee4)
#define g_sort GAME_VAR(int, 0x9dd1d0)
#define TEXT(c) set_colour_bits((Colour *)0x76d438, (c)[0], (c)[1], (c)[2], (c)[3])
	const u32 *bright = (const u32 *)0x9dcec0, *dim = (const u32 *)0x9dd338;
	static const u32 white[4] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
	static const u32 yellow[4] = { 0x3f800000, 0x3f800000, 0, 0x3f800000 };
	int hovered = GAME_CDECL(0x4323c0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* room_4323c0 */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	TEXT(bright);
	text_draw16(X0 + 0x10, Y0 + 0x10, (const char *)0x75aba4);
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexQuad_4284d0(X0 + 0xb0, Y0 + 0x26, X0 + 0xe4, Y0 + 0x3e, hovered == 0);
	menu_drawTexQuad_4285c0(X0 + 0x146, Y0 + 0x26, X0 + 0x17a, Y0 + 0x3e, hovered != 0 && hovered == 1);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	char page[64], last[64];
	int first = GAME_VAR(int, 0x9dd6ac) * 10 + 1;
	GAME_VAR(int, 0x9dd83c) = first;
	GAME_VAR(int, 0x9dd7dc) = (GAME_VAR(int, 0x9dd6ac) * 5 + 5) * 2;
	itoa(first, page, 10);
	itoa(GAME_VAR(int, 0x9dd7dc), last, 10);
	strcat(page, (const char *)0x4b278c);   /* " ~ " */
	strcat(page, last);
	menu_drawTexQuad_4282f0(X0 + 0xe6, Y0 + 0x24, X0 + 0x146, Y0 + 0x40, 1);
	text_draw8b(X0 + 0xe6, Y0 + 0x2a, X0 + 0x146, page);
	text_drawBox16(X1 - 0x78, Y0 + 0x10, X1 - 0x14, (const char *)0x75ac24);
	glEnable(GL_TEXTURE_2D);
	texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, hovered == 2 ? 1.0f : 0.6f);
	menu_drawTexQuad_4282f0(X1 - 0x78, Y0 + 0x24, X1 - 0x14, Y0 + 0x40, 1);
	TEXT(yellow);
	static const u32 sorted_by[4] = { 0x75ae24, 0x75af24, 0x75b024, 0x75aea4 };
	if ((unsigned)g_sort <= 3)
		text_draw8b(X1 - 0x78, Y0 + 0x2a, X1 - 0x14, (const char *)sorted_by[g_sort]);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x4a, X1 - 0x10, Y0 + 0x4a);
	menu_drawLine(X0 + 0x10, Y0 + 0x6e, X1 - 0x10, Y0 + 0x6e);
	/* the column heads, the numbers' right-aligned (8 a character) */
	TEXT(bright);
	text_draw8(X0 + 0x18, Y0 + 0x52, (const char *)0x75aca4);
	text_draw8(X0 + 0x48, Y0 + 0x52, (const char *)0x75ad24);
	text_draw8(X0 - (int)strlen((const char *)0x75ada4) * 8 + 0xec, Y0 + 0x52, (const char *)0x75ada4);
	static const struct { u32 text; int right, sort; } heads[5] = {
		{ 0x75ae24, 0x12c, 0 }, { 0x75aea4, 0x2d * 8, 3 }, { 0x75af24, 0x35 * 8, 1 }, { 0x75afa4, 0x3c * 8, -1 },
		{ 0x75b024, 0x226, 2 },
	};
	for (int c = 0; c < 5; c++) {
		int x = heads[c].right - (int)strlen((const char *)heads[c].text) * 8;
		if (heads[c].sort >= 0 && g_sort == heads[c].sort)
			TEXT(yellow);
		else
			TEXT(bright);
		text_draw8(X0 + x + 0x18, Y0 + 0x52, (const char *)heads[c].text);
	}
	TEXT(white);
	if (GAME_VAR(int, 0x9dd3b0)) {
		char text[64];
		for (int i = 0; i < 10; i++) {
			const u8 *row = (const u8 *)0x9dcef4 + i * 0x44;
#define ROW(type, offset) (*(const type *)(row + (offset)))
			if (!*row) {
				GAME_VAR(int, 0x9dd4b8) = GAME_VAR(int, 0x9dd6ac);
				break;
			}
			int y = Y0 + i * 0x16 + 0x78;
			TEXT(white);
			itoa(ROW(int, -4), text, 10);
			text_draw8(X0 + 0x18, y, text);
			text_draw8(X0 + 0x48, y, (const char *)row);
			glEnable(GL_TEXTURE_2D);
			texture = GAME_VAR(int, 0x76d448);
			tex_bind(g_textures->managers[texture / 512], texture % 512);
			rank_badge(ROW(int, 0x32), X0 + 0xd2, y);
			glDisable(GL_TEXTURE_2D);
			set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
			menu_drawRect(X0 + 0xd3, y + 1, X0 + 0xea, y + 0x10, 0);
			TEXT(white);
			if (g_sort == 0)
				TEXT(yellow);
			sprintf(text, (const char *)0x4b2784, (double)ROW(float, 0x36));   /* "%8.1f" */
			text_draw8(X0 - (int)strlen(text) * 8 + 0x144, y, text);
			TEXT(white);
			if (g_sort == 3)
				TEXT(yellow);
			sprintf(text, (const char *)0x4b277c, (double)ROW(float, 0x2e));   /* "%3.2f" */
			text_draw8(X0 + (0x30 - (int)strlen(text)) * 8, y, text);
			TEXT(white);
			if (g_sort == 1)
				TEXT(yellow);
			itoa(ROW(int, 0x26), text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x1bc, y, text);
			TEXT(white);
			itoa(ROW(int, 0x2a), text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x1f4, y, text);
			TEXT(white);
			if (g_sort == 2)
				TEXT(yellow);
			itoa(ROW(int, 0x1e), text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x23e, y, text);
#undef ROW
		}
	}
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y1 - 0x40, X1 - 0x10, Y1 - 0x40);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 3 && !(hovered == 3 && !GAME_VAR(int, 0x9dd6b8));
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0xc8;
		menu_drawTexQuad_4282f0(x + 0x7d, Y1 - 0x30, x + 0x11d, Y1 - 0x10, 1);
		if (lit)
			TEXT(bright);
		else
			TEXT(dim);
		text_drawBox16(x + 0x7d, Y1 - 0x28, x + 0x11d, (const char *)(0x75b0a4 + k * 0x80));
	}
	if (GAME_VAR(int, 0x9dd6b8)) {   /* loading: blinking in ten steps */
		int step = ftol(fmul_m(fld_m((const float *)0x4dba80), (const float *)0x4a9438)) % 10;
		float alpha = f32(fsubr_m(fmul_m((long double)step, (const float *)0x4a93ec), (const float *)0x4a9424));
		set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0, BITS(alpha));
		text_drawBox16(X0, Y0 + 0xc8, X1, (const char *)0x75b1a4);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_CDECL(0x428a00, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef TEXT
#undef g_sort
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* the create-game dialog closed, back to the room's page 99 (keys blocked, the room's state 300) */
static void creategame_close(void)
{
	set_680370_441250(4);
	GAME_VAR(int, 0x9dd834) = 99;
	GAME_VAR(int, 0x67ef20) = 300;
	GAME_CDECL(0x48b420, void, void)();   /* nullsub_48b420 */
}

/* 0x436990: the create-game dialog's keys. While its request is out (0x9dd838) or the login is due (0x9dd1c8)
   only cancel2 answers, closing the dialog (the answer dropped) and the lobby connection. Otherwise a click on its
   buttons (room_432200: 2 send, 3 close and disconnect, 4 room_4338c0), 0x4e14f4 send, back close, 0x4e150c
   room_4338c0 (none of these while typing, g_paused); the toggle key moves the highlight (g_dialogChoice) on: from
   the name (1) to the password field (2), to the OK button (3), then into the name field for typing; with shift,
   back: from OK (3) to the password field, to the name, then into the password field for typing. The original
   leaves eax to callers that ignore it */
void (menu_436990)(void)
{
#define g_editKey GAME_VAR(int, 0x9dc428)
	int dialogX = GAME_VAR(int, 0x9dd358), dialogBottom = GAME_VAR(int, 0x9dd364) - 0x30;
	if (GAME_VAR(int, 0x9dd838) || GAME_VAR(int, 0x9dd1c8)) {
		if (input_justPressed(g_keyCancel2)) {
			GAME_VAR(int, 0x9dd838) = 0;
			GAME_VAR(int, 0xa0b378) = 0;
			GAME_VAR(int, 0x9dd1c8) = 0;
			g_chatFieldFlag = 0;
			g_paused = 0;
			creategame_close();
			g_highlightShown = 0;
			net_disconnect();
		}
		return;
	}
	if (input_justPressed(g_keyClick) == 1) {
		int on = room_432200(g_mouseX, g_mouseY);
		if (on == 2) {
			if (GAME_VAR(int, 0x9dd1c8))
				return;
			sound_playMenu(0);
			g_highlightShown = 0;
			GAME_VAR(int, 0x9dd198) = 1;
			GAME_VAR(int, 0x9dd1c8) = 1;
			return;
		}
		if (on == 3) {
			sound_playMenu(0);
			g_paused = 0;
			creategame_close();
			g_chatFieldFlag = 0;
			g_highlightShown = 0;
			net_disconnect();
			return;
		}
		if (on == 4) {
			g_paused = 0;
			g_highlightShown = 0;
			sound_playMenu(0);
			room_4338c0();
			return;
		}
	}
	if (input_justPressed(GAME_VAR(int, 0x4e14f4)) == 1) {
		if (g_paused || GAME_VAR(int, 0x9dd1c8))
			return;
		sound_playMenu(0);
		GAME_VAR(int, 0x9dd198) = 1;
		GAME_VAR(int, 0x9dd1c8) = 1;
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		if (g_paused)
			return;
		g_chatFieldFlag = 0;
		sound_playMenu(0);
		creategame_close();
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e150c)) == 1) {
		if (g_paused)
			return;
		sound_playMenu(0);
		room_4338c0();
		return;
	}
	if (input_justPressed(g_keyToggle) != 1)
		return;
	g_editKey = 20;
	int choice = g_dialogChoice;
	if (input_isDown(g_keyLeftShift) == 1 || input_isDown(g_keyRightShift) == 1) {
		g_editKey = 10;
		if (choice == 1) {
			highlight_choice(0, dialogX + 0x180, GAME_VAR(int, 0x9dd35c) + 0x88);
			room_433bb0();
			GAME_VAR(int, 0x9dd6b0) = 1;
			g_chatFieldFlag = 1;
		} else if (choice == 2)
			highlight_choice(1, dialogX + 0x62, dialogBottom);
		else if (choice == 3)
			highlight_choice(2, dialogX + 0x102, dialogBottom);
		else
			return;
	} else {
		if (choice == 1)
			highlight_choice(2, dialogX + 0x102, dialogBottom);
		else if (choice == 2)
			highlight_choice(3, dialogX + 0x1a2, dialogBottom);
		else if (choice == 3) {
			highlight_choice(3, dialogX + 0x180, GAME_VAR(int, 0x9dd35c) + 0x88);
			room_433b00();
			g_editKey = 0;
			GAME_VAR(int, 0x9dd1cc) = 1;
			return;
		} else
			return;
	}
	g_editKey = 0;
#undef g_editKey
}

/* room_clicks.c: the game room's small handlers: clicks on its popups' buttons, starting the chat line, and the
   white fade over the screen. Buttons are hit-tested with the pointer (leaveDialog_hitTest and its kind: the index of the
   button under it, or -1). */
#include "../game.h"
#include <string.h>

#define g_roomPopup GAME_VAR(int, 0x9dd6c4)           /* (by use) the room's popup: 1 / 2 closed by its buttons */
#define g_leaveDialog GAME_VAR(int, 0x9dd850)         /* the "leave" dialog is up */
#define g_roomChatting GAME_VAR(int, 0x9dd6b4)        /* the chat line is being typed */
#define g_roomFade GAME_VAR(float, 0x4deb74)          /* the white fade, rising to 1 */

/* 0x435ab0: the "leave" dialog: yes (button 0) closes it and leaves (the game closes with exit code 2), no (button 1) only closes it */
void (leaveDialog_clicks)(void)
{
	if (g_dialogOpen != 0 || g_mouseClick == 0)
		return;
	switch (leaveDialog_hitTest(g_mouseX, g_mouseY)) {
	case 0:
		g_leaveDialog = 0;
		app_closeWindow(2);
		break;
	case 1:
		g_leaveDialog = 0;
		break;
	}
}

/* 0x435ce0: the popup's two buttons (popup_hitTest) close it with 1 or 2 */
void (popup_clicks)(void)
{
	if (g_mouseClick == 0)
		return;
	switch (popup_hitTest(g_mouseX, g_mouseY)) {
	case 0:
		sound_playMenu(0);
		g_roomPopup = 1;
		break;
	case 1:
		sound_playMenu(0);
		g_roomPopup = 2;
		break;
	}
}

/* 0x434da0: start the chat line, if the local player may type (a flag in the player's 0x4a-byte record) */
void (room_startChat)(void)
{
	g_roomChatting = 0;
	if (GAME_VAR(u8, 0x908807 + g_localPlayer * 0x4a) != 0) {
		g_roomChatting = 1;
		field_editMessage();
	}
}

/* 0x435f40: in room state 2, the button (gameListStop_hitTest) that stops the arena being set up: its flags off, the
   arena's connection closed (arena_leaveSession) and its timer (0x378) killed */
void (room_stopArenaSetup)(void)
{
	if (g_dialogOpen != 0 || g_mouseClick == 0 || g_roomMode != 2)
		return;
	g_cursorBlink = 0.0f;
	if (gameListStop_hitTest(g_mouseX, g_mouseY) == 0) {
		sound_playMenu(0);
		GAME_VAR(int, 0x4dbb10) = 0;
		g_arenaJoinWaiting = 0;
		arena_leaveSession();
		GAME_VAR(int, 0x4db8b4) = 0;
		KillTimer(g_hWndMain, 0x378);
	}
}

/* 0x43df00: the white fade over the whole screen, 0.015 per time unit (the stored value goes on past 1; the
   colour stops at 1) */
void (room_drawWhiteFade)(void)
{
	long double a = (long double)g_frameTime * 0.015f + g_roomFade;
	g_roomFade = f32(a);
	float alpha = f32(a);
	if (a > 1.0f)
		alpha = 1.0f;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	Color4_set(g_rectColour, 1.0f, 1.0f, 1.0f, alpha);
	menu_drawRect(0, 0, g_screenW, g_screenH, 1);
}

/* 0x405200 (arena_chatLine): the arena screen's chat line, the same way (flag 0x4db8bc, its message field) */
void (arena_chatLine)(void)
{
	GAME_VAR(int, 0x4db8bc) = 0;
	if (GAME_VAR(u8, 0x908807 + g_localPlayer * 0x4a) != 0) {
		GAME_VAR(int, 0x4db8bc) = 1;
		arena_editTextField_405010();
	}
}

/* 0x436940, 0x407970 (lobbyJoin_keys): the leave question's keys in the room and in the lobby: back closes it, O
   leaves (the game closes with exit code 2) */
static void leave_keys(int *question)
{
	if (input_justPressed(g_keyBack)) {
		*question = 0;
	} else if (input_justPressed(g_keyOk)) {
		*question = 0;
		app_closeWindow(2);
	}
}

void (menu_436940)(void) { leave_keys(&g_leaveDialog); }
void (lobbyJoin_keys)(void) { leave_keys(&GAME_VAR(int, 0x907b2c)); }

/* 0x443e20: the skirmish settings screen's clicks (no dialog open, 0x90d1c4): a right click leaves (0x443c80); a left
   click on its buttons (skirmishSettings_hitTest): rows 0..7 change that setting (0x443d50), 8 saves (0x443af0 with the
   selection 0x9f16a4), 9 leaves. Returns the last call's eax */
int (skirmish_saveSettings)(void)
{
	int r = GAME_VAR(int, 0x90d1c4);
	if (r)
		return r;
	if (g_keyEnter)
		GAME_CDECL(0x443c80, int, void)();
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	int row = GAME_CDECL(0x4438d0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* skirmishSettings_hitTest */
	if ((u32)row <= 7)
		return GAME_CDECL(0x443d50, int, int)(row);
	if (row == 8)
		return GAME_CDECL(0x443af0, int, int)(GAME_VAR(int, 0x9f16a4));
	if (row == 9)
		return GAME_CDECL(0x443c80, int, void)();
	return row;
}

/* ---- a menu key: the key bound at `binding` was just pressed (the confirm sound played then) ---- */
static int key_hit(u32 binding)
{
	if (!input_justPressed(GAME_VAR(int, binding)))
		return 0;
	sound_playMenu(0);
	return 1;
}

/* 0x437140: the game room's keys: back or leave leaves the game; the others open the room's pages (0x4334c0,
   0x433590, 0x433790, 0x433800) or the arm center (0x4dc24c = 3, menu_enterMenus). Returns the action's eax */
u32 (room_keys)(void)
{
	if (key_hit(0x76d48c))
		return GAME_CDECL(0x435a40, u32, void)();   /* room_leaveGame */
	if (key_hit(0x4e1514))
		return GAME_CDECL(0x4334c0, u32, void)();   /* room_requestJoin */
	if (key_hit(0x4e14f8))
		return GAME_CDECL(0x433590, u32, void)();   /* room_start */
	if (key_hit(0x4e0cdc))
		return GAME_CDECL(0x433790, u32, void)();   /* room_enterGameList */
	if (key_hit(0x4e151c))
		return GAME_CDECL(0x433800, u32, void)();   /* room_enterRoomList */
	if (key_hit(0x4e0cd4)) {
		GAME_VAR(int, 0x4dc24c) = 3;
		return GAME_CDECL(0x40ee20, u32, void)();   /* menu_enterMenus */
	}
	if (key_hit(0x4e153c))
		return GAME_CDECL(0x435a40, u32, void)();
	return 0;
}

/* 0x435b00: the game room's left clicks (nothing open: 0x9dd1c8, 0x9dd838; no right click) on its buttons
   (0x432200): 0 / 1 open the room's two lists (0x433b00, 0x433bb0), 2 opens the chat line, 3 leaves for the main
   menu (the keyboard taken back if it was let go, the connection closed), 4 0x4338c0. Returns the action's eax */
u32 (room_leftClicks)(void)
{
	u32 open = GAME_VAR(u32, 0x9dd1c8);
	if (open)
		return open;
	if ((open = GAME_VAR(u32, 0x9dd838)))
		return open;
	if ((open = GAME_VAR(u32, 0x4ded8c)))
		return open;
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	u32 button = GAME_CDECL(0x432200, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	u32 r;
	switch (button) {
	case 0:
		GAME_CDECL(0x433c70, void, void)();          /* chat_closeEdit */
		r = GAME_CDECL(0x433b00, u32, void)();       /* field_editGameName */
		g_typingRoomName = 1;
		return r;
	case 1:
		GAME_CDECL(0x433c70, void, void)();
		r = GAME_CDECL(0x433bb0, u32, void)();       /* field_editGamePassword */
		g_typingRoomPassword = 1;
		return r;
	case 2:
		if ((open = GAME_VAR(u32, 0x9dd1c8)))
			return open;
		sound_playMenu(0);
		GAME_VAR(int, 0x9dd198) = 1;
		g_roomLoginDue = 1;
		GAME_VAR(int, 0x9dd850) = 0;
		return 1;
	case 3:
		if (GAME_VAR(int, 0x68039c)) {
			GAME_VAR(int, 0x68039c) = 0;
			GAME_CDECL(0x431590, void, void)();      /* input_resetKeys */
			GAME_CDECL(0x401310, void, void *)(GAME_VAR(void *, 0x4ded18));   /* input_initKeyboard */
		}
		sound_playMenu(0);
		set_680370_441250(4);
		GAME_VAR(int, 0x9dd834) = 0x63;
		g_nextScreen = 300;
		GAME_VAR(int, 0x4e1868) = 0;
		GAME_CDECL(0x48b420, void, void)();          /* nullsub_48b420 */
		return GAME_CDECL(0x451e60, u32, void)();    /* net_disconnect */
	case 4:
		sound_playMenu(0);
		return GAME_CDECL(0x4338c0, u32, void)();    /* room_openDialog4d */
	}
	return button;
}

/* 0x435d30: the game room's page clicks (page open, 0x9dce48 not 0 or 1; no dialog): its six buttons (outlines at
   0x9daf88) open the room's pages, the arm center (0x4dc24c = 3) or leave the game; a right click (when 0x9dae10
   allows) leaves too. Returns what the original leaves in eax */
u32 (room_pageClicks)(void)
{
	static const u32 actions[6] = { 0x4334c0, 0x433590, 0x433790, 0, 0x433800, 0x435a40 };
	u32 page = GAME_VAR(u32, 0x9dce48);
	if (page == 1 || page == 0)
		return page;
	if (g_dialogOpen)
		return g_dialogOpen;
	if (GAME_VAR(int, 0x4ded88)) {
		const Outline *buttons = (const Outline *)0x9daf88;
		for (int i = 0; i < 6; i++) {
			if (point_in_outline(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c), buttons[i]) != 1)
				continue;
			sound_playMenu(0);
			if (i == 3) {   /* the arm center */
				GAME_VAR(int, 0x4dc24c) = 3;
				GAME_CDECL(0x40ee20, void, void)();   /* menu_enterMenus */
				g_enteringMenus = 0;
			} else
				GAME_CDECL(actions[i], void, void)();
			break;
		}
	}
	int right = g_keyEnter;
	if (!right)
		return 0;
	int allowed = GAME_VAR(int, 0x9dae10);
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	return GAME_CDECL(0x435a40, u32, void)();   /* room_leaveGame */
}

/* ---- the selected map's preview (map `selected`, a signed byte; its name 32 bytes a slot at 0x907b30) loaded as a
   texture: "<0x680bc4><name>/<name>" (the texture manager 0xa0e010) into 0x9da324; 0x680cd0 cleared ---- */
static void load_map_preview(u32 selected)
{
	char path[0x80], copy[0x40];
	const char *name = (const char *)(0x907b30 + (signed char)GAME_VAR(u8, selected) * 32);
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)0x680bc4);   /* the maps' folder */
	strcat(path, name);
	strcat(path, (const char *)0x4ad564);   /* "/" */
	strcat(path, name);
	strcpy(copy, path);
	GAME_VAR(int, 0x9da324) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), copy, 0, 0, 0, 0, 0, 0, 0);
	GAME_VAR(int, 0x680cd0) = 0;
}
/* 0x43bcb0: the game room's (selection 0x4df9e8); 0x40b420: the arena screen's (0x4db548) */
void (room_loadMapPreview)(void) { load_map_preview(0x4df9e8); }
void (arena_40b420)(void) { load_map_preview(0x4db548); }

/* 0x433d30: the typed line (0x9dc92c) committed to the room field being edited (when the keyboard was let go for it,
   0x68039c: the edit window 0x9dd888 destroyed and the focus back on the main window first): the room name
   (0x9dd1d8, 30 bytes), two short fields (0x9dd1f6, 0x9dd202, 12 bytes) or the comment (0x9dd20e, 50 bytes).
   Returns what the original leaves in eax */
/* typing closed if it was on: the hidden EDIT control destroyed, the focus back to the game window and the line
   closed (chat_closeLine); returns that call's eax, or 0 */
static u32 typing_end(void)
{
	if (!GAME_VAR(int, 0x68039c))
		return 0;
	IMPORT(0x4a9344, int, void *)(GAME_VAR(void *, 0x9dd888));   /* DestroyWindow */
	IMPORT(0x4a935c, void *, void *)(GAME_VAR(void *, 0x4ded18));   /* SetFocus */
	return GAME_CDECL(0x431600, u32, int)(1);   /* chat_closeLine */
}

u32 (room_433d30)(void)
{
	static const struct { u32 editing, field, size; } fields[4] = {
		{ 0x9dd348, 0x9dd1d8, 30 }, { 0x9dd3f8, 0x9dd1f6, 12 }, { 0x9dd564, 0x9dd202, 12 }, { 0x9dd6cc, 0x9dd20e, 50 } };
	u32 r = typing_end();
	const char *typed = (const char *)0x9dc92c;
	for (int k = 0; k < 4; k++) {
		if (GAME_VAR(int, fields[k].editing) != 1)
			continue;
		memset((void *)fields[k].field, 0, fields[k].size);
		strcpy((char *)fields[k].field, typed);
		return k == 3 ? strlen(typed) + 1 : 0;
	}
	return r;
}

/* 0x4355b0: the game room's hosting step (0x4ded60): 1 hosts the room's session (the music stopped, 0x452ec0, then
   dplay_host with the room's settings record 0x5b1b30 and name 0x9dd570) and takes its settings (the 32-byte
   rules, +0x20 .. +0x25); then 0 or 3 (3 also sets 0x907b2c) move on to 2, and 4 does too with message 0x2a.
   Returns the step (or the message's eax) */
u32 (room_hostingStep)(void)
{
	const u8 *room = (const u8 *)0x5b1b30;
	u32 step = GAME_VAR(u32, 0x4ded60);
	if (step == 2)
		return 2;
	if (step == 1) {
		GAME_VAR(int, 0x4dba88) = 0;
		GAME_VAR(int, 0x67ef14) = 1;
		GAME_VAR(int, 0x67ef04) = 1;
		music_shutdown();
		g_roomMode = 0;
		GAME_CDECL(0x452ec0, int, int, int)(0, 0);   /* arena_openSession */
		GAME_CDECL(0x453090, int, const void *, const char *, int, int, int, int, int, int)(
			room, (const char *)0x9dd570, (signed char)room[0x23], (signed char)room[0x21], (signed char)room[0x23],
			room[0x24], room[0x25], 0);   /* dplay_host: host */
		GAME_VAR(int, 0x9dad94) = (signed char)room[0x20];
		g_chosenGameMode = (signed char)room[0x23];
		memcpy((void *)0x67fb44, room, 32);
		g_mapRotation = (signed char)room[0x22];
		g_fragLimit = room[0x24];
		g_timeLimit = room[0x25];
		step = GAME_VAR(u32, 0x4ded60);
		GAME_VAR(int, 0x4ded54) = 1;
	}
	switch (step) {
	case 3:
		GAME_VAR(int, 0x907b2c) = 1;
		/* fall through */
	case 0:
		GAME_VAR(int, 0x4dba88) = 0;
		GAME_VAR(int, 0x4ded54) = 0;
		g_connectStep = 2;
		return step;
	case 4:
		GAME_VAR(int, 0x4dba88) = 0;
		g_connectStep = 2;
		GAME_VAR(int, 0x4ded54) = 0;
		return GAME_CDECL(0x41ee40, u32, int)(0x2a);   /* the message */
	}
	return step;
}

/* 0x434e70: the window closed while connecting. An arena wait (0x4dbb78): it ends, the arena is left and message
   0x44. Joining a listed game (0x4db708; the record 0x4a bytes a slot at 0x9087c0, row 0x4db710): the record's
   session from 0x4dbbf8 and its colour bytes (0x5b1b54/55) for the join. Joined (0x1f4): the music stopped and the
   player's settings taken from the record for the game; otherwise a message by the result and the arena left.
   Returns what the original leaves in eax */
u32 (app_onClose)(void)
{
	if (g_arenaJoinWaiting) {
		GAME_VAR(int, 0x4dbb10) = 0;
		g_arenaJoinWaiting = 0;
		GAME_CDECL(0x452fe0, void, void)();   /* arena_leaveSession */
		u32 r = GAME_CDECL(0x41ee40, u32, int)(0x44);   /* the message */
		GAME_VAR(int, 0x4db8b4) = 0;
		return r;
	}
	if (!GAME_VAR(int, 0x4db708))
		return 0;
	u32 row = GAME_VAR(u32, 0x4db710) * 0x4a;
	u8 *game = (u8 *)0x9087c0 + row;
	*(u32 *)game = *GAME_VAR(u32 *, 0x4dbbf8);
	GAME_VAR(u8, 0x5b1b54) = game[0x2d];
	GAME_VAR(u8, 0x5b1b55) = game[0x2e];
	int r = GAME_CDECL(0x453180, int, int, int, void *, int)(0, *(int *)game, (void *)0x9dd570, 0);   /* dplay_join */
	if (r != 0x1f4) {
		static const u8 message[5] = { 0x43, 0x42, 0x42, 0x44, 0x45 };
		if ((u32)(r - 0x1f5) <= 4)
			GAME_CDECL(0x41ee40, void, int)(message[r - 0x1f5]);
		u32 e = GAME_CDECL(0x452fe0, u32, void)();
		GAME_VAR(int, 0x4dbb10) = 0;
		GAME_VAR(int, 0x4db708) = 0;
		GAME_VAR(int, 0x4db8b4) = 0;
		return e;
	}
	GAME_CDECL(0x457310, void, void)();   /* music_shutdown */
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 2;
	g_roomMode = 0;
	GAME_VAR(int, 0x4dbb10) = 0;
	GAME_VAR(int, 0x4db708) = 0;
	GAME_VAR(int, 0x4db8b4) = 0;
	GAME_VAR(int, 0x9dad94) = (signed char)game[0x25];
	memcpy((void *)0x67fb44, game + 4, 32);
	g_mapRotation = (signed char)game[0x24];
	g_chosenGameMode = (signed char)game[0x2c];
	g_fragLimit = game[0x2d];
	g_timeLimit = game[0x2e];
	return row;
}

/* 0x4346c0: the account form checked (name 0x9dd1d8, password 0x9dd1f6 and its repeat 0x9dd202, e-mail 0x9dd20e):
   a blank name, a bad name or password character, a missing or mismatched password and a bad e-mail each give
   their message and reopen the field; all good, the next dialog (0x433980). Returns that call's eax */
u32 (account_checkForm)(void)
{
	GAME_CDECL(0x433d30, void, void)();   /* room_433d30 */
	GAME_VAR(int, 0x68039c) = 0;
	GAME_VAR(int, 0x9dc428) = 0;
	const char *name = (const char *)0x9dd1d8, *password = (const char *)0x9dd1f6;
	int message, reopen;
	if (strlen(name) == 0 || GAME_CDECL(0x4343b0, int, const char *)(name) == 1)   /* name_isBlank: blank */
		message = 0x24, reopen = 0x9dd348;
	else if (GAME_CDECL(0x434400, int, const char *)(name) == 1)                  /* room_nameHasBadChar: a bad character */
		message = 0x15a, reopen = 0x9dd348;
	else if (strlen(password) == 0)
		message = 0x25, reopen = 0x9dd3f8;
	else if (strcmp(password, (const char *)0x9dd202))
		message = 0x21, reopen = 0x9dd3f8;
	else if (GAME_CDECL(0x434400, int, const char *)(password) == 1)
		message = 0x15b, reopen = 0x9dd3f8;
	else if (GAME_CDECL(0x434400, int, const char *)((const char *)0x9dd20e) == 1)
		message = 0x81, reopen = 0x9dd6cc;
	else
		return GAME_CDECL(0x433980, u32, void)();   /* the next dialog */
	u32 r = GAME_CDECL(0x41ee40, u32, int)(message);
	GAME_VAR(int, reopen) = 1;
	return r;
}

/* 0x434b90: the account change sent: the old password (0x9dd6d8) right and the new one repeated, every field free
   of bad characters (else message 0x81 and 0x9dd1c8 cleared), the name, password and e-mail go out in message 0x1c.
   1 when sent */
int (account_sendChange)(void)
{
	if (strcmp((const char *)0x9dd58e, (const char *)0x9dd6d8) || strcmp((const char *)0x9dd1f6, (const char *)0x9dd202))
		return 0;
	static const u32 fields[4] = { 0x9dd6d8, 0x9dd1f6, 0x9dd202, 0x9dd20e };
	for (int i = 0; i < 4; i++)
		if (GAME_CDECL(0x434400, int, const char *)((const char *)fields[i]) == 1) {   /* room_nameHasBadChar */
			GAME_CDECL(0x41ee40, void, int)(0x81);
			g_roomLoginDue = 0;
			return 0;
		}
	char *out = GAME_VAR(char *, 0xa0b344);
	strcpy(out, (const char *)0x9dd1d8);
	strcpy(out + 0x1e, (const char *)0x9dd1f6);
	strcpy(out + 0x2a, (const char *)0x9dd20e);
	GAME_CDECL(0x4521c0, int, int, int)(0x1c, 0x65);   /* net_send */
	return 1;
}

/* a no-argument cdecl game function called with ebp saved around it: ranking_drawTable overruns a local buffer into its
   saved caller ebp at some stack alignments (see run_lifted in recomp.c); the original's caller never used ebp
   after it, compiled code may */
static u32 call_keeping_ebp(u32 address)
{
	u32 r;
	__asm__ volatile("pushl %%ebp\n\tcall *%1\n\tpopl %%ebp" : "=a"(r) : "r"(address) : "ecx", "edx", "memory");
	return r;
}

/* 0x43ede0: the ranking page. A request pending (0x9dd350) for sort column 0x9dd1d0: columns 0 .. 2 send their
   code (0x25 / 0x23 / 0x26) with the first rank of page 0x9dd6ac (ranks 0x9dd83c .. 0x9dd7dc) in message 0x15 and
   start waiting (0x9dd6b8, the blink at 1000); column 3 just clears the request. Then the room's tunnel; in room
   modes other than 0 / 1 (0x9dce48) and outside page 99: with a message box open (0x90d1c4) only it is drawn (a
   request made again once it closes), else while waiting an answer (0x76d40c) fills the list (roomList_fillPage) and
   keeps the column and page, the blink counts down by 0x4b071c * 0x4ad498 (from 1000 again below 0), and the
   table is drawn (ranking_drawTable). Returns what the original leaves in eax */
u32 (ranking_page)(void)
{
	if (g_rankingRequestPending) {
		u32 column = GAME_VAR(u32, 0x9dd1d0);
		static const int code[3] = { 0x25, 0x23, 0x26 };
		if (column == 3) {
			g_rankingRequestPending = 0;
			return 3;
		}
		int *out = GAME_VAR(int *, 0xa0b324);
		if (column < 3)
			out[0] = code[column];
		int page = g_roomListPage;
		GAME_VAR(int, 0x9dd83c) = page * 10 + 1;
		GAME_VAR(int, 0x9dd7dc) = page * 10 + 10;
		out[1] = page * 10 + 1;
		GAME_CDECL(0x4521c0, int, int, int)(0x15, 0x65);   /* net_send */
		g_rankingRequestPending = 0;
		g_lobbyBlinkClock = 1000.0f;
		GAME_VAR(int, 0x9dd6b8) = 1;
	}
	GAME_CDECL(0x4388e0, void, void)();   /* room_4388e0: the tunnel */
	int mode = g_roomMode;
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x9dd834) == 99)
		return mode;
	if (GAME_VAR(int, 0x90d1c4)) {
		const int *box = (const int *)0x9dced8;
		GAME_CDECL(0x428c30, void, int, int, int, int)(box[0], box[1], box[2], box[3]);   /* the message box */
		if (GAME_VAR(int, 0x90d1c4))
			return GAME_VAR(u32, 0x90d1c4);
		g_rankingRequestPending = 1;
		return 0;
	}
	if (GAME_VAR(int, 0x9dd6b8)) {
		if (g_roomListWaiting) {
			GAME_CDECL(0x435770, void, void)();   /* roomList_fillPage: the list filled */
			GAME_VAR(int, 0x9dd6b8) = 0;
			g_rankingHaveList = 1;
			g_roomListWaiting = 0;
			GAME_VAR(int, 0x9dd300) = GAME_VAR(int, 0x9dd1d0);
			GAME_VAR(int, 0x9dd1b4) = g_roomListPage;
		}
		long double blink = fld_m((const float *)0x4dba80) - fmul_m(fld_m((const float *)0x4b071c), (const float *)0x4ad498);
		g_lobbyBlinkClock = f32(blink);
		if (!(blink >= 0))
			g_lobbyBlinkClock = 1000.0f;
	}
	return call_keeping_ebp(0x43d060);   /* ranking_drawTable: the table */
}

/* 0x434490: the login sent: typing closed and the form's flags cleared; a name or password with a character the
   messages cannot carry gives its message (0x15a / 0x15b, 0x9dd1c8 cleared); else the name and password are kept
   (0x9dd570, 30 bytes, and 0x9dd58e, 12) and sent as message 0x18 (net_send 0xe), then 0x9dd838 set. Returns the
   message's or the send's eax */
u32 (login_send)(void)
{
	typing_end();
	GAME_VAR(int, 0x9dd830) = 0;
	GAME_VAR(int, 0x9dd38c) = 0;
	GAME_VAR(int, 0x4e1868) = 0;
	GAME_VAR(int, 0x68039c) = 0;
	const char *name = (const char *)0x9dd1d8, *password = (const char *)0x9dd1f6;
	int bad = GAME_CDECL(0x434400, int, const char *)(name) == 1 ? 0x15a
	        : GAME_CDECL(0x434400, int, const char *)(password) == 1 ? 0x15b : 0;   /* room_nameHasBadChar */
	if (bad) {
		u32 r = GAME_CDECL(0x41ee40, u32, int)(bad);
		g_roomLoginDue = 0;
		return r;
	}
	memset((void *)0x9dd570, 0, 30 + 12);
	strcpy((char *)0x9dd570, name);
	strcpy((char *)0x9dd58e, password);
	memset(GAME_VAR(u8 *, 0xa0b320) + 4, 0, 30);
	memset(GAME_VAR(u8 *, 0xa0b320) + 0x22, 0, 12);
	strcpy(GAME_VAR(char *, 0xa0b320) + 4, name);
	strcpy(GAME_VAR(char *, 0xa0b320) + 0x22, password);
	GAME_VAR(int *, 0xa0b320)[0] = 0x18;
	u32 r = GAME_CDECL(0x4521c0, u32, int, int)(0xe, 0x65);   /* net_send */
	g_roomRequestOut = 1;
	return r;
}

/* 0x436620: the ranking page's clicks (room modes other than 0 / 1, no message box open; a right click closes the
   page unless waiting for an answer). Not waiting (0x9dd6b8): buttons 0 .. 2 open the room's other pages
   (roomList_prevPage / 4359b0 / 4359f0), 4 closes the page, 5 / 7 / 8 sort by column 0 / 1 / 2 (the old column kept in
   0x9dd300 and a request made, the list's state cleared). While waiting, button 3 cancels it (the column and page
   put back from 0x9dd300 / 0x9dd1b4). Each with the click sound. Returns what the original leaves in eax */
u32 (ranking_clicks)(void)
{
	u32 mode = GAME_VAR(u32, 0x9dce48);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x90d1c4))
		return mode;
	int waiting = GAME_VAR(int, 0x9dd6b8);
	if (g_keyEnter && !waiting)
		g_roomMode = 0;
	if (!GAME_VAR(int, 0x4ded88))
		return mode;
	u32 button = GAME_CDECL(0x4323c0, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* ranking_hitTest */
	if (button > 8 || button == 6 || (button == 3 ? !GAME_VAR(int, 0x9dd6b8) : GAME_VAR(int, 0x9dd6b8) != 0))
		return button;
	u32 r = GAME_CDECL(0x41e760, u32, int)(0);   /* the click sound */
	static const u32 page[3] = { 0x435970, 0x4359b0, 0x4359f0 };
	int column;
	switch (button) {
	case 0: case 1: case 2:
		return GAME_CDECL(page[button], u32, void)();
	case 3:
		g_rankingHaveList = 1;
		GAME_VAR(int, 0x9dd6b8) = 0;
		g_roomListWaiting = 0;
		GAME_VAR(int, 0x9dd1d0) = GAME_VAR(int, 0x9dd300);
		return GAME_VAR(u32, 0x9dd6ac) = GAME_VAR(u32, 0x9dd1b4);
	case 4:
		g_roomMode = 0;
		return r;
	}
	column = button == 5 ? 0 : button == 7 ? 1 : 2;   /* 5, 7, 8 */
	u32 old = GAME_VAR(u32, 0x9dd1d0);
	GAME_VAR(u32, 0x9dd300) = old;
	GAME_VAR(int, 0x9dd1d0) = column;
	g_rankingRequestPending = 1;
	g_rankingHaveList = 0;
	g_roomListWaiting = 0;
	GAME_VAR(int, 0xa0b350) = 0;
	GAME_VAR(int, 0xa0b35c) = 0;
	return button == 8 ? old : r;
}

/* 0x436400: the game room's settings page clicked (no field being typed in, room modes other than 0 / 1, no message
   box; a right click closes the page). Buttons (roomSettings_hitTest): 0 / 1 type the room's name or password
   (field_editComment / 433a80), 3 the players +2 (4 .. 16, then 2), 5 the game type on (with a turn key held back) through
   0 .. 9, 6 / 7 the frag and time limits +5 (up to 50 / 60, then 5), 8 start (room_4351c0; not while connecting),
   9 close, 11 / 2, 10, 12 the map back / on (room_4356f0), 13 the map list (mapList_startEdit). Returns what the original
   leaves in eax (for the byte settings, its low byte the new value) */
u32 (room_settingsClicks)(void)
{
	static const u32 typing[4] = { 0x9dd380, 0x9dd388, 0x9dd568, 0x9dd6a8 };
	for (int k = 0; k < 4; k++)
		if (GAME_VAR(int, typing[k]))
			return GAME_VAR(u32, typing[k]);
	u32 mode = GAME_VAR(u32, 0x9dce48);
	if (mode == 1 || mode == 0)
		return mode;
	if (GAME_VAR(int, 0x90d1c4))
		return GAME_VAR(u32, 0x90d1c4);
	if (g_keyEnter)
		g_roomMode = 0;
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	u32 button = GAME_CDECL(0x432380, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* roomSettings_hitTest */
	u8 *players = (u8 *)0x4df9e9, *type = (u8 *)0x4df9eb, *frags = (u8 *)0x4df9ec, *time = (u8 *)0x4df9ed;
	u32 r;
	switch (button) {
	case 0:
		return GAME_CDECL(0x4339e0, u32, void)();   /* field_editComment */
	case 1:
		return GAME_CDECL(0x433a80, u32, void)();   /* field_editPassword */
	case 2: case 10: case 12:
		return GAME_CDECL(0x4356f0, u32, int)(1);   /* room_4356f0: the next map */
	case 11:
		return GAME_CDECL(0x4356f0, u32, int)(0);
	case 3:
		*players += 2;
		r = *players;
		if ((signed char)*players > 16)
			*players = 2;
		return r;
	case 5:
		if (input_isDown(GAME_VAR(int, 0x67ef24)) || input_isDown(GAME_VAR(int, 0x9db0ac)) ||
		    input_isDown(GAME_VAR(int, 0x6803a8)) || input_isDown(GAME_VAR(int, 0x9dad8c))) {
			r = GAME_CDECL(0x41e760, u32, int)(2);
			*type -= 1;
			r = (r & ~0xffu) | *type;
			if ((signed char)*type < 0)
				*type = 9;
		} else {
			r = GAME_CDECL(0x41e760, u32, int)(2);
			*type += 1;
			r = (r & ~0xffu) | *type;
			if ((signed char)*type > 9)
				*type = 0;
		}
		return r;
	case 6:
		*frags += 5;
		r = *frags;
		if (*frags > 50)
			*frags = 5;
		return r;
	case 7:
		*time += 5;
		r = *time;
		if (*time > 60)
			*time = 5;
		return r;
	case 8:
		if (GAME_VAR(int, 0x4ded54))
			return GAME_VAR(u32, 0x4ded54);
		sound_playMenu(0);
		return GAME_CDECL(0x4351c0, u32, void)();   /* room_4351c0: start */
	case 9:
		r = GAME_CDECL(0x41e760, u32, int)(0);
		g_roomMode = 0;
		return r;
	case 13:
		sound_playMenu(0);
		return GAME_CDECL(0x403490, u32, int)(2);   /* mapList_startEdit: the map list (the original pushes a 2 it ignores) */
	}
	return button;
}

/* 0x437630: the game room's settings page after typing (not while typing or with a message box): a typed field is
   taken (the room's name into 0x4df9c8 unless blank (sound 6); the password into 0x4df9ee; the frag and time limits
   as numbers into the bytes 0x4df9ec / 0x4df9ed; an empty line changes nothing), else the keys: start (0x4e1510;
   room_4351c0, not while connecting) and the two close keys (0x4e0cdc, 0x76d48c). Returns what the original leaves
   in eax */
u32 (room_settingsAfterTyping)(void)
{
	if (GAME_VAR(int, 0x90d1c4))
		return GAME_VAR(u32, 0x90d1c4);
	if (g_paused)
		return 0;
	const char *line = (const char *)0x9dc92c;
	if (GAME_VAR(int, 0x9dd380)) {   /* the room's name */
		if (!strlen(line) || GAME_CDECL(0x4343b0, int, const char *)(line) == 1) {   /* name_isBlank: blank */
			u32 r = strlen(line) ? GAME_CDECL(0x41e760, u32, int)(6) : 0;
			GAME_VAR(int, 0x9dd380) = 0;
			return r;
		}
		GAME_VAR(int, 0x9dd380) = 0;
		memset((void *)0x4df9c8, 0, 32);
		strcpy((char *)0x4df9c8, line);
		return strlen(line) + 1;
	}
	if (GAME_VAR(int, 0x9dd6a8)) {   /* the password */
		memset((void *)0x4df9ee, 0, 8);
		GAME_VAR(int, 0x9dd6a8) = 0;
		GAME_VAR(int, 0x4e1868) = 0;
		strcpy((char *)0x4df9ee, line);
		return 0;
	}
	static const u32 limit[2][2] = { { 0x9dd388, 0x4df9ec }, { 0x9dd568, 0x4df9ed } };   /* frags, time */
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(int, limit[k][0]))
			continue;
		u32 r = strlen(line) ? (u32)crt_atoi(line) : 0;
		GAME_VAR(int, limit[k][0]) = 0;
		if (strlen(line))
			GAME_VAR(u8, limit[k][1]) = (u8)r;
		return r;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1510)) && !GAME_VAR(int, 0x4ded54)) {
		sound_playMenu(0);
		return GAME_CDECL(0x4351c0, u32, void)();   /* room_4351c0: start */
	}
	u32 r = 0;
	static const u32 close[2] = { 0x4e0cdc, 0x76d48c };
	for (int k = 0; k < 2; k++) {
		r = (u32)input_justPressed(GAME_VAR(int, close[k]));
		if (r) {
			r = GAME_CDECL(0x41e760, u32, int)(0);
			g_roomMode = 0;
		}
	}
	return r;
}

/* ---- the map preview box (panel at y P[0], x P[1]; the box 0x80 square from (x - 0x96, y + 0x50)): the preview
   reloaded when asked (0x680cd0), then either "custom" (0x4ad56c, yellow on a dark box) when the custom flag is
   set or the preview texture 0x9da324, and a yellow outline. Returns the outline call's eax ---- */
static u32 map_preview_box(const int *panel, u32 custom, u32 reload)
{
#define X0 (panel[1] - 0x96)
#define X1 (panel[1] - 0x16)
#define Y0 (panel[0] + 0x50)
#define Y1 (panel[0] + 0xd0)
	if (GAME_VAR(int, 0x680cd0))
		GAME_CDECL(reload, void, void)();
	if (GAME_VAR(u8, custom)) {
		Color4_set((Colour *)0x9da480, 0.0f, 0.0f, 0.0f, 0.4f);
		menu_drawRect(X0, Y0, X1, Y1, 1);
		Color4_set((Colour *)0x76d438, 1.0f, 1.0f, 0.0f, 1.0f);
		text_drawBox16(X0, panel[0] + 0x88, X1, (const char *)0x4ad56c);
	} else {
		glEnable(GL_TEXTURE_2D);
		int texture = GAME_VAR(int, 0x9da324);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(7);   /* GL_QUADS */
		glTexCoord2f(0.0f, 0.0f);
		menu_vertex(X0, Y0);
		glTexCoord2f(1.0f, 0.0f);
		menu_vertex(X1, Y0);
		glTexCoord2f(1.0f, 1.0f);
		menu_vertex(X1, Y1);
		glTexCoord2f(0.0f, 1.0f);
		menu_vertex(X0, Y1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	Color4_set((Colour *)0x9da480, 1.0f, 1.0f, 0.0f, 1.0f);
	return GAME_CDECL(0x427970, u32, int, int, int, int, int)(X0, Y0, X1, Y1, 0);   /* menu_drawRect: the outline */
#undef X0
#undef X1
#undef Y0
#undef Y1
}

/* 0x43bde0: the game room's (panel 0x9dd1bc, custom flag 0x4df9ea, room_loadMapPreview); 0x40b550: the arena screen's
   (0x4dbb04, 0x4db54a, arena_40b420) */
u32 (room_drawCustomOption)(void) { return map_preview_box((const int *)0x9dd1bc, 0x4df9ea, 0x43bcb0); }
u32 (arena_drawCustomOption)(void) { return map_preview_box((const int *)0x4dbb04, 0x4db54a, 0x40b420); }

/* 0x43e7b0: the account page (room page 0; room modes other than 0 / 1, not page 99): with a message box only its
   frame; else the page (0x433610 when 0x9dd354, then account_drawPanel) and, once a field's typing has ended, the typed
   line taken into it (the name, password, its repeat (12 bytes each) or the e-mail (50)) and the key that ended it
   (0x9dc428: 0xa back, 0x14 on) opening the field before or after (room_434020 .. 434260). Returns what the
   original leaves in eax */
u32 (account_page)(void)
{
	static const struct { u32 editing, field, size, back, on; } fields[4] = {
		{ 0x9dd69c, 0x9dd6d8, 12, 0, 0x4340e0 }, { 0x9dd37c, 0x9dd1f6, 12, 0x434020, 0x4341a0 },
		{ 0x9dd378, 0x9dd202, 12, 0x4340e0, 0x434260 }, { 0x9dd304, 0x9dd20e, 50, 0x4341a0, 0 } };
	GAME_CDECL(0x4388e0, void, void)();   /* room_4388e0: the tunnel */
	u32 mode = GAME_VAR(u32, 0x9dce48);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x9dd834) == 99)
		return mode;
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x9dd368), GAME_VAR(int, 0x9dd36c),
		                                                     GAME_VAR(int, 0x9dd370), GAME_VAR(int, 0x9dd374));
	if (GAME_VAR(int, 0x9dd354))
		GAME_CDECL(0x433610, void, void)();
	u32 r = GAME_CDECL(0x43a420, u32, void)();   /* account_drawPanel: the page */
	if (GAME_VAR(int, 0x9dd6d4) == 1)
		return r;
	for (int k = 0; k < 4; k++) {
		if (!GAME_VAR(int, fields[k].editing))
			continue;
		if (g_paused)
			return r;
		memset((void *)fields[k].field, 0, fields[k].size);
		GAME_VAR(int, fields[k].editing) = 0;
		GAME_VAR(int, 0x4e1868) = 0;
		strcpy((char *)fields[k].field, (const char *)0x9dc92c);
		u32 key = GAME_VAR(u32, 0x9dc428);
		u32 next = key == 0xa ? fields[k].back : key == 0x14 ? fields[k].on : 0;
		if (!next)
			return key;
		r = GAME_CDECL(next, u32, void)();
		if (!(k == 2 && key == 0xa))   /* (the original keeps the key there) */
			GAME_VAR(int, 0x9dc428) = 0;
		return r;
	}
	return r;
}

/* ---- the server login dialog's keys: its text fields (0x74de1c: 0 .. 2), the text cursor placed in the one typed
   into (0x67ef34 / 0x67fb38) ---- */
#define g_loginField GAME_VAR(int, 0x74de1c)
#define g_tabDirection GAME_VAR(int, 0x9dc428)   /* 20 forward, 10 back (shift) */

/* the cursor into field to at (x, y) */
static void login_field(int to, int x, int y)
{
	g_loginField = to;
	GAME_VAR(int, 0x76d42c) = 1;
	GAME_VAR(u32, 0x680bc0) = 0x41a00000;   /* 20 */
	GAME_VAR(u32, 0x9da4a4) = 0x3ecccccd;   /* 0.4 */
	GAME_VAR(int, 0x67ef34) = x;
	GAME_VAR(int, 0x67fb38) = y;
	g_tabDirection = 0;
}

/* OK (button 4 clicked, or the OK key) logs in (account_checkForm), cancel (button 5, or 0x4e0cdc) closes (room_openDialog42);
   neither while a message is up (0x68039c) */
static int login_buttons(void)
{
	int button = -1;
	if (input_justPressed(GAME_VAR(int, 0x9dae70)) == 1)
		button = GAME_CDECL(0x432240, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* loginForm_hitTest */
	if (button != 4 && button != 5) {
		if (input_justPressed(g_keyOk) == 1)
			button = 4;
		else if (input_justPressed(GAME_VAR(int, 0x4e0cdc)) == 1)
			button = 5;
		else
			return 0;
	}
	if (!GAME_VAR(int, 0x68039c)) {
		sound_playMenu(0);
		if (button == 4)
			GAME_CDECL(0x4346c0, void, void)();   /* account_checkForm */
		else
			GAME_CDECL(0x434640, void, void)();   /* room_openDialog42 */
	}
	return 1;
}

/* 0x436e10: the server login dialog's keys: its two buttons, then Tab (0x680390) to the next field, or with shift
   (0x67ef24 / 0x9db0ac held) the one before (the original's path for "back" from the first field is never taken).
   The original leaves eax to callers that ignore it */
void (loginDialog_keys)(void)
{
	if (login_buttons())
		return;
	if (input_justPressed(GAME_VAR(int, 0x680390)) != 1 || GAME_VAR(int, 0x68039c))
		return;
	g_tabDirection = 20;
	if (input_isDown(GAME_VAR(int, 0x67ef24)) == 1 || input_isDown(GAME_VAR(int, 0x9db0ac)) == 1)
		g_tabDirection = 10;
	if (g_tabDirection == 20) {
		if (g_loginField == 1)
			login_field(2, GAME_VAR(int, 0x9dd6e8) + 0x172, GAME_VAR(int, 0x9dd6f4) - 0x30);
		else if (g_loginField == 2) {
			GAME_VAR(int, 0x9dd348) = 1;
			GAME_VAR(int, 0x9dd3f8) = 0;
			login_field(2, GAME_VAR(int, 0x9dd358) + 0x15c, GAME_VAR(int, 0x9dd35c) + 0x44);
		}
	} else {
		if (g_loginField == 1) {
			GAME_VAR(int, 0x9dd564) = 0;
			GAME_VAR(int, 0x9dd6cc) = 1;
			login_field(0, GAME_VAR(int, 0x9dd358) + 0x15c, GAME_VAR(int, 0x9dd35c) + 0xd4);
		} else if (g_loginField == 2)
			login_field(1, GAME_VAR(int, 0x9dd6e8) + 0xaa, GAME_VAR(int, 0x9dd6f4) - 0x30);
	}
}
#undef g_tabDirection
#undef g_loginField

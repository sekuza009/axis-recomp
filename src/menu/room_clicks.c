/* room_clicks.c: the game room's small handlers: clicks on its popups' buttons, starting the chat line, and the
   white fade over the screen. Buttons are hit-tested with the pointer (room_4321c0 and its kind: the index of the
   button under it, or -1). */
#include "../game.h"

#define g_roomPopup GAME_VAR(int, 0x9dd6c4)           /* (by use) the room's popup: 1 / 2 closed by its buttons */
#define g_leaveDialog GAME_VAR(int, 0x9dd850)         /* the "leave" dialog is up */
#define g_roomChatting GAME_VAR(int, 0x9dd6b4)        /* the chat line is being typed */
#define g_roomFade GAME_VAR(float, 0x4deb74)          /* the white fade, rising to 1 */

/* 0x435ab0: the "leave" dialog: yes (button 0) closes it and leaves (the game closes with exit code 2), no (button 1) only closes it */
void (room_435ab0)(void)
{
	if (g_dialogOpen != 0 || g_mouseClick == 0)
		return;
	switch (room_4321c0(g_mouseX, g_mouseY)) {
	case 0:
		g_leaveDialog = 0;
		profile_41e7a0(2);
		break;
	case 1:
		g_leaveDialog = 0;
		break;
	}
}

/* 0x435ce0: the popup's two buttons (room_432280) close it with 1 or 2 */
void (room_435ce0)(void)
{
	if (g_mouseClick == 0)
		return;
	switch (room_432280(g_mouseX, g_mouseY)) {
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
void (room_434da0)(void)
{
	g_roomChatting = 0;
	if (GAME_VAR(u8, 0x908807 + g_localPlayer * 0x4a) != 0) {
		g_roomChatting = 1;
		room_434320();
	}
}

/* 0x435f40: in room state 2, the button (room_432340) that stops the arena being set up: its flags off, the
   arena's connection closed (arena_452fe0) and its timer (0x378) killed */
void (room_435f40)(void)
{
	if (g_dialogOpen != 0 || g_mouseClick == 0 || GAME_VAR(int, 0x9dce48) != 2)
		return;
	g_cursorBlink = 0.0f;
	if (room_432340(g_mouseX, g_mouseY) == 0) {
		sound_playMenu(0);
		GAME_VAR(int, 0x4dbb10) = 0;
		GAME_VAR(int, 0x4dbb78) = 0;
		arena_452fe0();
		GAME_VAR(int, 0x4db8b4) = 0;
		KillTimer(g_hWndMain, 0x378);
	}
}

/* 0x43df00: the white fade over the whole screen, 0.015 per time unit (the stored value goes on past 1; the
   colour stops at 1) */
void (room_43df00)(void)
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

/* 0x405200 (FUN_00405200): the arena screen's chat line, the same way (flag 0x4db8bc, its message field) */
void (FUN_00405200)(void)
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
		profile_41e7a0(2);
	}
}

void (menu_436940)(void) { leave_keys(&g_leaveDialog); }
void (lobbyJoin_keys)(void) { leave_keys(&GAME_VAR(int, 0x907b2c)); }

/* 0x443e20: the skirmish settings screen's clicks (no dialog open, 0x90d1c4): a right click leaves (0x443c80); a left
   click on its buttons (skirmish_4438d0): rows 0..7 change that setting (0x443d50), 8 saves (0x443af0 with the
   selection 0x9f16a4), 9 leaves. Returns the last call's eax */
int (skirmish_saveSettings)(void)
{
	int r = GAME_VAR(int, 0x90d1c4);
	if (r)
		return r;
	if (GAME_VAR(int, 0x4ded8c))
		GAME_CDECL(0x443c80, int, void)();
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	int row = GAME_CDECL(0x4438d0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* skirmish_4438d0 */
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
u32 (menu_437140)(void)
{
	if (key_hit(0x76d48c))
		return GAME_CDECL(0x435a40, u32, void)();   /* room_leaveGame */
	if (key_hit(0x4e1514))
		return GAME_CDECL(0x4334c0, u32, void)();   /* room_4334c0 */
	if (key_hit(0x4e14f8))
		return GAME_CDECL(0x433590, u32, void)();   /* room_433590 */
	if (key_hit(0x4e0cdc))
		return GAME_CDECL(0x433790, u32, void)();   /* room_433790 */
	if (key_hit(0x4e151c))
		return GAME_CDECL(0x433800, u32, void)();   /* room_433800 */
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
u32 (room_435b00)(void)
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
		GAME_CDECL(0x433c70, void, void)();          /* room_433c70 */
		r = GAME_CDECL(0x433b00, u32, void)();       /* room_433b00 */
		GAME_VAR(int, 0x9dd1cc) = 1;
		return r;
	case 1:
		GAME_CDECL(0x433c70, void, void)();
		r = GAME_CDECL(0x433bb0, u32, void)();       /* room_433bb0 */
		GAME_VAR(int, 0x9dd6b0) = 1;
		return r;
	case 2:
		if ((open = GAME_VAR(u32, 0x9dd1c8)))
			return open;
		sound_playMenu(0);
		GAME_VAR(int, 0x9dd198) = 1;
		GAME_VAR(int, 0x9dd1c8) = 1;
		GAME_VAR(int, 0x9dd850) = 0;
		return 1;
	case 3:
		if (GAME_VAR(int, 0x68039c)) {
			GAME_VAR(int, 0x68039c) = 0;
			GAME_CDECL(0x431590, void, void)();      /* match_431590 */
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
		return GAME_CDECL(0x4338c0, u32, void)();    /* room_4338c0 */
	}
	return button;
}

/* 0x435d30: the game room's page clicks (page open, 0x9dce48 not 0 or 1; no dialog): its six buttons (outlines at
   0x9daf88) open the room's pages, the arm center (0x4dc24c = 3) or leave the game; a right click (when 0x9dae10
   allows) leaves too. Returns what the original leaves in eax */
u32 (room_435d30)(void)
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
				GAME_VAR(int, 0x4deb48) = 0;
			} else
				GAME_CDECL(actions[i], void, void)();
			break;
		}
	}
	int right = GAME_VAR(int, 0x4ded8c);
	if (!right)
		return 0;
	int allowed = GAME_VAR(int, 0x9dae10);
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	return GAME_CDECL(0x435a40, u32, void)();   /* room_leaveGame */
}

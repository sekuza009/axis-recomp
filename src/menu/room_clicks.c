/* room_clicks.c: the game room's small handlers: clicks on its popups' buttons, starting the chat line, and the
   white fade over the screen. Buttons are hit-tested with the pointer (room_4321c0 and its kind: the index of the
   button under it, or -1). */
#include "../game.h"

#define g_roomPopup GAME_VAR(int, 0x9dd6c4)           /* (by use) the room's popup: 1 / 2 closed by its buttons */
#define g_leaveDialog GAME_VAR(int, 0x9dd850)         /* the "leave" dialog is up */
#define g_roomChatting GAME_VAR(int, 0x9dd6b4)        /* the chat line is being typed */
#define g_roomFade GAME_VAR(float, 0x4deb74)          /* the white fade, rising to 1 */

/* 0x435ab0: the "leave" dialog: yes (button 0) closes it and leaves (message 2), no (button 1) only closes it */
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

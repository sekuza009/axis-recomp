/* profile_dialogs.c: the profile screen's dialogs: typing a new pilot's name, and the two yes / no questions. */
#include "../game.h"

#define g_profileDialog GAME_VAR(int, 0x9f8f10)       /* (by use) the open dialog: 2 the name, 3 and 5 the questions */
#define g_questionX GAME_VAR(int, 0x67ef34)           /* where the two-button question is drawn */
#define g_questionY GAME_VAR(int, 0x67fb38)

/* 0x44b600: the new pilot's name (16 characters), typed into the panel at 0x9f8ea8 */
void (profile_44b600)(void)
{
	input_releaseKeyboard();
	g_paused = 1;
	menu_clearInputBuffer(0x10);
	g_chatCaretX = GAME_VAR(int, 0x9f8eac) + 0x24;
	g_chatCaretY = GAME_VAR(int, 0x9f8ea8) + 0x38;
	g_menuFade = 5.0f;
	g_profileDialog = 2;
	g_dialogOpen = 1;
	GAME_VAR(int, 0x9f8f34) = 0;
	chat_createEdit(0x10);
}

/* a two-button question (dialog kind) placed over the panel whose corner is (x, y) */
static void ask(int kind, int x, int y)
{
	sound_playMenu(0);
	g_dialogOpen = 1;
	g_highlightShown = 1;
	g_profileDialog = kind;
	g_cursorBlink = 0.0f;
	g_dialogChoice = 0;
	GAME_VAR(float, 0x680bc0) = 20.0f;
	GAME_VAR(float, 0x9da4a4) = 0.2f;
	g_questionX = x + 0x9c;
	g_questionY = y + 0x4a;
}

/* 0x44b670, 0x44b6e0: question 3 over the pilot panel, question 5 over the second panel */
void (profile_44b670)(void) { ask(3, GAME_VAR(int, 0x9f8f1c), GAME_VAR(int, 0x9f8f0c)); }
void (profile_44b6e0)(void) { ask(5, GAME_VAR(int, 0x9f6834), GAME_VAR(int, 0x9f683c)); }

/* 0x44f810: the profile screen: only its frame while a dialog is up, else the pilot preview (when shown) and the
   screen */
void (profile_44f810)(void)
{
	if (g_dialogOpen != 0) {
		menu_drawFrame(GAME_VAR(int, 0x9f8c54), GAME_VAR(int, 0x9f8c50), GAME_VAR(int, 0x9f6830), GAME_VAR(int, 0x9f682c));
		return;
	}
	if (GAME_VAR(int, 0x9f8d68) != 0)
		profile_44bc50();
	profile_44e640();
}

/* profile_keys.c: the profile screen's keys, one handler per page (profile_screenKeys picks it). Pages 3 and 5 are
   two-button dialogs (yes on the left, no on the right) worked by the arrow keys, a toggle key or a click on a
   button; page 6 is CHARACTER SELECT's 3 x 3 pilot grid. Every handler first stops the text cursor's blink. */
#include "../game.h"

/* the highlight of a two-button dialog whose frame is at (x, y): choice 0 the left button, 1 the right one */
static void dialog_select(int choice, int x, int y)
{
	g_dialogFocus = choice;
	g_pointerGliding = 1;
	g_pointerGlideTime = 20.0f;
	g_unusedHighlightAlpha = 0.4f;
	g_highlightX = x + (choice ? 0x114 : 0x9c);
	g_highlightY = y + 0x4a;
	sound_playMenu(2);
}
/* the arrow and toggle keys of a two-button dialog; answers whether one moved the highlight */
static int dialog_keys(int x, int y)
{
	if (input_justPressed(g_keyRight) == 1 && g_dialogFocus == 0) {
		dialog_select(1, x, y);
		return 1;
	}
	if (input_justPressed(g_keyLeft) == 1 && g_dialogFocus == 1) {
		dialog_select(0, x, y);
		return 1;
	}
	if (input_justPressed(g_keyToggle) == 1) {
		dialog_select(g_dialogFocus == 0 ? 1 : 0, x, y);
		return 1;
	}
	return 0;
}

/* 0x44c850: page 2 (the new pilot's name) keys: only while its message is up (g_profileMessage, NAME ALREADY
   REGISTRED): a click or OK closes it and the name is typed again (profile_typeNewName) */
void (profile_messageKeys)(void)
{
	g_menuRepeatClock = 0.0f;
	if (!g_profileMessage)
		return;
	if (input_justPressed(g_keyClick) == 1) {
		g_profileMessage = 0;
		g_textFieldOpen = 1;
		profile_typeNewName();
	}
	if (input_justPressed(g_keyOk) == 1) {
		g_profileMessage = 0;
		g_textFieldOpen = 1;
		profile_typeNewName();
	}
}

/* 0x44c8c0 (profile_deleteKeys): page 3, "delete this profile?": OK or a click on the left button deletes it, the
   right button or a cancel key keeps it; either way back to the list */
void (profile_deleteKeys)(void)
{
	g_menuRepeatClock = 0.0f;
	if (input_justPressed(g_keyOk) == 1) {
		sound_playMenu(0);
		profile_deleteChosen();
		g_profilePage = 1;
		return;
	}
	int button = -1;
	if (input_justPressed(g_keyClick) == 1) {
		button = deleteDialog_hitTest(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_deleteChosen();
			g_profilePage = 1;
			return;
		}
	}
	if (button == 1 || input_justPressed(g_keyBack) == 1 || input_justPressed(g_keyCancel2) != 0) {
		sound_playMenu(0);
		g_profilePage = 1;
		return;
	}
	dialog_keys(g_profileDialogX, g_profileDialogY);
}

/* 0x44ca90 (profile_logOutKeys): page 5, "log out, are you sure?": OK or a click on the left button confirms
   (profile_quitGame), the right button or a cancel key goes back to the list */
void (profile_logOutKeys)(void)
{
	g_menuRepeatClock = 0.0f;
	if (input_justPressed(g_keyOk) == 1) {
		sound_playMenu(0);
		profile_quitGame();
		return;
	}
	int button = -1;
	if (input_justPressed(g_keyClick) == 1) {
		button = logOutDialog_hitTest(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_quitGame();
			return;
		}
	}
	if (button == 1 || input_justPressed(g_keyCancel) == 1 || input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		g_pointerGliding = 0;
		g_profilePage = 1;
		return;
	}
	dialog_keys(g_logOutDialogX, g_logOutDialogY);
}

/* 0x44cc60 (pilotSelect_keys): page 6, the pilot grid: OK makes the profile with the pilot chosen (profile_create), back or
   cancel leaves; either way back to the list. The arrows move the cursor (0..8) and wrap within its row or column */
void (pilotSelect_keys)(void)
{
	g_menuRepeatClock = 0.0f;
	if (input_justPressed(g_keyOk) == 1) {
		sound_playMenu(0);
		profile_create();
	} else if (input_justPressed(g_keyBack) == 1 || input_justPressed(g_keyCancel) == 1) {
		sound_playMenu(0);
	} else {
		if (input_justPressed(g_keyRight) == 1) {
			if (++g_pilotSelectCursor % 3 == 0)
				g_pilotSelectCursor = g_pilotSelectCursor - 3;
		} else if (input_justPressed(g_keyLeft) == 1) {
			if (--g_pilotSelectCursor < 0)
				g_pilotSelectCursor = 2;
			else if (g_pilotSelectCursor % 3 == 2)
				g_pilotSelectCursor = g_pilotSelectCursor + 3;
		} else if (input_justPressed(g_keyUp) == 1) {
			g_pilotSelectCursor = g_pilotSelectCursor - 3;
			if (g_pilotSelectCursor < 0)
				g_pilotSelectCursor = g_pilotSelectCursor + 9;
		} else if (input_justPressed(g_keyDown) == 1) {
			g_pilotSelectCursor = g_pilotSelectCursor + 3;
			if (g_pilotSelectCursor > 8)
				g_pilotSelectCursor = g_pilotSelectCursor - 9;
		} else {
			return;
		}
		g_statBarsStale = 1;
		sound_playMenu(2);
		(*(int *)&g_profileRevealClock) = 0;
		g_profileReveal = 0;
		return;
	}
	g_profilePage = 1;
	g_pointerGliding = 0;
}

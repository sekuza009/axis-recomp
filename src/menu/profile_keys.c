/* profile_keys.c: the profile screen's keys, one handler per page (profile_screenKeys picks it). Pages 3 and 5 are
   two-button dialogs (yes on the left, no on the right) worked by the arrow keys, a toggle key or a click on a
   button; page 6 is the 3 x 3 emblem grid. Every handler first stops the text cursor's blink. */
#include "../game.h"

/* the highlight of a two-button dialog whose frame is at (x, y): choice 0 the left button, 1 the right one */
static void dialog_select(int choice, int x, int y)
{
	g_dialogChoice = choice;
	g_highlightShown = 1;
	g_highlightSize = 20.0f;
	g_highlightAlpha = 0.4f;
	g_highlightX = x + (choice ? 0x114 : 0x9c);
	g_highlightY = y + 0x4a;
	sound_playMenu(2);
}
/* the arrow and toggle keys of a two-button dialog; answers whether one moved the highlight */
static int dialog_keys(int x, int y)
{
	if (input_justPressed(g_keyRight) == 1 && g_dialogChoice == 0) {
		dialog_select(1, x, y);
		return 1;
	}
	if (input_justPressed(g_keyLeft) == 1 && g_dialogChoice == 1) {
		dialog_select(0, x, y);
		return 1;
	}
	if (input_justPressed(g_keyToggle) == 1) {
		dialog_select(g_dialogChoice == 0 ? 1 : 0, x, y);
		return 1;
	}
	return 0;
}

/* 0x44c850 (profile_messageKeys): page 2, a message: OK or a click closes it */
void (profile_messageKeys)(void)
{
	g_cursorBlink = 0.0f;
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
	g_cursorBlink = 0.0f;
	if (input_justPressed(g_keyOk) == 1) {
		sound_playMenu(0);
		profile_deleteFiles();
		g_profilePage = 1;
		return;
	}
	int button = -1;
	if (input_justPressed(g_keyClick) == 1) {
		button = deleteDialog_hitTest(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_deleteFiles();
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

/* 0x44ca90 (profile_secondDialogKeys): page 5, the second two-button dialog: OK or a click on the left button confirms
   (profile_resetCamera), the right button or a cancel key goes back to the list */
void (profile_secondDialogKeys)(void)
{
	g_cursorBlink = 0.0f;
	if (input_justPressed(g_keyOk) == 1) {
		sound_playMenu(0);
		profile_resetCamera();
		return;
	}
	int button = -1;
	if (input_justPressed(g_keyClick) == 1) {
		button = secondDialog_hitTest(g_mouseX, g_mouseY);
		if (button == 0) {
			sound_playMenu(0);
			profile_resetCamera();
			return;
		}
	}
	if (button == 1 || input_justPressed(g_keyCancel) == 1 || input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		g_highlightShown = 0;
		g_profilePage = 1;
		return;
	}
	dialog_keys(g_profileDialog2X, g_profileDialog2Y);
}

/* 0x44cc60 (profile_emblemKeys): page 6, the emblem grid: OK takes the profile (profile_selectAndLoad), back or
   cancel leaves; either way back to the list. The arrows move the cursor (0..8) and wrap within its row or column */
void (profile_emblemKeys)(void)
{
	g_cursorBlink = 0.0f;
	if (input_justPressed(g_keyOk) == 1) {
		sound_playMenu(0);
		profile_selectAndLoad();
	} else if (input_justPressed(g_keyBack) == 1 || input_justPressed(g_keyCancel) == 1) {
		sound_playMenu(0);
	} else {
		if (input_justPressed(g_keyRight) == 1) {
			if (++g_emblemCursor % 3 == 0)
				g_emblemCursor = g_emblemCursor - 3;
		} else if (input_justPressed(g_keyLeft) == 1) {
			if (--g_emblemCursor < 0)
				g_emblemCursor = 2;
			else if (g_emblemCursor % 3 == 2)
				g_emblemCursor = g_emblemCursor + 3;
		} else if (input_justPressed(g_keyUp) == 1) {
			g_emblemCursor = g_emblemCursor - 3;
			if (g_emblemCursor < 0)
				g_emblemCursor = g_emblemCursor + 9;
		} else if (input_justPressed(g_keyDown) == 1) {
			g_emblemCursor = g_emblemCursor + 3;
			if (g_emblemCursor > 8)
				g_emblemCursor = g_emblemCursor - 9;
		} else {
			return;
		}
		g_emblemMoved = 1;
		sound_playMenu(2);
		g_profileRevealClock = 0;
		g_profileReveal = 0;
		return;
	}
	g_profilePage = 1;
	g_highlightShown = 0;
}

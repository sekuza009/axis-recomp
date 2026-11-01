/* room_dialogs.c: the room screen's dialogs opened and its state reset: each dialog a box (left, top, right,
   bottom), its fields cleared, the screen's sub-state (0x9dd834) set to the dialog's. */
#include "../game.h"
#include <string.h>


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
	g_typingGameName = 0;
	g_typingGamePassword = 0;
	g_chatFieldFlag = 0;
	g_paused = 0;
}

/* 0x433980: dialog 0x58 */
void (room_openDialog58)(void)
{
	set_box(IMG(0x9dd1a0), 0x50, 0x78, 0x230, 0x168);
	popup_layout();
	dialog_opened(0x58);
	g_roomPopup = 0;
}

/* 0x4338c0: dialog 0x4d, its two 0x2a-byte name buffers emptied */
void (room_openDialog4d)(void)
{
	set_box(ADDR(g_loginFormLeft), 0x1e, 0x32, 0x262, 0x1ae);
	loginDialog_layout();
	memset((void *)OBJ(g_accountName), 0, 0x54);
	dialog_opened(0x4d);
	g_openLoginName = 1;
	g_roomLeaveDialog = 0;
}

/* 0x434640: dialog 0x42, its name field filled from 0x9dd570 */
void (room_openDialog42)(void)
{
	static const u32 cleared[] = { ADDR(g_typingAccountName), ADDR(g_unusedLoginWord), ADDR(g_typingAccountPassword), ADDR(g_typingAccountRepeat), ADDR(g_typingAccountEmail), IMG(0x4e1868), IMG(0x68039c) };
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	memset((void *)OBJ(g_accountName), 0, 7 * 4 + 2 + 12);
	g_roomState = 0x42;
	g_retypePassword = 1;
	strcpy(g_accountName, g_joinedTitleName);
}

/* 0x433590: the room screen's start: state 1, fade 0.7, 30 (0x5b1914), 999 (0x907b24), the rest cleared */
void (room_start)(void)
{
	static const u32 cleared[] = { ADDR(g_roomRefreshing), ADDR(g_roomSearching), ADDR(g_gameListLoaded), ADDR(g_roomSearchAnswerIn), ADDR(g_gameCount), ADDR(g_lobbyBlinkClock), IMG(0x76d41c), ADDR(g_gameListTop),
	                               ADDR(g_lobbyListRow), ADDR(g_gameListJoinClicked), ADDR(g_roomJoined), ADDR(g_roomListRefreshTimer), ADDR(g_gameListClickArmed), ADDR(g_gameListClickTimer), ADDR(g_roomNameSum) };
	g_roomPanelBrightness = 0x3f333333;   /* 0.7 */
	g_roomState = 1;
	g_roomMode = 1;
	g_lastPanel = 999;
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	g_listRefreshPeriod = 30;
}

#define CALL(addr) GAME_CDECL(addr, u32, void)()
#define sound(id) GAME_FN(sound_playMenu, 0x41e760, u32, int)(id)   /* sound_playMenu, its eax */

/* 0x4378e0: the game room's mouse, by state (0x9dd834): 0 .. 2, 4 and 99 while no dialog is open (0x9dd7d8; 2: the map
   list's keys when open), 66 and 88 (a message box 0x9dd850 first), 77. Returns what the handler leaves in eax */
u32 (room_mouse)(void)
{
	u32 state = (*(u32 *)&g_roomState);
	int dialog = g_roomDialogOpen;
	switch (state) {
	case 0: return dialog ? (u32)dialog : GAME_FN(room_readyKeys, 0x437240, u32, void)();   /* room_readyKeys */
	case 1: return dialog ? (u32)dialog : GAME_FN(room_gameListKeys, 0x4372f0, u32, void)();
	case 2:
		if (dialog)
			return (u32)dialog;
		return g_mapListOpen ? GAME_FN(room_mapListKeys, 0x403870, u32, void)() : GAME_FN(room_settingsAfterTyping, 0x437630, u32, void)();
	case 4: return dialog ? (u32)dialog : GAME_FN(roomList_passwordKeys, 0x437810, u32, void)();
	case 66: return g_roomLeaveDialog == 1 ? GAME_FN(leaveDialog_keys, 0x436940, u32, void)() : GAME_FN(createDialog_keys, 0x436990, u32, void)();
	case 77: return GAME_FN(loginDialog_keys, 0x436e10, u32, void)();
	case 88: return g_roomLeaveDialog == 1 ? GAME_FN(leaveDialog_keys, 0x436940, u32, void)() : GAME_FN(room_leaveKeys, 0x4370e0, u32, void)();
	case 99: return dialog ? (u32)dialog : GAME_FN(room_keys, 0x437140, u32, void)();
	}
	return state;
}

/* 0x437240: the game room's keys (unless typing): with the confirm box up (0x9dd6d4) one key closes it; else the
   first key starts the game when ready (0x434b90), or plays the refusal sound and shows message 5; two more keys
   leave the screen (0x9dce48 = 0). Returns what the original leaves in eax */
u32 (room_readyKeys)(void)
{
	if (g_paused)
		return (*(u32 *)&g_paused);
	if (g_roomAwaitingServer == 1) {
		if (!input_justPressed(g_dikEscape_2))
			return 0;
	} else if (input_justPressed(g_dikO)) {
		if (GAME_FN(account_sendChange, 0x434b90, u32, void)() != 1) {   /* not ready */
			sound(6);
			return GAME_FN(menu_showMessage, 0x41ee40, u32, int)(5);   /* menu_showMessage: the message */
		}
	} else if (!input_justPressed(g_dikC) && !input_justPressed(g_dikEscape_2))
		return 0;
	u32 r = sound(0);
	g_roomMode = 0;
	return r;
}

/* 0x435c20: the game settings dialog's clicks: a right click (or button 5) closes it, buttons 0 .. 3 pick an option
   page, 4 applies. Returns what the original leaves in eax */
u32 (settingsDialog_clicks)(void)
{
	if (g_keyEnter) {
		sound(0);
		return GAME_FN(room_openDialog42, 0x434640, u32, void)();   /* closed */
	}
	if (!g_mouseClick)
		return 0;
	u32 button = GAME_FN(loginForm_hitTest, 0x432240, u32, int, int)(g_mouseX, g_mouseY);   /* the dialog's hit test */
	if (button <= 3) {
		GAME_FN(account_endTyping, 0x433d30, u32, void)();
		return GAME_FN(loginForm_openField, 0x433e60, u32, int)((int)button);
	}
	if (button == 4) {
		sound(0);
		return GAME_FN(account_checkForm, 0x4346c0, u32, void)();   /* applied */
	}
	if (button == 5) {
		sound(0);
		return GAME_FN(room_openDialog42, 0x434640, u32, void)();
	}
	return button;
}

/* 0x434dd0: joining session i of the list: its DirectPlay connection (0x452ec0) and the join (dplay_listSessions); a failure
   shows message 0x3f or 0x40 and stops the search; on success the join's wait starts (timer 0x378, 2 s, its id
   kept). Returns what the original leaves in eax */
u32 (room_joinSession)(int i)
{
	g_roomJoined = 0;
	if (!GAME_FN(arena_openSession, 0x452ec0, int, int, void *)(0, (void *)((OBJ(g_gameList) + 0x2b) + i * 0x4a))) {
		menu_showMessage(0x3f);
		return GAME_FN(arena_leaveSession, 0x452fe0, u32, void)();   /* arena_leaveSession */
	}
	g_arenaJoinRow = i;
	if (!GAME_FN(dplay_listSessions, 0x453260, u32, void)()) {        /* dplay_listSessions */
		menu_showMessage(0x40);
		return GAME_FN(arena_leaveSession, 0x452fe0, u32, void)();
	}
	g_arenaSearchTicks = 0;
	g_arenaConfirming = 1;
	g_arenaJoinWaiting = 0;
	g_arenaJoinPending = 0;
	u32 timer = IMPORT(0x4a9334, u32, void *, u32, u32, void *)(g_hWndMain, 0x378, 2000, NULL);   /* SetTimer */
	g_arenaJoinTimer = timer;
	return timer;
}

/* 0x434d00: the game room's list opened: its state reset, the session list cleared, the request for the server's
   room list sent (message 0x13, 0x65 bytes), 30 seconds. Returns 1 */
int (gameList_open)(void)
{
	g_connectionAwaited = 1;
	g_connectStep = 2;
	g_roomSearchAnswerIn = 0;
	g_roomRefreshing = 0;
	g_roomSearching = 1;
	g_gameServerState = 0;
	g_unusedRoomListWord = 0;
	g_gameCount = 0;
	g_gameListLoaded = 1;
	g_localPlayer = 0;
	(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;   /* 1000 */
	g_gameListTop = 0;
	g_lobbyListRow = 0;
	GAME_FN(arena_clearChatRecord, 0x4045e0, u32, void)();   /* arena_clearChatRecord */
	GAME_VAR(u32, g_netRequestWord) = 0x180001;
	GAME_FN(net_send, 0x4521c0, int, int, int)(0x13, 0x65);   /* net_send */
	g_roomNameSum = 0;
	g_listRefreshPeriod = 0x1e;
	return 1;
}

/* 0x406200: joining arena i of the list (99999: the one typed in, 0x4dbbd4): the search stopped first if it runs,
   the connection made (0x452ec0; message 0x3f and the search stopped on a failure), the join (dplay_listSessions, not
   checked), the join's wait (timer 0x378, 2 s). Returns what the original leaves in eax */
u32 (arena_joinListed)(int i)
{
	g_lobbyJoinStarted = 0;
	g_lobbyJoinRequest = 0;
	if (g_arenaSearchStarted)
		GAME_FN(arena_leaveSession, 0x452fe0, u32, void)();
	void *session = i == 99999 ? (void *)ADDR(g_typedArenaName) : (void *)((OBJ(g_gameList) + 0x2b) + i * 0x4a);
	if (!GAME_FN(arena_openSession, 0x452ec0, int, int, void *)(0, session)) {
		menu_showMessage(0x3f);
		return GAME_FN(arena_leaveSession, 0x452fe0, u32, void)();
	}
	g_arenaJoinRow = i;
	GAME_FN(dplay_listSessions, 0x453260, u32, void)();
	g_arenaSearchTicks = 0;
	g_arenaConfirming = 1;
	g_arenaJoinWaiting = 0;
	g_arenaJoinPending = 0;
	u32 timer = IMPORT(0x4a9334, u32, void *, u32, u32, void *)(g_hWndMain, 0x378, 2000, NULL);   /* SetTimer */
	g_arenaJoinTimer = timer;
	return timer;
}

/* 0x436800: the game room's keys, by state (0x9dd834): as room_mouse's mouse, with the room's own handlers (state 1:
   the join's wait while it runs, 0x4db8b4). Returns what the handler leaves in eax */
u32 (room_processKeys)(void)
{
	u32 state = (*(u32 *)&g_roomState);
	int dialog = g_roomDialogOpen;
	switch (state) {
	case 0: return dialog ? (u32)dialog : GAME_FN(room_openClicks, 0x435e70, u32, void)();   /* room_openClicks */
	case 1:
		if (dialog)
			return (u32)dialog;
		return g_arenaConfirming ? GAME_FN(room_stopArenaSetup, 0x435f40, u32, void)() : GAME_FN(gameList_mouse, 0x435fc0, u32, void)();
	case 2:
		if (dialog)
			return (u32)dialog;
		return g_mapListOpen ? GAME_FN(mapList_mouse, 0x4036c0, u32, void)() : GAME_FN(room_settingsClicks, 0x436400, u32, void)();
	case 4: return dialog ? (u32)dialog : GAME_FN(ranking_clicks, 0x436620, u32, void)();
	case 66: return g_roomLeaveDialog ? GAME_FN(leaveDialog_clicks, 0x435ab0, u32, void)() : GAME_FN(room_leftClicks, 0x435b00, u32, void)();
	case 77: return GAME_FN(settingsDialog_clicks, 0x435c20, u32, void)();   /* settingsDialog_clicks */
	case 88: return g_roomLeaveDialog ? GAME_FN(leaveDialog_clicks, 0x435ab0, u32, void)() : GAME_FN(popup_clicks, 0x435ce0, u32, void)();
	case 99: return dialog ? (u32)dialog : GAME_FN(room_pageClicks, 0x435d30, u32, void)();
	}
	return state;
}

/* 0x435e70: the game room's clicks while it is open (0x9dce48 past 1; no confirm box, dialog or typing): buttons 0 .. 3
   edit the settings' fields, 4 starts the game when ready (else message 5 and the refusal sound), 5 (or a right click)
   leaves. Returns what the original leaves in eax */
u32 (room_openClicks)(void)
{
	int mode = g_roomMode;
	if (mode == 1 || mode == 0 || g_roomAwaitingServer == 1)
		return (u32)mode;
	if (g_dialogOpen)
		return (u32)g_dialogOpen;
	if (g_paused)
		return (*(u32 *)&g_paused);
	if (!g_keyEnter) {
		if (!g_mouseClick)
			return 0;
		u32 button = GAME_FN(account_hitTest, 0x4322c0, u32, int, int)(g_mouseX, g_mouseY);   /* the room's hit test */
		switch (button) {
		case 0: return GAME_FN(account_editOldPassword, 0x434020, u32, void)();
		case 1: return GAME_FN(account_editPassword, 0x4340e0, u32, void)();
		case 2: return GAME_FN(account_editPasswordRepeat, 0x4341a0, u32, void)();
		case 3: return GAME_FN(account_editEmail, 0x434260, u32, void)();
		case 4:
			if (GAME_FN(account_sendChange, 0x434b90, u32, void)() == 1)
				break;
			menu_showMessage(5);
			return sound(6);
		case 5:
			break;
		default:
			return button;
		}
	}
	u32 r = sound(0);
	g_roomMode = 0;
	return r;
}

/* 0x43ed20: the game room drawn (its background first): while open and not leaving (state 99), the dialog's frame if
   one is open, else the room settings kept in range (players 0 .. 16 else 8, the frag limit at most 50 and the time
   at most 60 else 30, the map 0 .. 11 else 0), the settings panel, the map list when open, the options when shown.
   Returns what the original leaves in eax */
u32 (room_draw)(void)
{
	GAME_FN(room_drawTunnel, 0x4388e0, u32, void)();   /* room_drawTunnel */
	int mode = g_roomMode;
	if (mode == 1 || mode == 0 || g_roomState == 0x63)
		return (u32)mode;
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(g_roomFormLeft, g_roomFormTop,
		                                                     g_roomFormRight, g_roomFormBottom);   /* menu_drawFrame */
	signed char players = (*(signed char *)&g_roomRecPlayers);
	if (players < 0 || players > 0x10)
		g_roomRecPlayers = 8;
	if (g_roomRecFragLimit > 0x32)
		g_roomRecFragLimit = 0x1e;
	if (g_roomRecTimeLimit > 0x3c)
		g_roomRecTimeLimit = 0x1e;
	signed char map = (*(signed char *)&g_roomRecGameMode);
	if (map < 0 || map > 0xb)
		g_roomRecGameMode = 0;
	GAME_FN(room_drawGameSettings, 0x43bfe0, u32, void)();   /* room_drawGameSettings */
	if (g_mapListOpen == 1)
		GAME_FN(mapList_draw, 0x4038e0, u32, void)();   /* mapList_draw: the map list */
	if (!g_connectionAwaited)
		return 0;
	return GAME_FN(room_hostingStep, 0x4355b0, u32, void)();   /* room_hostingStep */
}

/* 0x433c70: the chat edit control closed (the window focused again, the line sent): typed into the room's name
   (0x9dd1cc set: up to 30 bytes at 0x9dd1d8) or its password (0x9dd6b0: 12 bytes at 0x9dd1f6, the stars off).
   Returns what the original leaves in eax */
u32 (chat_closeEdit)(void)
{
	IMPORT(0x4a9344, u32, void *)(g_hChatEdit);   /* DestroyWindow */
	IMPORT(0x4a935c, void *, void *)(g_hWndMain);               /* SetFocus */
	GAME_FN(chat_closeLine, 0x431600, u32, int)(1);                           /* chat_closeLine: the line sent */
	if (g_typingRoomName == 1) {
		memset((void *)OBJ(g_accountName), 0, 30);
		g_typingRoomName = 0;
		strcpy(g_accountName, g_chatLine);
		return 0;
	}
	if (g_typingRoomPassword == 1) {
		memset((void *)OBJ(g_accountPassword), 0, 12);
		g_chatFieldFlag = 0;
		strcpy(g_accountPassword, g_chatLine);
		g_typingRoomPassword = 0;
		return 0;
	}
	return (*(u32 *)&g_typingRoomName);
}

/* the dialog's button choice (g_dialogChoice) highlighted at (x, y) */
static void highlight_choice(int choice, int x, int y)
{
	g_dialogChoice = choice;
	g_highlightShown = 1;
	(*(u32 *)&g_highlightSize) = 0x41a00000;   /* g_highlightSize 20 */
	(*(u32 *)&g_highlightAlpha) = 0x3ecccccd;   /* g_highlightAlpha 0.4 */
	g_highlightX = x;
	g_highlightY = y;
}

/* 0x43df80: the create-game dialog (its panel at 0x9dd358): a password to retype (0x9dced0: the settings back and
   the password opened again), the login to send (0x9dd198); once typing has ended (g_paused clear), the line taken
   into the game's name (0x9dd830; 30 bytes at 0x9dd1d8) or password (0x9dd38c; 12 at 0x9dd1f6) and the key that
   ended it (0x9dc428: 10 back, 20 on) moving to the other field or the dialog's buttons; else the server's answer
   to the request (0xa0b378, awaited: 0x9dd838): 33 accepted (state 99, the settings written and taken), 42 done
   (0x9dd850), 31 / 32 / 34 a message (31 / 32 / 35), anything else message 42 */
void (createDialog_draw)(void)
{
#define g_editKey g_fieldTabKey
	if (g_retypePassword) {
		room_copyJoinedSettings();
		field_editGamePassword();
		g_retypePassword = 0;
		return;
	}
	if (g_loginToSend == 1) {
		chat_closeEdit();
		login_send();
		g_loginToSend = 0;
		return;
	}
	if (g_typingGameName) {
		if (g_paused)
			return;
		g_typingGameName = 0;
		memset((void *)OBJ(g_accountName), 0, 30);
		strcpy(g_accountName, g_chatLine);
		if (g_editKey == 10) {
			highlight_choice(3, g_roomLoginLeft + 0x1a2, g_roomLoginBottom - 0x30);
			g_typingRoomName = 0;
			g_editKey = 0;
		} else if (g_editKey == 20) {
			g_typingRoomName = 0;
			field_editGamePassword();
			g_typingRoomPassword = 1;
			g_chatFieldFlag = 1;
			g_editKey = 0;
		}
		return;
	}
	if (g_typingGamePassword) {
		if (g_paused)
			return;
		memset((void *)OBJ(g_accountPassword), 0, 12);
		g_typingGamePassword = 0;
		strcpy(g_accountPassword, g_chatLine);
		g_chatFieldFlag = 0;
		if (g_editKey == 10) {
			g_typingRoomName = 1;
			g_typingRoomPassword = 0;
			field_editGameName();
			g_editKey = 0;
		} else if (g_editKey == 20) {
			highlight_choice(1, g_roomLoginLeft + 0x62, g_roomLoginBottom - 0x30);
			g_typingRoomName = 0;
			g_typingRoomPassword = 0;
			g_editKey = 0;
		}
		return;
	}
	if (!g_roomRequestOut)
		return;
	u32 answer = (*(u32 *)&g_gameServerAnswer);
	if (answer == 0)
		return;
	g_roomRequestOut = 0;
	if (answer == 0x21) {
		g_roomState = 99;
		reg_writeCharacterSettings();
		room_takeReceivedSettings();
	} else if (answer == 0x2a)
		g_roomLeaveDialog = 1;
	else if (answer == 0x1f || answer == 0x20)
		menu_showMessage(answer);
	else if (answer == 0x22)
		menu_showMessage(0x23);
	else
		menu_showMessage(0x2a);
	g_gameServerAnswer = 0;
	g_roomLoginDue = 0;
#undef g_editKey
}

/* 0x43e290: the login form (its panel at 0x9dd6e8): the name opened when asked (0x9dd4a0); with no message box
   (0x4df900) and typing ended, the line taken into the field being typed in (the first of the four flagged 1) and
   the key that ended it (0x9dc428: 20 on, 10 back) moving to the next or previous field; on from the e-mail
   highlights the right button, back from the name the left one (the name's flag left set). Then the flagged field
   opened again for typing (the password's before the repeat's) */
void (loginForm_update)(void)
{
	static const struct { u32 editing, text; int size; } field[4] = {
		{ ADDR(g_typingAccountName), OBJ(g_accountName), 30 }, { ADDR(g_typingAccountPassword), OBJ(g_accountPassword), 12 }, { ADDR(g_typingAccountRepeat), OBJ(g_accountPasswordRepeat), 12 }, { ADDR(g_typingAccountEmail), OBJ(g_accountEmail), 50 } };
#define EDITING(k) GAME_VAR(int, field[k].editing)
	if (g_openLoginName) {
		loginForm_openField(0);
		g_openLoginName = 0;
		return;
	}
	if (g_dialogPending || g_paused)
		return;
	int key = g_fieldTabKey;
	if (key == 20 || key == 10) {
		int k = 0;
		while (k < 4 && EDITING(k) != 1)
			k++;
		if (k < 4) {
			memset((void *)RELOC(field[k].text), 0, field[k].size);
			strcpy((char *)RELOC(field[k].text), g_chatLine);
			if (key == 10 && k == 0)
				highlight_choice(2, g_loginFormLeft + 0x172, g_loginFormBottom - 0x2c);
			else {
				EDITING(k) = 0;
				if (key == 10)
					EDITING(k - 1) = 1;
				else if (k < 3)
					EDITING(k + 1) = 1;
				else {
					EDITING(0) = 0;
					highlight_choice(1, g_loginFormLeft + 0xaa, g_loginFormBottom - 0x2c);
				}
			}
		}
		g_fieldTabKey = 0;
	}
	if (EDITING(0) == 1) {
		loginForm_openField(0);
		return;
	}
	if (EDITING(1) == 1)
		loginForm_openField(1);
	if (EDITING(2) == 1) {
		loginForm_openField(2);
		return;
	}
	if (EDITING(3) == 1)
		loginForm_openField(3);
#undef EDITING
}

/* 0x43e610: the game room's network events: a pending leave (0x9dd6c4: 1 leave now, 2 to state 0x4d), then the
   server's answer (0xa0b37c, when awaited: 0x9dd6a4): 33 accepted (the ladder game set up, the settings written, to
   state 99), 30 message 0x22, 42 a message box, anything else message 0x2a. Returns what the original leaves in eax */
u32 (room_networkEvents)(void)
{
	u32 r = (*(u32 *)&g_roomPopup) - 2;   /* (what the original's compare chain leaves) */
	if (g_roomPopup == 1) {
		r = GAME_FN(room_host, 0x434820, u32, void)();   /* room_host */
		g_roomPopup = 0;
	} else if (g_roomPopup == 2) {
		r = 0;
		g_roomState = 0x4d;
		g_roomPopup = 0;
	}
	if (!g_roomAnswerAwaited)
		return r;
	u32 answer = (*(u32 *)&g_gameServerAnswer15);
	switch (answer) {
	case 0:
		return 0;
	case 33:
		g_roomState = 0x63;
		g_roomRequestOut = 0;
		GAME_FN(lobby_ladderGameName, 0x432620, u32, void)();   /* lobby_ladderGameName */
		r = GAME_FN(reg_writeCharacterSettings, 0x432400, u32, void)();   /* reg_writeCharacterSettings */
		g_gameServerAnswer15 = 0;
		g_roomConnected = 1;
		return r;
	case 30:
		g_roomRequestOut = 0;
		r = GAME_FN(menu_showMessage, 0x41ee40, u32, int)(0x22);
		g_gameServerAnswer15 = 0;
		return r;
	case 42:
		g_roomRequestOut = 0;
		g_gameServerAnswer15 = 0;
		g_roomLeaveDialog = 1;
		return answer;
	}
	g_roomRequestOut = 0;
	r = GAME_FN(menu_showMessage, 0x41ee40, u32, int)(0x2a);
	g_gameServerAnswer15 = 0;
	return r;
}

/* 0x437810: the room list's keys while its password box is up (0x9dd6b8): one key cancels it (the list's page and
   mode put back), another cancels it or, without it, leaves the screen; a third leaves the screen. Returns what the
   original leaves in eax */
u32 (roomList_passwordKeys)(void)
{
	u32 r;
	if (input_justPressed(g_dikS)) {
		if (!g_rankingWaiting)
			return 0;
		r = sound(0);
		g_rankingWaiting = 0;
		g_roomListWaiting = 0;
		g_roomListPage = g_roomListPrevPage;
		g_rankingSort = g_roomListPrev;
		g_rankingHaveList = 1;
		return r;
	}
	if (input_justPressed(g_dikC)) {
		if (g_rankingWaiting)
			return (*(u32 *)&g_rankingWaiting);
		r = sound(0);
		g_rankingWaiting = 0;
		g_rankingHaveList = 0;
		g_roomListWaiting = 0;
		g_roomMode = 0;
		return r;
	}
	if (!input_justPressed(g_dikEscape_2))
		return 0;
	if (g_rankingWaiting)
		return (*(u32 *)&g_rankingWaiting);
	r = sound(0);
	g_roomMode = 0;
	return r;
}

/* 0x4334c0: the request to join the selected room sent: the room's password and state cleared, the room screen at
   state 0 (open, brightness 0.7), the room's name (0x9dd570, 30 bytes) as message 0x1d; then the confirm box up.
   Returns net_send's eax */
u32 (room_requestJoin)(void)
{
	static const u32 cleared[] = { OBJ(g_accountPasswordRepeat), OBJ(g_accountPassword), (OBJ(g_accountPasswordRepeat) + 0x4), OBJ(g_accountOldPassword), (OBJ(g_accountPassword) + 0x4), (OBJ(g_accountPasswordRepeat) + 0x8), (OBJ(g_accountOldPassword) + 0x4), ADDR(g_roomState) };
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	g_roomMode = 1;
	g_roomPanelBrightness = 0x3f333333;
	static const u32 cleared2[] = { ADDR(g_editingOldPassword), ADDR(g_editingAccountPassword), ADDR(g_editingPasswordRepeat), ADDR(g_editingEmail), IMG(0x9dd6d0), (OBJ(g_accountPassword) + 0x8), (OBJ(g_accountOldPassword) + 0x8) };
	for (unsigned k = 0; k < sizeof cleared2 / sizeof cleared2[0]; k++)
		GAME_VAR(int, cleared2[k]) = 0;
	char *message = g_netJoinMessage;
	memset(message, 0, 30);
	strcpy(message, g_joinedTitleName);
	u32 r = net_send(0x1d, 0x65);
	g_accountNotice = 0;
	g_roomAwaitingServer = 1;
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
   MSG(341, "CREATE NEW ID"), four labelled lines (MSG(342, "INPUT ID"), 0x80 apart) with underlines, the values (the name 0x9dd1d8, the two
   passwords 0x9dd1f6 / 0x9dd202 as stars, 0x9dd20e), each left out while its field is being typed in (0x9dd348 /
   0x9dd3f8 / 0x9dd564 / 0x9dd6cc, with the keys taken), the two buttons (the one under the pointer, 4 / 5 by
   FUN_00432240, bright) and the border. Returns the frame's or the border's eax */
u32 (loginDialog_draw)(void)
{
#define X0 g_loginFormLeft
#define Y0 GAME_VAR(int, 0x9dd6ec)
#define X1 GAME_VAR(int, 0x9dd6f0)
#define Y1 g_loginFormBottom
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the frame */
	const u32 *bright = g_roomBright, *dim = g_roomDim;
	int hovered = GAME_FN(loginForm_hitTest, 0x432240, int, int, int)(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x40, Y0 + 0x10, (const char *)MSG(341, "CREATE NEW ID"));
	set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
	for (int k = 0; k < 4; k++) {
		text_draw8(X0 + 0x30, Y0 + k * 0x30 + 0x3c, (const char *)(MSG(342, "INPUT ID") + k * 0x80));
		menu_drawLine(X0 + 0x84, Y0 + k * 0x30 + 0x50, X0 + 0x200, Y0 + k * 0x30 + 0x50);
	}
	char hidden[64];   /* (30 bytes cleared, as the original's buffer) */
	if (!g_typingAccountName || !g_paused)
		text_draw8(X0 + 0x94, Y0 + 0x3c, g_accountName);
	if (!g_typingAccountPassword || !g_paused) {
		stars(hidden, sizeof hidden, g_accountPassword);
		text_draw8(X0 + 0x94, Y0 + 0x6c, hidden);
	}
	if (!g_typingAccountRepeat || !g_paused) {
		stars(hidden, sizeof hidden, g_accountPasswordRepeat);
		text_draw8(X0 + 0x94, Y0 + 0x9c, hidden);
	}
	if (!g_typingAccountEmail || !g_paused)
		text_draw8(X0 + 0x94, Y0 + 0xcc, g_accountEmail);
	for (int k = 0; k < 2; k++) {
		int x = k * 0xc8;
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		const u32 *colour = hovered == k + 4 ? bright : dim;
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k + 4 ? 1.0f : 0.4f);
		profile_drawButton(X0 + x + 0x5a, Y1 - 0x40, X0 + x + 0xfa, Y1 - 0x20, 1);
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(X0 + x + 0x5a, Y1 - 0x38, X0 + x + 0xfa, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawCornerOrnaments, 0x428a00, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* the confirmation over a room dialog (0x9dd850): the screen dimmed, a box with two lines (0x74dfa4, 0x74e024) and
   its two buttons (MSG(115, "$[0] O K"); the one under the pointer, by leaveDialog_hitTest, in cyan) */
static void confirm_box(void)
{
	int hovered = leaveDialog_hitTest(g_mouseX, g_mouseY);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f000000);   /* 0.1, 0.1, 0.1, 0.5 */
	menu_drawRect(0, 0, 0x280, 0x1e0, 1);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f4ccccd);   /* 0.1, 0.1, 0.1, 0.8 */
	menu_drawRect(0x64, 0xb4, 0x21c, 0x140, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(0x68, 0xb8, 0x218, 0x13c, 0);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_drawBox16(0x64, 0xc8, 0x21c, (const char *)MSG(3, "THIS PROGRAM HAS BEEN UPDATED"));
	text_drawBox16(0x64, 0xdc, 0x21c, (const char *)MSG(4, "DO DOWNLOAD A NEW VERSION"));
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int x = 0xb4 + k * 0xa0;
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k ? 1.0f : 0.4f);
		menu_drawWideButton(x, 0x104, x + 0x78, 0x124, 1);
		if (hovered == k)
			set_colour_bits(g_textColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		else
			set_colour_bits(g_textColour, 0x3e99999a, 0x3f333333, 0x3f333333, 0x3f800000);   /* 0.3, 0.7, 0.7, 1 */
		text_drawBox16(x, 0x10c, x + 0x78, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
}

/* 0x439e00: the room's server dialog (0x9dd1a0 .. 0x9dd1ac; only its frame while a message box is open): the title
   MSG(351, "CREATE NEW ID"), a rule, the server name 0x9dd1d8 in a green-framed box, the note MSG(352, "NEW ID ON REGISTRATION"), two buttons (MSG(354, "$[0] O K"), 0x80
   apart; the one under the pointer by popup_hitTest bright), the confirmation (0x9dd850) and the border. Returns the
   frame's or the border's eax */
u32 (serverDialog_draw)(void)
{
#define X0 GAME_VAR(int, 0x9dd1a0)
#define Y0 GAME_VAR(int, 0x9dd1a4)
#define X1 GAME_VAR(int, 0x9dd1a8)
#define Y1 GAME_VAR(int, 0x9dd1ac)
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* menu_drawFrame */
	const u32 *bright = g_roomBright, *dim = g_roomDim;
	int hovered = popup_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTextureFlipped(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)MSG(351, "CREATE NEW ID"));
	set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x20, Y0 + 0x20, X1 - 0x20, Y0 + 0x20);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f800000);   /* 0.1, 0.1, 0.1, 1 */
	menu_drawRect(X0 + 0x30, Y0 + 0x40, X1 - 0x30, Y0 + 0x60, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0, 0x3f800000);
	menu_drawRect(X0 + 0x30, Y0 + 0x40, X1 - 0x30, Y0 + 0x60, 0);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
	text_drawBox16(X0 + 0x30, Y0 + 0x48, X1 - 0x30, g_accountName);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_drawBox16(X0, Y0 + 0x8c, X1, (const char *)MSG(352, "NEW ID ON REGISTRATION"));
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k ? 1.0f : 0.4f);
		int x = X0 + k * 0xb4;
		menu_drawWideButton(x + 0x64, Y1 - 0x40, x + 0xdc, Y1 - 0x20, 1);
		const u32 *colour = hovered == k ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x64, Y1 - 0x38, x + 0xdc, (const char *)(MSG(354, "$[0] O K") + k * 0x80));
	}
	if (g_roomLeaveDialog)
		confirm_box();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawTopRightOrnament, 0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x4392c0: the room login dialog (0x9dd358 .. 0x9dd364; only its frame while a message box is open): the title
   MSG(331, "LADDER GAME ID MANAGER") and its rule, two labelled dark boxes (MSG(332, "YOUR ID"), 0x80 apart) with the name 0x9dd1d8 and the password
   0x9dd1f6 as stars (each left out while it is being typed in: 0x9dd830 / 0x9dd38c), three buttons (MSG(334, "LOG$[0] IN"); the
   one under the pointer, 2 .. 4 by createDialog_hitTest, bright unless connecting), while connecting (0x9dd838) a box with
   two lines (MSG(49, "CHECKING YOUR ID. PLEASE WAIT."), MSG(50, "PRESS ESC-KEY TO CANCEL")), the confirmation (0x9dd850) and the border. Returns the frame's or the border's
   eax */
u32 (roomLogin_draw)(void)
{
#define X0 g_roomLoginLeft
#define Y0 g_roomLoginTop
#define X1 GAME_VAR(int, 0x9dd360)
#define Y1 g_roomLoginBottom
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* menu_drawFrame */
	const u32 *bright = g_roomBright, *dim = g_roomDim;
	int hovered = createDialog_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x40, Y0 + 0x10, (const char *)MSG(331, "LADDER GAME ID MANAGER"));
	set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
	menu_drawLine(X0 + 0x40, Y0 + 0x24, X1 - 0x40, Y0 + 0x24);
	for (int k = 0; k < 2; k++) {
		int y = Y0 + k * 0x30;
		text_draw16(X0 + 0x40, y + 0x58, (const char *)(MSG(332, "YOUR ID") + k * 0x80));
		set_colour_bits(g_rectColour, 0, 0, 0, 0x3f000000);
		menu_drawRect(X0 + 0xb8, y + 0x50, X0 + 0x1a8, y + 0x70, 1);
		set_colour_bits(g_rectColour, bright[0], bright[1], bright[2], bright[3]);
		menu_drawRect(X0 + 0xb8, y + 0x50, X0 + 0x1a8, y + 0x70, 0);
	}
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	if (!g_typingGameName)
		text_draw8(X0 + 0xc8, Y0 + 0x58, g_accountName);
	if (!g_typingGamePassword) {
		char hidden[30];
		stars(hidden, sizeof hidden, g_accountPassword);
		text_draw8(X0 + 0xc8, Y0 + 0x88, hidden);
	}
	for (int k = 0; k < 3; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 2 && !g_roomRequestOut;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0xa0;
		menu_drawWideButton(x + 0x30, Y1 - 0x40, x + 0xa8, Y1 - 0x20, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x30, Y1 - 0x38, x + 0xa8, (const char *)(MSG(334, "LOG$[0] IN") + k * 0x80));
	}
	if (g_roomRequestOut) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
		menu_drawRect(0x64, 0xc8, 0x21c, 0x140, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x69, 0xdc, 0x217, (const char *)MSG(49, "CHECKING YOUR ID. PLEASE WAIT."));
		text_drawBox16(0x69, 0xf4, 0x217, (const char *)MSG(50, "PRESS ESC-KEY TO CANCEL"));
	}
	if (g_roomLeaveDialog)
		confirm_box();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawCornerOrnaments, 0x428a00, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* a rank's badge (rank 1 .. : cell rank - 1 of the 10-wide grid of the font texture 0x76d448, bound) 24 x 16 at
   (x, y) */
static void rank_badge(int rank, int x, int y)
{
	const float *col_w = k_0_09375f, *row_h = k_0_0625f;
	int cell = rank - 1;
	float u0 = f32(fmul_m((long double)(cell % 10), col_w));
	float v0 = f32(fadd_m(fmul_m((long double)(cell / 10), row_h), k_0_875f));
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
   box with two lines (MSG(423, "DOWNLOADING RANKING DATA"), MSG(50, "PRESS ESC-KEY TO CANCEL")). The title MSG(361, "USER INFOMATION"), five labels for the fields (MSG(362, "USER ID"), 0x80 apart) and
   seven for the record (MSG(367, "LEVEL")); four dark boxes with the name 0x9dd1d8, three passwords as stars (0x9dd6d8,
   0x9dd1f6, 0x9dd202; each left out while it is being typed in: 0x9dd69c / 0x9dd37c / 0x9dd378) and 0x9dd20e (left
   out while 0x9dd304); the level 0x9dd5d8 with its rank badge (cell (level - 1) % 10, / 10 of the texture 0x76d448),
   the clan 0x9dd248 (MSG(374, "OUT OF RANK(1000)") when none), two ratios ("%.2f": 0x9dd5e4, 0x9dd5f4) and three counts (0x9dd5ec,
   0x9dd5f0, 0x9dd5dc); two buttons (MSG(115, "$[0] O K"); 4 / 5 under the pointer by account_hitTest, lit unless 0x68039c), a
   rule and the border. The original leaves eax to callers that ignore it */
void (account_drawPanel)(void)
{
#define X0 g_accountPanelLeft
#define Y0 g_accountPanelTop
#define X1 g_accountPanelRight
#define Y1 g_accountPanelBottom
#define K(addr) ((const float *)RELOC(addr))
	const u32 *bright = g_roomBright, *dim = g_roomDim;
	int hovered = GAME_FN(account_hitTest, 0x4322c0, int, int, int)(g_mouseX, g_mouseY);   /* account_hitTest */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	if (g_roomAwaitingServer == 1) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
		menu_drawRect(0x50, 0xc8, 0x230, 0x118, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x50, 0xdc, 0x230, (const char *)MSG(423, "DOWNLOADING RANKING DATA"));
		text_drawBox16(0x50, 0xf0, 0x230, (const char *)MSG(50, "PRESS ESC-KEY TO CANCEL"));
		return;
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)MSG(361, "USER INFOMATION"));
	for (int k = 0; k < 5; k++)
		text_draw8(X0 + 0x20, Y0 + k * 0x1c + 0x34, (const char *)(MSG(362, "USER ID") + k * 0x80));
	for (int k = 0; k < 7; k++)
		text_draw8(X0 + 0x20, Y0 + k * 0x18 + 0xbe, (const char *)(MSG(367, "LEVEL") + k * 0x80));
	text_draw8(X0 + 0x98, Y0 + 0x38, g_accountName);
	for (int k = 0; k < 4; k++) {
		int y = Y0 + k * 0x1c;
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f800000);   /* 0.1, 0.1, 0.1, 1 */
		menu_drawRect(X0 + 0x8e, y + 0x4e, X1 - 0x20, y + 0x64, 1);
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0, 0x3f800000);
		menu_drawRect(X0 + 0x8e, y + 0x4e, X1 - 0x20, y + 0x64, 0);
	}
	char text[20];
	static const struct { u32 typing, password; int y; } hidden[3] = {
		{ ADDR(g_editingOldPassword), OBJ(g_accountOldPassword), 0x50 }, { ADDR(g_editingAccountPassword), OBJ(g_accountPassword), 0x6c }, { ADDR(g_editingPasswordRepeat), OBJ(g_accountPasswordRepeat), 0x88 },
	};
	for (int k = 0; k < 3; k++)
		if (!GAME_VAR(int, hidden[k].typing)) {
			stars(text, sizeof text, (const char *)hidden[k].password);
			text_draw8(X0 + 0x98, Y0 + hidden[k].y, text);
		}
	if (!g_editingEmail)
		text_draw8(X0 + 0x98, Y0 + 0xa4, g_accountEmail);
	itoa(g_pilotLevel, text, 10);
	text_draw8(X0 + 0x98, Y0 + 0xbe, text);
	/* the rank badge */
	glEnable(GL_TEXTURE_2D);
	int texture = g_fontAscii;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	rank_badge(g_pilotLevel, X0 + 0xc0, Y0 + 0xbe);
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
	menu_drawRect(X0 + 0xc1, Y0 + 0xbe, X0 + 0xd8, Y0 + 0xce, 0);
	/* the record */
	if (!g_accountClan)
		text_draw8(X0 + 0x98, Y0 + 0xd6, (const char *)MSG(374, "OUT OF RANK(1000)"));
	else {
		itoa(g_accountClan, text, 10);
		text_draw8(X0 + 0x98, Y0 + 0xd6, text);
	}
	sprintf(text, (const char *)STR(0x4b0268, "%.2f"), (double)(*(float *)&g_pilotRating));
	text_draw8(X0 + 0x98, Y0 + 0xee, text);
	sprintf(text, (const char *)STR(0x4b0268, "%.2f"), (double)g_pilotWinRate);
	text_draw8(X0 + 0x98, Y0 + 0x106, text);
	static const u32 counts[3] = { ADDR(g_pilotWins), ADDR(g_pilotLosses), ADDR(g_pilotPoints) };
	for (int k = 0; k < 3; k++) {
		itoa(GAME_VAR(int, counts[k]), text, 10);
		text_draw8(X0 + 0x98, Y0 + 0x11e + k * 0x18, text);
	}
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 4 && !g_paused;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0xa0;
		menu_drawWideButton(x + 0x7d, Y1 - 0x30, x + 0xf5, Y1 - 0x10, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x7d, Y1 - 0x28, x + 0xf5, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y1 - 0x40, X1 - 0x10, Y1 - 0x40);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
#undef K
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x43d060: the ranking table (0x9dced8 .. 0x9dcee4): the title 0x75aba4; the page arrows (0 / 1 under the pointer,
   by ranking_hitTest, lit) about "first ~ last" of page 0x9dd6ac (stored in 0x9dd83c / 0x9dd7dc); the sort button
   (MSG(412, "OPTION"); 2) with the sorted column's name; two rules and the column heads (MSG(413, "RANK") .., the sorted one in
   yellow); when there is a list (0x9dd3b0) up to ten 0x44-byte rows (the name at 0x9dcef4, its rank at -4) until an
   empty name (which stores the page in 0x9dd4b8): rank, name, rank badge (+0x32) in a yellow frame, "%8.1f" (+0x36),
   "%3.2f" (+0x2e) and three counts (+0x26, +0x2a, +0x1e), the sorted value in yellow; a rule, two buttons
   (MSG(421, "$[0] STOP"); 3 / 4, the first dead until the list is loaded, 0x9dd6b8); while loading the blinking MSG(423, "DOWNLOADING RANKING DATA"); the
   border. Returns the border's eax */
u32 (ranking_drawTable)(void)
{
#define X0 GAME_VAR(int, 0x9dced8)
#define Y0 GAME_VAR(int, 0x9dcedc)
#define X1 GAME_VAR(int, 0x9dcee0)
#define Y1 GAME_VAR(int, 0x9dcee4)
#define TEXT(c) set_colour_bits(g_textColour, (c)[0], (c)[1], (c)[2], (c)[3])
	const u32 *bright = g_roomBright, *dim = g_roomDim;
	static const u32 white[4] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
	static const u32 yellow[4] = { 0x3f800000, 0x3f800000, 0, 0x3f800000 };
	int hovered = GAME_FN(ranking_hitTest, 0x4323c0, int, int, int)(g_mouseX, g_mouseY);   /* ranking_hitTest */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	TEXT(bright);
	text_draw16(X0 + 0x10, Y0 + 0x10, (const char *)MSG(411, "LADDER GAME RANKING"));
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton1(X0 + 0xb0, Y0 + 0x26, X0 + 0xe4, Y0 + 0x3e, hovered == 0);
	menu_drawSmallButton2(X0 + 0x146, Y0 + 0x26, X0 + 0x17a, Y0 + 0x3e, hovered != 0 && hovered == 1);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	char page[64], last[64];
	int first = g_roomListPage * 10 + 1;
	g_rankingFirst = first;
	g_rankingLast = (g_roomListPage * 5 + 5) * 2;
	itoa(first, page, 10);
	itoa(g_rankingLast, last, 10);
	strcat(page, (const char *)STR(0x4b278c, " ~ "));
	strcat(page, last);
	menu_drawWideButton(X0 + 0xe6, Y0 + 0x24, X0 + 0x146, Y0 + 0x40, 1);
	text_draw8b(X0 + 0xe6, Y0 + 0x2a, X0 + 0x146, page);
	text_drawBox16(X1 - 0x78, Y0 + 0x10, X1 - 0x14, (const char *)MSG(412, "OPTION"));
	glEnable(GL_TEXTURE_2D);
	texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, hovered == 2 ? 1.0f : 0.6f);
	menu_drawWideButton(X1 - 0x78, Y0 + 0x24, X1 - 0x14, Y0 + 0x40, 1);
	TEXT(yellow);
	static const u32 sorted_by[4] = { MSG(416, "POWER"), MSG(418, "KILL"), MSG(420, "EXP"), MSG(417, "RATE") };
	if ((unsigned)g_rankingSort <= 3)
		text_draw8b(X1 - 0x78, Y0 + 0x2a, X1 - 0x14, (const char *)RELOC(sorted_by[g_rankingSort]));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x4a, X1 - 0x10, Y0 + 0x4a);
	menu_drawLine(X0 + 0x10, Y0 + 0x6e, X1 - 0x10, Y0 + 0x6e);
	/* the column heads, the numbers' right-aligned (8 a character) */
	TEXT(bright);
	text_draw8(X0 + 0x18, Y0 + 0x52, (const char *)MSG(413, "RANK"));
	text_draw8(X0 + 0x48, Y0 + 0x52, (const char *)MSG(414, "ID"));
	text_draw8(X0 - (int)strlen((const char *)MSG(415, "GRADE")) * 8 + 0xec, Y0 + 0x52, (const char *)MSG(415, "GRADE"));
	static const struct { u32 text; int right, sort; } heads[5] = {
		{ MSG(416, "POWER"), 0x12c, 0 }, { MSG(417, "RATE"), 0x2d * 8, 3 }, { MSG(418, "KILL"), 0x35 * 8, 1 }, { MSG(419, "DEATH"), 0x3c * 8, -1 },
		{ MSG(420, "EXP"), 0x226, 2 },
	};
	for (int c = 0; c < 5; c++) {
		int x = heads[c].right - (int)strlen((const char *)heads[c].text) * 8;
		if (heads[c].sort >= 0 && g_rankingSort == heads[c].sort)
			TEXT(yellow);
		else
			TEXT(bright);
		text_draw8(X0 + x + 0x18, Y0 + 0x52, (const char *)heads[c].text);
	}
	TEXT(white);
	if (g_rankingHaveList) {
		char text[64];
		for (int i = 0; i < 10; i++) {
			const u8 *row = (const u8 *)IMG(0x9dcef4) + i * 0x44;
#define ROW(type, offset) (*(const type *)(row + (offset)))
			if (!*row) {
				g_roomListPages = g_roomListPage;
				break;
			}
			int y = Y0 + i * 0x16 + 0x78;
			TEXT(white);
			itoa(ROW(int, -4), text, 10);
			text_draw8(X0 + 0x18, y, text);
			text_draw8(X0 + 0x48, y, (const char *)row);
			glEnable(GL_TEXTURE_2D);
			texture = g_fontAscii;
			tex_bind(g_textures->managers[texture / 512], texture % 512);
			rank_badge(ROW(int, 0x32), X0 + 0xd2, y);
			glDisable(GL_TEXTURE_2D);
			set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
			menu_drawRect(X0 + 0xd3, y + 1, X0 + 0xea, y + 0x10, 0);
			TEXT(white);
			if (g_rankingSort == 0)
				TEXT(yellow);
			sprintf(text, (const char *)STR(0x4b2784, "%8.1f"), (double)ROW(float, 0x36));
			text_draw8(X0 - (int)strlen(text) * 8 + 0x144, y, text);
			TEXT(white);
			if (g_rankingSort == 3)
				TEXT(yellow);
			sprintf(text, (const char *)STR(0x4b277c, "%3.2f"), (double)ROW(float, 0x2e));
			text_draw8(X0 + (0x30 - (int)strlen(text)) * 8, y, text);
			TEXT(white);
			if (g_rankingSort == 1)
				TEXT(yellow);
			itoa(ROW(int, 0x26), text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x1bc, y, text);
			TEXT(white);
			itoa(ROW(int, 0x2a), text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x1f4, y, text);
			TEXT(white);
			if (g_rankingSort == 2)
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
		texture = g_buttonTexture;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 3 && !(hovered == 3 && !g_rankingWaiting);
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0xc8;
		menu_drawWideButton(x + 0x7d, Y1 - 0x30, x + 0x11d, Y1 - 0x10, 1);
		if (lit)
			TEXT(bright);
		else
			TEXT(dim);
		text_drawBox16(x + 0x7d, Y1 - 0x28, x + 0x11d, (const char *)(MSG(421, "$[0] STOP") + k * 0x80));
	}
	if (g_rankingWaiting) {   /* loading: blinking in ten steps */
		int step = ftol(fmul_m(fld_m((const float *)ADDR(g_lobbyBlinkClock)), k_0_333333f)) % 10;
		float alpha = f32(fsubr_m(fmul_m((long double)step, (const float *)ADDR(k_tenthsToDegrees)), (const float *)ADDR(k_1f)));
		set_colour_bits(g_textColour, 0, 0x3f800000, 0, BITS(alpha));
		text_drawBox16(X0, Y0 + 0xc8, X1, (const char *)MSG(423, "DOWNLOADING RANKING DATA"));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawCornerOrnaments, 0x428a00, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef TEXT
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* the create-game dialog closed, back to the room's page 99 (keys blocked, the room's state 300) */
static void creategame_close(void)
{
	input_setKeysBlocked(4);
	g_roomState = 99;
	g_nextScreen = 300;
	GAME_FN(debug_traceStripped, 0x48b420, void, void)();   /* debug_traceStripped */
}

/* 0x436990: the create-game dialog's keys. While its request is out (0x9dd838) or the login is due (0x9dd1c8)
   only cancel2 answers, closing the dialog (the answer dropped) and the lobby connection. Otherwise a click on its
   buttons (createDialog_hitTest: 2 send, 3 close and disconnect, 4 room_openDialog4d), 0x4e14f4 send, back close, 0x4e150c
   room_openDialog4d (none of these while typing, g_paused); the toggle key moves the highlight (g_dialogChoice) on: from
   the name (1) to the password field (2), to the OK button (3), then into the name field for typing; with shift,
   back: from OK (3) to the password field, to the name, then into the password field for typing. The original
   leaves eax to callers that ignore it */
void (createDialog_keys)(void)
{
#define g_editKey g_fieldTabKey
	int dialogX = g_roomLoginLeft, dialogBottom = g_roomLoginBottom - 0x30;
	if (g_roomRequestOut || g_roomLoginDue) {
		if (input_justPressed(g_keyCancel2)) {
			g_roomRequestOut = 0;
			g_gameServerAnswer = 0;
			g_roomLoginDue = 0;
			g_chatFieldFlag = 0;
			g_paused = 0;
			creategame_close();
			g_highlightShown = 0;
			net_disconnect();
		}
		return;
	}
	if (input_justPressed(g_keyClick) == 1) {
		int on = createDialog_hitTest(g_mouseX, g_mouseY);
		if (on == 2) {
			if (g_roomLoginDue)
				return;
			sound_playMenu(0);
			g_highlightShown = 0;
			g_loginToSend = 1;
			g_roomLoginDue = 1;
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
			room_openDialog4d();
			return;
		}
	}
	if (input_justPressed(g_dikI) == 1) {
		if (g_paused || g_roomLoginDue)
			return;
		sound_playMenu(0);
		g_loginToSend = 1;
		g_roomLoginDue = 1;
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
	if (input_justPressed(g_dikN) == 1) {
		if (g_paused)
			return;
		sound_playMenu(0);
		room_openDialog4d();
		return;
	}
	if (input_justPressed(g_keyToggle) != 1)
		return;
	g_editKey = 20;
	int choice = g_dialogChoice;
	if (input_isDown(g_keyLeftShift) == 1 || input_isDown(g_keyRightShift) == 1) {
		g_editKey = 10;
		if (choice == 1) {
			highlight_choice(0, dialogX + 0x180, g_roomLoginTop + 0x88);
			field_editGamePassword();
			g_typingRoomPassword = 1;
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
			highlight_choice(3, dialogX + 0x180, g_roomLoginTop + 0x88);
			field_editGameName();
			g_editKey = 0;
			g_typingRoomName = 1;
			return;
		} else
			return;
	}
	g_editKey = 0;
#undef g_editKey
}

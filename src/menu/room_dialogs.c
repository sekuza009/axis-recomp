/* room_dialogs.c: the room screen's dialogs opened and its state reset: each dialog a box (left, top, right,
   bottom), its fields cleared, the screen's sub-state (g_roomState) set to the dialog's. */
#include "../game.h"
#include <string.h>


static void set_box(u32 box, int left, int top, int right, int bottom)
{
	int *b = (int *)RELOC(box);
	b[0] = left;
	b[1] = top;
	b[2] = right;
	b[3] = bottom;
}

/* the cursor, the picked field and the key repeat of a dialog cleared */
static void dialog_opened(int state)
{
	g_roomState = state;
	g_frameOpening = 1;
	g_typingLoginId = 0;
	g_typingLoginPassword = 0;
	g_inputLineHidden = 0;
	g_textFieldOpen = 0;
}

/* 0x433980: the new ID's confirmation (state 0x58 = 88) opened */
void (room_openNewIdConfirm)(void)
{
	set_box(OBJ(g_newIdConfirmBox), 0x50, 0x78, 0x230, 0x168);
	newIdConfirm_layout();
	dialog_opened(0x58);
	g_newIdConfirmChoice = 0;
}

/* 0x4338c0: the new-ID form (state 0x4d = 77) opened: its window laid out, the account fields emptied (0x54 bytes) */
void (room_openNewIdForm)(void)
{
	set_box(ADDR(g_newIdFormLeft), 0x1e, 0x32, 0x262, 0x1ae);
	newIdForm_layout();
	memset((void *)OBJ(g_accountName), 0, 0x54);
	dialog_opened(0x4d);
	g_openLoginName = 1;
	g_roomUpdateNotice = 0;
}

/* 0x434640: the Ladder login (state 0x42 = 66) opened, its ID field filled from g_ladderId */
void (room_openLogin)(void)
{
	static const u32 cleared[] = { ADDR(g_typingAccountName), ADDR(g_unusedLoginWord), ADDR(g_typingAccountPassword), ADDR(g_typingAccountRepeat), ADDR(g_typingAccountEmail), ADDR(g_inputLineHidden), ADDR(g_textFieldOpen) };
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	memset((void *)OBJ(g_accountName), 0, 7 * 4 + 2 + 12);
	g_roomState = 0x42;
	g_retypePassword = 1;
	strcpy(g_accountName, g_ladderId);
}

/* 0x433590: the game list page (state 1) entered: brightness 0.7, the list refreshed every 30 s, no panel (999), the
   rest cleared */
void (room_enterGameList)(void)
{
	static const u32 cleared[] = { ADDR(g_roomRefreshing), ADDR(g_roomSearching), ADDR(g_gameListLoaded), ADDR(g_roomSearchAnswerIn), ADDR(g_gameCount), ADDR(g_lobbyBlinkClock), ADDR(g_pickedGame), ADDR(g_gameListTop),
	                               ADDR(g_gameListRow), ADDR(g_gameListRefreshClicked), ADDR(g_roomJoinStarted), ADDR(g_roomListRefreshTimer), ADDR(g_gameListClickArmed), ADDR(g_gameListClickTimer), ADDR(g_roomListPlayers) };
	(*(u32 *)&g_unusedRoomFloat) = 0x3f333333;   /* 0.7 */
	g_roomState = 1;
	g_roomCameraMode = 1;
	g_lastPanel = 999;
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	g_listRefreshPeriod = 30;
}

#define sound(id) GAME_FN(sound_playMenu, 0x41e760, u32, int)(id)   /* sound_playMenu, its eax */

/* 0x4378e0: the game room's keys, by state (g_roomState): 0 .. 2, 4 and 99 while no dialog is open (g_roomPanelsSliding; 2: the map
   list's keys when open), 66 and 88 (the update notice, g_roomUpdateNotice, first), 77. Returns what the handler leaves in eax */
u32 (room_keysByState)(void)
{
	u32 state = (*(u32 *)&g_roomState);
	int dialog = g_roomPanelsSliding;
	switch (state) {
	case 0: return dialog ? (u32)dialog : account_keys();   /* account_keys */
	case 1: return dialog ? (u32)dialog : gameList_keys();
	case 2:
		if (dialog)
			return (u32)dialog;
		return g_mapListOpen ? mapList_keys() : room_settingsAfterTyping();
	case 4: return dialog ? (u32)dialog : ranking_keys();
	case 66: return g_roomUpdateNotice == 1 ? roomUpdateNotice_keys() : roomLogin_keys();
	case 77: return newIdForm_keys();
	case 88: return g_roomUpdateNotice == 1 ? roomUpdateNotice_keys() : newIdConfirm_keys();
	case 99: return dialog ? (u32)dialog : room_keys();
	}
	return state;
}

/* 0x437240: the account page's keys (unless typing): while the server is awaited (g_roomAwaitingServer) only Esc, leaving; else O
   sends the account change (account_sendChange; refused: sound 6 and message 5); C or Esc leave the page (g_roomCameraMode 0: back home). Returns what the original leaves in eax */
u32 (account_keys)(void)
{
	if (g_textFieldOpen)
		return (*(u32 *)&g_textFieldOpen);
	if (g_roomAwaitingServer == 1) {
		if (!input_justPressed(g_dikEscape_2))
			return 0;
	} else if (input_justPressed(g_dikO)) {
		if (account_sendChange() != 1) {   /* not ready */
			sound(6);
			return menu_showMessage(5);   /* menu_showMessage: the message */
		}
	} else if (!input_justPressed(g_dikC) && !input_justPressed(g_dikEscape_2))
		return 0;
	u32 r = sound(0);
	g_roomCameraMode = 0;
	return r;
}

/* 0x435c20: the new-ID form's clicks: a right click (or button 5, CANCEL) back to the login, buttons 0 .. 3 type into
   that field (newIdForm_openField), 4 (OK) checks the form (newIdForm_check). Returns what the original leaves in eax */
u32 (newIdForm_clicks)(void)
{
	if (g_rightClick) {
		sound(0);
		return room_openLogin();
	}
	if (!g_mouseClick)
		return 0;
	u32 button = ((u32)newIdForm_hitTest(g_mouseX, g_mouseY));
	if (button <= 3) {
		newIdForm_endTyping();
		return ((u32)newIdForm_openField((int)button));
	}
	if (button == 4) {
		sound(0);
		return newIdForm_check();
	}
	if (button == 5) {
		sound(0);
		return room_openLogin();
	}
	return button;
}

/* 0x434dd0: joining session i of the list: its DirectPlay connection (dplay_openConnection) and the join (dplay_listSessions); a failure
   shows message 0x3f or 0x40 and stops the search; on success the join's wait starts (timer 0x378, 2 s, its id
   kept). Returns what the original leaves in eax */
u32 (room_joinSession)(int i)
{
	g_roomJoinStarted = 0;
	if (!dplay_openConnection(0, g_sessionList[i].address)) {
		menu_showMessage(0x3f);
		return dplay_leaveSession();   /* dplay_leaveSession */
	}
	g_arenaJoinRow = i;
	if (!dplay_listSessions()) {        /* dplay_listSessions */
		menu_showMessage(0x40);
		return dplay_leaveSession();
	}
	g_joinPollTicks = 0;
	g_joinConnecting = 1;
	g_joinTimedOut = 0;
	g_sessionFound = 0;
	u32 timer = SetTimer(g_mainWindow, 0x378, 2000, NULL);   /* SetTimer */
	g_arenaJoinTimer = timer;
	return timer;
}

/* 0x434d00: the game room's list opened: its state reset, the session list cleared, the request for the server's
   room list sent (message 0x13, 0x65 bytes), 30 seconds. Returns 1 */
int (gameList_open)(void)
{
	g_connectionAwaited = 1;
	g_hostAnswer = 2;
	g_roomSearchAnswerIn = 0;
	g_roomRefreshing = 0;
	g_roomSearching = 1;
	g_roomListAnswer = 0;
	g_unusedRoomListWord = 0;
	g_gameCount = 0;
	g_gameListLoaded = 1;
	g_pickedGame = 0;
	(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;   /* 1000 */
	g_gameListTop = 0;
	g_gameListRow = 0;
	arena_clearSessionEntry();   /* arena_clearSessionEntry */
	GAME_VAR(u32, g_roomListRequest) = 0x180001;
	net_send(0x13, 0x65);   /* net_send */
	g_roomListPlayers = 0;
	g_listRefreshPeriod = 0x1e;
	return 1;
}

/* 0x406200: joining arena i of the list (99999: the one typed in, g_typedArenaAddress): the search stopped first if it runs,
   the connection made (dplay_openConnection; message 0x3f and the search stopped on a failure), the join (dplay_listSessions, not
   checked), the join's wait (timer 0x378, 2 s). Returns what the original leaves in eax */
u32 (arena_joinListed)(int i)
{
	g_lobbyJoinStarted = 0;
	g_lanJoinRequest = 0;
	if (g_lanSearchStarted)
		dplay_leaveSession();
	void *session = i == 99999 ? (void *)ADDR(g_typedArenaAddress) : (void *)g_sessionList[i].address;
	if (!dplay_openConnection(0, session)) {
		menu_showMessage(0x3f);
		return dplay_leaveSession();
	}
	g_arenaJoinRow = i;
	dplay_listSessions();
	g_joinPollTicks = 0;
	g_joinConnecting = 1;
	g_joinTimedOut = 0;
	g_sessionFound = 0;
	u32 timer = SetTimer(g_mainWindow, 0x378, 2000, NULL);   /* SetTimer */
	g_arenaJoinTimer = timer;
	return timer;
}

/* 0x436800: the game room's clicks, by state (g_roomState), as room_keysByState does the keys (state 1: the stop button
   while a join is waited for, g_joinConnecting). Returns what the handler leaves in eax */
u32 (room_clicksByState)(void)
{
	u32 state = (*(u32 *)&g_roomState);
	int dialog = g_roomPanelsSliding;
	switch (state) {
	case 0: return dialog ? (u32)dialog : account_clicks();   /* account_clicks */
	case 1:
		if (dialog)
			return (u32)dialog;
		return g_joinConnecting ? gameList_stopJoin() : gameList_mouse();
	case 2:
		if (dialog)
			return (u32)dialog;
		return g_mapListOpen ? mapList_mouse() : room_settingsClicks();
	case 4: return dialog ? (u32)dialog : ranking_clicks();
	case 66: return g_roomUpdateNotice ? updateNotice_clicks() : roomLogin_clicks();
	case 77: return newIdForm_clicks();   /* newIdForm_clicks */
	case 88: return g_roomUpdateNotice ? updateNotice_clicks() : newIdConfirm_clicks();
	case 99: return dialog ? (u32)dialog : room_pageClicks();
	}
	return state;
}

/* 0x435e70: the account page's clicks (g_roomCameraMode 2; not while the server is awaited, a dialog or typing): buttons
   0 .. 3 edit its fields (the old password, the new one, its repeat, the e-mail), 4 sends the change
   (account_sendChange; refused: message 5 and the refusal sound), 5 (or a right click) leaves the page. Returns what the original leaves in eax */
u32 (account_clicks)(void)
{
	int mode = g_roomCameraMode;
	if (mode == 1 || mode == 0 || g_roomAwaitingServer == 1)
		return (u32)mode;
	if (g_frameOpening)
		return (u32)g_frameOpening;
	if (g_textFieldOpen)
		return (*(u32 *)&g_textFieldOpen);
	if (!g_rightClick) {
		if (!g_mouseClick)
			return 0;
		u32 button = account_hitTest(g_mouseX, g_mouseY);
		switch (button) {
		case 0: return account_editOldPassword();
		case 1: return account_editPassword();
		case 2: return account_editPasswordRepeat();
		case 3: return account_editEmail();
		case 4:
			if (account_sendChange() == 1)
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
	g_roomCameraMode = 0;
	return r;
}

/* 0x43ed20: the game room's settings page (state 2; next to account_page, gameList_pageFrame, ranking_page): the
   room's tunnel; with the room camera arrived and not leaving (state 99), the dialog's frame if one is opening, else
   the registry record's settings kept in range (players 0 .. 16 else 8, the frag limit at most 50 and the time at
   most 60 else 30, the game mode (g_roomRecGameMode, +0x23) 0 .. 11 else 0), the settings form
   (room_drawGameSettings), the map list when open, and while a connection is awaited (g_connectionAwaited) the
   hosting step (room_hostingStep). Returns what the original leaves in eax */
u32 (roomSettings_page)(void)
{
	room_drawTunnel();   /* room_drawTunnel */
	int mode = g_roomCameraMode;
	if (mode == 1 || mode == 0 || g_roomState == 0x63)
		return (u32)mode;
	if (g_frameOpening)
		return menu_drawFrame(g_roomFormLeft, g_roomFormTop,
		                                                     g_roomFormRight, g_roomFormBottom);   /* menu_drawFrame */
	signed char players = g_roomRecMaxPlayers;
	if (players < 0 || players > 0x10)
		(*(u8 *)&g_roomRecMaxPlayers) = 8;
	if (g_roomRecFragLimit > 0x32)
		g_roomRecFragLimit = 0x1e;
	if (g_roomRecTimeLimit > 0x3c)
		g_roomRecTimeLimit = 0x1e;
	signed char gameMode = g_roomRecGameMode;
	if (gameMode < 0 || gameMode > 0xb)
		(*(u8 *)&g_roomRecGameMode) = 0;
	room_drawGameSettings();   /* room_drawGameSettings */
	if (g_mapListOpen == 1)
		mapList_draw();   /* mapList_draw: the map list */
	if (!g_connectionAwaited)
		return 0;
	return room_hostingStep();   /* room_hostingStep */
}

/* 0x433c70: typing in the Ladder login ended: the hidden EDIT control destroyed, the focus back on the main window,
   the line closed (menu_closeInputLine); the line then taken into the field it was for: the ID (g_lineToLoginId: 30 bytes
   at g_accountName) or the password (g_lineToLoginPassword: 12 bytes at g_accountPassword, the stars off). Returns
   what the original leaves in eax */
u32 (roomLogin_endTyping)(void)
{
	DestroyWindow(g_hEditField);   /* DestroyWindow */
	SetFocus(g_mainWindow);               /* SetFocus */
	menu_closeInputLine(1);                           /* menu_closeInputLine: the line sent */
	if (g_lineToLoginId == 1) {
		memset((void *)OBJ(g_accountName), 0, 30);
		g_lineToLoginId = 0;
		strcpy(g_accountName, g_chatLine);
		return 0;
	}
	if (g_lineToLoginPassword == 1) {
		memset((void *)OBJ(g_accountPassword), 0, 12);
		g_inputLineHidden = 0;
		strcpy(g_accountPassword, g_chatLine);
		g_lineToLoginPassword = 0;
		return 0;
	}
	return (*(u32 *)&g_lineToLoginId);
}

/* the dialog's button choice (g_dialogFocus) highlighted at (x, y) */
static void highlight_choice(int choice, int x, int y)
{
	g_dialogFocus = choice;
	g_pointerGliding = 1;
	(*(u32 *)&g_pointerGlideTime) = 0x41a00000;   /* g_pointerGlideTime 20 */
	(*(u32 *)&g_unusedHighlightAlpha) = 0x3ecccccd;   /* g_unusedHighlightAlpha 0.4 */
	g_highlightX = x;
	g_highlightY = y;
}

/* 0x43df80: the Ladder login dialog's update (its panel at g_roomLoginLeft): a password to retype (g_retypePassword: the settings back and
   the password opened again), the login to send (g_loginToSend); once typing has ended (g_textFieldOpen clear), the line taken
   into the ID (g_typingLoginId; 30 bytes at g_accountForm) or password (g_typingLoginPassword; 12 at g_accountPassword) and the key that
   ended it (g_fieldStep: 10 back, 20 on) moving to the other field or the dialog's buttons; else the server's answer
   to the request (g_gameServerAnswer, awaited: g_roomRequestOut): 33 accepted (state 99, the settings written and taken), 42 done
   (g_roomUpdateNotice), 31 / 32 / 34 a message (31 / 32 / 35), anything else message 42 */
void (roomLogin_update)(void)
{
	if (g_retypePassword) {
		room_copyAccountRecord();
		roomLogin_editPassword();
		g_retypePassword = 0;
		return;
	}
	if (g_loginToSend == 1) {
		roomLogin_endTyping();
		login_send();
		g_loginToSend = 0;
		return;
	}
	if (g_typingLoginId) {
		if (g_textFieldOpen)
			return;
		g_typingLoginId = 0;
		memset((void *)OBJ(g_accountName), 0, 30);
		strcpy(g_accountName, g_chatLine);
		if (g_fieldStep == 10) {
			highlight_choice(3, g_roomLoginLeft + 0x1a2, g_roomLoginBottom - 0x30);
			g_lineToLoginId = 0;
			g_fieldStep = 0;
		} else if (g_fieldStep == 20) {
			g_lineToLoginId = 0;
			roomLogin_editPassword();
			g_lineToLoginPassword = 1;
			g_inputLineHidden = 1;
			g_fieldStep = 0;
		}
		return;
	}
	if (g_typingLoginPassword) {
		if (g_textFieldOpen)
			return;
		memset((void *)OBJ(g_accountPassword), 0, 12);
		g_typingLoginPassword = 0;
		strcpy(g_accountPassword, g_chatLine);
		g_inputLineHidden = 0;
		if (g_fieldStep == 10) {
			g_lineToLoginId = 1;
			g_lineToLoginPassword = 0;
			roomLogin_editId();
			g_fieldStep = 0;
		} else if (g_fieldStep == 20) {
			highlight_choice(1, g_roomLoginLeft + 0x62, g_roomLoginBottom - 0x30);
			g_lineToLoginId = 0;
			g_lineToLoginPassword = 0;
			g_fieldStep = 0;
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
		reg_writeLadderSettings();
		login_takeAccountRecord();
	} else if (answer == 0x2a)
		g_roomUpdateNotice = 1;
	else if (answer == 0x1f || answer == 0x20)
		menu_showMessage(answer);
	else if (answer == 0x22)
		menu_showMessage(0x23);
	else
		menu_showMessage(0x2a);
	g_gameServerAnswer = 0;
	g_roomLoginDue = 0;
}

/* 0x43e290: the new-ID form ("CREATE NEW ID"; its panel at g_newIdFormLeft): the name opened when asked (g_openLoginName); with no message box
   (g_dialogPending) and typing ended, the line taken into the field being typed in (the first of the four flagged 1) and
   the key that ended it (g_fieldStep: 20 on, 10 back) moving to the next or previous field; on from the e-mail
   highlights the right button, back from the name the left one (the name's flag left set). Then the flagged field
   opened again for typing (the password's before the repeat's) */
void (newIdForm_update)(void)
{
	static const struct { u32 editing, text; int size; } field[4] = {
		{ ADDR(g_typingAccountName), OBJ(g_accountName), 30 }, { ADDR(g_typingAccountPassword), OBJ(g_accountPassword), 12 }, { ADDR(g_typingAccountRepeat), OBJ(g_accountPasswordRepeat), 12 }, { ADDR(g_typingAccountEmail), OBJ(g_accountEmail), 50 } };
#define EDITING(k) GAME_VAR(int, field[k].editing)
	if (g_openLoginName) {
		newIdForm_openField(0);
		g_openLoginName = 0;
		return;
	}
	if (g_dialogPending || g_textFieldOpen)
		return;
	int key = g_fieldStep;
	if (key == 20 || key == 10) {
		int k = 0;
		while (k < 4 && EDITING(k) != 1)
			k++;
		if (k < 4) {
			memset((void *)RELOC(field[k].text), 0, field[k].size);
			strcpy((char *)RELOC(field[k].text), g_chatLine);
			if (key == 10 && k == 0)
				highlight_choice(2, g_newIdFormLeft + 0x172, g_newIdFormBottom - 0x2c);
			else {
				EDITING(k) = 0;
				if (key == 10)
					EDITING(k - 1) = 1;
				else if (k < 3)
					EDITING(k + 1) = 1;
				else {
					EDITING(0) = 0;
					highlight_choice(1, g_newIdFormLeft + 0xaa, g_newIdFormBottom - 0x2c);
				}
			}
		}
		g_fieldStep = 0;
	}
	if (EDITING(0) == 1) {
		newIdForm_openField(0);
		return;
	}
	if (EDITING(1) == 1)
		newIdForm_openField(1);
	if (EDITING(2) == 1) {
		newIdForm_openField(2);
		return;
	}
	if (EDITING(3) == 1)
		newIdForm_openField(3);
#undef EDITING
}

/* 0x43e610: the new ID's confirmation (state 88): its choice (g_newIdConfirmChoice: 1 OK registers it, newId_register; 2 back to
   the form, state 0x4d), then the server's answer (g_newIdAnswer, when awaited: g_newIdAnswerAwaited): 33 accepted (the settings
   written, to state 99), 30 message 0x22, 42 a message box, anything else message 0x2a. Returns what the original leaves in eax */
u32 (newIdConfirm_update)(void)
{
	u32 r = (*(u32 *)&g_newIdConfirmChoice) - 2;   /* (what the original's compare chain leaves) */
	if (g_newIdConfirmChoice == 1) {
		r = newId_register();   /* newId_register */
		g_newIdConfirmChoice = 0;
	} else if (g_newIdConfirmChoice == 2) {
		r = 0;
		g_roomState = 0x4d;
		g_newIdConfirmChoice = 0;
	}
	if (!g_newIdAnswerAwaited)
		return r;
	u32 answer = (*(u32 *)&g_newIdAnswer);
	switch (answer) {
	case 0:
		return 0;
	case 33:
		g_roomState = 0x63;
		g_roomRequestOut = 0;
		room_setLadderDefaults();
		r = reg_writeLadderSettings();   /* reg_writeLadderSettings */
		g_newIdAnswer = 0;
		g_roomConnected = 1;
		return r;
	case 30:
		g_roomRequestOut = 0;
		r = menu_showMessage(0x22);
		g_newIdAnswer = 0;
		return r;
	case 42:
		g_roomRequestOut = 0;
		g_newIdAnswer = 0;
		g_roomUpdateNotice = 1;
		return answer;
	}
	g_roomRequestOut = 0;
	r = menu_showMessage(0x2a);
	g_newIdAnswer = 0;
	return r;
}

/* 0x437810: the ranking page's keys: S cancels the request out (g_rankingWaiting; the page and
   sort put back); C, with no request out, closes the page (g_roomCameraMode 0); Esc, with none out, leaves the screen. Returns what the
   original leaves in eax */
u32 (ranking_keys)(void)
{
	u32 r;
	if (input_justPressed(g_dikS)) {
		if (!g_rankingWaiting)
			return 0;
		r = sound(0);
		g_rankingWaiting = 0;
		g_rankingListIn = 0;
		g_rankingPage = g_rankingPrevPage;
		g_rankingSort = g_rankingPrevSort;
		g_rankingHaveList = 1;
		return r;
	}
	if (input_justPressed(g_dikC)) {
		if (g_rankingWaiting)
			return (*(u32 *)&g_rankingWaiting);
		r = sound(0);
		g_rankingWaiting = 0;
		g_rankingHaveList = 0;
		g_rankingListIn = 0;
		g_roomCameraMode = 0;
		return r;
	}
	if (!input_justPressed(g_dikEscape_2))
		return 0;
	if (g_rankingWaiting)
		return (*(u32 *)&g_rankingWaiting);
	r = sound(0);
	g_roomCameraMode = 0;
	return r;
}

/* 0x4334c0: the account page (state 0) entered: the account fields and their flags cleared (brightness 0.7), and the
   account's details asked for: the logged-in ID (g_ladderId, 30 bytes) as message 0x1d, the server awaited.
   Returns net_send's eax */
u32 (room_enterAccountPage)(void)
{
	static const u32 cleared[] = { OBJ(g_accountPasswordRepeat), OBJ(g_accountPassword), (OBJ(g_accountPasswordRepeat) + 0x4), OBJ(g_accountOldPassword), (OBJ(g_accountPassword) + 0x4), (OBJ(g_accountPasswordRepeat) + 0x8), (OBJ(g_accountOldPassword) + 0x4), ADDR(g_roomState) };
	for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
		GAME_VAR(int, cleared[k]) = 0;
	g_roomCameraMode = 1;
	(*(u32 *)&g_unusedRoomFloat) = 0x3f333333;
	static const u32 cleared2[] = { ADDR(g_editingOldPassword), ADDR(g_editingAccountPassword), ADDR(g_editingPasswordRepeat), ADDR(g_editingEmail), ADDR(g_unusedAccountWord), (OBJ(g_accountPassword) + 0x8), (OBJ(g_accountOldPassword) + 0x8) };
	for (unsigned k = 0; k < sizeof cleared2 / sizeof cleared2[0]; k++)
		GAME_VAR(int, cleared2[k]) = 0;
	char *message = g_netAccountRequest;
	memset(message, 0, 30);
	strcpy(message, g_ladderId);
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

/* 0x4399c0: the new-ID form ("CREATE NEW ID"; 0x9dd6e8 .. 0x9dd6f4; only its frame while a message box is open): the title
   MSG(341, "CREATE NEW ID"), four labelled lines (MSG(342, "INPUT ID"), 0x80 apart) with underlines, the values (the name g_accountForm, the two
   passwords g_accountPassword / g_accountPasswordRepeat as stars, g_accountEmail), each left out while its field is being typed in (g_typingAccountName /
   g_typingAccountPassword / g_typingAccountRepeat / g_typingAccountEmail, with the keys taken), the two buttons (the one under the pointer, 4 / 5 by
   newIdForm_hitTest, bright) and the border. Returns the frame's or the border's eax */
u32 (newIdForm_draw)(void)
{
#define X0 g_newIdFormLeft
#define Y0 g_newIdFormTop
#define X1 g_newIdFormRight
#define Y1 g_newIdFormBottom
	if (g_frameOpening)
		return menu_drawFrame(X0, Y0, X1, Y1);   /* the frame */
	const u32 *bright = ((u32 *)g_roomBright), *dim = ((u32 *)g_roomDim);
	int hovered = newIdForm_hitTest(g_mouseX, g_mouseY);
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
	if (!g_typingAccountName || !g_textFieldOpen)
		text_draw8(X0 + 0x94, Y0 + 0x3c, g_accountName);
	if (!g_typingAccountPassword || !g_textFieldOpen) {
		stars(hidden, sizeof hidden, g_accountPassword);
		text_draw8(X0 + 0x94, Y0 + 0x6c, hidden);
	}
	if (!g_typingAccountRepeat || !g_textFieldOpen) {
		stars(hidden, sizeof hidden, g_accountPasswordRepeat);
		text_draw8(X0 + 0x94, Y0 + 0x9c, hidden);
	}
	if (!g_typingAccountEmail || !g_textFieldOpen)
		text_draw8(X0 + 0x94, Y0 + 0xcc, g_accountEmail);
	for (int k = 0; k < 2; k++) {
		int x = k * 0xc8;
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		const u32 *colour = hovered == k + 4 ? bright : dim;
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k + 4 ? 1.0f : 0.4f);
		menu_drawLargeButton(X0 + x + 0x5a, Y1 - 0x40, X0 + x + 0xfa, Y1 - 0x20, 1);
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(X0 + x + 0x5a, Y1 - 0x38, X0 + x + 0xfa, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return menu_drawCornerOrnaments(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* the update notice over a room dialog (g_roomUpdateNotice): the screen dimmed, a box with two lines (MSG(3, "THIS PROGRAM HAS BEEN UPDATED"), MSG(4, "DO DOWNLOAD A NEW VERSION")) and
   its two buttons (MSG(115, "$[0] O K"); the one under the pointer, by updateNotice_hitTest, in cyan) */
static void update_notice(void)
{
	int hovered = updateNotice_hitTest(g_mouseX, g_mouseY);
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
		tex_bind(g_textures->banks[texture / 512], texture % 512);
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

/* 0x439e00: the new ID's confirmation (state 88; 0x9dd1a0 .. 0x9dd1ac; only its frame while a message box is open): the title
   MSG(351, "CREATE NEW ID"), a rule, the new ID (g_accountName) in a green-framed box, the note MSG(352, "NEW ID ON REGISTRATION"), two buttons (MSG(354, "$[0] O K"), 0x80
   apart; the one under the pointer by newIdConfirm_hitTest bright), the update notice (g_roomUpdateNotice) and the border. Returns the
   frame's or the border's eax */
u32 (newIdConfirm_draw)(void)
{
#define X0 (g_newIdConfirmBox[0])
#define Y0 (g_newIdConfirmBox[1])
#define X1 (g_newIdConfirmBox[2])
#define Y1 (g_newIdConfirmBox[3])
	if (g_frameOpening)
		return menu_drawFrame(X0, Y0, X1, Y1);   /* menu_drawFrame */
	const u32 *bright = ((u32 *)g_roomBright), *dim = ((u32 *)g_roomDim);
	int hovered = newIdConfirm_hitTest(g_mouseX, g_mouseY);
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
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k ? 1.0f : 0.4f);
		int x = X0 + k * 0xb4;
		menu_drawWideButton(x + 0x64, Y1 - 0x40, x + 0xdc, Y1 - 0x20, 1);
		const u32 *colour = hovered == k ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x64, Y1 - 0x38, x + 0xdc, (const char *)(MSG(354, "$[0] O K") + k * 0x80));
	}
	if (g_roomUpdateNotice)
		update_notice();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawTopRightOrnament, 0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x4392c0: the room login dialog (0x9dd358 .. 0x9dd364; only its frame while a message box is open): the title
   MSG(331, "LADDER GAME ID MANAGER") and its rule, two labelled dark boxes (MSG(332, "YOUR ID"), 0x80 apart) with the name g_accountForm and the password
   g_accountPassword as stars (each left out while it is being typed in: g_typingLoginId / g_typingLoginPassword), three buttons (MSG(334, "LOG$[0] IN"); the
   one under the pointer, 2 .. 4 by roomLogin_hitTest, bright unless connecting), while connecting (g_roomRequestOut) a box with
   two lines (MSG(49, "CHECKING YOUR ID. PLEASE WAIT."), MSG(50, "PRESS ESC-KEY TO CANCEL")), the update notice (g_roomUpdateNotice) and the border. Returns the frame's or the border's
   eax */
u32 (roomLogin_draw)(void)
{
#define X0 g_roomLoginLeft
#define Y0 g_roomLoginTop
#define X1 g_roomLoginRight
#define Y1 g_roomLoginBottom
	if (g_frameOpening)
		return menu_drawFrame(X0, Y0, X1, Y1);   /* menu_drawFrame */
	const u32 *bright = ((u32 *)g_roomBright), *dim = ((u32 *)g_roomDim);
	int hovered = roomLogin_hitTest(g_mouseX, g_mouseY);
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
	if (!g_typingLoginId)
		text_draw8(X0 + 0xc8, Y0 + 0x58, g_accountName);
	if (!g_typingLoginPassword) {
		char hidden[30];
		stars(hidden, sizeof hidden, g_accountPassword);
		text_draw8(X0 + 0xc8, Y0 + 0x88, hidden);
	}
	for (int k = 0; k < 3; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
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
	if (g_roomUpdateNotice)
		update_notice();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return menu_drawCornerOrnaments(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* a rank's badge (rank 1 .. : cell rank - 1 of the 10-wide grid of the font texture g_fontAscii, bound) 24 x 16 at
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

/* 0x43a420: the pilot's account panel (0x9dd368 .. 0x9dd374); while waiting for the server (g_roomAwaitingServer = 1) only a
   box with two lines (MSG(423, "DOWNLOADING RANKING DATA"), MSG(50, "PRESS ESC-KEY TO CANCEL")). The title MSG(361, "USER INFOMATION"), five labels for the fields (MSG(362, "USER ID"), 0x80 apart) and
   seven for the record (MSG(367, "LEVEL")); four dark boxes with the name g_accountForm, three passwords as stars (g_accountOldPassword,
   g_accountPassword, g_accountPasswordRepeat; each left out while it is being typed in: g_editingOldPassword / g_editingAccountPassword / g_editingPasswordRepeat) and g_accountEmail (left
   out while g_editingEmail); the level g_pilotLevel with its rank badge (cell (level - 1) % 10, / 10 of the texture g_fontAscii),
   the rank g_accountRank (MSG(374, "OUT OF RANK(1000)") when none), two ratios ("%.2f": g_pilotPower, g_pilotKillRate) and three counts (g_pilotKills,
   g_pilotDeaths, g_pilotExp); two buttons (MSG(115, "$[0] O K"); 4 / 5 under the pointer by account_hitTest, lit unless g_textFieldOpen), a
   rule and the border. The original leaves eax to callers that ignore it */
void (account_drawPanel)(void)
{
#define X0 g_accountPanelLeft
#define Y0 g_accountPanelTop
#define X1 g_accountPanelRight
#define Y1 g_accountPanelBottom
#define K(addr) ((const float *)RELOC(addr))
	const u32 *bright = ((u32 *)g_roomBright), *dim = ((u32 *)g_roomDim);
	int hovered = ((int)account_hitTest(g_mouseX, g_mouseY));   /* account_hitTest */
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
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	rank_badge(g_pilotLevel, X0 + 0xc0, Y0 + 0xbe);
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
	menu_drawRect(X0 + 0xc1, Y0 + 0xbe, X0 + 0xd8, Y0 + 0xce, 0);
	/* the record */
	if (!g_accountRank)
		text_draw8(X0 + 0x98, Y0 + 0xd6, (const char *)MSG(374, "OUT OF RANK(1000)"));
	else {
		itoa(g_accountRank, text, 10);
		text_draw8(X0 + 0x98, Y0 + 0xd6, text);
	}
	sprintf(text, (const char *)STR(0x4b0268, "%.2f"), (double)g_pilotPower);
	text_draw8(X0 + 0x98, Y0 + 0xee, text);
	sprintf(text, (const char *)STR(0x4b0268, "%.2f"), (double)g_pilotKillRate);
	text_draw8(X0 + 0x98, Y0 + 0x106, text);
	static const u32 counts[3] = { ADDR(g_pilotKills), ADDR(g_pilotDeaths), ADDR(g_pilotExp) };
	for (int k = 0; k < 3; k++) {
		itoa(GAME_VAR(int, counts[k]), text, 10);
		text_draw8(X0 + 0x98, Y0 + 0x11e + k * 0x18, text);
	}
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		int lit = hovered == k + 4 && !g_textFieldOpen;
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

/* 0x43d060: the ranking table (0x9dced8 .. 0x9dcee4): the title MSG(411, "LADDER GAME RANKING"); the page arrows (0 / 1 under the pointer,
   by ranking_hitTest, lit) about "first ~ last" of page g_rankingPage (stored in g_rankingFirst / g_rankingLast); the sort button
   (MSG(412, "OPTION"); 2) with the sorted column's name; two rules and the column heads (MSG(413, "RANK") .., the sorted one in
   yellow); when there is a list (g_rankingHaveList) up to ten rows (g_rankingRows) until an
   empty name (which stores the page in g_rankingLastPage): rank, name, rank badge (level) in a yellow frame, power "%8.1f",
   rate "%3.2f" and three counts (kills, deaths, exp), the sorted value in yellow; a rule, two buttons
   (MSG(421, "$[0] STOP"); 3 / 4, the first dead until the list is loaded, g_rankingWaiting); while loading the blinking MSG(423, "DOWNLOADING RANKING DATA"); the
   border. Returns the border's eax */
u32 (ranking_drawTable)(void)
{
#define X0 (g_rankingRect[0])
#define Y0 (g_rankingRect[1])
#define X1 (g_rankingRect[2])
#define Y1 (g_rankingRect[3])
#define TEXT(c) set_colour_bits(g_textColour, (c)[0], (c)[1], (c)[2], (c)[3])
	const u32 *bright = ((u32 *)g_roomBright), *dim = ((u32 *)g_roomDim);
	static const u32 white[4] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
	static const u32 yellow[4] = { 0x3f800000, 0x3f800000, 0, 0x3f800000 };
	int hovered = ((int)ranking_hitTest(g_mouseX, g_mouseY));   /* ranking_hitTest */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	TEXT(bright);
	text_draw16(X0 + 0x10, Y0 + 0x10, (const char *)MSG(411, "LADDER GAME RANKING"));
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton1(X0 + 0xb0, Y0 + 0x26, X0 + 0xe4, Y0 + 0x3e, hovered == 0);
	menu_drawSmallButton2(X0 + 0x146, Y0 + 0x26, X0 + 0x17a, Y0 + 0x3e, hovered != 0 && hovered == 1);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	char page[64], last[64];
	int first = g_rankingPage * 10 + 1;
	g_rankingFirst = first;
	g_rankingLast = (g_rankingPage * 5 + 5) * 2;
	itoa(first, page, 10);
	itoa(g_rankingLast, last, 10);
	strcat(page, (const char *)STR(0x4b278c, " ~ "));
	strcat(page, last);
	menu_drawWideButton(X0 + 0xe6, Y0 + 0x24, X0 + 0x146, Y0 + 0x40, 1);
	text_drawCentred8(X0 + 0xe6, Y0 + 0x2a, X0 + 0x146, page);
	text_drawBox16(X1 - 0x78, Y0 + 0x10, X1 - 0x14, (const char *)MSG(412, "OPTION"));
	glEnable(GL_TEXTURE_2D);
	texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, hovered == 2 ? 1.0f : 0.6f);
	menu_drawWideButton(X1 - 0x78, Y0 + 0x24, X1 - 0x14, Y0 + 0x40, 1);
	TEXT(yellow);
	static const u32 sorted_by[4] = { MSG(416, "POWER"), MSG(418, "KILL"), MSG(420, "EXP"), MSG(417, "RATE") };
	if ((unsigned)g_rankingSort <= 3)
		text_drawCentred8(X1 - 0x78, Y0 + 0x2a, X1 - 0x14, (const char *)RELOC(sorted_by[g_rankingSort]));
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
			const RankRow *row = &g_rankingRows[i];
			if (!row->name[0]) {
				g_rankingLastPage = g_rankingPage;
				break;
			}
			int y = Y0 + i * 0x16 + 0x78;
			TEXT(white);
			itoa(row->rank, text, 10);
			text_draw8(X0 + 0x18, y, text);
			text_draw8(X0 + 0x48, y, row->name);
			glEnable(GL_TEXTURE_2D);
			texture = g_fontAscii;
			tex_bind(g_textures->banks[texture / 512], texture % 512);
			rank_badge(row->level, X0 + 0xd2, y);
			glDisable(GL_TEXTURE_2D);
			set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
			menu_drawRect(X0 + 0xd3, y + 1, X0 + 0xea, y + 0x10, 0);
			TEXT(white);
			if (g_rankingSort == 0)
				TEXT(yellow);
			sprintf(text, (const char *)STR(0x4b2784, "%8.1f"), (double)row->power);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x144, y, text);
			TEXT(white);
			if (g_rankingSort == 3)
				TEXT(yellow);
			sprintf(text, (const char *)STR(0x4b277c, "%3.2f"), (double)row->rate);
			text_draw8(X0 + (0x30 - (int)strlen(text)) * 8, y, text);
			TEXT(white);
			if (g_rankingSort == 1)
				TEXT(yellow);
			itoa(row->kills, text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x1bc, y, text);
			TEXT(white);
			itoa(row->deaths, text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x1f4, y, text);
			TEXT(white);
			if (g_rankingSort == 2)
				TEXT(yellow);
			itoa(row->exp, text, 10);
			text_draw8(X0 - (int)strlen(text) * 8 + 0x23e, y, text);
		}
	}
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y1 - 0x40, X1 - 0x10, Y1 - 0x40);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
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
	return menu_drawCornerOrnaments(X0, Y0, X1, Y1);   /* the border */
#undef TEXT
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* the Ladder login dialog closed, back to the room's page 99 (keys blocked, the room's state 300) */
static void creategame_close(void)
{
	menuCamera_setMove(4);
	g_roomState = 99;
	g_nextScreen = 300;
	GAME_FN(shared_emptyFunction, 0x48b420, void, void)();   /* shared_emptyFunction */
}

/* 0x436990: the Ladder login dialog's keys. While its request is out (g_roomRequestOut) or the login is due (g_roomLoginDue)
   only cancel2 answers, closing the dialog (the answer dropped) and the lobby connection. Otherwise a click on its
   buttons (roomLogin_hitTest: 2 send, 3 close and disconnect, 4 room_openNewIdForm), g_dikI send, back close, g_dikN
   room_openNewIdForm (none of these while typing, g_textFieldOpen); the toggle key moves the highlight (g_dialogFocus) on: from
   the name (1) to the password field (2), to the OK button (3), then into the name field for typing; with shift,
   back: from OK (3) to the password field, to the name, then into the password field for typing. The original
   leaves eax to callers that ignore it */
void (roomLogin_keys)(void)
{
	int dialogX = g_roomLoginLeft, dialogBottom = g_roomLoginBottom - 0x30;
	if (g_roomRequestOut || g_roomLoginDue) {
		if (input_justPressed(g_keyCancel2)) {
			g_roomRequestOut = 0;
			g_gameServerAnswer = 0;
			g_roomLoginDue = 0;
			g_inputLineHidden = 0;
			g_textFieldOpen = 0;
			creategame_close();
			g_pointerGliding = 0;
			net_disconnect();
		}
		return;
	}
	if (input_justPressed(g_keyClick) == 1) {
		int on = roomLogin_hitTest(g_mouseX, g_mouseY);
		if (on == 2) {
			if (g_roomLoginDue)
				return;
			sound_playMenu(0);
			g_pointerGliding = 0;
			g_loginToSend = 1;
			g_roomLoginDue = 1;
			return;
		}
		if (on == 3) {
			sound_playMenu(0);
			g_textFieldOpen = 0;
			creategame_close();
			g_inputLineHidden = 0;
			g_pointerGliding = 0;
			net_disconnect();
			return;
		}
		if (on == 4) {
			g_textFieldOpen = 0;
			g_pointerGliding = 0;
			sound_playMenu(0);
			room_openNewIdForm();
			return;
		}
	}
	if (input_justPressed(g_dikI) == 1) {
		if (g_textFieldOpen || g_roomLoginDue)
			return;
		sound_playMenu(0);
		g_loginToSend = 1;
		g_roomLoginDue = 1;
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		if (g_textFieldOpen)
			return;
		g_inputLineHidden = 0;
		sound_playMenu(0);
		creategame_close();
		return;
	}
	if (input_justPressed(g_dikN) == 1) {
		if (g_textFieldOpen)
			return;
		sound_playMenu(0);
		room_openNewIdForm();
		return;
	}
	if (input_justPressed(g_keyToggle) != 1)
		return;
	g_fieldStep = 20;
	int choice = g_dialogFocus;
	if (input_isDown(g_keyLeftShift) == 1 || input_isDown(g_keyRightShift) == 1) {
		g_fieldStep = 10;
		if (choice == 1) {
			highlight_choice(0, dialogX + 0x180, g_roomLoginTop + 0x88);
			roomLogin_editPassword();
			g_lineToLoginPassword = 1;
			g_inputLineHidden = 1;
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
			roomLogin_editId();
			g_fieldStep = 0;
			g_lineToLoginId = 1;
			return;
		} else
			return;
	}
	g_fieldStep = 0;
}

/* room_clicks.c: the game room's handlers: its pages' clicks and keys, the Ladder login and new-ID forms checked and
   sent, the account change, the hosting step and the join's answer, the map previews (the room's and the arena's),
   the update notices, the join passwords, the white fade; also the mission list's clicks. */
#include "../game.h"
#include <string.h>


/* 0x435ab0: the update notice ("THIS PROGRAM HAS BEEN UPDATED"): OK (button 0) closes it and the game (exit code 2, for the
   launcher to update), CANCEL (button 1) only closes it */
void (updateNotice_clicks)(void)
{
	if (g_frameOpening != 0 || g_mouseClick == 0)
		return;
	switch (updateNotice_hitTest(g_mouseX, g_mouseY)) {
	case 0:
		g_roomUpdateNotice = 0;
		app_closeWindow(2);
		break;
	case 1:
		g_roomUpdateNotice = 0;
		break;
	}
}

/* 0x435ce0: the new ID confirmation's two buttons (newIdConfirm_hitTest): OK (1) or CANCEL (2) chosen */
void (newIdConfirm_clicks)(void)
{
	if (g_mouseClick == 0)
		return;
	switch (newIdConfirm_hitTest(g_mouseX, g_mouseY)) {
	case 0:
		sound_playMenu(0);
		g_newIdConfirmChoice = 1;
		break;
	case 1:
		sound_playMenu(0);
		g_newIdConfirmChoice = 2;
		break;
	}
}

/* 0x434da0: the join password asked for (room_editJoinPassword) when the game picked (g_pickedGame) is locked */
void (room_askJoinPassword)(void)
{
	g_roomJoinNeedsPassword = 0;
	if (g_sessionList[g_pickedGame].locked != 0) {
		g_roomJoinNeedsPassword = 1;
		room_editJoinPassword();
	}
}

/* 0x435f40: the CONNECTING TO THE GAME SERVER box's CANCEL over the game list (gameListJoinBox_hitTest; with the room camera arrived): the join being waited
   for given up: its flags off, the session left (dplay_leaveSession) and its timer (0x378) killed */
void (gameList_stopJoin)(void)
{
	if (g_frameOpening != 0 || g_mouseClick == 0 || g_roomCameraMode != 2)
		return;
	g_menuRepeatClock = 0.0f;
	if (gameListJoinBox_hitTest(g_mouseX, g_mouseY) == 0) {
		sound_playMenu(0);
		g_joinPollTicks = 0;
		g_joinTimedOut = 0;
		dplay_leaveSession();
		g_joinConnecting = 0;
		KillTimer(g_mainWindow, 0x378);
	}
}

/* 0x43df00: the white fade over the whole screen, 0.015 per time unit (the stored value goes on past 1; the
   colour stops at 1) */
void (room_drawWhiteFade)(void)
{
	long double a = (long double)g_frameTime * 0.015f + g_whiteFade;
	g_whiteFade = f32(a);
	float alpha = f32(a);
	if (a > 1.0f)
		alpha = 1.0f;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	Color4_set(g_rectColour, 1.0f, 1.0f, 1.0f, alpha);
	menu_drawRect(0, 0, g_screenW, g_screenH, 1);
}

/* 0x405200: the same for the arena lobby: when the game picked (g_pickedGame) is locked, g_arenaJoinNeedsPassword set
   and its password asked for (arena_editJoinPassword) */
void (arena_askJoinPassword)(void)
{
	g_arenaJoinNeedsPassword = 0;
	if (g_sessionList[g_pickedGame].locked != 0) {
		g_arenaJoinNeedsPassword = 1;
		arena_editJoinPassword();
	}
}

/* 0x436940, 0x407970: the update notice's keys in the room and in the lobby: back closes it, O closes the game
   (exit code 2) */
static void update_notice_keys(int *question)
{
	if (input_justPressed(g_keyBack)) {
		*question = 0;
	} else if (input_justPressed(g_keyOk)) {
		*question = 0;
		app_closeWindow(2);
	}
}

void (roomUpdateNotice_keys)(void) { update_notice_keys(&g_roomUpdateNotice); }
void (arenaUpdateNotice_keys)(void) { update_notice_keys(&g_arenaUpdateNotice); }

/* 0x443e20: the mission list's clicks (screen 900) (not while a panel frame opens, g_frameOpening): a right click leaves (missions_leave); a
   left click on its buttons (missionList_hitTest): rows 0..7 pick that mission (missions_clickRow), 8 its briefing
   (mission_loadBriefing), 9 leaves. Returns the last call's eax */
int (missions_listClicks)(void)
{
	int r = g_frameOpening;
	if (r)
		return r;
	if (g_rightClick)
		missions_leave();
	if (!g_mouseClick)
		return 0;
	int row = missionList_hitTest(g_mouseX, g_mouseY);   /* missionList_hitTest */
	if ((u32)row <= 7)
		return missions_clickRow(row);
	if (row == 8)
		return ((int)mission_loadBriefing(g_missionPicked));
	if (row == 9)
		return ((int)missions_leave());
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

/* 0x437140: the game room's keys: back or leave leaves the game; the others open the room's pages (room_enterAccountPage,
   room_enterGameList, room_enterCreatePage, ranking_enter) or the arm center (g_armcFrom = 3, armc_open). Returns the action's eax */
u32 (room_keys)(void)
{
	if (key_hit(ADDR(g_dikEscape_2)))
		return room_leave();   /* room_leave */
	if (key_hit(ADDR(g_dikP)))
		return room_enterAccountPage();   /* room_enterAccountPage */
	if (key_hit(ADDR(g_dikJ)))
		return room_enterGameList();   /* room_enterGameList */
	if (key_hit(ADDR(g_dikC)))
		return room_enterCreatePage();   /* room_enterCreatePage */
	if (key_hit(ADDR(g_dikR)))
		return ranking_enter();   /* ranking_enter */
	if (key_hit(ADDR(g_dikA))) {
		g_armcFrom = 3;
		return armc_open();
	}
	if (key_hit(ADDR(g_dikX)))
		return room_leave();
	return 0;
}

/* 0x435b00: the Ladder login's clicks (nothing pending: g_roomLoginDue, g_roomRequestOut) on its buttons (roomLogin_hitTest): 0 / 1
   type the ID / the password (roomLogin_editId / Password), 2 LOG IN (the login due), 3 CANCEL back to the main
   menu (the keyboard taken back if it was let go, the connection closed), 4 NEW ID (room_openNewIdForm). Returns the action's eax */
u32 (roomLogin_clicks)(void)
{
	u32 busy = (*(u32 *)&g_roomLoginDue);
	if (busy)
		return busy;
	if ((busy = (*(u32 *)&g_roomRequestOut)))
		return busy;
	if ((busy = (*(u32 *)&g_rightClick)))
		return busy;
	if (!g_mouseClick)
		return 0;
	u32 button = ((u32)roomLogin_hitTest(g_mouseX, g_mouseY));
	u32 r;
	switch (button) {
	case 0:
		roomLogin_endTyping();
		r = roomLogin_editId();       /* roomLogin_editId */
		g_lineToLoginId = 1;
		return r;
	case 1:
		roomLogin_endTyping();
		r = roomLogin_editPassword();       /* roomLogin_editPassword */
		g_lineToLoginPassword = 1;
		return r;
	case 2:
		if ((busy = (*(u32 *)&g_roomLoginDue)))
			return busy;
		sound_playMenu(0);
		g_loginToSend = 1;
		g_roomLoginDue = 1;
		g_roomUpdateNotice = 0;
		return 1;
	case 3:
		if (g_textFieldOpen) {
			g_textFieldOpen = 0;
			input_resetKeys();
			input_initKeyboard(g_mainWindow);   /* input_initKeyboard */
		}
		sound_playMenu(0);
		menuCamera_setMove(4);
		g_roomState = 0x63;
		g_nextScreen = 300;
		g_inputLineHidden = 0;
		GAME_FN(shared_emptyFunction, 0x48b420, void, void)();          /* shared_emptyFunction */
		return net_disconnect();
	case 4:
		sound_playMenu(0);
		return room_openNewIdForm();    /* room_openNewIdForm */
	}
	return button;
}

/* 0x435d30: the game room's page clicks (the room camera arrived (g_roomCameraMode 2); no dialog): its six buttons (outlines at
   g_roomOutlines) open the room's pages, the arm center (g_armcFrom = 3) or leave the game; a right click (when a tunnel ring is behind:
   g_tunnelRings > 0) leaves too. Returns what the original leaves in eax */
u32 (room_pageClicks)(void)
{
	static const u32 actions[6] = { FN_ADDR(room_enterAccountPage, 0x4334c0), FN_ADDR(room_enterGameList, 0x433590), FN_ADDR(room_enterCreatePage, 0x433790), 0, FN_ADDR(ranking_enter, 0x433800), FN_ADDR(room_leave, 0x435a40) };
	u32 cameraMode = (*(u32 *)&g_roomCameraMode);
	if (cameraMode == 1 || cameraMode == 0)
		return cameraMode;
	if (g_frameOpening)
		return g_frameOpening;
	if (g_mouseClick) {
		const Outline *buttons = (const Outline *)OBJ(g_roomOutlines);
		for (int i = 0; i < 6; i++) {
			if (point_in_outline(g_mouseX, g_mouseY, buttons[i]) != 1)
				continue;
			sound_playMenu(0);
			if (i == 3) {   /* the arm center */
				g_armcFrom = 3;
				armc_open();   /* armc_open */
				g_enteringMenus = 0;
			} else
				GAME_CDECL(actions[i], void, void)();
			break;
		}
	}
	int right = g_rightClick;
	if (!right)
		return 0;
	int rings = g_tunnelRings;
	if (rings <= 0)
		return rings;
	sound_playMenu(0);
	return room_leave();   /* room_leave */
}

/* ---- the selected map's preview (map `selected`, a signed byte; its name 32 bytes a slot at g_mapNames) loaded as a
   texture: "<g_stageDir><name>/<name>" (the texture manager g_textures) into g_mapPreviewTexture; g_mapPreviewChanged cleared ---- */
static void load_map_preview(u32 selected)
{
	char path[0x80], copy[0x40];
	const char *name = (const char *)(OBJ(g_mapNames) + (signed char)GAME_VAR(u8, selected) * 32);
	memset(path, 0, sizeof path);
	strcpy(path, g_stageDir);   /* the maps' folder */
	strcat(path, name);
	strcat(path, (const char *)STR(0x4ad564, "/"));
	strcat(path, name);
	strcpy(copy, path);
	g_mapPreviewTexture = tex_getIdByName((*(void **)&g_textures), copy, 0, 0, 0, 0, 0, 0, 0);
	g_mapPreviewChanged = 0;
}
/* 0x43bcb0: the game room's (selection g_roomMap); arena_loadMapPreview: the arena screen's (g_newArenaMap) */
void (room_loadMapPreview)(void) { load_map_preview(ADDR(g_roomMap)); }
void (arena_loadMapPreview)(void) { load_map_preview(ADDR(g_newArenaMap)); }

/* 0x433d30: the typed line (g_inputLine) committed to the new-ID form's field being edited (when the keyboard was let go for it,
   g_textFieldOpen: the edit window g_hEditField destroyed and the focus back on the main window first): the ID
   (g_accountName, 30 bytes), the password and its repeat (g_accountPassword, g_accountPasswordRepeat, 12 bytes) or the e-mail (g_accountEmail, 50 bytes).
   Returns what the original leaves in eax */
/* typing closed if it was on: the hidden EDIT control destroyed, the focus back to the game window and the line
   closed (menu_closeInputLine); returns that call's eax, or 0 */
static u32 typing_end(void)
{
	if (!g_textFieldOpen)
		return 0;
	DestroyWindow(g_hEditField);   /* DestroyWindow */
	SetFocus(g_mainWindow);   /* SetFocus */
	return menu_closeInputLine(1);   /* menu_closeInputLine */
}

u32 (newIdForm_endTyping)(void)
{
	static const struct { u32 editing, field, size; } fields[4] = {
		{ ADDR(g_typingAccountName), OBJ(g_accountName), 30 }, { ADDR(g_typingAccountPassword), OBJ(g_accountPassword), 12 }, { ADDR(g_typingAccountRepeat), OBJ(g_accountPasswordRepeat), 12 }, { ADDR(g_typingAccountEmail), OBJ(g_accountEmail), 50 } };
	u32 r = typing_end();
	const char *typed = g_inputLine;
	for (int k = 0; k < 4; k++) {
		if (GAME_VAR(int, fields[k].editing) != 1)
			continue;
		memset((void *)RELOC(fields[k].field), 0, fields[k].size);
		strcpy((char *)RELOC(fields[k].field), typed);
		return k == 3 ? strlen(typed) + 1 : 0;
	}
	return r;
}

/* 0x4355b0: the game room's hosting step (g_hostAnswer): 1 hosts the room's session (the music stopped, dplay_openConnection, then
   dplay_host with the room's settings record g_roomRecName and name g_ladderId) and takes its settings (the 32-byte
   rules, +0x20 .. +0x25); then 0 or 3 (3 also sets g_arenaUpdateNotice) move on to 2, and 4 does too with message 0x2a.
   Returns the step (or the message's eax) */
u32 (room_hostingStep)(void)
{
	const u8 *room = (const u8 *)OBJ(g_roomRecName);
	u32 answer = (*(u32 *)&g_hostAnswer);
	if (answer == 2)
		return 2;
	if (answer == 1) {
		g_connectionAwaited = 0;
		g_leavingForMatch = 1;
		g_netRole = 1;
		music_stop();
		g_roomCameraMode = 0;
		GAME_FN(dplay_openConnection, 0x452ec0, int, int, int)(0, 0);   /* dplay_openConnection */
		dplay_host(
			room, g_ladderId, (signed char)room[0x23], (signed char)room[0x21], (signed char)room[0x23],
			room[0x24], room[0x25], 0);   /* dplay_host: host */
		g_mapIndex = (signed char)room[0x20];
		g_chosenGameMode = (signed char)room[0x23];
		memcpy((void *)OBJ(g_gameTitle), room, 32);
		g_mapRotation = (signed char)room[0x22];
		g_fragLimit = room[0x24];
		g_timeLimit = room[0x25];
		answer = (*(u32 *)&g_hostAnswer);
		g_arenaGameSetUp = 1;
	}
	switch (answer) {
	case 3:
		g_arenaUpdateNotice = 1;
		/* fall through */
	case 0:
		g_connectionAwaited = 0;
		g_arenaGameSetUp = 0;
		g_hostAnswer = 2;
		return answer;
	case 4:
		g_connectionAwaited = 0;
		g_hostAnswer = 2;
		g_arenaGameSetUp = 0;
		return menu_showMessage(0x2a);   /* the message */
	}
	return answer;
}

/* 0x434e70: the join's wait ended in the game room (WM_TIMER 0x378 in game_wndProc when g_screen is 800, after 30
   polls or a session found). Timed out (g_joinTimedOut): the session left and message 0x44 (CONNETION TIME OUT). A
   session found (g_sessionFound; its g_sessionList entry, row g_arenaJoinRow): the entry's guid from the session
   received (g_receivedSession) and its frag and time limits taken, then joined (dplay_join); joined (0x1f4): the
   music stopped and the match's settings taken from the entry; otherwise a message by the result (0x43 / 0x42 / 0x42
   / 0x44 / 0x45) and the session left. Returns what the original leaves in eax */
u32 (room_joinAnswer)(void)
{
	if (g_joinTimedOut) {
		g_joinPollTicks = 0;
		g_joinTimedOut = 0;
		dplay_leaveSession();
		u32 r = menu_showMessage(0x44);   /* the message */
		g_joinConnecting = 0;
		return r;
	}
	if (!g_sessionFound)
		return 0;
	u32 row = (*(u32 *)&g_arenaJoinRow);
	SessionEntry *game = &g_sessionList[row];
	game->guid = ((const SessionDesc *)g_receivedSession)->guid;
	g_roomRecFragLimit = game->fragLimit;
	g_roomRecTimeLimit = game->timeLimit;
	int r = dplay_join(0, (int)game->guid, (void *)OBJ(g_ladderId), 0);   /* dplay_join */
	if (r != 0x1f4) {
		static const u8 message[5] = { 0x43, 0x42, 0x42, 0x44, 0x45 };
		if ((u32)(r - 0x1f5) <= 4)
			menu_showMessage(message[r - 0x1f5]);
		u32 e = dplay_leaveSession();
		g_joinPollTicks = 0;
		g_sessionFound = 0;
		g_joinConnecting = 0;
		return e;
	}
	music_stop();
	g_leavingForMatch = 1;
	g_netRole = 2;
	g_roomCameraMode = 0;
	g_joinPollTicks = 0;
	g_sessionFound = 0;
	g_joinConnecting = 0;
	g_mapIndex = game->map;
	memcpy((void *)OBJ(g_gameTitle), game->name, 32);
	g_mapRotation = game->rotation;
	g_chosenGameMode = game->gameMode;
	g_fragLimit = game->fragLimit;
	g_timeLimit = game->timeLimit;
	return row * sizeof(SessionEntry);   /* (the original's eax: the entry's offset) */
}

/* 0x4346c0: the new-ID form checked (name g_accountName, password g_accountPassword and its repeat g_accountPasswordRepeat, e-mail g_accountEmail):
   a blank name, a bad name or password character, a missing or mismatched password and a bad e-mail each give
   their message and reopen the field; all good, its confirmation (room_openNewIdConfirm). Returns that call's eax */
u32 (newIdForm_check)(void)
{
	newIdForm_endTyping();   /* newIdForm_endTyping */
	g_textFieldOpen = 0;
	g_fieldStep = 0;
	const char *name = g_accountName, *password = g_accountPassword;
	int message, reopen;
	if (strlen(name) == 0 || name_isBlank(name) == 1)   /* name_isBlank: blank */
		message = 0x24, reopen = ADDR(g_typingAccountName);
	else if (account_hasBadChar(name) == 1)                  /* account_hasBadChar: a bad character */
		message = 0x15a, reopen = ADDR(g_typingAccountName);
	else if (strlen(password) == 0)
		message = 0x25, reopen = ADDR(g_typingAccountPassword);
	else if (strcmp(password, g_accountPasswordRepeat))
		message = 0x21, reopen = ADDR(g_typingAccountPassword);
	else if (account_hasBadChar(password) == 1)
		message = 0x15b, reopen = ADDR(g_typingAccountPassword);
	else if (account_hasBadChar(g_accountEmail) == 1)
		message = 0x81, reopen = ADDR(g_typingAccountEmail);
	else
		return room_openNewIdConfirm();
	u32 r = menu_showMessage(message);
	GAME_VAR(int, reopen) = 1;
	return r;
}

/* 0x434b90: the account change sent: the old password (g_accountOldPassword) right and the new one repeated, every field free
   of bad characters (else message 0x81 and g_roomLoginDue cleared), the name, password and e-mail go out in message 0x1c.
   1 when sent */
int (account_sendChange)(void)
{
	if (strcmp((const char *)ADDR(g_ladderPassword), g_accountOldPassword) || strcmp(g_accountPassword, g_accountPasswordRepeat))
		return 0;
	static const u32 fields[4] = { OBJ(g_accountOldPassword), OBJ(g_accountPassword), OBJ(g_accountPasswordRepeat), OBJ(g_accountEmail) };
	for (int i = 0; i < 4; i++)
		if (account_hasBadChar((const char *)RELOC(fields[i])) == 1) {   /* account_hasBadChar */
			menu_showMessage(0x81);
			g_roomLoginDue = 0;
			return 0;
		}
	AccountForm *out = (AccountForm *)g_netAccountBuffer;
	strcpy(out->name, g_accountName);
	strcpy(out->password, g_accountPassword);
	strcpy(out->email, g_accountEmail);
	net_send(0x1c, 0x65);   /* net_send */
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

/* 0x43ede0: the ranking page. A request pending (g_rankingRequestPending) for sort column g_rankingSort: columns 0 .. 2 send their
   code (0x25 / 0x23 / 0x26) with the first rank of page g_rankingPage (ranks 0x9dd83c .. 0x9dd7dc) in message 0x15 and
   start waiting (g_rankingWaiting, the blink at 1000); column 3 just clears the request. Then the room's tunnel; with
   the room camera arrived (g_roomCameraMode 2) and outside page 99: while a panel frame opens (g_frameOpening) only it is drawn (a
   request made again once it closes), else while waiting an answer (g_rankingListIn) fills the list (ranking_fillPage) and
   keeps the column and page, the blink counts down by g_frameTime * g_lobbyBlinkRate (from 1000 again below 0), and the
   table is drawn (ranking_drawTable). Returns what the original leaves in eax */
u32 (ranking_page)(void)
{
	if (g_rankingRequestPending) {
		u32 column = (*(u32 *)&g_rankingSort);
		static const int code[3] = { 0x25, 0x23, 0x26 };
		if (column == 3) {
			g_rankingRequestPending = 0;
			return 3;
		}
		int *out = g_netRankingBuffer;
		if (column < 3)
			out[0] = code[column];
		int page = g_rankingPage;
		g_rankingFirst = page * 10 + 1;
		g_rankingLast = page * 10 + 10;
		out[1] = page * 10 + 1;
		net_send(0x15, 0x65);   /* net_send */
		g_rankingRequestPending = 0;
		g_lobbyBlinkClock = 1000.0f;
		g_rankingWaiting = 1;
	}
	room_drawTunnel();   /* room_drawTunnel: the tunnel */
	int mode = g_roomCameraMode;
	if (mode == 1 || mode == 0 || g_roomState == 99)
		return mode;
	if (g_frameOpening) {
		const int *box = g_rankingRect;
		menu_drawFrameOpening(box[0], box[1], box[2], box[3]);   /* the message box */
		if (g_frameOpening)
			return (*(u32 *)&g_frameOpening);
		g_rankingRequestPending = 1;
		return 0;
	}
	if (g_rankingWaiting) {
		if (g_rankingListIn) {
			ranking_fillPage();   /* ranking_fillPage: the list filled */
			g_rankingWaiting = 0;
			g_rankingHaveList = 1;
			g_rankingListIn = 0;
			g_rankingPrevSort = g_rankingSort;
			g_rankingPrevPage = g_rankingPage;
		}
		long double blink = fld_m((const float *)ADDR(g_lobbyBlinkClock)) - fmul_m(fld_m((const float *)ADDR(g_frameTime)), (const float *)ADDR(g_lobbyBlinkRate));
		g_lobbyBlinkClock = f32(blink);
		if (!(blink >= 0))
			g_lobbyBlinkClock = 1000.0f;
	}
	return call_keeping_ebp(FN_ADDR(ranking_drawTable, 0x43d060));   /* ranking_drawTable: the table */
}

/* 0x434490: the login sent: typing closed and the form's flags cleared; a name or password with a character the
   messages cannot carry gives its message (0x15a / 0x15b, g_roomLoginDue cleared); else the name and password are kept
   (g_ladderId, 30 bytes, and g_ladderPassword, 12) and sent as message 0x18 (net_send 0xe), then g_roomRequestOut set. Returns the
   message's or the send's eax */
u32 (login_send)(void)
{
	typing_end();
	g_typingLoginId = 0;
	g_typingLoginPassword = 0;
	g_inputLineHidden = 0;
	g_textFieldOpen = 0;
	const char *name = g_accountName, *password = g_accountPassword;
	int bad = account_hasBadChar(name) == 1 ? 0x15a
	        : account_hasBadChar(password) == 1 ? 0x15b : 0;   /* account_hasBadChar */
	if (bad) {
		u32 r = menu_showMessage(bad);
		g_roomLoginDue = 0;
		return r;
	}
	memset((void *)OBJ(g_ladderId), 0, 30 + 12);
	strcpy(g_ladderId, name);
	strcpy((char *)ADDR(g_ladderPassword), password);
	AccountPacket *account = g_accountPacket;
	memset(account->name, 0, 30);
	memset(account->password, 0, 12);
	strcpy(account->name, name);
	strcpy(account->password, password);
	account->kind = 0x18;
	u32 r = net_send(0xe, 0x65);
	g_roomRequestOut = 1;
	return r;
}

/* 0x436620: the ranking page's clicks (the room camera arrived (g_roomCameraMode 2), no message box open; a right click closes the
   page unless waiting for an answer). Not waiting (g_rankingWaiting): buttons 0 .. 2 the page arrows and the sort button
   (ranking_prevPage / ranking_nextPage / ranking_cycleSort), 4 closes the page, 5 / 7 / 8 sort by column 0 / 1 / 2 (the old column kept in
   g_rankingPrevSort and a request made, the list's state cleared). While waiting, button 3 cancels it (the column and page
   put back from g_rankingPrevSort / g_rankingPrevPage). Each with the click sound. Returns what the original leaves in eax */
u32 (ranking_clicks)(void)
{
	u32 mode = (*(u32 *)&g_roomCameraMode);
	if (mode == 1 || mode == 0 || g_frameOpening)
		return mode;
	int waiting = g_rankingWaiting;
	if (g_rightClick && !waiting)
		g_roomCameraMode = 0;
	if (!g_mouseClick)
		return mode;
	u32 button = ranking_hitTest(g_mouseX, g_mouseY);   /* ranking_hitTest */
	if (button > 8 || button == 6 || (button == 3 ? !g_rankingWaiting : g_rankingWaiting != 0))
		return button;
	u32 r = sound_playMenu(0);   /* the click sound */
	static const u32 actions[3] = { FN_ADDR(ranking_prevPage, 0x435970), FN_ADDR(ranking_nextPage, 0x4359b0), FN_ADDR(ranking_cycleSort, 0x4359f0) };
	int column;
	switch (button) {
	case 0: case 1: case 2:
		return GAME_CDECL(actions[button], u32, void)();
	case 3:
		g_rankingHaveList = 1;
		g_rankingWaiting = 0;
		g_rankingListIn = 0;
		g_rankingSort = g_rankingPrevSort;
		return (*(u32 *)&g_rankingPage) = (*(u32 *)&g_rankingPrevPage);
	case 4:
		g_roomCameraMode = 0;
		return r;
	}
	column = button == 5 ? 0 : button == 7 ? 1 : 2;   /* 5, 7, 8 */
	u32 old = (*(u32 *)&g_rankingSort);
	(*(u32 *)&g_rankingPrevSort) = old;
	g_rankingSort = column;
	g_rankingRequestPending = 1;
	g_rankingHaveList = 0;
	g_rankingListIn = 0;
	g_playerListDone = 0;
	g_playerListCount = 0;
	return button == 8 ? old : r;
}

/* 0x436400: the game room's settings page clicked (no field being typed in, the room camera arrived (g_roomCameraMode 2), no message
   box; a right click closes the page). Buttons (roomSettings_hitTest): 0 / 1 type the room's name or password
   (room_editGameName / room_editPassword), 3 the players +2 (4 .. 16, then 2), 5 the game type on (with a turn key held back) through
   0 .. 9, 6 / 7 the frag and time limits +5 (up to 50 / 60, then 5), 8 start (room_announceGame; not while connecting),
   9 close, 11 / 2, 10, 12 the map back / on (room_stepMap), 13 ADVANCED: the map list (mapList_startEdit). Returns what the original
   leaves in eax (for the byte settings, its low byte the new value) */
u32 (room_settingsClicks)(void)
{
	static const u32 typing[4] = { ADDR(g_editingRoomName), ADDR(g_editingFragLimit), ADDR(g_editingTimeLimit), ADDR(g_editingRoomPassword) };
	for (int k = 0; k < 4; k++)
		if (GAME_VAR(int, typing[k]))
			return GAME_VAR(u32, typing[k]);
	u32 mode = (*(u32 *)&g_roomCameraMode);
	if (mode == 1 || mode == 0)
		return mode;
	if (g_frameOpening)
		return (*(u32 *)&g_frameOpening);
	if (g_rightClick)
		g_roomCameraMode = 0;
	if (!g_mouseClick)
		return 0;
	u32 button = ((u32)roomSettings_hitTest(g_mouseX, g_mouseY));   /* roomSettings_hitTest */
	u8 *players = (u8 *)ADDR(g_roomMaxPlayers), *type = (u8 *)ADDR(g_roomGameMode), *frags = (u8 *)ADDR(g_roomFragLimit), *time = (u8 *)ADDR(g_roomTimeLimit);
	u32 r;
	switch (button) {
	case 0:
		return room_editGameName();   /* room_editGameName */
	case 1:
		return room_editPassword();   /* room_editPassword */
	case 2: case 10: case 12:
		return room_stepMap(1);   /* room_stepMap: the next map */
	case 11:
		return room_stepMap(0);
	case 3:
		*players += 2;
		r = *players;
		if ((signed char)*players > 16)
			*players = 2;
		return r;
	case 5:
		if (input_isDown(g_dikLShift) || input_isDown(g_dikRShift) ||
		    input_isDown(g_dikLCtrl) || input_isDown(g_dikRCtrl)) {
			r = sound_playMenu(2);
			*type -= 1;
			r = (r & ~0xffu) | *type;
			if ((signed char)*type < 0)
				*type = 9;
		} else {
			r = sound_playMenu(2);
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
		if (g_arenaGameSetUp)
			return (*(u32 *)&g_arenaGameSetUp);
		sound_playMenu(0);
		return room_announceGame();   /* room_announceGame: start */
	case 9:
		r = sound_playMenu(0);
		g_roomCameraMode = 0;
		return r;
	case 13:
		sound_playMenu(0);
		return mapList_startEdit(2);   /* mapList_startEdit: the map list (the original pushes a 2 it ignores) */
	}
	return button;
}

/* 0x437630: the game room's create-game page's keys (room_keysByState state 2; not while typing or with a message box): a typed field is
   taken (the room's name into g_roomSettingsName unless blank (sound 6); the password into 0x4df9ee; the frag and time limits
   as numbers into the bytes g_roomFragLimit / g_roomTimeLimit; an empty line changes nothing), else the keys: start (g_dikO;
   room_announceGame, not while connecting) and the two close keys (g_dikC, g_dikEscape_2). Returns what the original leaves
   in eax */
u32 (roomSettings_keys)(void)
{
	if (g_frameOpening)
		return (*(u32 *)&g_frameOpening);
	if (g_textFieldOpen)
		return 0;
	const char *line = g_inputLine;
	if (g_editingRoomName) {   /* the room's name */
		if (!strlen(line) || name_isBlank(line) == 1) {   /* name_isBlank: blank */
			u32 r = strlen(line) ? sound_playMenu(6) : 0;
			g_editingRoomName = 0;
			return r;
		}
		g_editingRoomName = 0;
		memset((void *)OBJ(g_roomSettingsName), 0, 32);
		strcpy(g_roomSettingsName, line);
		return strlen(line) + 1;
	}
	if (g_editingRoomPassword) {   /* the password */
		GameSettings *rs = (GameSettings *)OBJ(g_roomSettingsName);
		memset(rs->password, 0, 8);
		g_editingRoomPassword = 0;
		g_inputLineHidden = 0;
		strcpy(rs->password, line);
		return 0;
	}
	static const u32 limit[2][2] = { { ADDR(g_editingFragLimit), ADDR(g_roomFragLimit) }, { ADDR(g_editingTimeLimit), ADDR(g_roomTimeLimit) } };   /* frags, time */
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(int, limit[k][0]))
			continue;
		u32 r = strlen(line) ? (u32)crt_atoi(line) : 0;
		GAME_VAR(int, limit[k][0]) = 0;
		if (strlen(line))
			GAME_VAR(u8, limit[k][1]) = (u8)r;
		return r;
	}
	if (input_justPressed(g_dikO) && !g_arenaGameSetUp) {
		sound_playMenu(0);
		return room_announceGame();   /* room_announceGame: start */
	}
	u32 r = 0;
	static const u32 close[2] = { ADDR(g_dikC), ADDR(g_dikEscape_2) };
	for (int k = 0; k < 2; k++) {
		r = (u32)input_justPressed(GAME_VAR(int, close[k]));
		if (r) {
			r = sound_playMenu(0);
			g_roomCameraMode = 0;
		}
	}
	return r;
}

/* ---- the map preview box (panel at y P[0], x P[1]; the box 0x80 square from (x - 0x96, y + 0x50)): the preview
   reloaded when asked (g_mapPreviewChanged), then either "CUSTOM" (yellow on a dark box) while the map rotation
   is on or the preview texture g_mapPreviewTexture, and a yellow outline. Returns the outline call's eax ---- */
static u32 map_preview_box(const int *panel, u32 rotation, u32 reload)
{
#define X0 (panel[1] - 0x96)
#define X1 (panel[1] - 0x16)
#define Y0 (panel[0] + 0x50)
#define Y1 (panel[0] + 0xd0)
	if (g_mapPreviewChanged)
		GAME_CDECL(reload, void, void)();
	if (GAME_VAR(u8, rotation)) {
		Color4_set(g_rectColour, 0.0f, 0.0f, 0.0f, 0.4f);
		menu_drawRect(X0, Y0, X1, Y1, 1);
		Color4_set(g_textColour, 1.0f, 1.0f, 0.0f, 1.0f);
		text_drawCentredLines16(X0, panel[0] + 0x88, X1, (const char *)STR(0x4ad56c, "CUSTOM"));
	} else {
		glEnable(GL_TEXTURE_2D);
		int texture = g_mapPreviewTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
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
	Color4_set(g_rectColour, 1.0f, 1.0f, 0.0f, 1.0f);
	return menu_drawRect(X0, Y0, X1, Y1, 0);   /* menu_drawRect: the outline */
#undef X0
#undef X1
#undef Y0
#undef Y1
}

/* 0x43bde0: the game room's (panel g_roomFormTop, map rotation g_roomRotation, room_loadMapPreview); arena_drawMapPreview: the arena screen's
   (g_newArenaFormTop, g_newArenaRotation, arena_loadMapPreview) */
u32 (room_drawMapPreview)(void) { return map_preview_box((const int *)ADDR(g_roomFormTop), ADDR(g_roomRotation), FN_ADDR(room_loadMapPreview, 0x43bcb0)); }
u32 (arena_drawMapPreview)(void) { return map_preview_box((const int *)ADDR(g_newArenaFormTop), ADDR(g_newArenaRotation), FN_ADDR(arena_loadMapPreview, 0x40b420)); }

/* 0x43e7b0: the account page (room page 0; the room camera arrived (g_roomCameraMode 2), not page 99): with a message box only its
   frame; else the page (account_takeRank when g_accountRankDue, then account_drawPanel) and, once a field's typing has ended, the typed
   line taken into it (the name, password, its repeat (12 bytes each) or the e-mail (50)) and the key that ended it
   (g_fieldStep: 0xa back, 0x14 on) opening the field before or after (account_editOldPassword .. 434260). Returns what the
   original leaves in eax */
u32 (account_page)(void)
{
	static const struct { u32 editing, field, size, back, on; } fields[4] = {
		{ ADDR(g_editingOldPassword), OBJ(g_accountOldPassword), 12, 0, FN_ADDR(account_editPassword, 0x4340e0) }, { ADDR(g_editingAccountPassword), OBJ(g_accountPassword), 12, FN_ADDR(account_editOldPassword, 0x434020), FN_ADDR(account_editPasswordRepeat, 0x4341a0) },
		{ ADDR(g_editingPasswordRepeat), OBJ(g_accountPasswordRepeat), 12, FN_ADDR(account_editPassword, 0x4340e0), FN_ADDR(account_editEmail, 0x434260) }, { ADDR(g_editingEmail), OBJ(g_accountEmail), 50, FN_ADDR(account_editPasswordRepeat, 0x4341a0), 0 } };
	room_drawTunnel();   /* room_drawTunnel: the tunnel */
	u32 mode = (*(u32 *)&g_roomCameraMode);
	if (mode == 1 || mode == 0 || g_roomState == 99)
		return mode;
	if (g_frameOpening)
		return menu_drawFrameOpening(g_accountPanelLeft, g_accountPanelTop,
		                                                     g_accountPanelRight, g_accountPanelBottom);
	if (g_accountRankDue)
		account_takeRank();
	u32 r = account_drawPanel();   /* account_drawPanel: the page */
	if (g_roomAwaitingServer == 1)
		return r;
	for (int k = 0; k < 4; k++) {
		if (!GAME_VAR(int, fields[k].editing))
			continue;
		if (g_textFieldOpen)
			return r;
		memset((void *)RELOC(fields[k].field), 0, fields[k].size);
		GAME_VAR(int, fields[k].editing) = 0;
		g_inputLineHidden = 0;
		strcpy((char *)RELOC(fields[k].field), g_inputLine);
		u32 step = (*(u32 *)&g_fieldStep);
		u32 next = step == 0xa ? fields[k].back : step == 0x14 ? fields[k].on : 0;
		if (!next)
			return step;
		r = GAME_CDECL(next, u32, void)();
		if (!(k == 2 && step == 0xa))   /* (the original keeps the step there) */
			g_fieldStep = 0;
		return r;
	}
	return r;
}

/* ---- the new-ID form's keys: its text fields (g_dialogFocus: 0 .. 2), the text cursor placed in the one typed
   into (g_pointerGlideX / g_pointerGlideY) ---- */
#define g_loginField g_dialogFocus

/* the cursor into field to at (x, y) */
static void login_field(int to, int x, int y)
{
	g_loginField = to;
	g_pointerGliding = 1;
	(*(u32 *)&g_pointerGlideTime) = 0x41a00000;   /* 20 */
	(*(u32 *)&g_unusedHighlightAlpha) = 0x3ecccccd;   /* 0.4 */
	g_pointerGlideX = x;
	g_pointerGlideY = y;
	g_fieldStep = 0;
}

/* OK (button 4 clicked, or the OK key) checks the form (newIdForm_check), cancel (button 5, or g_dikC) closes it, back to the login (room_openLogin);
   neither while a message is up (g_textFieldOpen) */
static int form_buttons(void)
{
	int button = -1;
	if (input_justPressed(g_dikEnter) == 1)
		button = newIdForm_hitTest(g_mouseX, g_mouseY);   /* newIdForm_hitTest */
	if (button != 4 && button != 5) {
		if (input_justPressed(g_keyOk) == 1)
			button = 4;
		else if (input_justPressed(g_dikC) == 1)
			button = 5;
		else
			return 0;
	}
	if (!g_textFieldOpen) {
		sound_playMenu(0);
		if (button == 4)
			newIdForm_check();   /* newIdForm_check */
		else
			room_openLogin();   /* room_openLogin */
	}
	return 1;
}

/* 0x436e10: the new-ID form's keys: its two buttons, then Tab (g_dikTab) to the next field, or with shift
   (g_dikLShift / g_dikRShift held) the one before (the original's path for "back" from the first field is never taken).
   The original leaves eax to callers that ignore it */
void (newIdForm_keys)(void)
{
	if (form_buttons())
		return;
	if (input_justPressed(g_dikTab) != 1 || g_textFieldOpen)
		return;
	g_fieldStep = 20;
	if (input_isDown(g_dikLShift) == 1 || input_isDown(g_dikRShift) == 1)
		g_fieldStep = 10;
	if (g_fieldStep == 20) {
		if (g_loginField == 1)
			login_field(2, g_newIdFormLeft + 0x172, g_newIdFormBottom - 0x30);
		else if (g_loginField == 2) {
			g_typingAccountName = 1;
			g_typingAccountPassword = 0;
			login_field(2, g_roomLoginLeft + 0x15c, g_roomLoginTop + 0x44);
		}
	} else {
		if (g_loginField == 1) {
			g_typingAccountRepeat = 0;
			g_typingAccountEmail = 1;
			login_field(0, g_roomLoginLeft + 0x15c, g_roomLoginTop + 0xd4);
		} else if (g_loginField == 2)
			login_field(1, g_newIdFormLeft + 0xaa, g_newIdFormBottom - 0x30);
	}
}
#undef g_loginField

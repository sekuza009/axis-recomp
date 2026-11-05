/* room_clicks.c: the game room's small handlers: clicks on its popups' buttons, starting the chat line, and the
   white fade over the screen. Buttons are hit-tested with the pointer (leaveDialog_hitTest and its kind: the index of the
   button under it, or -1). */
#include "../game.h"
#include <string.h>


/* 0x435ab0: the "leave" dialog: yes (button 0) closes it and leaves (the game closes with exit code 2), no (button 1) only closes it */
void (leaveDialog_clicks)(void)
{
	if (g_dialogOpen != 0 || g_mouseClick == 0)
		return;
	switch (leaveDialog_hitTest(g_mouseX, g_mouseY)) {
	case 0:
		g_roomLeaveDialog = 0;
		app_closeWindow(2);
		break;
	case 1:
		g_roomLeaveDialog = 0;
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

/* 0x434da0: start the chat line (the password typed) when the game picked (g_localPlayer) is locked */
void (room_startChat)(void)
{
	g_roomChatting = 0;
	if (g_sessionList[g_localPlayer].locked != 0) {
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
		g_arenaSearchTicks = 0;
		g_arenaJoinWaiting = 0;
		arena_leaveSession();
		g_arenaConfirming = 0;
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
	g_arenaJoining = 0;
	if (g_sessionList[g_localPlayer].locked != 0) {
		g_arenaJoining = 1;
		arena_editMessage();
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

void (leaveDialog_keys)(void) { leave_keys(&g_roomLeaveDialog); }
void (lobbyJoin_keys)(void) { leave_keys(&g_arenaLeaving); }

/* 0x443e20: the skirmish settings screen's clicks (no dialog open, 0x90d1c4): a right click leaves (0x443c80); a left
   click on its buttons (skirmishSettings_hitTest): rows 0..7 change that setting (0x443d50), 8 saves (0x443af0 with the
   selection 0x9f16a4), 9 leaves. Returns the last call's eax */
int (skirmish_clicks)(void)
{
	int r = g_dialogOpen;
	if (r)
		return r;
	if (g_keyEnter)
		skirmishSettings_leave();
	if (!g_mouseClick)
		return 0;
	int row = skirmishSettings_hitTest(g_mouseX, g_mouseY);   /* skirmishSettings_hitTest */
	if ((u32)row <= 7)
		return skirmish_clickRow(row);
	if (row == 8)
		return ((int)mission_saveAxisMis(g_missionPicked));
	if (row == 9)
		return ((int)skirmishSettings_leave());
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
   0x433590, 0x433790, 0x433800) or the arm center (0x4dc24c = 3, armc_enterParts). Returns the action's eax */
u32 (room_keys)(void)
{
	if (key_hit(ADDR(g_dikEscape_2)))
		return room_leaveGame();   /* room_leaveGame */
	if (key_hit(ADDR(g_dikP)))
		return room_requestJoin();   /* room_requestJoin */
	if (key_hit(ADDR(g_dikJ)))
		return room_start();   /* room_start */
	if (key_hit(ADDR(g_dikC)))
		return room_enterGameList();   /* room_enterGameList */
	if (key_hit(ADDR(g_dikR)))
		return room_enterRoomList();   /* room_enterRoomList */
	if (key_hit(ADDR(g_dikA))) {
		g_armcFrom = 3;
		return armc_enterParts();
	}
	if (key_hit(ADDR(g_dikX)))
		return room_leaveGame();
	return 0;
}

/* 0x435b00: the game room's left clicks (nothing open: 0x9dd1c8, 0x9dd838; no right click) on its buttons
   (0x432200): 0 / 1 open the room's two lists (0x433b00, 0x433bb0), 2 opens the chat line, 3 leaves for the main
   menu (the keyboard taken back if it was let go, the connection closed), 4 0x4338c0. Returns the action's eax */
u32 (room_leftClicks)(void)
{
	u32 open = (*(u32 *)&g_roomLoginDue);
	if (open)
		return open;
	if ((open = (*(u32 *)&g_roomRequestOut)))
		return open;
	if ((open = (*(u32 *)&g_keyEnter)))
		return open;
	if (!g_mouseClick)
		return 0;
	u32 button = ((u32)createDialog_hitTest(g_mouseX, g_mouseY));
	u32 r;
	switch (button) {
	case 0:
		chat_closeEdit();
		r = field_editGameName();       /* field_editGameName */
		g_typingRoomName = 1;
		return r;
	case 1:
		chat_closeEdit();
		r = field_editGamePassword();       /* field_editGamePassword */
		g_typingRoomPassword = 1;
		return r;
	case 2:
		if ((open = (*(u32 *)&g_roomLoginDue)))
			return open;
		sound_playMenu(0);
		g_loginToSend = 1;
		g_roomLoginDue = 1;
		g_roomLeaveDialog = 0;
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
		GAME_FN(debug_traceStripped, 0x48b420, void, void)();          /* debug_traceStripped */
		return net_disconnect();
	case 4:
		sound_playMenu(0);
		return room_openDialog4d();    /* room_openDialog4d */
	}
	return button;
}

/* 0x435d30: the game room's page clicks (page open, 0x9dce48 not 0 or 1; no dialog): its six buttons (outlines at
   0x9daf88) open the room's pages, the arm center (0x4dc24c = 3) or leave the game; a right click (when 0x9dae10
   allows) leaves too. Returns what the original leaves in eax */
u32 (room_pageClicks)(void)
{
	static const u32 actions[6] = { FN_ADDR(room_requestJoin, 0x4334c0), FN_ADDR(room_start, 0x433590), FN_ADDR(room_enterGameList, 0x433790), 0, FN_ADDR(room_enterRoomList, 0x433800), FN_ADDR(room_leaveGame, 0x435a40) };
	u32 page = (*(u32 *)&g_roomMode);
	if (page == 1 || page == 0)
		return page;
	if (g_dialogOpen)
		return g_dialogOpen;
	if (g_mouseClick) {
		const Outline *buttons = (const Outline *)OBJ(g_roomOutlines);
		for (int i = 0; i < 6; i++) {
			if (point_in_outline(g_mouseX, g_mouseY, buttons[i]) != 1)
				continue;
			sound_playMenu(0);
			if (i == 3) {   /* the arm center */
				g_armcFrom = 3;
				armc_enterParts();   /* armc_enterParts */
				g_enteringMenus = 0;
			} else
				GAME_CDECL(actions[i], void, void)();
			break;
		}
	}
	int right = g_keyEnter;
	if (!right)
		return 0;
	int allowed = g_tunnelRings;
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	return room_leaveGame();   /* room_leaveGame */
}

/* ---- the selected map's preview (map `selected`, a signed byte; its name 32 bytes a slot at 0x907b30) loaded as a
   texture: "<0x680bc4><name>/<name>" (the texture manager 0xa0e010) into 0x9da324; 0x680cd0 cleared ---- */
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
/* 0x43bcb0: the game room's (selection 0x4df9e8); 0x40b420: the arena screen's (0x4db548) */
void (room_loadMapPreview)(void) { load_map_preview(ADDR(g_roomMap)); }
void (arena_loadMapPreview)(void) { load_map_preview(ADDR(g_newArenaMap)); }

/* 0x433d30: the typed line (0x9dc92c) committed to the room field being edited (when the keyboard was let go for it,
   0x68039c: the edit window 0x9dd888 destroyed and the focus back on the main window first): the room name
   (0x9dd1d8, 30 bytes), two short fields (0x9dd1f6, 0x9dd202, 12 bytes) or the comment (0x9dd20e, 50 bytes).
   Returns what the original leaves in eax */
/* typing closed if it was on: the hidden EDIT control destroyed, the focus back to the game window and the line
   closed (chat_closeLine); returns that call's eax, or 0 */
static u32 typing_end(void)
{
	if (!g_textFieldOpen)
		return 0;
	DestroyWindow(g_hChatEdit);   /* DestroyWindow */
	SetFocus(g_mainWindow);   /* SetFocus */
	return chat_closeLine(1);   /* chat_closeLine */
}

u32 (account_endTyping)(void)
{
	static const struct { u32 editing, field, size; } fields[4] = {
		{ ADDR(g_typingAccountName), OBJ(g_accountName), 30 }, { ADDR(g_typingAccountPassword), OBJ(g_accountPassword), 12 }, { ADDR(g_typingAccountRepeat), OBJ(g_accountPasswordRepeat), 12 }, { ADDR(g_typingAccountEmail), OBJ(g_accountEmail), 50 } };
	u32 r = typing_end();
	const char *typed = g_chatLine;
	for (int k = 0; k < 4; k++) {
		if (GAME_VAR(int, fields[k].editing) != 1)
			continue;
		memset((void *)RELOC(fields[k].field), 0, fields[k].size);
		strcpy((char *)RELOC(fields[k].field), typed);
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
	const u8 *room = (const u8 *)OBJ(g_roomRecName);
	u32 step = (*(u32 *)&g_connectStep);
	if (step == 2)
		return 2;
	if (step == 1) {
		g_connectionAwaited = 0;
		g_quitAsked = 1;
		g_netRole = 1;
		music_shutdown();
		g_roomMode = 0;
		GAME_FN(arena_openSession, 0x452ec0, int, int, int)(0, 0);   /* arena_openSession */
		dplay_host(
			room, g_joinedTitleName, (signed char)room[0x23], (signed char)room[0x21], (signed char)room[0x23],
			room[0x24], room[0x25], 0);   /* dplay_host: host */
		g_missionStage = (signed char)room[0x20];
		g_chosenGameMode = (signed char)room[0x23];
		memcpy((void *)OBJ(g_mapTitle), room, 32);
		g_mapRotation = (signed char)room[0x22];
		g_fragLimit = room[0x24];
		g_timeLimit = room[0x25];
		step = (*(u32 *)&g_connectStep);
		g_arenaGameSetUp = 1;
	}
	switch (step) {
	case 3:
		g_arenaLeaving = 1;
		/* fall through */
	case 0:
		g_connectionAwaited = 0;
		g_arenaGameSetUp = 0;
		g_connectStep = 2;
		return step;
	case 4:
		g_connectionAwaited = 0;
		g_connectStep = 2;
		g_arenaGameSetUp = 0;
		return menu_showMessage(0x2a);   /* the message */
	}
	return step;
}

/* 0x434e70: the window closed while connecting. An arena wait (0x4dbb78): it ends, the arena is left and message
   0x44. Joining a listed game (0x4db708; its g_sessionList entry, row 0x4db710): the entry's
   guid from the session received (0x4dbbf8) and its frag and time limits (0x5b1b54/55) for the join. Joined (0x1f4): the music stopped and the
   player's settings taken from the record for the game; otherwise a message by the result and the arena left.
   Returns what the original leaves in eax */
u32 (app_onClose)(void)
{
	if (g_arenaJoinWaiting) {
		g_arenaSearchTicks = 0;
		g_arenaJoinWaiting = 0;
		arena_leaveSession();
		u32 r = menu_showMessage(0x44);   /* the message */
		g_arenaConfirming = 0;
		return r;
	}
	if (!g_arenaJoinPending)
		return 0;
	u32 row = (*(u32 *)&g_arenaJoinRow);
	SessionEntry *game = &g_sessionList[row];
	game->guid = ((const SessionDesc *)g_receivedSession)->guid;
	g_roomRecFragLimit = game->fragLimit;
	g_roomRecTimeLimit = game->timeLimit;
	int r = dplay_join(0, (int)game->guid, (void *)OBJ(g_joinedTitleName), 0);   /* dplay_join */
	if (r != 0x1f4) {
		static const u8 message[5] = { 0x43, 0x42, 0x42, 0x44, 0x45 };
		if ((u32)(r - 0x1f5) <= 4)
			menu_showMessage(message[r - 0x1f5]);
		u32 e = arena_leaveSession();
		g_arenaSearchTicks = 0;
		g_arenaJoinPending = 0;
		g_arenaConfirming = 0;
		return e;
	}
	music_shutdown();
	g_quitAsked = 1;
	g_netRole = 2;
	g_roomMode = 0;
	g_arenaSearchTicks = 0;
	g_arenaJoinPending = 0;
	g_arenaConfirming = 0;
	g_missionStage = game->map;
	memcpy((void *)OBJ(g_mapTitle), game->name, 32);
	g_mapRotation = game->rotation;
	g_chosenGameMode = game->gameMode;
	g_fragLimit = game->fragLimit;
	g_timeLimit = game->timeLimit;
	return row * sizeof(SessionEntry);   /* (the original's eax: the entry's offset) */
}

/* 0x4346c0: the account form checked (name 0x9dd1d8, password 0x9dd1f6 and its repeat 0x9dd202, e-mail 0x9dd20e):
   a blank name, a bad name or password character, a missing or mismatched password and a bad e-mail each give
   their message and reopen the field; all good, the next dialog (0x433980). Returns that call's eax */
u32 (account_checkForm)(void)
{
	account_endTyping();   /* account_endTyping */
	g_textFieldOpen = 0;
	g_fieldTabKey = 0;
	const char *name = g_accountName, *password = g_accountPassword;
	int message, reopen;
	if (strlen(name) == 0 || name_isBlank(name) == 1)   /* name_isBlank: blank */
		message = 0x24, reopen = ADDR(g_typingAccountName);
	else if (room_nameHasBadChar(name) == 1)                  /* room_nameHasBadChar: a bad character */
		message = 0x15a, reopen = ADDR(g_typingAccountName);
	else if (strlen(password) == 0)
		message = 0x25, reopen = ADDR(g_typingAccountPassword);
	else if (strcmp(password, g_accountPasswordRepeat))
		message = 0x21, reopen = ADDR(g_typingAccountPassword);
	else if (room_nameHasBadChar(password) == 1)
		message = 0x15b, reopen = ADDR(g_typingAccountPassword);
	else if (room_nameHasBadChar(g_accountEmail) == 1)
		message = 0x81, reopen = ADDR(g_typingAccountEmail);
	else
		return room_openDialog58();   /* the next dialog */
	u32 r = menu_showMessage(message);
	GAME_VAR(int, reopen) = 1;
	return r;
}

/* 0x434b90: the account change sent: the old password (0x9dd6d8) right and the new one repeated, every field free
   of bad characters (else message 0x81 and 0x9dd1c8 cleared), the name, password and e-mail go out in message 0x1c.
   1 when sent */
int (account_sendChange)(void)
{
	if (strcmp((const char *)ADDR(g_joinedTitleLevel), g_accountOldPassword) || strcmp(g_accountPassword, g_accountPasswordRepeat))
		return 0;
	static const u32 fields[4] = { OBJ(g_accountOldPassword), OBJ(g_accountPassword), OBJ(g_accountPasswordRepeat), OBJ(g_accountEmail) };
	for (int i = 0; i < 4; i++)
		if (room_nameHasBadChar((const char *)RELOC(fields[i])) == 1) {   /* room_nameHasBadChar */
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
		u32 column = (*(u32 *)&g_rankingSort);
		static const int code[3] = { 0x25, 0x23, 0x26 };
		if (column == 3) {
			g_rankingRequestPending = 0;
			return 3;
		}
		int *out = g_netRankingBuffer;
		if (column < 3)
			out[0] = code[column];
		int page = g_roomListPage;
		g_rankingFirst = page * 10 + 1;
		g_rankingLast = page * 10 + 10;
		out[1] = page * 10 + 1;
		net_send(0x15, 0x65);   /* net_send */
		g_rankingRequestPending = 0;
		g_lobbyBlinkClock = 1000.0f;
		g_rankingWaiting = 1;
	}
	room_drawTunnel();   /* room_drawTunnel: the tunnel */
	int mode = g_roomMode;
	if (mode == 1 || mode == 0 || g_roomState == 99)
		return mode;
	if (g_dialogOpen) {
		const int *box = g_roomMessageRect;
		menu_drawFrame(box[0], box[1], box[2], box[3]);   /* the message box */
		if (g_dialogOpen)
			return (*(u32 *)&g_dialogOpen);
		g_rankingRequestPending = 1;
		return 0;
	}
	if (g_rankingWaiting) {
		if (g_roomListWaiting) {
			roomList_fillPage();   /* roomList_fillPage: the list filled */
			g_rankingWaiting = 0;
			g_rankingHaveList = 1;
			g_roomListWaiting = 0;
			g_roomListPrev = g_rankingSort;
			g_roomListPrevPage = g_roomListPage;
		}
		long double blink = fld_m((const float *)ADDR(g_lobbyBlinkClock)) - fmul_m(fld_m((const float *)ADDR(g_frameTime)), (const float *)ADDR(g_lobbyBlinkRate));
		g_lobbyBlinkClock = f32(blink);
		if (!(blink >= 0))
			g_lobbyBlinkClock = 1000.0f;
	}
	return call_keeping_ebp(FN_ADDR(ranking_drawTable, 0x43d060));   /* ranking_drawTable: the table */
}

/* 0x434490: the login sent: typing closed and the form's flags cleared; a name or password with a character the
   messages cannot carry gives its message (0x15a / 0x15b, 0x9dd1c8 cleared); else the name and password are kept
   (0x9dd570, 30 bytes, and 0x9dd58e, 12) and sent as message 0x18 (net_send 0xe), then 0x9dd838 set. Returns the
   message's or the send's eax */
u32 (login_send)(void)
{
	typing_end();
	g_typingGameName = 0;
	g_typingGamePassword = 0;
	g_inputLineHidden = 0;
	g_textFieldOpen = 0;
	const char *name = g_accountName, *password = g_accountPassword;
	int bad = room_nameHasBadChar(name) == 1 ? 0x15a
	        : room_nameHasBadChar(password) == 1 ? 0x15b : 0;   /* room_nameHasBadChar */
	if (bad) {
		u32 r = menu_showMessage(bad);
		g_roomLoginDue = 0;
		return r;
	}
	memset((void *)OBJ(g_joinedTitleName), 0, 30 + 12);
	strcpy(g_joinedTitleName, name);
	strcpy((char *)ADDR(g_joinedTitleLevel), password);
	AccountPacket *account = (*(AccountPacket **)&g_accountPacket);
	memset(account->name, 0, 30);
	memset(account->password, 0, 12);
	strcpy(account->name, name);
	strcpy(account->password, password);
	account->kind = 0x18;
	u32 r = net_send(0xe, 0x65);
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
	u32 mode = (*(u32 *)&g_roomMode);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	int waiting = g_rankingWaiting;
	if (g_keyEnter && !waiting)
		g_roomMode = 0;
	if (!g_mouseClick)
		return mode;
	u32 button = ranking_hitTest(g_mouseX, g_mouseY);   /* ranking_hitTest */
	if (button > 8 || button == 6 || (button == 3 ? !g_rankingWaiting : g_rankingWaiting != 0))
		return button;
	u32 r = sound_playMenu(0);   /* the click sound */
	static const u32 page[3] = { FN_ADDR(roomList_prevPage, 0x435970), FN_ADDR(roomList_nextPage, 0x4359b0), FN_ADDR(roomList_cycleMode, 0x4359f0) };
	int column;
	switch (button) {
	case 0: case 1: case 2:
		return GAME_CDECL(page[button], u32, void)();
	case 3:
		g_rankingHaveList = 1;
		g_rankingWaiting = 0;
		g_roomListWaiting = 0;
		g_rankingSort = g_roomListPrev;
		return (*(u32 *)&g_roomListPage) = (*(u32 *)&g_roomListPrevPage);
	case 4:
		g_roomMode = 0;
		return r;
	}
	column = button == 5 ? 0 : button == 7 ? 1 : 2;   /* 5, 7, 8 */
	u32 old = (*(u32 *)&g_rankingSort);
	(*(u32 *)&g_roomListPrev) = old;
	g_rankingSort = column;
	g_rankingRequestPending = 1;
	g_rankingHaveList = 0;
	g_roomListWaiting = 0;
	g_playerListRefused = 0;
	g_playerListCount = 0;
	return button == 8 ? old : r;
}

/* 0x436400: the game room's settings page clicked (no field being typed in, room modes other than 0 / 1, no message
   box; a right click closes the page). Buttons (roomSettings_hitTest): 0 / 1 type the room's name or password
   (field_editComment / 433a80), 3 the players +2 (4 .. 16, then 2), 5 the game type on (with a turn key held back) through
   0 .. 9, 6 / 7 the frag and time limits +5 (up to 50 / 60, then 5), 8 start (room_announceGame; not while connecting),
   9 close, 11 / 2, 10, 12 the map back / on (room_stepMap), 13 the map list (mapList_startEdit). Returns what the original
   leaves in eax (for the byte settings, its low byte the new value) */
u32 (room_settingsClicks)(void)
{
	static const u32 typing[4] = { ADDR(g_editingRoomName), ADDR(g_editingFragLimit), ADDR(g_editingTimeLimit), ADDR(g_editingRoomPassword) };
	for (int k = 0; k < 4; k++)
		if (GAME_VAR(int, typing[k]))
			return GAME_VAR(u32, typing[k]);
	u32 mode = (*(u32 *)&g_roomMode);
	if (mode == 1 || mode == 0)
		return mode;
	if (g_dialogOpen)
		return (*(u32 *)&g_dialogOpen);
	if (g_keyEnter)
		g_roomMode = 0;
	if (!g_mouseClick)
		return 0;
	u32 button = ((u32)roomSettings_hitTest(g_mouseX, g_mouseY));   /* roomSettings_hitTest */
	u8 *players = (u8 *)ADDR(g_roomPlayers), *type = (u8 *)ADDR(g_roomGameMode), *frags = (u8 *)ADDR(g_roomFragLimit), *time = (u8 *)ADDR(g_roomTimeLimit);
	u32 r;
	switch (button) {
	case 0:
		return field_editComment();   /* field_editComment */
	case 1:
		return field_editPassword();   /* field_editPassword */
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
		g_roomMode = 0;
		return r;
	case 13:
		sound_playMenu(0);
		return mapList_startEdit(2);   /* mapList_startEdit: the map list (the original pushes a 2 it ignores) */
	}
	return button;
}

/* 0x437630: the game room's settings page after typing (not while typing or with a message box): a typed field is
   taken (the room's name into 0x4df9c8 unless blank (sound 6); the password into 0x4df9ee; the frag and time limits
   as numbers into the bytes 0x4df9ec / 0x4df9ed; an empty line changes nothing), else the keys: start (0x4e1510;
   room_announceGame, not while connecting) and the two close keys (0x4e0cdc, 0x76d48c). Returns what the original leaves
   in eax */
u32 (room_settingsAfterTyping)(void)
{
	if (g_dialogOpen)
		return (*(u32 *)&g_dialogOpen);
	if (g_textFieldOpen)
		return 0;
	const char *line = g_chatLine;
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
	if (g_mapPreviewChanged)
		GAME_CDECL(reload, void, void)();
	if (GAME_VAR(u8, custom)) {
		Color4_set(g_rectColour, 0.0f, 0.0f, 0.0f, 0.4f);
		menu_drawRect(X0, Y0, X1, Y1, 1);
		Color4_set(g_textColour, 1.0f, 1.0f, 0.0f, 1.0f);
		text_drawBox16(X0, panel[0] + 0x88, X1, (const char *)STR(0x4ad56c, "CUSTOM"));
	} else {
		glEnable(GL_TEXTURE_2D);
		int texture = g_mapPreviewTexture;
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
	Color4_set(g_rectColour, 1.0f, 1.0f, 0.0f, 1.0f);
	return menu_drawRect(X0, Y0, X1, Y1, 0);   /* menu_drawRect: the outline */
#undef X0
#undef X1
#undef Y0
#undef Y1
}

/* 0x43bde0: the game room's (panel 0x9dd1bc, custom flag 0x4df9ea, room_loadMapPreview); 0x40b550: the arena screen's
   (0x4dbb04, 0x4db54a, arena_loadMapPreview) */
u32 (room_drawCustomOption)(void) { return map_preview_box((const int *)ADDR(g_roomFormTop), ADDR(g_roomCustom), FN_ADDR(room_loadMapPreview, 0x43bcb0)); }
u32 (arena_drawCustomOption)(void) { return map_preview_box((const int *)ADDR(g_newArenaFormTop), ADDR(g_newArenaKind), FN_ADDR(arena_loadMapPreview, 0x40b420)); }

/* 0x43e7b0: the account page (room page 0; room modes other than 0 / 1, not page 99): with a message box only its
   frame; else the page (0x433610 when 0x9dd354, then account_drawPanel) and, once a field's typing has ended, the typed
   line taken into it (the name, password, its repeat (12 bytes each) or the e-mail (50)) and the key that ended it
   (0x9dc428: 0xa back, 0x14 on) opening the field before or after (account_editOldPassword .. 434260). Returns what the
   original leaves in eax */
u32 (account_page)(void)
{
	static const struct { u32 editing, field, size, back, on; } fields[4] = {
		{ ADDR(g_editingOldPassword), OBJ(g_accountOldPassword), 12, 0, FN_ADDR(account_editPassword, 0x4340e0) }, { ADDR(g_editingAccountPassword), OBJ(g_accountPassword), 12, FN_ADDR(account_editOldPassword, 0x434020), FN_ADDR(account_editPasswordRepeat, 0x4341a0) },
		{ ADDR(g_editingPasswordRepeat), OBJ(g_accountPasswordRepeat), 12, FN_ADDR(account_editPassword, 0x4340e0), FN_ADDR(account_editEmail, 0x434260) }, { ADDR(g_editingEmail), OBJ(g_accountEmail), 50, FN_ADDR(account_editPasswordRepeat, 0x4341a0), 0 } };
	room_drawTunnel();   /* room_drawTunnel: the tunnel */
	u32 mode = (*(u32 *)&g_roomMode);
	if (mode == 1 || mode == 0 || g_roomState == 99)
		return mode;
	if (g_dialogOpen)
		return menu_drawFrame(g_accountPanelLeft, g_accountPanelTop,
		                                                     g_accountPanelRight, g_accountPanelBottom);
	if (g_accountNotice)
		room_selectJoinedSession();
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
		strcpy((char *)RELOC(fields[k].field), g_chatLine);
		u32 key = (*(u32 *)&g_fieldTabKey);
		u32 next = key == 0xa ? fields[k].back : key == 0x14 ? fields[k].on : 0;
		if (!next)
			return key;
		r = GAME_CDECL(next, u32, void)();
		if (!(k == 2 && key == 0xa))   /* (the original keeps the key there) */
			g_fieldTabKey = 0;
		return r;
	}
	return r;
}

/* ---- the server login dialog's keys: its text fields (0x74de1c: 0 .. 2), the text cursor placed in the one typed
   into (0x67ef34 / 0x67fb38) ---- */
#define g_loginField g_dialogChoice
#define g_tabDirection g_fieldTabKey   /* 20 forward, 10 back (shift) */

/* the cursor into field to at (x, y) */
static void login_field(int to, int x, int y)
{
	g_loginField = to;
	g_highlightShown = 1;
	(*(u32 *)&g_highlightSize) = 0x41a00000;   /* 20 */
	(*(u32 *)&g_highlightAlpha) = 0x3ecccccd;   /* 0.4 */
	g_highlightX = x;
	g_highlightY = y;
	g_tabDirection = 0;
}

/* OK (button 4 clicked, or the OK key) logs in (account_checkForm), cancel (button 5, or 0x4e0cdc) closes (room_openDialog42);
   neither while a message is up (0x68039c) */
static int login_buttons(void)
{
	int button = -1;
	if (input_justPressed(g_dikEnter) == 1)
		button = loginForm_hitTest(g_mouseX, g_mouseY);   /* loginForm_hitTest */
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
			account_checkForm();   /* account_checkForm */
		else
			room_openDialog42();   /* room_openDialog42 */
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
	if (input_justPressed(g_dikTab) != 1 || g_textFieldOpen)
		return;
	g_tabDirection = 20;
	if (input_isDown(g_dikLShift) == 1 || input_isDown(g_dikRShift) == 1)
		g_tabDirection = 10;
	if (g_tabDirection == 20) {
		if (g_loginField == 1)
			login_field(2, g_loginFormLeft + 0x172, g_loginFormBottom - 0x30);
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
			login_field(1, g_loginFormLeft + 0xaa, g_loginFormBottom - 0x30);
	}
}
#undef g_tabDirection
#undef g_loginField

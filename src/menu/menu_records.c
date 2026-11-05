/* menu_records.c: the front end's small records: the lobby player name, the data paths, the chat input line and
   its history, the message box line, the session records of the arena list, the saved mech, and the paged lists
   of the room and skirmish screens. */
#include "../game.h"
#include <string.h>

/* a name field cleared, then the name copied in (the lobby and room code always do both) */
static void copy_name(u32 dst, int clear_bytes, const char *src)
{
	memset((void *)RELOC(dst), 0, clear_bytes);
	strcpy((char *)RELOC(dst), src);
}

/* ---- the lobby player record (0x4db560: name, two fields) ---- */
/* 0x4050f0: "PLAYER" (0x4ad4b0) and both fields 0 */
void (cfg_defaultPlayerName)(void)
{
	copy_name(OBJ(g_arenaName), 32, (const char *)STR(0x4ad4b0, "PLAYER"));
	g_arenaCorporation = 0;
	g_arenaSex = 0;
}

/* 0x404930: the profile's name and fields (0x4dedb0) */
void (arena_copyProfile)(void)
{
	g_arenaSex = g_playerSex;
	copy_name(OBJ(g_arenaName), 32, g_cfgPlayerName);
	g_arenaCorporation = g_playerCorporation;
}

/* 0x43f5a0: "initdata/" (0x4b29bc) into both data path buffers, the stage path (0x4b0498) into the third */
void (app_setDataPaths)(void)
{
	copy_name(OBJ(g_dataDir), 0x105, (const char *)STR(0x4b29bc, "initdata/"));
	copy_name(OBJ(g_mapInfoDir), 0x105, (const char *)STR(0x4b29bc, "initdata/"));
	copy_name(OBJ(g_stageDir), 0x105, (const char *)STR(0x4b0498, "stage/"));
}

/* ---- the chat input line (0x400 bytes at 0x9dc92c) and its three-line history ---- */
/* 0x431560: the line emptied, in input mode mode */
void (menu_clearInputBuffer)(int mode)
{
	memset((void *)OBJ(g_chatLine), 0, 0x400);
	g_chatLength = 0;
	g_typedLength = mode;
}

/* 0x4315c0: the line pushed onto the history (the oldest line dropped) */
void (chat_pushHistory)(void)
{
	memcpy((void *)(OBJ(g_chatHistory) + 0x800), (void *)(OBJ(g_chatHistory) + 0x400), 0x400);
	memcpy((void *)(OBJ(g_chatHistory) + 0x400), (void *)OBJ(g_chatHistory), 0x400);
	memcpy((void *)OBJ(g_chatHistory), (void *)OBJ(g_chatLine), 0x400);
}

/* 0x41ee40: message i of the 0x80-byte table at 0x74de24 shown in the message box */
void (menu_showMessage)(int i)
{
	g_dialogPending = 1;
	memset((void *)OBJ(g_messageBoxLine), 0, 0x50);
	g_lobbyReply = 0;
	strcpy(g_messageBoxLine, (const char *)(MSG(0, "PRESS ENTER OR CLICK MOUSE") + i * 0x80));
}

/* ---- session list entries (SessionEntry) ---- */
/* 0x4065a0: entries a and b swapped */
void (record_swap)(void *a, void *b)
{
	SessionEntry t;
	memcpy(&t, a, sizeof t);
	memcpy(a, b, sizeof t);
	memcpy(b, &t, sizeof t);
}

/* 0x4045e0: session list entry g_gameCount (0x67ef30) cleared (all but its guid and rotation); the original does it
   256 times over without moving on */
void (arena_clearSessionEntry)(void)
{
	SessionEntry *e = &g_sessionList[g_gameCount];
	memset(e->name, 0, 32);
	e->map = 0;
	e->gameMode = 0;
	e->maxPlayers = 0;
	e->players = 0;
	e->fragLimit = 0;
	e->timeLimit = 0;
	e->ping = 0;
}

/* ---- the saved mech (0x4dc878 parts, 0x4dcf18 weapons, 0x4dcfe0 colours) ---- */
/* 0x430390: the empty mech: no weapons, part 0, colour pairs (0,1,0) (0,1,0) */
void (mech_setEmpty)(void)
{
	static const float colour[6] = { 0, 1, 0, 0, 1, 0 };
	g_savedMechItem3 = g_savedMechItem4 = g_savedMechItem5 =
		g_savedMechWeapons = g_savedMechItem1 = -1;
	g_savedMechParts = g_savedMechChest = g_savedMechArm =
		g_savedMechLeg = g_savedMechBooster = 0;
	g_savedMechItem2 = 0;
	for (u32 p = OBJ(g_savedColourChoices); p < (OBJ(g_savedColourChoices) + 0x78); p += 24)
		memcpy((void *)RELOC(p), colour, 24);
}

/* 0x40ddb0: the mech unpacked from the network / profile record at 0x9dd5f8 (signed bytes: five parts, the weapons,
   then the colours) */
void (mech_unpackFromRecord)(void)
{
	const signed char *rec = (const signed char *)OBJ(g_roomMech);
	g_savedMechParts = rec[0];
	g_savedMechChest = rec[1];
	g_savedMechArm = rec[2];
	g_savedMechLeg = rec[3];
	g_savedMechBooster = rec[4];
	for (int i = 0; i < 4; i++)
		GAME_VAR(int, OBJ(g_savedMechSettings) + 8 + i * 4) = rec[7 + i];   /* (items 2 .. 5) */
	g_savedMechItem1 = rec[6];
	g_savedMechWeapons = rec[5];
	memcpy((void *)OBJ(g_savedColourChoices), (void *)OBJ(g_roomColours), 0x90);
}

/* 0x4463a0: the mech loaded from the profile record (0x9f19f8 ..): the parts, the weapons, the six colour pairs (a
   negative or NaN chroma or value becomes 0 in the record first) */
void (mech_loadFromProfile)(void)
{
	g_savedMechChest = g_profileMechChest;
	g_savedMechParts = g_profileMechRecord;
	g_savedMechArm = g_profileMechArm;
	g_savedMechBooster = g_profileMechBooster;
	g_savedMechLeg = g_profileMechLeg;
	g_savedMechItem2 = g_profileMechItem2;
	g_savedMechItem4 = g_profileMechItem4;
	g_savedMechItem3 = g_profileMechItem3;
	g_savedMechItem5 = g_profileMechItem5;
	g_savedMechWeapons = g_profileMechItem0;
	g_savedMechItem1 = g_profileMechItem1;
	for (int o = 0; o < 0x90; o += 0x18) {
		if (!(GAME_VAR(float, OBJ(g_campaign) + 0x320 + o) >= 0.0f))
			GAME_VAR(int, OBJ(g_campaign) + 0x320 + o) = 0;
		if (!(GAME_VAR(float, OBJ(g_campaign) + 0x324 + o) >= 0.0f))
			GAME_VAR(int, OBJ(g_campaign) + 0x324 + o) = 0;
		memcpy((void *)(OBJ(g_savedColourChoices) + o), (void *)((OBJ(g_campaign) + 0x31c) + o), 0x18);
	}
}

/* 0x4464b0: the mech stored into the profile record (the inverse of mech_loadFromProfile) */
void (mech_storeToProfile)(void)
{
	g_profileMechRecord = g_savedMechParts;
	g_profileMechChest = g_savedMechChest;
	g_profileMechLeg = g_savedMechLeg;
	g_profileMechArm = g_savedMechArm;
	g_profileMechBooster = g_savedMechBooster;
	g_profileMechItem3 = g_savedMechItem3;
	g_profileMechItem2 = g_savedMechItem2;
	g_profileMechItem4 = g_savedMechItem4;
	g_profileMechItem1 = g_savedMechItem1;
	g_profileMechItem5 = g_savedMechItem5;
	g_profileMechItem0 = g_savedMechWeapons;
	memcpy((void *)(OBJ(g_campaign) + 0x31c), (void *)OBJ(g_savedColourChoices), 0x90);
}

/* 0x447910: the menu camera put back (armc_restoreMenuCamera without its flag) */
void (menu_restoreCamera)(void)
{
	(*(int *)&g_menuCameraPos) = g_camPoint0X;
	(*(int *)&g_armcCamHeight) = g_camPoint0Y;
	(*(int *)&g_armcCamDistance) = g_camPoint0Z;
	(*(int *)&g_menuCameraLook) = g_camAim0X;
	(*(int *)&g_menuCameraLookY) = g_camAim0Y;
	g_menuCameraHeight = g_camAim0Z;
}

/* 0x445de0: a click (either button) starts the menu fade, once */
void (menu_clickStartFade)(void)
{
	if ((g_mouseClick || g_keyEnter) && !g_titleShown) {
		g_titleShown = 1;
		g_titleFrames = 0;
	}
}

/* ---- the room list's pages: page 0x9dd6ac of 0x9dd4b8 (at most 99), the page before in 0x9dd1b4 ---- */
static void room_pageChanged(void)
{
	g_rankingRequestPending = 1;
	g_rankingHaveList = 0;
	g_roomListWaiting = 0;
	g_playerListRefused = 0;
	g_playerListCount = 0;
}

/* 0x435970, 0x4359b0: the previous and the next page */
void (roomList_prevPage)(void)
{
	int *page = &g_roomListPage;
	if (*page > 0) {
		g_roomListPrevPage = *page;
		(*page)--;
		room_pageChanged();
	}
}

void (roomList_nextPage)(void)
{
	int *page = &g_roomListPage;
	if (*page < g_roomListPages && *page < 99) {
		g_roomListPrevPage = *page;
		(*page)++;
		room_pageChanged();
	}
}

/* 0x4359f0: the list's mode cycled 0 .. 2 (the one before kept in 0x9dd300), its distance limit back to 10,000,000 */
void (roomList_cycleMode)(void)
{
	int mode = g_rankingSort;
	g_roomListPrev = mode;
	room_pageChanged();
	g_roomListPrevRank = 0;
	g_roomListDistanceLimit = 0x4b189680;   /* 10000000.0f */
	g_rankingSort = (mode + 1) % 3;
}

/* the value a row is ranked by in mode (0x9dd1d0): 0 its power, 1 its kills, 2 its exp, 3 its rate; another mode
   keeps the one before (0: none) */
static int rank_value(const RankRow *row, int mode, long double *value)
{
	if (mode == 0)
		*value = fld_m(&row->power);
	else if (mode == 1)
		*value = (long double)row->kills;
	else if (mode == 2)
		*value = (long double)row->exp;
	else if (mode == 3)
		*value = fld_m(&row->rate);
	else
		return 0;
	return 1;
}

/* 0x435770: the room list's page of ten rows (0x44 bytes from 0x9dceec) filled from the players received (62-byte
   records from 0xa05330, up to the first without a name): each row its rank (page 0x9dd6ac * 10 + its place) or,
   when its value (rank_value) equals the row's before, that row's rank; the page before's last value and rank
   (0x9dd384, 0x9dd328) start the comparison, and this page's are kept there for the next */
void (roomList_fillPage)(void)
{
	RankRow *rows = g_roomListRows;
	for (int i = 0; i < 10; i++) {
		RankRow *row = &rows[i];
		row->rank = 0;
		memset(row->name, 0, 30);
		row->exp = row->value2a = row->kills = row->deaths = 0;   /* (power is left as it was) */
		BITS(row->rate) = 0;
		row->level = 1;
	}
	long double value = fld_m((const float *)ADDR(k_1000000f));
	float before = 1000000.0f;
	int i;
	for (i = 0; i < 10; i++) {
		const RankedPlayer *player = &g_netPlayerList[i];
		if (!player->name[0])
			break;
		RankRow *row = &rows[i];
		row->rank = i + g_roomListPage * 10 + 1;
		strcpy(row->name, player->name);
		row->exp = player->exp;
		BITS(row->power) = BITS(player->power);
		BITS(row->rate) = BITS(player->rate);
		row->value2a = player->value22;
		row->kills = player->kills;
		row->deaths = player->deaths;
		row->level = player->level;
		int mode = g_rankingSort, rank;
		if (i == 0) {
			before = (*(float *)&g_roomListDistanceLimit);
			rank = g_roomListPrevRank;
		} else {
			long double v;
			rank = row[-1].rank;
			if (rank_value(&row[-1], mode, &v))
				before = f32(v);
		}
		rank_value(row, mode, &value);
		if (!(value < before) && !(value > before))   /* (fcom: unordered counts as equal) */
			row->rank = rank;
	}
	(*(float *)&g_roomListDistanceLimit) = f32(value);
	g_roomListPrevRank = rows[i - 1].rank;
}

/* ---- the skirmish list: eight rows shown from entry top, the cursor on row; sel = top + row ---- */
#define sk_top g_missionTop
#define sk_row g_skirmishRow
#define sk_sel g_missionPicked
#define sk_count g_missionCount

/* 0x443cd0: cursor up (the list scrolls at the top row) */
void (skirmish_cursorUp)(void)
{
	if (sk_row > 0) {
		sk_row--;
		sk_sel = sk_top + sk_row;
		return;
	}
	if (sk_top > 0)
		sk_top--;
	sk_sel = sk_top + sk_row;
}

/* 0x443d10: cursor down (the list scrolls at the bottom row) */
void (skirmish_cursorDown)(void)
{
	if (sk_top + sk_row < sk_count - 1) {
		if (sk_row < 7)
			sk_row++;
		else
			sk_top++;
		sk_sel = sk_top + sk_row;
	}
}

/* 0x443d50: a click on row */
void (skirmish_clickRow)(int row)
{
	if (sk_top + row < sk_count) {
		sk_row = row;
		sk_sel = sk_top + row;
	}
}

/* ---- the skirmish settings' undo stack: values at 0x9eeadc (depth 0x9f1060), the current one 0x9eeba4; the
   pending step 0x9ef1f4 and its flag 0x4d7348; each change clears the 400-dword work buffer at 0x9f1064 ---- */
#define undo_stack (g_undoStack)
#define undo_value g_briefingStart
#define undo_step g_briefingShown
#define undo_pending g_briefingSkipped

/* 0x443d80: the pending step pushed (value = the top - 1 + step) */
void (undo_push)(void)
{
	if (undo_pending) {
		int d = g_undoDepth;
		g_undoDepth = d + 1;
		undo_value = undo_stack[d] - 1 + undo_step;
		undo_step = 0;
		undo_stack[d + 1] = undo_value;
		memset((void *)OBJ(g_briefingText), 0, 1600);
		undo_pending = 0;
	}
}

/* 0x443de0: one step undone */
void (undo_pop)(void)
{
	if (g_undoDepth > 0) {
		g_undoDepth--;
		undo_value = undo_stack[g_undoDepth];
		memset((void *)OBJ(g_briefingText), 0, 1600);
		undo_step = 0;
		undo_pending = 0;
		g_briefingDone = 0;
	}
}

/* 0x443ea0: a click on the skirmish settings' arrows: 1 marks a change (0x9ef1f8 = 10, as a right click does), 2 adds
   the pending step, 3 undoes one */
void (skirmish_settingsArrowClick)(void)
{
	if (g_dialogOpen)
		return;
	if (!g_keyEnter) {
		if (!g_mouseClick)
			return;
		switch (briefing_hitTest(g_mouseX, g_mouseY)) {
		case 1:
			break;
		case 2:
			undo_push();
			return;
		case 3:
			undo_pop();
			return;
		default:
			return;
		}
	}
	g_settingsPage = 10;
}

/* ---- leaving the skirmish settings (0x443c80) or the mission settings (0x447960): the screen's state cleared, the
   view squeezed (aspect 0.1) to open out again, the camera to (?, 0, 1600) looking ahead, a sound, the menu camera
   put back. Both return what that leaves in eax ---- */
#define put_camera_back() GAME_FN(menu_restoreCamera, 0x447910, u32, void)()   /* menu_restoreCamera */
static u32 leave_settings(u32 state)
{
	GAME_VAR(int, state) = 0;
	(*(u32 *)&g_viewAspect) = 0x3dcccccd;   /* g_viewAspect = 0.1 */
	(*(int *)&g_armcCamHeight) = 0;
	(*(u32 *)&g_armcCamDistance) = 0x44c80000;   /* 1600 */
	(*(int *)&g_menuCameraLookY) = 0;
	g_menuCameraHeight = 0;
	sound_playMenu(4);
	return put_camera_back();
}
u32 (skirmishSettings_leave)(void) { return leave_settings(ADDR(g_settingsState)); }
u32 (missionSettings_leave)(void) { return leave_settings(ADDR(g_missionPage)); }

/* 0x4370e0: the room's two keys: the first asks to leave (0x9dd6c4 = 1), the second to go back (2), each with the
   menu sound. Returns what the original leaves in eax */
u32 (room_leaveKeys)(void)
{
	u32 r = input_justPressed(g_dikO);
	if (r == 1) {
		r = sound_playMenu(0);   /* sound_playMenu */
		g_roomPopup = 1;
		return r;
	}
	r = input_justPressed(g_dikC);
	if (r == 1) {
		r = sound_playMenu(0);
		g_roomPopup = 2;
	}
	return r;
}

/* 0x445be0: the skirmish settings screen drawn: the background (when 0x9eeba8), the map list unless closing (state
   2), the camera; then while open (state past 1) the dialog's frame if one is open, else the screen A (0x9ef1f8 10)
   or B (20). Returns what the original leaves in eax */
u32 (menuState900_skirmishSetup)(void)
{
	if (g_skirmishDrawBackground)
		menu_drawBackground();
	if (g_settingsState != 2)
		skirmish_drawTunnel();   /* skirmish_drawTunnel */
	skirmish_camera();       /* skirmish_camera: the camera */
	int state = g_settingsState;
	if (state == 1 || state == 0)
		return state;
	if (g_dialogOpen)
		return menu_drawFrame(g_briefingX, g_briefingY,
		                                                     g_briefingRight, g_briefingBottom);   /* menu_drawFrame */
	int screen = g_settingsPage;
	if (screen == 10)
		return skirmish_frameScreenA();   /* missionList_draw */
	if (screen == 20)
		return skirmish_frameScreenB();   /* missionBriefing_draw */
	return screen;
}

/* 0x444070: the skirmish settings' keys: two keys (and a third) switch to screen A (0x9ef1f8 = 10), two step the
   settings forward and back. Returns what the original leaves in eax */
u32 (skirmish_settingsKeys)(void)
{
	if (input_justPressed(g_dikA) == 1)
		return 1;
	if (input_justPressed(g_dikC) == 1 || input_justPressed(g_dikEscape_2) == 1) {
		g_settingsPage = 10;
		return 1;
	}
	if (input_justPressed(g_dikN) == 1)
		return undo_push();   /* undo_push: the pending step pushed */
	u32 r = input_justPressed(g_dikP);
	if (r == 1)
		return undo_pop();   /* undo_pop: one step undone */
	return r;
}

/* ---- the mission select (selection 0x9f63b4) ---- */
/* 0x4479d0: mission sel chosen: its 32-byte record (0x907b30) as the current one (0x67fb44), its three values from the
   0x5c-byte records of g_skirmishInfo (+0x4c ..), the settings left, mission mode (0x67ef14 = 1, 0x5ae9c4 = 3) */
u32 (mission_choose)(void)
{
	int sel = g_missionShown;
	u32 t = (u32)sel * 0x5c;
	g_missionStage = sel;
	memcpy((void *)OBJ(g_mapTitle), (const void *)(OBJ(g_mapNames) + sel * 32), 32);
	const SkirmishInfo *rec = (const SkirmishInfo *)(OBJ(g_skirmishInfo) + t);
	int a = rec->gameMode, b = rec->fragLimit, c = rec->timeLimit;
	g_mapRotation = 0;
	g_chosenGameMode = a;
	g_fragLimit = b;
	g_timeLimit = c;
	u32 r = missionSettings_leave();   /* missionSettings_leave: the settings left */
	g_quitAsked = 1;
	g_matchMode = 3;
	return r;
}

/* 0x447a50: the mission select's clicks (no dialog open): a right click leaves; buttons 0 choose, 1 leave, 2 and 3
   step the selection down and up (within 0 .. the count 0x9f181c and 14). Returns what the original leaves in eax */
u32 (missionsel_clicks)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (g_keyEnter)
		missionSettings_leave();
	if (!g_mouseClick)
		return 0;
	u32 button = ((u32)missionsel_hitTest(g_mouseX, g_mouseY));   /* the screen's hit test */
	int sel = g_missionShown;
	switch (button) {
	case 0:
		return mission_choose();   /* mission_choose */
	case 1:
		return missionSettings_leave();
	case 2:
		if (sel <= 0)
			return (u32)sel;
		g_missionShown = --sel;
		return mission_chosen(sel);   /* mission_chosen */
	case 3:
		if (sel >= g_progress || sel >= 0xe)
			return (u32)sel;
		g_missionShown = ++sel;
		return mission_chosen(sel);
	}
	return button;
}

/* 0x431600: the chat line closed: sent (into the history) when ok, else emptied; typing off, the keyboard taken again,
   the fade timer 10. Returns what the original leaves in eax */
u32 (chat_closeLine)(int ok)
{
	u32 r;
	g_textFieldOpen = 0;
	if (ok) {
		input_resetKeys();
		input_initKeyboard(g_hWndMain);
		r = chat_pushHistory();   /* chat_pushHistory: into the history */
	} else {
		if (g_typedLength > 0)
			memset((void *)OBJ(g_chatLine), 0, g_typedLength);
		input_resetKeys();
		r = (u32)input_initKeyboard(g_hWndMain);
	}
	g_typedLength = 0;
	g_chatLength = 0;
	(*(u32 *)&g_menuFade) = 0x41200000;   /* 10 */
	return r;
}

/* 0x431950: any of three keys closes the message box (0x4df900). Returns the last key's state */
u32 (messageBox_keyClose)(void)
{
	static const u32 keys[3] = { ADDR(g_dikEnter), ADDR(g_dikSpace), ADDR(g_dikEscape) };
	u32 r = 0;
	for (int k = 0; k < 3; k++) {
		r = input_justPressed(GAME_VAR(int, keys[k]));
		if (r == 1) {
			(*(int *)&g_cursorBlink) = 0;
			g_dialogPending = 0;
		}
	}
	return r;
}

/* 0x4318b0: any of three keys starts the menu's fade (0x4df01c, once; its timer 0x4e0458 from 0). Returns what the
   original leaves in eax */
u32 (menu_keyStartFade)(void)
{
	static const u32 keys[3] = { ADDR(g_dikEnter), ADDR(g_dikSpace), ADDR(g_dikEscape) };
	u32 r = 0;
	for (int k = 0; k < 3; k++) {
		r = input_justPressed(GAME_VAR(int, keys[k]));
		if (r == 1) {
			if (g_titleShown)
				return (*(u32 *)&g_titleShown);
			g_titleShown = 1;
			g_titleFrames = 0;
		}
	}
	return r;
}

/* 0x442d10: the map list's visible names: up to 10 rows, 20 pixels apart, from the first shown (0x9dd92c) of the
   0x9dd928 maps (0x44-byte records from 0x9dda88): a flagged one (+0x40) on a red bar with yellow text, the others
   pale blue. Returns the last text_draw8's eax (0 with no rows) */
u32 (mapSelect_drawNames)(void)
{
	u32 r = 0;
	for (int i = 0, dy = 0; i < g_mapSelectCount && dy < 200; i++, dy += 20) {
		set_colour_bits(g_textColour, 0x3f4ccccd, 0x3f4ccccd, 0x3f800000, 0x3f800000);   /* (0.8, 0.8, 1, 1) */
		int map = g_mapSelectFirst + i;
		if (g_fileList[map].flag) {
			set_colour_bits(g_rectColour, 0x3f800000, 0x3dcccccd, 0x3e99999a, 0x3f000000);   /* (1, 0.1, 0.3, 0.5) */
			menu_drawRect(g_mapSelectLeft + 0x20, g_mapSelectTop + dy + 0x2b, g_mapSelectRight - 0x50,
			              g_mapSelectTop + dy + 0x3d, 1);
			set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);   /* yellow */
		}
		map = g_mapSelectFirst + i;
		r = text_draw8(g_mapSelectLeft + 0x28, g_mapSelectTop + dy + 0x2c,
		                                                      g_fileList[map].name);   /* text_draw8 */
	}
	return r;
}

/* the game left for the launcher: the keys held (4), the camera pulled back (0x4deb48, next screen 210), the
   progress saved and 0x48b420. Returns its eax */
static u32 leave_game(void)
{
	menuCamera_setMove(4);
	g_enteringMenus = 1;
	g_nextScreen = 210;
	profile_saveProgress();
	return GAME_FN(debug_traceStripped, 0x48b420, u32, void)();
}

/* main menu choice i (with its sound; 0x4dda44 cleared): 0 the campaign (menuState500_enter), 1 skirmish (next
   screen 400), 2 network play (net_connect, then 0x452170; messages 0x2a / 0x29 when they fail; next screen 800), 3
   the setup (600), 4 the armour centre (0x40ee20), 5 quit. The original's eax into *r; 1 when a failure ended the
   caller there */
static int menu_choice(int i, u32 *r)
{
	sound_playMenu(0);
	if (i)
		g_cursorBlink = 0.0f;
	int result;
	switch (i) {
	case 0:
		*r = menuState500_enter();   /* menuState500_enter */
		g_enteringMenus = 0;
		return 0;
	case 2:
		result = net_connect(0x65);
		if (result == 2 || result == 0 || net_asyncSelect(g_mainWindow, 0x65) == 0) {
			sound_playMenu(6);
			*r = menu_showMessage(result == 2 ? 0x2a : 0x29);
			return 1;
		}
		/* fall through */
	case 1: case 3:
		*r = menuCamera_setMove(2);   /* menuCamera_setMove */
		g_enteringMenus = 0;
		g_nextScreen = i == 1 ? 400 : i == 2 ? 800 : 600;
		return 0;
	case 4:
		g_armcFrom = 1;
		*r = armc_enterParts();   /* armc_enterParts: the armour centre */
		g_enteringMenus = 0;
		return 0;
	default:
		*r = leave_game();
		return 0;
	}
}

/* 0x4419d0: the main menu clicked (not while it is fading in (0x9db994 = 1); the map-select dialog first if open):
   its six buttons (outlines 0x2c bytes apart from 0x4deb80) as menu_choice. A right click quits too when the game
   was started from the launcher (0x9dae10). Returns what the original leaves in eax */
u32 (mainmenu_startNetGame)(void)
{
	if (g_mainMenuFadingIn == 1)
		return 1;
	if (g_mainMenuPicked)
		return mapSelect_mouse();   /* mapSelect_mouse: the map-select dialog */
	if (g_mouseClick) {
		g_cursorBlink = 0.0f;
		const Outline *buttons = (const Outline *)OBJ(g_mainMenuOutlines);
		int i = 0;
		while (i < 6 && point_in_outline(g_mouseX, g_mouseY, buttons[i]) != 1)
			i++;
		u32 r;
		if (i < 6 && menu_choice(i, &r))
			return r;
	}
	if (!g_keyEnter)
		return 0;
	int launched = g_tunnelRings;
	if (launched <= 0)
		return launched;
	g_cursorBlink = 0.0f;
	return leave_game();
}

/* 0x441e00: the main menu's keys (not while fading in; the map-select dialog's keys (mapSelect_keys) when open):
   the six choices' keys as menu_choice, the back key quitting (without saving) when started from the launcher, and
   the map-select key (0x440d70, the dialog opened). Returns what the original leaves in eax */
u32 (mainmenu_processKeys)(void)
{
	static const u32 key[6] = { ADDR(g_dikK), ADDR(g_dikM), ADDR(g_dikL), ADDR(g_dikS), ADDR(g_dikA), ADDR(g_dikX) };
	if (g_mainMenuFadingIn == 1)
		return 1;
	if (g_mainMenuPicked)
		return mapSelect_keys();   /* mapSelect_keys */
	for (int i = 0; i < 6; i++)
		if (input_justPressed(GAME_VAR(int, key[i])) == 1) {
			u32 r;
			menu_choice(i, &r);
			return r;
		}
	if (input_justPressed(g_dikEscape_2) && g_tunnelRings > 0) {
		g_cursorBlink = 0.0f;
		menuCamera_setMove(4);
		g_enteringMenus = 1;
		g_nextScreen = 210;
		return GAME_FN(debug_traceStripped, 0x48b420, u32, void)();
	}
	u32 r = (u32)input_justPressed(g_excludedKey);
	if (r != 1)
		return r;
	r = replayList_open();
	g_mainMenuPicked = 1;
	return r;
}

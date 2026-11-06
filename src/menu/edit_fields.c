/* edit_fields.c: opening a text field for typing, on the arena screens and in the game room. Typing goes through a
   hidden EDIT control (editField_createEdit) into the shared line g_chatLine, drawn with a caret at
   (g_editCaretX, g_editCaretY); the menu keys wait meanwhile (g_textFieldOpen, g_menuKeyGuard). Each field starts from its
   current text (copied in) or empty, and raises its own "being edited" flag. */
#include "../game.h"

/* where each screen's panel is (its top left, menu units); the fields sit at fixed offsets from it */
#define PANEL_X(addr) GAME_VAR(int, addr)
#define PANEL_Y(addr) GAME_VAR(int, (addr) + 4)
#define ARENA_SETUP ADDR(g_newArenaFormLeft)      /* the arena settings (name, password, limits) */
#define PLAYER_SETUP ADDR(g_playerSetupLeft)     /* the arena lobby's SETUP PLAYER dialog */
#define ARENA_JOIN ADDR(g_arenaGameListLeft)    /* the game list (the join password) */
#define ROOM_TOP ADDR(g_roomFormLeft)
#define ROOM_LOGIN ADDR(g_roomLoginLeft)     /* the Ladder login (ID, password) */
#define ACCOUNT ADDR(g_accountPanelLeft)       /* the account page */
#define ROOM_JOIN ADDR(g_roomGameListLeft)     /* the game list (the join password) */

/* "being edited" flags, one per field */
#define EDITING(addr) GAME_VAR(int, addr)

static void edit_start(int maxLength)
{
	input_releaseKeyboard();
	g_textFieldOpen = 1;
	menu_clearInputBuffer(maxLength);
}

static void line_clear(void)
{
	for (int i = 0; i < 0x100; i++)
		((u32 *)g_chatLine)[i] = 0;
}

static void line_set(const char *text)
{
	int i = 0;
	do
		g_chatLine[i] = text[i];
	while (text[i++] != '\0');
}

static int line_length(void)
{
	int n = 0;
	while (g_chatLine[n] != '\0')
		n++;
	return n;
}

static void caret(int x, int y)
{
	g_editCaretX = x;
	g_editCaretY = y;
}

/* ---- arena ---- */

/* 0x404cd0: the SETUP PLAYER dialog's player name (16; g_arenaPlayerName, g_typingArenaPlayerName), its caret in the
   dialog (g_playerSetupLeft + 0xc2, top + 100) */
void (arena_editPlayerName)(void)
{
	edit_start(0x10);
	line_set(g_arenaPlayerName);
	caret(PANEL_X(PLAYER_SETUP) + 0xc2, PANEL_Y(PLAYER_SETUP) + 100);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	g_typingArenaPlayerName = 1;
	g_inputLineHidden = 0;
	editField_createEdit(0x10);
}

/* 0x404d70: the new arena's game name (30; g_newArenaName, the CREATE ARENA form's first row, MSG(157) "GAME NAME";
   g_editingNewArenaName) */
void (arena_editGameName)(void)
{
	edit_start(0x1e);
	line_set(g_newArenaName);
	caret(PANEL_X(ARENA_SETUP) + 0xa4, PANEL_Y(ARENA_SETUP) + 0x32);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	g_editingNewArenaName = 1;
	g_inputLineHidden = 0;
	editField_createEdit(0x1e);
}

/* 0x404e10 / 0x404ed0: the two limits, bytes 0 and 1 of g_newArenaFragLimit, typed as up to three digits */
static void edit_limit(int value, int y, int *editing)
{
	char digits[12];
	edit_start(3);
	itoa(value, digits, 10);
	line_set(digits);
	caret(PANEL_X(ARENA_SETUP) + 0xa4, PANEL_Y(ARENA_SETUP) + y);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	*editing = 1;
	g_inputLineHidden = 0;
	editField_createEdit(3);
}

void (arena_editFragLimit)(void)
{
	edit_limit(g_newArenaFragLimit, 0xfe, &g_editingNewArenaFragLimit);
}

void (arena_editTimeLimit)(void)
{
	edit_limit(g_newArenaTimeLimit, 0x120, &g_editingNewArenaTimeLimit);
}

/* 0x404f90: the password (8), from what the line holds */
void (arena_editPassword)(void)
{
	edit_start(8);
	caret(PANEL_X(ARENA_SETUP) + 0xa4, PANEL_Y(ARENA_SETUP) + 0x54);
	g_chatLength = line_length();
	g_menuKeyGuard = 5.0f;
	g_typingArenaPassword = 1;
	g_inputLineHidden = 1;
	editField_createEdit(8);
}

/* 0x405010: the password to join a locked game (8), starting empty */
void (arena_editJoinPassword)(void)
{
	edit_start(8);
	line_clear();
	g_arenaJoinPassword = 0;
	caret(PANEL_X(ARENA_JOIN) + 0xd8, PANEL_Y(ARENA_JOIN) + 0xd0);
	g_chatLength = line_length();
	g_arenaJoinPassword4 = 0;
	g_menuKeyGuard = 5.0f;
	g_typingArenaJoinPassword = 1;
	editField_createEdit(8);
}

/* ---- the game room ---- */

/* 0x4339e0: the room's create-game form's game name (30; g_roomSettingsName, row 0 GAME NAME; g_editingRoomName) */
void (room_editGameName)(void)
{
	edit_start(0x1e);
	line_set(g_roomSettingsName);
	caret(PANEL_X(ROOM_TOP) + 0xa4, PANEL_Y(ROOM_TOP) + 0x32);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	g_editingRoomName = 1;
	g_inputLineHidden = 0;
	editField_createEdit(0x1e);
}

/* 0x433a80: the room's password (8), from what the line holds */
void (room_editPassword)(void)
{
	edit_start(8);
	caret(PANEL_X(ROOM_TOP) + 0xa4, PANEL_Y(ROOM_TOP) + 0x54);
	g_chatLength = line_length();
	g_menuKeyGuard = 5.0f;
	g_editingRoomPassword = 1;
	g_inputLineHidden = 1;
	editField_createEdit(8);
}

/* 0x433b00: the Ladder login's ID (16) */
void (roomLogin_editId)(void)
{
	edit_start(0x10);
	line_clear();
	line_set(g_accountName);
	caret(PANEL_X(ROOM_LOGIN) + 200, PANEL_Y(ROOM_LOGIN) + 0x58);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	g_typingLoginId = 1;
	g_typingLoginPassword = 0;
	g_inputLineHidden = 0;
	editField_createEdit(0x10);
}

/* 0x433bb0: the Ladder login's password (12), kept unless it is to be retyped (g_retypePassword) */
void (roomLogin_editPassword)(void)
{
	edit_start(0xc);
	line_clear();
	if (g_retypePassword == 0)
		line_set(g_accountPassword);
	caret(PANEL_X(ROOM_LOGIN) + 200, PANEL_Y(ROOM_LOGIN) + 0x88);
	g_chatLength = line_length();
	g_menuKeyGuard = 5.0f;
	g_typingLoginId = 0;
	g_typingLoginPassword = 1;
	g_inputLineHidden = 1;
	editField_createEdit(0xc);
}

/* 0x434020, 0x4340e0, 0x4341a0, 0x434260: the account page's four fields (the old password, the new one, its repeat
   (12 each, hidden) and the e-mail (50)), one below the other; opening one clears the others' flags */
static void edit_account(int field, const char *text, int y, int maxLength, int hidden)
{
	edit_start(maxLength);
	line_clear();
	line_set(text);
	caret(PANEL_X(ACCOUNT) + 0x98, PANEL_Y(ACCOUNT) + y);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	g_editingOldPassword = field == 0;
	g_editingAccountPassword = field == 1;
	g_editingPasswordRepeat = field == 2;
	g_editingEmail = field == 3;
	g_inputLineHidden = hidden;
	editField_createEdit(maxLength);
}

void (account_editOldPassword)(void) { edit_account(0, g_accountOldPassword, 0x50, 0xc, 1); }
void (account_editPassword)(void) { edit_account(1, g_accountPassword, 0x6c, 0xc, 1); }
void (account_editPasswordRepeat)(void) { edit_account(2, g_accountPasswordRepeat, 0x88, 0xc, 1); }
void (account_editEmail)(void) { edit_account(3, g_accountEmail, 0xa4, 0x32, 0); }

/* 0x434320: the password to join a locked game (8), starting empty */
void (room_editJoinPassword)(void)
{
	edit_start(8);
	line_clear();
	g_roomJoinPassword = 0;
	caret(PANEL_X(ROOM_JOIN) + 0xd8, PANEL_Y(ROOM_JOIN) + 0xd0);
	g_chatLength = line_length();
	g_roomJoinPassword4 = 0;
	g_menuKeyGuard = 5.0f;
	g_typingRoomJoinPassword = 1;
	editField_createEdit(8);
}

/* ---- the match ---- */

/* 0x44ac90: a text field in the match (the chat line), its caret at (x, y) */
void (chat_textField)(int x, int y, int maxLength)
{
	input_releaseKeyboard();
	g_textFieldOpen = 1;
	g_chatTyping = 1;
	menu_clearInputBuffer(maxLength);
	g_matchChatCaretX = x;
	g_matchChatCaretY = y;
	g_menuKeyGuard = 20.0f;
	editField_createEdit(maxLength);
}

/* 0x43f980: while typing, the line taken from the hidden EDIT control */
void (editField_readTyping)(void)
{
	if (g_textFieldOpen == 0)
		return;
	int n = GetWindowTextLengthA(g_hEditField);
	GetWindowTextA(g_hEditField, g_chatLine, n + 1);
	g_chatLength = line_length();
}

/* 0x433e60: the new-ID form's field k opened for typing: the name (16 typed, a 30-byte buffer), the password and its
   repeat (12; typed hidden, g_inputLineHidden 1) or the e-mail (40), its current text copied in, the caret by the
   form (g_newIdFormLeft; rows 0x30 apart). Another k only clears the form's flags. Returns 0 (the original's eax) */
int (newIdForm_openField)(int k)
{
	static const struct { u32 editing, text; int bufferLength, maxLength, flag; } field[4] = {
		{ ADDR(g_typingAccountName), OBJ(g_accountName), 0x1e, 0x10, 0 }, { ADDR(g_typingAccountPassword), OBJ(g_accountPassword), 0xc, 0xc, 1 }, { ADDR(g_typingAccountRepeat), OBJ(g_accountPasswordRepeat), 0xc, 0xc, 1 },
		{ ADDR(g_typingAccountEmail), OBJ(g_accountEmail), 0x28, 0x28, 0 } };
	input_releaseKeyboard();
	line_clear();
	g_textFieldOpen = 1;
	g_typingAccountName = 0;
	g_unusedLoginWord = 0;
	g_typingAccountPassword = 0;
	g_typingAccountRepeat = 0;
	g_typingAccountEmail = 0;
	g_inputLineHidden = 0;
	int row = 0;
	if ((u32)k <= 3) {
		menu_clearInputBuffer(field[k].bufferLength);
		EDITING(field[k].editing) = 1;
		if (field[k].flag)
			g_inputLineHidden = 1;
		line_set((const char *)RELOC(field[k].text));
		editField_createEdit(field[k].maxLength);
		row = k;
	}
	caret(g_newIdFormLeft + 0x94, PANEL_Y(ADDR(g_newIdFormLeft)) + row * 0x30 + 0x3c);
	g_menuKeyGuard = 5.0f;
	g_chatLength = line_length();
	return 0;
}

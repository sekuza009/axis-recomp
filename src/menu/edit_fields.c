/* edit_fields.c: opening a text field for typing, on the arena screens and in the game room. Typing goes through a
   hidden EDIT control (chat_createEdit) into the shared line g_chatLine, drawn with a caret at
   (g_chatCaretX, g_chatCaretY); the menu keys wait meanwhile (g_paused, g_menuFade). Each field starts from its
   current text (copied in) or empty, and raises its own "being edited" flag. */
#include "../game.h"

/* where each screen's panel is (its top left, menu units); the fields sit at fixed offsets from it */
#define PANEL_X(addr) GAME_VAR(int, addr)
#define PANEL_Y(addr) GAME_VAR(int, (addr) + 4)
#define ARENA_SETUP 0x4dbb00      /* the arena settings (name, password, limits) */
#define ARENA_CREATE 0x4dbb68     /* "create arena" */
#define ARENA_MESSAGE 0x4db8c8    /* the message line */
#define ROOM_TOP 0x9dd1b8
#define ROOM_GAME 0x9dd358
#define ROOM_RULES 0x9dd368
#define ROOM_MESSAGE 0x9dd4a8

/* "being edited" flags, one per field */
#define EDITING(addr) GAME_VAR(int, addr)

static void edit_start(int maxLength)
{
	input_releaseKeyboard();
	g_paused = 1;
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
	g_chatCaretX = x;
	g_chatCaretY = y;
}

/* ---- arena ---- */

/* 0x404cd0: the arena's name (16 characters) */
void (arena_editTextField_404cd0)(void)
{
	edit_start(0x10);
	line_set((const char *)0x4db560);
	caret(PANEL_X(ARENA_CREATE) + 0xc2, PANEL_Y(ARENA_CREATE) + 100);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	EDITING(0x4dbbd0) = 1;
	g_chatFieldFlag = 0;
	chat_createEdit(0x10);
}

/* 0x404d70: the arena's comment (30) */
void (arena_editTextField_404d70)(void)
{
	edit_start(0x1e);
	line_set((const char *)0x4db528);
	caret(PANEL_X(ARENA_SETUP) + 0xa4, PANEL_Y(ARENA_SETUP) + 0x32);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	EDITING(0x4dbab0) = 1;
	g_chatFieldFlag = 0;
	chat_createEdit(0x1e);
}

/* 0x404e10 / 0x404ed0: the two limits, bytes 0 and 1 of 0x4db54c, typed as up to three digits */
static void edit_limit(int value, int y, int *editing)
{
	char digits[12];
	edit_start(3);
	itoa(value, digits, 10);
	line_set(digits);
	caret(PANEL_X(ARENA_SETUP) + 0xa4, PANEL_Y(ARENA_SETUP) + y);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	*editing = 1;
	g_chatFieldFlag = 0;
	chat_createEdit(3);
}

void (arena_editNumberField_404e10)(void)
{
	edit_limit(GAME_VAR(u8, 0x4db54c), 0xfe, &EDITING(0x4db850));
}

void (arena_editNumberField_404ed0)(void)
{
	edit_limit(GAME_VAR(u8, 0x4db54d), 0x120, &EDITING(0x4db518));
}

/* 0x404f90: the password (8), from what the line holds */
void (arena_editTextField_404f90)(void)
{
	edit_start(8);
	caret(PANEL_X(ARENA_SETUP) + 0xa4, PANEL_Y(ARENA_SETUP) + 0x54);
	g_chatLength = line_length();
	g_menuFade = 5.0f;
	EDITING(0x4dbacc) = 1;
	g_chatFieldFlag = 1;
	chat_createEdit(8);
}

/* 0x405010: a message (8), starting empty */
void (arena_editTextField_405010)(void)
{
	edit_start(8);
	line_clear();
	GAME_VAR(int, 0x4db520) = 0;
	caret(PANEL_X(ARENA_MESSAGE) + 0xd8, PANEL_Y(ARENA_MESSAGE) + 0xd0);
	g_chatLength = line_length();
	GAME_VAR(int, 0x4db524) = 0;
	g_menuFade = 5.0f;
	EDITING(0x4db70c) = 1;
	chat_createEdit(8);
}

/* ---- the game room ---- */

/* 0x4339e0: the room's comment (30) */
void (field_editComment)(void)
{
	edit_start(0x1e);
	line_set((const char *)0x4df9c8);
	caret(PANEL_X(ROOM_TOP) + 0xa4, PANEL_Y(ROOM_TOP) + 0x32);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	EDITING(0x9dd380) = 1;
	g_chatFieldFlag = 0;
	chat_createEdit(0x1e);
}

/* 0x433a80: the password (8), from what the line holds */
void (field_editPassword)(void)
{
	edit_start(8);
	caret(PANEL_X(ROOM_TOP) + 0xa4, PANEL_Y(ROOM_TOP) + 0x54);
	g_chatLength = line_length();
	g_menuFade = 5.0f;
	EDITING(0x9dd6a8) = 1;
	g_chatFieldFlag = 1;
	chat_createEdit(8);
}

/* 0x433b00: the game's name (16) */
void (field_editGameName)(void)
{
	edit_start(0x10);
	line_clear();
	line_set((const char *)0x9dd1d8);
	caret(PANEL_X(ROOM_GAME) + 200, PANEL_Y(ROOM_GAME) + 0x58);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	EDITING(0x9dd830) = 1;
	EDITING(0x9dd38c) = 0;
	g_chatFieldFlag = 0;
	chat_createEdit(0x10);
}

/* 0x433bb0: the game's password (12), kept unless 0x9dced0 */
void (field_editGamePassword)(void)
{
	edit_start(0xc);
	line_clear();
	if (g_retypePassword == 0)
		line_set((const char *)0x9dd1f6);
	caret(PANEL_X(ROOM_GAME) + 200, PANEL_Y(ROOM_GAME) + 0x88);
	g_chatLength = line_length();
	g_menuFade = 5.0f;
	EDITING(0x9dd830) = 0;
	EDITING(0x9dd38c) = 1;
	g_chatFieldFlag = 1;
	chat_createEdit(0xc);
}

/* 0x434020, 0x4340e0, 0x4341a0, 0x434260: the four rule fields of the room (12, 12, 12 and 50 characters), one
   below the other; opening one clears the others' flags */
static void edit_rule(int field, const char *text, int y, int maxLength, int flag)
{
	edit_start(maxLength);
	line_clear();
	line_set(text);
	caret(PANEL_X(ROOM_RULES) + 0x98, PANEL_Y(ROOM_RULES) + y);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	EDITING(0x9dd69c) = field == 0;
	EDITING(0x9dd37c) = field == 1;
	EDITING(0x9dd378) = field == 2;
	EDITING(0x9dd304) = field == 3;
	g_chatFieldFlag = flag;
	chat_createEdit(maxLength);
}

void (room_434020)(void) { edit_rule(0, (const char *)0x9dd6d8, 0x50, 0xc, 1); }
void (room_4340e0)(void) { edit_rule(1, (const char *)0x9dd1f6, 0x6c, 0xc, 1); }
void (room_4341a0)(void) { edit_rule(2, (const char *)0x9dd202, 0x88, 0xc, 1); }
void (room_434260)(void) { edit_rule(3, (const char *)0x9dd20e, 0xa4, 0x32, 0); }

/* 0x434320: a message (8), starting empty */
void (field_editMessage)(void)
{
	edit_start(8);
	line_clear();
	GAME_VAR(int, 0x9dcee8) = 0;
	caret(PANEL_X(ROOM_MESSAGE) + 0xd8, PANEL_Y(ROOM_MESSAGE) + 0xd0);
	g_chatLength = line_length();
	GAME_VAR(int, 0x9dceec) = 0;
	g_menuFade = 5.0f;
	EDITING(0x9dd6c8) = 1;
	chat_createEdit(8);
}

/* ---- the match ---- */

/* 0x44ac90: a text field in the match (the chat line), its caret at (x, y) */
void (chat_textField)(int x, int y, int maxLength)
{
	input_releaseKeyboard();
	g_paused = 1;
	GAME_VAR(int, 0x9f67e8) = 1;
	menu_clearInputBuffer(maxLength);
	GAME_VAR(int, 0x9f63c8) = x;
	GAME_VAR(int, 0x9f63c4) = y;
	g_menuFade = 20.0f;
	chat_createEdit(maxLength);
}

/* 0x43f980: while typing, the line taken from the hidden EDIT control */
void (editField_readTyping)(void)
{
	if (g_paused == 0)
		return;
	int n = GetWindowTextLengthA(g_hChatEdit);
	GetWindowTextA(g_hChatEdit, g_chatLine, n + 1);
	g_chatLength = line_length();
}

/* 0x433e60: the login form's field k opened for typing: the name (16 typed, a 30-byte buffer), the password and
   its repeat (12; the short-field flag set) or the e-mail (40), its current text copied in, the caret by the form (0x9dd6e8; rows 0x30
   apart). Another k only clears the form's flags. Returns 0 (the original's eax) */
int (loginForm_openField)(int k)
{
	static const struct { u32 editing, text; int bufferLength, maxLength, flag; } field[4] = {
		{ 0x9dd348, 0x9dd1d8, 0x1e, 0x10, 0 }, { 0x9dd3f8, 0x9dd1f6, 0xc, 0xc, 1 }, { 0x9dd564, 0x9dd202, 0xc, 0xc, 1 },
		{ 0x9dd6cc, 0x9dd20e, 0x28, 0x28, 0 } };
	input_releaseKeyboard();
	line_clear();
	g_paused = 1;
	EDITING(0x9dd348) = 0;
	GAME_VAR(int, 0x9dd32c) = 0;
	EDITING(0x9dd3f8) = 0;
	EDITING(0x9dd564) = 0;
	EDITING(0x9dd6cc) = 0;
	g_chatFieldFlag = 0;
	int row = 0;
	if ((u32)k <= 3) {
		menu_clearInputBuffer(field[k].bufferLength);
		EDITING(field[k].editing) = 1;
		if (field[k].flag)
			g_chatFieldFlag = 1;
		line_set((const char *)field[k].text);
		chat_createEdit(field[k].maxLength);
		row = k;
	}
	caret(PANEL_X(0x9dd6e8) + 0x94, PANEL_Y(0x9dd6e8) + row * 0x30 + 0x3c);
	g_menuFade = 5.0f;
	g_chatLength = line_length();
	return 0;
}

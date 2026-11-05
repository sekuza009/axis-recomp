/* settings_form.c: the game settings form, as the game room shows it and as the arena screen shows it for a new
   arena: the window, a title, the labels down the left and each value in its box, the value under the pointer drawn
   again with a shadow in yellow, the buttons, the map preview with its arrows and the ADVANCED button (the rotation's map list). Both
   forms show a GameSettings record (the room's at g_roomSettingsName, the new arena's at g_newArenaName) in the same boxes. */
#include "../game.h"
#include <string.h>

/* where a form keeps its parts: the window (left, top, right, bottom), the record, the four "being edited" flags
   (name, password, the two limits: each hides its value), the mode names (0x80 apart), and the text of the fifth row (MAP
   ROTATION, the settings' rotation): fixed (rotationFixed: the room's "DO NOT USE") or its OFF / ON name
   (rotationNames, 20 apart: the arena's) */
typedef struct {
	u32 window;
	GameSettings *s;
	u32 edited[4];
	u32 modes;
	u32 rotationFixed, rotationNames;
	int stars;   /* the password's star buffer: 20 bytes (the room) or 10 (the arena) */
} Form;

#define X0 GAME_VAR(int, f->window)
#define Y0 GAME_VAR(int, f->window + 4)
#define X1 GAME_VAR(int, f->window + 8)
#define Y1 GAME_VAR(int, f->window + 12)

/* a value's box at (x0, y0) .. (x1, y1): black at 0.4, a cyan border at 0.5 */
static void field_box(int x0, int y0, int x1, int y1)
{
	set_colour_bits(g_rectColour, 0, 0, 0, 0x3ecccccd);
	menu_drawRect(x0, y0, x1, y1, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f000000);
	menu_drawRect(x0, y0, x1, y1, 0);
}

/* the hovered value drawn again: its shadow at (x, y), then in yellow one up and left */
static void hover_text(int x, int y, const char *text)
{
	set_colour_bits(g_textColour, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01 */
	text_draw8(x, y, text);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);            /* 1, 0.8, 0, 1 */
	text_draw8(x - 1, y - 1, text);
}

static void colour(const u32 *c)
{
	set_colour_bits(g_textColour, c[0], c[1], c[2], c[3]);
}

static const u32 k_white[4] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
#define white() colour(k_white)

static void bind_buttons(void)
{
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
}

/* the password as stars into out (cleared first, f->stars bytes) */
static const char *stars(const Form *f, char *out)
{
	memset(out, 0, f->stars);
	int n = (int)strlen(f->s->password);
	if (n > 0)
		memset(out, '*', n);
	return out;
}

static const char *map_name(const Form *f) { return (const char *)(OBJ(g_mapAbouts) + f->s->map * 0x50); }
static const char *mode_name(const Form *f) { return (const char *)(RELOC(f->modes) + f->s->mode * 0x80); }
static const char *rotation_text(const Form *f)
{
	return f->rotationNames ? (const char *)(RELOC(f->rotationNames) + f->s->rotation * 20) : (const char *)RELOC(f->rotationFixed);
}

/* the eight rows' values in their boxes (white text); a value being edited is left out */
static void draw_values(const Form *f, char *text)
{
	const GameSettings *s = f->s;
	field_box(X0 + 0x9f, Y0 + 0x2f, X0 + 0x1a7, Y0 + 0x45);
	white();
	if (!GAME_VAR(int, f->edited[0]))
		text_draw8(X0 + 0xa4, Y0 + 0x32, s->name);
	field_box(X0 + 0x9f, Y0 + 0x51, X0 + 0xef, Y0 + 0x67);
	if (!GAME_VAR(int, f->edited[1]))
		text_draw8(X0 + 0xa4, Y0 + 0x54, stars(f, text));
	field_box(X0 + 0x9f, Y0 + 0x6d, X0 + 0x18f, Y0 + 0x91);
	if (s->rotation)
		text_draw8(X0 + 0xa4, Y0 + 0x76, (const char *)STR(0x4ad56c, "CUSTOM"));   /* CUSTOM */
	else
		text_draw8(X0 + 0xa4, Y0 + 0x6f, map_name(f));
	field_box(X0 + 0x9f, Y0 + 0x95, X0 + 0xef, Y0 + 0xab);
	itoa(s->players, text, 10);
	text_draw8(X0 + 0xa4, Y0 + 0x98, text);
	field_box(X0 + 0x9f, Y0 + 0xb7, X0 + 0xef, Y0 + 0xcd);
	white();
	text_draw8(X0 + 0xa4, Y0 + 0xba, rotation_text(f));
	field_box(X0 + 0x9f, Y0 + 0xd9, X0 + 0x18f, Y0 + 0xef);
	white();
	text_draw8(X0 + 0xa4, Y0 + 0xdc, mode_name(f));
	field_box(X0 + 0x9f, Y0 + 0xfb, X0 + 0xef, Y0 + 0x111);
	white();
	if (!GAME_VAR(int, f->edited[2])) {
		itoa(s->limit[0], text, 10);
		text_draw8(X0 + 0xa4, Y0 + 0xfe, text);
	}
	field_box(X0 + 0x9f, Y0 + 0x11d, X0 + 0xef, Y0 + 0x133);
	if (!GAME_VAR(int, f->edited[3])) {
		itoa(s->limit[1], text, 10);
		text_draw8(X0 + 0xa4, Y0 + 0x120, text);
	}
}

/* the value under the pointer (rows 0 .. 7) drawn again. The map is not highlighted while the map rotation is on; in
   the arena's form the fifth row is too, and the mode only with the rotation off */
static void draw_hover(const Form *f, int hovered, char *text)
{
	const GameSettings *s = f->s;
	int arena = f->rotationNames != 0;
	switch (hovered) {
	case 0:
		hover_text(X0 + 0xa4, Y0 + 0x32, s->name);
		break;
	case 1:
		hover_text(X0 + 0xa4, Y0 + 0x54, stars(f, text));
		break;
	case 2:
		if (!s->rotation)
			hover_text(X0 + 0xa4, Y0 + 0x6f, map_name(f));
		break;
	case 3:
		itoa(s->players, text, 10);
		hover_text(X0 + 0xa4, Y0 + 0x98, text);
		break;
	case 4:
		if (arena)
			hover_text(X0 + 0xa4, Y0 + 0xba, rotation_text(f));
		break;
	case 5:
		if (!arena || !s->rotation)
			hover_text(X0 + 0xa4, Y0 + 0xdc, mode_name(f));
		break;
	case 6:
	case 7:
		itoa(s->limit[hovered - 6], text, 10);
		hover_text(X0 + 0xa4, Y0 + (hovered == 6 ? 0xfe : 0x120), text);
		break;
	}
}

/* a button (the button texture bound first) at (x0, y0) .. (x1, y1), its text at ty: lit at alpha a_lit in colour
   bright, else at 0.4 in dim */
static void button(int lit, float a_lit, int x0, int y0, int x1, int y1, int ty, const u32 *bright, const u32 *dim,
                   u32 text)
{
	glEnable(GL_TEXTURE_2D);
	bind_buttons();
	glColor4f(1.0f, 1.0f, 1.0f, lit ? a_lit : 0.4f);
	menu_drawWideButton(x0, y0, x1, y1, 1);
	colour(lit ? bright : dim);
	text_drawBox16(x0, ty, x1, (const char *)RELOC(text));
}

/* the preview's arrows (lit as given) and the ADVANCED button (the rotation's map list): lit in white, else at 0.4 in the colour other */
static void preview_controls(const Form *f, int left, int right, int rotation, const u32 *other)
{
	bind_buttons();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton1(X1 - 0x8c, Y0 + 0xd7, X1 - 0x5c, Y0 + 0xef, left);
	menu_drawSmallButton2(X1 - 0x50, Y0 + 0xd7, X1 - 0x20, Y0 + 0xef, right);
	glEnable(GL_TEXTURE_2D);
	bind_buttons();
	if (rotation) {
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		white();
	} else {
		glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
		colour(other);
	}
	menu_drawWideButton(X1 - 0x96, Y0 + 0xf5, X1 - 0x16, Y0 + 0x111, 1);
	text_drawBox16(X1 - 0x96, Y0 + 0xfb, X1 - 0x16, (const char *)MSG(501, "ADVANCED"));
}

/* 0x43bfe0: the game room's settings form (0x9dd1b8 .. 0x9dd1c4) for g_roomSettingsName: the title MSG(396, "CREATE LADDER GAME"), a cyan line, the
   labels (MSG(397, "TITLE"), 0x80 apart), the values (the fifth row's text MSG(17, "DO NOT USE"), the modes at MSG(791, "DEATH MATCH"); hidden while
   edited: g_editingRoomName, g_editingRoomPassword, g_editingFragLimit, g_editingTimeLimit). Unless a field is being edited (g_textFieldOpen) or the "leave?" box is up
   (g_arenaUpdateNotice), the value under the pointer (roomSettings_hitTest) highlighted. Two buttons (MSG(405, "$[0] O K"), lit from 8 unless
   editing), the map preview (room_drawMapPreview), its arrows (11 / 12) and the ADVANCED button (13, not while
   the map list is up, g_mapListOpen); the border. The caller ignores the eax it leaves */
void (room_drawGameSettings)(void)
{
	static const Form form = { ADDR(g_roomFormLeft), (GameSettings *)OBJ(g_roomSettingsName), { ADDR(g_editingRoomName), ADDR(g_editingRoomPassword), ADDR(g_editingFragLimit), ADDR(g_editingTimeLimit) }, MSG(791, "DEATH MATCH"),
	                           MSG(17, "DO NOT USE"), 0, 20 };
	static const u32 grey[4] = { 0x3e99999a, 0x3f333333, 0x3f333333, 0x3f800000 };   /* 0.3, 0.7, 0.7, 1 */
	const Form *f = &form;
	const u32 *bright = g_roomBright, *dim = g_roomDim;
	int editing = g_textFieldOpen, open = editing || g_arenaUpdateNotice;
	char text[20];
	int hovered = roomSettings_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	colour(bright);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)MSG(396, "CREATE LADDER GAME"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	for (int k = 0; k < 8; k++)   /* (the original would grey labels past the eighth: there are none) */
		text_draw8(X0 + 0x40, Y0 + 0x32 + k * 0x22, (const char *)(MSG(397, "TITLE") + k * 0x80));
	draw_values(f, text);
	if (!open)
		draw_hover(f, hovered, text);
	for (int k = 0; k < 2; k++) {
		int bx = X0 + k * 0xc8;
		button(hovered == k + 8 && !editing, 1.0f, bx + 0x64, Y1 - 0x40, bx + 0x104, Y1 - 0x20, Y1 - 0x38, bright, dim,
		       MSG(405, "$[0] O K") + k * 0x80);
	}
	room_drawMapPreview(f->s->map);
	preview_controls(f, hovered == 11 && !open, hovered == 12 && !open,
	                 hovered == 13 && !editing && !g_mapListOpen, grey);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
}

/* two buttons (MSG(115, "$[0] O K"), 0x80 apart) in a box over the arena form; the button lit is lit_from + its index */
static void box_buttons(int hovered, int lit_from)
{
	const u32 *bright = g_arenaBright, *dim = g_arenaDim;
	for (int k = 0; k < 2; k++) {
		int x = 0xb4 + k * 0xa0;
		button(hovered == lit_from + k, 1.0f, x, 0x104, x + 0x78, 0x124, 0x10c, bright, dim, MSG(115, "$[0] O K") + k * 0x80);
	}
}

/* 0x40b750: the arena screen's form for a new arena (0x4dbb00 .. 0x4dbb0c) for g_newArenaName: the title MSG(156, "CREATE ARENA"), the
   labels (MSG(157, "GAME NAME")), the values (the rotation's OFF / ON from g_arenaOnOff2, the modes at MSG(471, "DEATH MATCH"); hidden while edited: g_editingNewArenaName,
   g_typingArenaPassword, g_editingNewArenaFragLimit, g_editingNewArenaTimeLimit). Unless a field is being edited, the confirmation (g_hostErrorBox) or "leave?" box (g_arenaUpdateNotice)
   or the map list (g_mapListOpen) is up, the value under the pointer (createArena_hitTest) highlighted. Two buttons (MSG(165, "$[0] IPX GAME"), lit
   from 8 at 0.9) and below the second of the next pair (MSG(168, "$[0] CANCEL"), 11), the map preview (arena_drawMapPreview), its
   arrows (13 / 14) and the ADVANCED button (lit with the rotation on). The confirmation box (MSG(168, "$[0] CANCEL") / MSG(169, "NETWORK INITIALIZE ERROR"), its buttons
   15 / 16) and the "leave?" box over the whole screen (MSG(3, "THIS PROGRAM HAS BEEN UPDATED") / MSG(4, "DO DOWNLOAD A NEW VERSION"), its buttons by arenaCreate_hitTest); the border.
   The caller ignores the eax it leaves */
void (arena_createDraw)(void)
{
	static const Form form = { ADDR(g_newArenaFormLeft), (GameSettings *)OBJ(g_newArenaName), { ADDR(g_editingNewArenaName), ADDR(g_typingArenaPassword), ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit) }, MSG(471, "DEATH MATCH"),
	                           0, OBJ(g_arenaOnOff2), 10 };
	const Form *f = &form;
	const u32 *bright = g_arenaBright, *dim = g_arenaDim;
	int editing = g_textFieldOpen, hostError = g_hostErrorBox, updateNotice = g_arenaUpdateNotice;
	int open = editing || hostError || updateNotice, blocked = open || g_mapListOpen;
	char text[20];
	int hovered = createArena_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	colour(bright);
	text_draw16(X0 + 0x50, Y0 + 0x10, (const char *)MSG(156, "CREATE ARENA"));
	for (int k = 0; k < 8; k++) {
		colour(bright);
		text_draw8(X0 + 0x40, Y0 + 0x32 + k * 0x22, (const char *)(MSG(157, "GAME NAME") + k * 0x80));
	}
	draw_values(f, text);
	if (!blocked)
		draw_hover(f, hovered, text);
	for (int k = 0; k < 2; k++) {
		int bx = X0 + k * 0xfa;
		button(hovered == k + 8 && !blocked, 0.9f, bx + 0x3c, Y1 - 0x5a, bx + 0x104, Y1 - 0x3a, Y1 - 0x52, bright, dim,
		       MSG(165, "$[0] IPX GAME") + k * 0x80);
	}
	/* (the next row's first button is skipped) */
	button(hovered == 11 && !blocked, 1.0f, X0 + 0xfa + 0x3c, Y1 - 0x32, X0 + 0xfa + 0x104, Y1 - 0x12, Y1 - 0x2a, bright,
	       dim, MSG(168, "$[0] CANCEL"));
	arena_drawMapPreview(f->s->map);
	preview_controls(f, hovered == 13 && !blocked, hovered == 14 && !open, f->s->rotation == 1 && !blocked, dim);
	if (hostError) {
		glColor4f(0.7f, 0.0f, 1.0f, 1.0f);
		menu_drawTextureFlipped(0x64, 0xb4, 0x21c, 0x140, g_dialogFrameTexture);
		white();
		text_drawBox16(0x64, 0xc8, 0x21c, (const char *)MSG(168, "$[0] CANCEL"));
		text_drawBox16(0x64, 0xdc, 0x21c, (const char *)MSG(169, "NETWORK INITIALIZE ERROR"));
		box_buttons(hovered, 15);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		GAME_FN(menu_drawTopRightOrnament, 0x428b50, void, int, int, int, int)(0x64, 0xb4, 0x21c, 0x140);   /* menu_drawTopRightOrnament */
	}
	if (updateNotice) {
		int choice = arenaCreate_hitTest(g_mouseX, g_mouseY);
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3ecccccd);   /* 0.1, 0.4: the screen dimmed */
		menu_drawRect(0, 0, 0x280, 0x1e0, 1);
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f4ccccd);
		menu_drawRect(0x64, 0xb4, 0x21c, 0x140, 1);
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(0x68, 0xb8, 0x218, 0x13c, 0);
		white();
		text_drawBox16(0x64, 0xc8, 0x21c, (const char *)MSG(3, "THIS PROGRAM HAS BEEN UPDATED"));
		text_drawBox16(0x64, 0xdc, 0x21c, (const char *)MSG(4, "DO DOWNLOAD A NEW VERSION"));
		box_buttons(choice, 0);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
}
#undef X0
#undef Y0
#undef X1
#undef Y1

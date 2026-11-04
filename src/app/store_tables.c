/* store_tables.c: initialisers that set many globals to constants (or copy them from other globals): kept as tables of {address, value} stores, applied in order. Tables made by tools/straightline.py from the original code. */
#include "../game.h"

#define GAME_U32(a) GAME_VAR(u32, a)

typedef struct { u32 a, v; } Store;                 /* *(u32 *)a = v */
typedef struct { u32 a, v; u8 copy; } CStore;       /* copy: v is a source address, read when the function starts */

static void apply_stores(const Store *s, int n) { for (int k = 0; k < n; k++) GAME_U32(s[k].a) = s[k].v; }

static void apply_cstores(const CStore *s, int n)
{
	u32 val[128];
	for (int k = 0; k < n; k++) val[k] = s[k].copy ? GAME_U32(s[k].v) : s[k].v;   /* all sources read before any store */
	for (int k = 0; k < n; k++) GAME_U32(s[k].a) = val[k];
}

static const Store k_color_initDefaultColours[16] = {
	{ OBJ(g_defaultColours), 0xffffffff }, { (OBJ(g_defaultColours) + 0x4), 0xff5454f3 }, { (OBJ(g_defaultColours) + 0xc), 0xfff35466 }, { (OBJ(g_defaultColours) + 0x8), 0xffe7b7fd }, { (OBJ(g_defaultColours) + 0x10), 0xffffcc00 },
	{ (OBJ(g_defaultColours) + 0x18), 0xffa6ffcc }, { (OBJ(g_defaultColours) + 0x1c), 0xff00f0ff }, { (OBJ(g_defaultColours) + 0x20), 0xffd3c8c8 }, { (OBJ(g_defaultColours) + 0x24), 0xffa09090 }, { (OBJ(g_defaultColours) + 0x14), 0xff23d33c },
	{ (OBJ(g_defaultColours) + 0x28), 0xff859a98 }, { (OBJ(g_defaultColours) + 0x2c), 0xff000085 }, { (OBJ(g_defaultColours) + 0x30), 0xffff000c }, { (OBJ(g_defaultColours) + 0x34), 0xffff00d2 }, { (OBJ(g_defaultColours) + 0x38), 0xff3a322e },
	{ (OBJ(g_defaultColours) + 0x3c), 0xffa2ff00 } };

void (color_initDefaultColours)(void) { apply_stores(k_color_initDefaultColours, 16); }   /* 0x46dc50 default RGBA colours (bytes) */

static const Store k_intro_42f500[44] = {
	{ (OBJ(g_lobbyTopOutlines) + 0x18), 0xe7 }, { (OBJ(g_lobbyTopOutlines) + 0x28), 0xe7 }, { (OBJ(g_lobbyTopOutlines) + 0x74), 0xe7 }, { (OBJ(g_lobbyTopOutlines) + 0x4), 0xffffff65 }, { (OBJ(g_lobbyTopOutlines) + 0x14), 0xffffff65 },
	{ (OBJ(g_lobbyTopOutlines) + 0xc), 0xffffff7e }, { (OBJ(g_lobbyTopOutlines) + 0x10), 0xfffffef2 }, { (OBJ(g_lobbyTopOutlines) + 0x30), 0xfffffef2 }, { (OBJ(g_lobbyTopOutlines) + 0x34), 0xffffff7e }, { (OBJ(g_lobbyTopOutlines) + 0x40), 0xfffffef2 },
	{ (OBJ(g_lobbyTopOutlines) + 0x64), 0x10e }, { (OBJ(g_lobbyTopOutlines) + 0x8c), 0x10e }, { (OBJ(g_lobbyTopOutlines) + 0x44), 0xffffffc1 }, { (OBJ(g_lobbyTopOutlines) + 0x54), 0xffffffc1 }, { (OBJ(g_lobbyTopOutlines) + 0xa0), 0xffffffc1 },
	{ OBJ(g_lobbyTopOutlines), 0x4 }, { (OBJ(g_lobbyTopOutlines) + 0x8), 0xffffffb6 }, { (OBJ(g_lobbyTopOutlines) + 0x1c), 0x6e }, { (OBJ(g_lobbyTopOutlines) + 0x20), 0x1f }, { (OBJ(g_lobbyTopOutlines) + 0x24), 0x42 },
	{ (OBJ(g_lobbyTopOutlines) + 0x2c), 0x4 }, { (OBJ(g_lobbyTopOutlines) + 0x48), 0xffffffe2 }, { (OBJ(g_lobbyTopOutlines) + 0x38), 0xffffffb5 }, { (OBJ(g_lobbyTopOutlines) + 0x4c), 0xffffff90 }, { (OBJ(g_lobbyTopOutlines) + 0x3c), 0xffffff67 },
	{ (OBJ(g_lobbyTopOutlines) + 0x50), 0xffffff1a }, { (OBJ(g_lobbyTopOutlines) + 0x58), 0x4 }, { (OBJ(g_lobbyTopOutlines) + 0x5c), 0x49 }, { (OBJ(g_lobbyTopOutlines) + 0x70), 0x70 }, { (OBJ(g_lobbyTopOutlines) + 0x60), 0x9b },
	{ (OBJ(g_lobbyTopOutlines) + 0x78), 0x42 }, { (OBJ(g_lobbyTopOutlines) + 0x68), 0x82 }, { (OBJ(g_lobbyTopOutlines) + 0x7c), 0x1f }, { (OBJ(g_lobbyTopOutlines) + 0x6c), 0x49 }, { (OBJ(g_lobbyTopOutlines) + 0x80), 0x70 },
	{ (OBJ(g_lobbyTopOutlines) + 0x84), 0x4 }, { (OBJ(g_lobbyTopOutlines) + 0x88), 0x82 }, { (OBJ(g_lobbyTopOutlines) + 0x9c), 0xffffffe2 }, { (OBJ(g_lobbyTopOutlines) + 0x90), 0x9b }, { (OBJ(g_lobbyTopOutlines) + 0xa4), 0xffffff1a },
	{ (OBJ(g_lobbyTopOutlines) + 0x94), 0x4b }, { (OBJ(g_lobbyTopOutlines) + 0xa8), 0xffffff90 }, { (OBJ(g_lobbyTopOutlines) + 0x98), 0x82 }, { (OBJ(g_lobbyTopOutlines) + 0xac), 0xffffffe2 } };

void (menu_initKeyRepeatDefaults)(void) { apply_stores(k_intro_42f500, 44); }   /* 0x42f500 intro table */

static const Store k_input_initVkTable[57] = {
	{ OBJ(g_vkTable), 0x1b }, { (OBJ(g_vkTable) + 0x4), 0x31 }, { (OBJ(g_vkTable) + 0x8), 0x32 }, { (OBJ(g_vkTable) + 0xc), 0x33 }, { (OBJ(g_vkTable) + 0x10), 0x34 },
	{ (OBJ(g_vkTable) + 0x14), 0x35 }, { (OBJ(g_vkTable) + 0x18), 0x36 }, { (OBJ(g_vkTable) + 0x1c), 0x37 }, { (OBJ(g_vkTable) + 0x20), 0x38 }, { (OBJ(g_vkTable) + 0x24), 0x39 },
	{ (OBJ(g_vkTable) + 0x28), 0x30 }, { (OBJ(g_vkTable) + 0x2c), 0x2d }, { (OBJ(g_vkTable) + 0x30), 0x3d }, { (OBJ(g_vkTable) + 0x34), 0x8 }, { (OBJ(g_vkTable) + 0x38), 0x9 },
	{ (OBJ(g_vkTable) + 0x3c), 0x51 }, { (OBJ(g_vkTable) + 0x40), 0x57 }, { (OBJ(g_vkTable) + 0x44), 0x45 }, { (OBJ(g_vkTable) + 0x48), 0x52 }, { (OBJ(g_vkTable) + 0x4c), 0x54 },
	{ (OBJ(g_vkTable) + 0x50), 0x59 }, { (OBJ(g_vkTable) + 0x54), 0x55 }, { (OBJ(g_vkTable) + 0x58), 0x49 }, { (OBJ(g_vkTable) + 0x5c), 0x4f }, { (OBJ(g_vkTable) + 0x60), 0x50 },
	{ (OBJ(g_vkTable) + 0x64), 0x5b }, { (OBJ(g_vkTable) + 0x68), 0x5d }, { (OBJ(g_vkTable) + 0x6c), 0xd }, { (OBJ(g_vkTable) + 0x70), 0x0 }, { (OBJ(g_vkTable) + 0x74), 0x41 },
	{ (OBJ(g_vkTable) + 0x78), 0x53 }, { (OBJ(g_vkTable) + 0x7c), 0x44 }, { (OBJ(g_vkTable) + 0x80), 0x46 }, { (OBJ(g_vkTable) + 0x84), 0x47 }, { (OBJ(g_vkTable) + 0x88), 0x48 },
	{ (OBJ(g_vkTable) + 0x8c), 0x4a }, { (OBJ(g_vkTable) + 0x90), 0x4b }, { (OBJ(g_vkTable) + 0x94), 0x4c }, { (OBJ(g_vkTable) + 0x98), 0x3b }, { (OBJ(g_vkTable) + 0x9c), 0x27 },
	{ (OBJ(g_vkTable) + 0xa0), 0x60 }, { (OBJ(g_vkTable) + 0xa4), 0x10 }, { (OBJ(g_vkTable) + 0xa8), 0x5c }, { (OBJ(g_vkTable) + 0xac), 0x5a }, { (OBJ(g_vkTable) + 0xb0), 0x58 },
	{ (OBJ(g_vkTable) + 0xb4), 0x43 }, { (OBJ(g_vkTable) + 0xb8), 0x56 }, { (OBJ(g_vkTable) + 0xbc), 0x42 }, { (OBJ(g_vkTable) + 0xc0), 0x4e }, { (OBJ(g_vkTable) + 0xc4), 0x4d },
	{ (OBJ(g_vkTable) + 0xc8), 0x2c }, { (OBJ(g_vkTable) + 0xcc), 0x2e }, { (OBJ(g_vkTable) + 0xd0), 0x2f }, { (OBJ(g_vkTable) + 0xd4), 0x10 }, { (OBJ(g_vkTable) + 0xd8), 0x2a },
	{ (OBJ(g_vkTable) + 0xdc), 0x0 }, { (OBJ(g_vkTable) + 0xe0), 0x20 } };

void (input_initVkTable)(void) { apply_stores(k_input_initVkTable, 57); }   /* 0x431680 scan-code row -> virtual key table */

static const Store k_replay_46d4d0[64] = {
	{ OBJ(g_textColours), 0x3f800000 }, { (OBJ(g_textColours) + 0x4), 0x3f800000 }, { (OBJ(g_textColours) + 0x8), 0x3f800000 }, { (OBJ(g_textColours) + 0xc), 0x3f800000 }, { (OBJ(g_textColours) + 0x10), 0x3f73f3f4 },
	{ (OBJ(g_textColours) + 0x14), 0x3ea8a8a9 }, { (OBJ(g_textColours) + 0x18), 0x3ea8a8a9 }, { (OBJ(g_textColours) + 0x1c), 0x3f800000 }, { (OBJ(g_textColours) + 0x20), 0x3f7dfdfe }, { (OBJ(g_textColours) + 0x24), 0x3f37b7b8 },
	{ (OBJ(g_textColours) + 0x28), 0x3f67e7e8 }, { (OBJ(g_textColours) + 0x2c), 0x3f800000 }, { (OBJ(g_textColours) + 0x30), 0x3ecccccd }, { (OBJ(g_textColours) + 0x34), 0x3ea8a8a9 }, { (OBJ(g_textColours) + 0x38), 0x3f73f3f4 },
	{ (OBJ(g_textColours) + 0x3c), 0x3f800000 }, { (OBJ(g_textColours) + 0x40), 0x0 }, { (OBJ(g_textColours) + 0x44), 0x3f4ccccd }, { (OBJ(g_textColours) + 0x48), 0x3f800000 }, { (OBJ(g_textColours) + 0x4c), 0x3f800000 },
	{ (OBJ(g_textColours) + 0x50), 0x3e70f0f1 }, { (OBJ(g_textColours) + 0x54), 0x3f53d3d4 }, { (OBJ(g_textColours) + 0x58), 0x3e0c8c8d }, { (OBJ(g_textColours) + 0x5c), 0x3f800000 }, { (OBJ(g_textColours) + 0x60), 0x3f4ccccd },
	{ (OBJ(g_textColours) + 0x64), 0x3f800000 }, { (OBJ(g_textColours) + 0x68), 0x3f26a6a7 }, { (OBJ(g_textColours) + 0x6c), 0x3f800000 }, { (OBJ(g_textColours) + 0x70), 0x3f800000 }, { (OBJ(g_textColours) + 0x74), 0x3f70f0f1 },
	{ (OBJ(g_textColours) + 0x78), 0x0 }, { (OBJ(g_textColours) + 0x7c), 0x3f800000 }, { (OBJ(g_textColours) + 0x80), 0x3f48c8c9 }, { (OBJ(g_textColours) + 0x84), 0x3f48c8c9 }, { (OBJ(g_textColours) + 0x88), 0x3f53d3d4 },
	{ (OBJ(g_textColours) + 0x8c), 0x3f800000 }, { (OBJ(g_textColours) + 0x90), 0x3f109091 }, { (OBJ(g_textColours) + 0x94), 0x3f109091 }, { (OBJ(g_textColours) + 0x98), 0x3f20a0a1 }, { (OBJ(g_textColours) + 0x9c), 0x3f800000 },
	{ (OBJ(g_textColours) + 0xa0), 0x3f189899 }, { (OBJ(g_textColours) + 0xa4), 0x3f1a9a9b }, { (OBJ(g_textColours) + 0xa8), 0x3f058586 }, { (OBJ(g_textColours) + 0xac), 0x3f800000 }, { (OBJ(g_textColours) + 0xb0), 0x3f058586 },
	{ (OBJ(g_textColours) + 0xb4), 0x0 }, { (OBJ(g_textColours) + 0xb8), 0x0 }, { (OBJ(g_textColours) + 0xbc), 0x3f800000 }, { (OBJ(g_textColours) + 0xc0), 0x3d40c0c1 }, { (OBJ(g_textColours) + 0xc4), 0x0 },
	{ (OBJ(g_textColours) + 0xc8), 0x3f800000 }, { (OBJ(g_textColours) + 0xcc), 0x3f800000 }, { (OBJ(g_textColours) + 0xd0), 0x3f52d2d3 }, { (OBJ(g_textColours) + 0xd4), 0x0 }, { (OBJ(g_textColours) + 0xd8), 0x3f800000 },
	{ (OBJ(g_textColours) + 0xdc), 0x3f800000 }, { (OBJ(g_textColours) + 0xe0), 0x3e38b8b9 }, { (OBJ(g_textColours) + 0xe4), 0x3e48c8c9 }, { (OBJ(g_textColours) + 0xe8), 0x3e68e8e9 }, { (OBJ(g_textColours) + 0xec), 0x3f800000 },
	{ (OBJ(g_textColours) + 0xf0), 0x0 }, { (OBJ(g_textColours) + 0xf4), 0x3f800000 }, { (OBJ(g_textColours) + 0xf8), 0x3f22a2a3 }, { (OBJ(g_textColours) + 0xfc), 0x3f800000 } };

void (color_initTextColours)(void) { apply_stores(k_replay_46d4d0, 64); }   /* 0x46d4d0 64-entry table */

static const Store k_intro_42f2b0[66] = {
	{ (OBJ(g_mainMenuOutlines) + 0x30), 0xfffffefc }, { (OBJ(g_mainMenuOutlines) + 0x3c), 0xfffffefc }, { (OBJ(g_mainMenuOutlines) + 0x40), 0xfffffefc }, { (OBJ(g_mainMenuOutlines) + 0x34), 0xffffff81 }, { (OBJ(g_mainMenuOutlines) + 0x38), 0xffffff81 },
	{ (OBJ(g_mainMenuOutlines) + 0x4), 0xffffff6f }, { (OBJ(g_mainMenuOutlines) + 0x14), 0xffffff6f }, { (OBJ(g_mainMenuOutlines) + 0x68), 0xffffff6f }, { OBJ(g_mainMenuOutlines), 0x4 }, { (OBJ(g_mainMenuOutlines) + 0x18), 0xe8 },
	{ (OBJ(g_mainMenuOutlines) + 0x28), 0xe8 }, { (OBJ(g_mainMenuOutlines) + 0x2c), 0x4 }, { (OBJ(g_mainMenuOutlines) + 0x58), 0x4 }, { (OBJ(g_mainMenuOutlines) + 0x5c), 0xffffff01 }, { (OBJ(g_mainMenuOutlines) + 0x6c), 0xffffff01 },
	{ (OBJ(g_mainMenuOutlines) + 0x84), 0x4 }, { (OBJ(g_mainMenuOutlines) + 0xa0), 0xe8 }, { (OBJ(g_mainMenuOutlines) + 0xb0), 0x4 }, { (OBJ(g_mainMenuOutlines) + 0xdc), 0x4 }, { (OBJ(g_mainMenuOutlines) + 0x70), 0xffffff9c },
	{ (OBJ(g_mainMenuOutlines) + 0x80), 0xffffff9c }, { (OBJ(g_mainMenuOutlines) + 0xf8), 0xffffff9c }, { (OBJ(g_mainMenuOutlines) + 0x88), 0x46 }, { (OBJ(g_mainMenuOutlines) + 0x98), 0x46 }, { (OBJ(g_mainMenuOutlines) + 0xec), 0x46 },
	{ (OBJ(g_mainMenuOutlines) + 0x8), 0xffffffba }, { (OBJ(g_mainMenuOutlines) + 0x1c), 0x6e }, { (OBJ(g_mainMenuOutlines) + 0xc), 0xffffff86 }, { (OBJ(g_mainMenuOutlines) + 0x20), 0x32 }, { (OBJ(g_mainMenuOutlines) + 0x10), 0xffffff06 },
	{ (OBJ(g_mainMenuOutlines) + 0x24), 0x64 }, { (OBJ(g_mainMenuOutlines) + 0x44), 0x56 }, { (OBJ(g_mainMenuOutlines) + 0x48), 0x28 }, { (OBJ(g_mainMenuOutlines) + 0x4c), 0xffffffd8 }, { (OBJ(g_mainMenuOutlines) + 0x50), 0xffffffad },
	{ (OBJ(g_mainMenuOutlines) + 0x54), 0x56 }, { (OBJ(g_mainMenuOutlines) + 0x60), 0xffffff86 }, { (OBJ(g_mainMenuOutlines) + 0x74), 0xffffffcf }, { (OBJ(g_mainMenuOutlines) + 0x64), 0xffffffb8 }, { (OBJ(g_mainMenuOutlines) + 0x78), 0xffffff91 },
	{ (OBJ(g_mainMenuOutlines) + 0x7c), 0xffffff1a }, { (OBJ(g_mainMenuOutlines) + 0x9c), 0x6f }, { (OBJ(g_mainMenuOutlines) + 0x8c), 0x91 }, { (OBJ(g_mainMenuOutlines) + 0x90), 0xff }, { (OBJ(g_mainMenuOutlines) + 0xa4), 0x67 },
	{ (OBJ(g_mainMenuOutlines) + 0x94), 0x78 }, { (OBJ(g_mainMenuOutlines) + 0xa8), 0x32 }, { (OBJ(g_mainMenuOutlines) + 0xac), 0x6f }, { (OBJ(g_mainMenuOutlines) + 0xb4), 0x7d }, { (OBJ(g_mainMenuOutlines) + 0xc8), 0x28 },
	{ (OBJ(g_mainMenuOutlines) + 0xb8), 0x106 }, { (OBJ(g_mainMenuOutlines) + 0xcc), 0x56 }, { (OBJ(g_mainMenuOutlines) + 0xbc), 0x106 }, { (OBJ(g_mainMenuOutlines) + 0xd0), 0xffffffaa }, { (OBJ(g_mainMenuOutlines) + 0xc0), 0x7d },
	{ (OBJ(g_mainMenuOutlines) + 0xd4), 0xffffffd8 }, { (OBJ(g_mainMenuOutlines) + 0xc4), 0x7d }, { (OBJ(g_mainMenuOutlines) + 0xd8), 0x28 }, { (OBJ(g_mainMenuOutlines) + 0xe0), 0x78 }, { (OBJ(g_mainMenuOutlines) + 0xf4), 0xffffffce },
	{ (OBJ(g_mainMenuOutlines) + 0xe4), 0xff }, { (OBJ(g_mainMenuOutlines) + 0xe8), 0x92 }, { (OBJ(g_mainMenuOutlines) + 0xfc), 0xffffff1a }, { (OBJ(g_mainMenuOutlines) + 0x100), 0xffffff91 }, { (OBJ(g_mainMenuOutlines) + 0xf0), 0x78 },
	{ (OBJ(g_mainMenuOutlines) + 0x104), 0xffffffce } };

void (menu_initMainButtons)(void) { apply_stores(k_intro_42f2b0, 66); }   /* 0x42f2b0 intro table */

static const Store k_intro_42f690[66] = {
	{ (OBJ(g_roomOutlines) + 0x30), 0xfffffefc }, { (OBJ(g_roomOutlines) + 0x3c), 0xfffffefc }, { (OBJ(g_roomOutlines) + 0x40), 0xfffffefc }, { (OBJ(g_roomOutlines) + 0x34), 0xffffff81 }, { (OBJ(g_roomOutlines) + 0x38), 0xffffff81 },
	{ (OBJ(g_roomOutlines) + 0x4), 0xffffff6f }, { (OBJ(g_roomOutlines) + 0x14), 0xffffff6f }, { (OBJ(g_roomOutlines) + 0x68), 0xffffff6f }, { OBJ(g_roomOutlines), 0x4 }, { (OBJ(g_roomOutlines) + 0x18), 0xe8 },
	{ (OBJ(g_roomOutlines) + 0x28), 0xe8 }, { (OBJ(g_roomOutlines) + 0x2c), 0x4 }, { (OBJ(g_roomOutlines) + 0x58), 0x4 }, { (OBJ(g_roomOutlines) + 0x5c), 0xffffff01 }, { (OBJ(g_roomOutlines) + 0x6c), 0xffffff01 },
	{ (OBJ(g_roomOutlines) + 0x84), 0x4 }, { (OBJ(g_roomOutlines) + 0xa0), 0xe8 }, { (OBJ(g_roomOutlines) + 0xb0), 0x4 }, { (OBJ(g_roomOutlines) + 0xdc), 0x4 }, { (OBJ(g_roomOutlines) + 0x70), 0xffffff9c },
	{ (OBJ(g_roomOutlines) + 0x80), 0xffffff9c }, { (OBJ(g_roomOutlines) + 0xf8), 0xffffff9c }, { (OBJ(g_roomOutlines) + 0x88), 0x46 }, { (OBJ(g_roomOutlines) + 0x98), 0x46 }, { (OBJ(g_roomOutlines) + 0xec), 0x46 },
	{ (OBJ(g_roomOutlines) + 0x8), 0xffffffba }, { (OBJ(g_roomOutlines) + 0x1c), 0x6e }, { (OBJ(g_roomOutlines) + 0xc), 0xffffff86 }, { (OBJ(g_roomOutlines) + 0x20), 0x32 }, { (OBJ(g_roomOutlines) + 0x10), 0xffffff06 },
	{ (OBJ(g_roomOutlines) + 0x24), 0x64 }, { (OBJ(g_roomOutlines) + 0x44), 0x56 }, { (OBJ(g_roomOutlines) + 0x48), 0x28 }, { (OBJ(g_roomOutlines) + 0x4c), 0xffffffd8 }, { (OBJ(g_roomOutlines) + 0x50), 0xffffffad },
	{ (OBJ(g_roomOutlines) + 0x54), 0x56 }, { (OBJ(g_roomOutlines) + 0x60), 0xffffff86 }, { (OBJ(g_roomOutlines) + 0x74), 0xffffffcf }, { (OBJ(g_roomOutlines) + 0x64), 0xffffffb8 }, { (OBJ(g_roomOutlines) + 0x78), 0xffffff91 },
	{ (OBJ(g_roomOutlines) + 0x7c), 0xffffff1a }, { (OBJ(g_roomOutlines) + 0x9c), 0x6f }, { (OBJ(g_roomOutlines) + 0x8c), 0x91 }, { (OBJ(g_roomOutlines) + 0x90), 0xff }, { (OBJ(g_roomOutlines) + 0xa4), 0x67 },
	{ (OBJ(g_roomOutlines) + 0x94), 0x78 }, { (OBJ(g_roomOutlines) + 0xa8), 0x32 }, { (OBJ(g_roomOutlines) + 0xac), 0x6f }, { (OBJ(g_roomOutlines) + 0xb4), 0x7d }, { (OBJ(g_roomOutlines) + 0xc8), 0x28 },
	{ (OBJ(g_roomOutlines) + 0xb8), 0x106 }, { (OBJ(g_roomOutlines) + 0xcc), 0x56 }, { (OBJ(g_roomOutlines) + 0xbc), 0x106 }, { (OBJ(g_roomOutlines) + 0xd0), 0xffffffaa }, { (OBJ(g_roomOutlines) + 0xc0), 0x7d },
	{ (OBJ(g_roomOutlines) + 0xd4), 0xffffffd8 }, { (OBJ(g_roomOutlines) + 0xc4), 0x7d }, { (OBJ(g_roomOutlines) + 0xd8), 0x28 }, { (OBJ(g_roomOutlines) + 0xe0), 0x78 }, { (OBJ(g_roomOutlines) + 0xf4), 0xffffffce },
	{ (OBJ(g_roomOutlines) + 0xe4), 0xff }, { (OBJ(g_roomOutlines) + 0xe8), 0x92 }, { (OBJ(g_roomOutlines) + 0xfc), 0xffffff1a }, { (OBJ(g_roomOutlines) + 0x100), 0xffffff91 }, { (OBJ(g_roomOutlines) + 0xf0), 0x78 },
	{ (OBJ(g_roomOutlines) + 0x104), 0xffffffce } };

void (room_initMenuButtons)(void) { apply_stores(k_intro_42f690, 66); }   /* 0x42f690 intro table */

static const Store k_input_setDefaultKeyBindings[118] = {
	{ ADDR(g_dikNone), 0x0 }, { ADDR(g_dikEscape), 0x1 }, { ADDR(g_dik1), 0x2 }, { ADDR(g_dik2), 0x3 }, { ADDR(g_dik3), 0x4 },
	{ ADDR(g_dik4), 0x5 }, { ADDR(g_dik5), 0x6 }, { ADDR(g_dik6), 0x7 }, { ADDR(g_dik7), 0x8 }, { ADDR(g_dik8), 0x9 },
	{ ADDR(g_dik9), 0xa }, { ADDR(g_dik0), 0xb }, { ADDR(g_dikA), 0x1e }, { ADDR(g_dikB), 0x30 }, { ADDR(g_dikC), 0x2e },
	{ ADDR(g_dikD), 0x20 }, { ADDR(g_dikE), 0x12 }, { ADDR(g_dikF), 0x21 }, { ADDR(g_dikG), 0x22 }, { ADDR(g_dikH), 0x23 },
	{ ADDR(g_dikI), 0x17 }, { ADDR(g_dikJ), 0x24 }, { ADDR(g_dikK), 0x25 }, { ADDR(g_dikL), 0x26 }, { ADDR(g_dikM), 0x32 },
	{ ADDR(g_dikN), 0x31 }, { ADDR(g_dikO), 0x18 }, { ADDR(g_dikP), 0x19 }, { ADDR(g_dikQ), 0x10 }, { ADDR(g_dikR), 0x13 },
	{ ADDR(g_dikS), 0x1f }, { ADDR(g_dikT), 0x14 }, { ADDR(g_dikU), 0x16 }, { ADDR(g_dikV), 0x2f }, { ADDR(g_dikW), 0x11 },
	{ ADDR(g_dikX), 0x2d }, { ADDR(g_dikY), 0x15 }, { ADDR(g_dikZ), 0x2c }, { ADDR(g_dikEnter), 0x1c }, { ADDR(g_dikMinus), 0xc },
	{ ADDR(g_dikEquals), 0xd }, { ADDR(g_dikBack), 0xe }, { ADDR(g_dikTab), 0xf }, { ADDR(g_dikLBracket), 0x1a }, { ADDR(g_dikRBracket), 0x1b },
	{ ADDR(g_dikSemicolon), 0x27 }, { ADDR(g_dikGrave), 0x29 }, { ADDR(g_dikBackslash), 0x2b }, { ADDR(g_dikComma), 0x33 }, { ADDR(g_dikPeriod), 0x34 },
	{ ADDR(g_dikSlash), 0x35 }, { ADDR(g_dikApostrophe), 0x28 }, { ADDR(g_dikRCtrl), 0x9d }, { ADDR(g_dikLCtrl), 0x1d }, { ADDR(g_dikLShift), 0x2a },
	{ ADDR(g_dikRShift), 0x36 }, { ADDR(g_dikLAlt), 0x38 }, { ADDR(g_dikRAlt), 0xb8 }, { ADDR(g_dikSpace), 0x39 }, { ADDR(g_dikCapsLock), 0x3a },
	{ ADDR(g_excludedKey), 0x3b }, { ADDR(g_dikF2), 0x3c }, { ADDR(g_dikF3), 0x3d }, { ADDR(g_dikF4), 0x3e }, { ADDR(g_dikF5), 0x3f },
	{ ADDR(g_dikF6), 0x40 }, { ADDR(g_dikF7), 0x41 }, { ADDR(g_dikF8), 0x42 }, { ADDR(g_dikF9), 0x43 }, { ADDR(g_dikF10), 0x44 },
	{ ADDR(g_dikF11), 0x57 }, { ADDR(g_dikF12), 0x58 }, { ADDR(g_dikNumLock), 0x45 }, { ADDR(g_dikScrollLock), 0x46 }, { ADDR(g_dikPrintScreen), 0xb7 },
	{ ADDR(g_dikNumpad1), 0x4f }, { ADDR(g_dikNumpad2), 0x50 }, { ADDR(g_dikNumpad3), 0x51 }, { ADDR(g_dikNumpad4), 0x4b }, { ADDR(g_dikNumpad5), 0x4c },
	{ ADDR(g_dikNumpad6), 0x4d }, { ADDR(g_dikNumpad7), 0x47 }, { ADDR(g_dikNumpad8), 0x48 }, { ADDR(g_dikNumpad9), 0x49 }, { ADDR(g_dikNumpad0), 0x52 },
	{ ADDR(g_dikNumpadMinus), 0x4a }, { ADDR(g_dikNumpadPlus), 0x4e }, { ADDR(g_dikNumpadDot), 0x53 }, { ADDR(g_dikNumpadEnter), 0x9c }, { ADDR(g_dikNumpadStar), 0x37 },
	{ ADDR(g_dikNumpadSlash), 0xb5 }, { ADDR(g_dikUp), 0xc8 }, { ADDR(g_dikDown), 0xd0 }, { ADDR(g_dikLeft), 0xcb }, { ADDR(g_dikRight), 0xcd },
	{ ADDR(g_dikPageUp), 0xc9 }, { ADDR(g_dikPageDown), 0xd1 }, { ADDR(g_dikHome), 0xc7 }, { ADDR(g_dikEnd), 0xcf }, { ADDR(g_dikInsert), 0xd2 },
	{ ADDR(g_dikDelete), 0xd3 }, { ADDR(g_dikLWin), 0xdb }, { ADDR(g_dikRWin), 0xdc }, { ADDR(g_dikApps), 0xdd }, { ADDR(g_dikEscape_2), 0x1 },
	{ ADDR(g_dikInsert_2), 0xd2 }, { ADDR(g_dikPageUp_2), 0xc9 }, { ADDR(g_dikHome_2), 0xc7 }, { ADDR(g_dikEnd_2), 0xcf }, { ADDR(g_dikDelete_2), 0xd3 },
	{ ADDR(g_dikPageDown_2), 0xd1 }, { ADDR(g_dikZ_2), 0x2c }, { ADDR(g_dikEnter_2), 0x1c }, { ADDR(g_dikMouse1), 0xfa }, { ADDR(g_dikMouse2), 0xfb },
	{ ADDR(g_dikMouse3), 0xfc }, { ADDR(g_dikWheelDown), 0xfd }, { ADDR(g_dikWheelUp), 0xfe } };

void (input_setDefaultKeyBindings)(void) { apply_stores(k_input_setDefaultKeyBindings, 118); }   /* 0x42fd40 default key bindings */

static const CStore k_input_applyKeyBindings[68] = {
	{ ADDR(g_keyFreeCam1), ADDR(g_dikS), 1 }, { ADDR(g_keyFreeCam2), ADDR(g_dikA), 1 }, { ADDR(g_keyFreeCam3), ADDR(g_dikD), 1 }, { (OBJ(g_controls) + 0x20), ADDR(g_dikLeft), 1 },
	{ (OBJ(g_controls) + 0x28), ADDR(g_dikRight), 1 }, { (OBJ(g_controls) + 0x30), ADDR(g_dikMouse2), 1 }, { (OBJ(g_controls) + 0x38), ADDR(g_dikSpace), 1 }, { (OBJ(g_controls) + 0x40), ADDR(g_dikR), 1 },
	{ (OBJ(g_controls) + 0x48), ADDR(g_dikF), 1 }, { (OBJ(g_controls) + 0x50), ADDR(g_dikMouse1), 1 }, { (OBJ(g_controls) + 0x58), ADDR(g_dikQ), 1 }, { (OBJ(g_controls) + 0x60), ADDR(g_dikE), 1 },
	{ (OBJ(g_controls) + 0x78), ADDR(g_dik1), 1 }, { (OBJ(g_controls) + 0x80), ADDR(g_dik2), 1 }, { (OBJ(g_controls) + 0x88), ADDR(g_dik3), 1 }, { (OBJ(g_controls) + 0x90), ADDR(g_dik4), 1 },
	{ (OBJ(g_controls) + 0x68), ADDR(g_dik5), 1 }, { (OBJ(g_controls) + 0x70), ADDR(g_dik6), 1 }, { (OBJ(g_controls) + 0x98), ADDR(g_dikLShift), 1 }, { (OBJ(g_controls) + 0xa0), ADDR(g_dikRCtrl), 1 },
	{ ADDR(g_keyWatchChat), ADDR(g_dikEnter), 1 }, { (OBJ(g_controls) + 0xb0), ADDR(g_dikC), 1 }, { ADDR(g_keyFreeCam0), ADDR(g_dikW), 1 }, { (OBJ(g_controls) + 0xb8), ADDR(g_dikX), 1 },
	{ (OBJ(g_controls) + 0xc0), ADDR(g_dikB), 1 }, { (OBJ(g_controls) + 0x4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xc), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x14), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x1c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x24), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x2c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x34), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x3c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x44), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x4c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x54), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x5c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x64), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x7c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x84), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x8c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x94), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x6c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x74), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x9c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xa4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xac), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xb4), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xbc), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xc4), ADDR(g_dikNone), 1 }, { ADDR(g_keyLoadingSkip), ADDR(g_dikEscape_2), 1 }, { ADDR(g_keyLoadingSkip2), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xd0), ADDR(g_dikF4), 1 }, { (OBJ(g_controls) + 0xd8), ADDR(g_dikF5), 1 }, { (OBJ(g_controls) + 0xd4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xdc), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xe0), ADDR(g_dikTab), 1 }, { (OBJ(g_controls) + 0xe4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xe8), ADDR(g_dikF10), 1 }, { (OBJ(g_controls) + 0xec), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xf4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xfc), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xf0), ADDR(g_dikV), 1 }, { (OBJ(g_controls) + 0xf8), ADDR(g_excludedKey), 1 },
	{ ADDR(g_mouseInvert), 0x0, 0 }, { ADDR(g_mouseSmooth), 0x0, 0 }, { ADDR(g_mouseSensitivity), 0x32, 0 }, { ADDR(g_crosshairSetting), 0x0, 0 } };

void (input_applyKeyBindings)(void) { apply_cstores(k_input_applyKeyBindings, 68); }

static const CStore k_setup_controlTabHelper_420c10[68] = {
	{ (OBJ(g_controlsEdit) + 0x8), ADDR(g_dikS), 1 }, { (OBJ(g_controlsEdit) + 0x10), ADDR(g_dikA), 1 }, { (OBJ(g_controlsEdit) + 0x18), ADDR(g_dikD), 1 }, { (OBJ(g_controlsEdit) + 0x20), ADDR(g_dikLeft), 1 },
	{ (OBJ(g_controlsEdit) + 0x28), ADDR(g_dikRight), 1 }, { (OBJ(g_controlsEdit) + 0x30), ADDR(g_dikMouse2), 1 }, { (OBJ(g_controlsEdit) + 0x38), ADDR(g_dikSpace), 1 }, { (OBJ(g_controlsEdit) + 0x40), ADDR(g_dikR), 1 },
	{ (OBJ(g_controlsEdit) + 0x48), ADDR(g_dikF), 1 }, { (OBJ(g_controlsEdit) + 0x50), ADDR(g_dikMouse1), 1 }, { (OBJ(g_controlsEdit) + 0x58), ADDR(g_dikQ), 1 }, { (OBJ(g_controlsEdit) + 0x60), ADDR(g_dikE), 1 },
	{ (OBJ(g_controlsEdit) + 0x78), ADDR(g_dik1), 1 }, { (OBJ(g_controlsEdit) + 0x80), ADDR(g_dik2), 1 }, { (OBJ(g_controlsEdit) + 0x88), ADDR(g_dik3), 1 }, { (OBJ(g_controlsEdit) + 0x90), ADDR(g_dik4), 1 },
	{ (OBJ(g_controlsEdit) + 0x68), ADDR(g_dik5), 1 }, { (OBJ(g_controlsEdit) + 0x70), ADDR(g_dik6), 1 }, { (OBJ(g_controlsEdit) + 0x98), ADDR(g_dikLShift), 1 }, { (OBJ(g_controlsEdit) + 0xa0), ADDR(g_dikLCtrl), 1 },
	{ (OBJ(g_controlsEdit) + 0xa8), ADDR(g_dikEnter), 1 }, { (OBJ(g_controlsEdit) + 0xb0), ADDR(g_dikC), 1 }, { OBJ(g_controlsEdit), ADDR(g_dikW), 1 }, { (OBJ(g_controlsEdit) + 0xb8), ADDR(g_dikX), 1 },
	{ (OBJ(g_controlsEdit) + 0xc0), ADDR(g_dikB), 1 }, { (OBJ(g_controlsEdit) + 0x4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xc), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x14), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x1c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x24), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x2c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x34), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x3c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x44), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x4c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x54), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x5c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x64), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x7c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x84), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x8c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x94), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x6c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x74), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x9c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xa4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xac), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xb4), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xbc), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xc4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xc8), ADDR(g_dikEscape_2), 1 }, { (OBJ(g_controlsEdit) + 0xcc), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xd0), ADDR(g_dikF4), 1 }, { (OBJ(g_controlsEdit) + 0xd8), ADDR(g_dikF5), 1 }, { (OBJ(g_controlsEdit) + 0xd4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xdc), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xe0), ADDR(g_dikTab), 1 }, { (OBJ(g_controlsEdit) + 0xe4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xe8), ADDR(g_dikF10), 1 }, { (OBJ(g_controlsEdit) + 0xec), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xf4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xfc), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xf0), ADDR(g_dikV), 1 }, { (OBJ(g_controlsEdit) + 0xf8), ADDR(g_excludedKey), 1 },
	{ OBJ(g_setupToggles), 0x0, 0 }, { (OBJ(g_setupToggles) + 0x4), 0x0, 0 }, { ADDR(g_sensitivitySlider), 0x32, 0 }, { ADDR(g_crosshair), 0x0, 0 } };

void (setup_keepKeyBindings)(void) { apply_cstores(k_setup_controlTabHelper_420c10, 68); }

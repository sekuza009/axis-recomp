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

static const Store k_defaultColours[16] = {
	{ OBJ(g_defaultColours), 0xffffffff }, { (u32)&g_defaultColours[1], 0xff5454f3 }, { (u32)&g_defaultColours[3], 0xfff35466 }, { (u32)&g_defaultColours[2], 0xffe7b7fd }, { (u32)&g_defaultColours[4], 0xffffcc00 },
	{ (u32)&g_defaultColours[6], 0xffa6ffcc }, { (u32)&g_defaultColours[7], 0xff00f0ff }, { (u32)&g_defaultColours[8], 0xffd3c8c8 }, { (u32)&g_defaultColours[9], 0xffa09090 }, { (u32)&g_defaultColours[5], 0xff23d33c },
	{ (u32)&g_defaultColours[10], 0xff859a98 }, { (u32)&g_defaultColours[11], 0xff000085 }, { (u32)&g_defaultColours[12], 0xffff000c }, { (u32)&g_defaultColours[13], 0xffff00d2 }, { (u32)&g_defaultColours[14], 0xff3a322e },
	{ (u32)&g_defaultColours[15], 0xffa2ff00 } };

void (colour_initDefaultColours)(void) { apply_stores(k_defaultColours, 16); }   /* 0x46dc50 default RGBA colours (bytes) */

static const Store k_lobbyTopOutlines[44] = {
	{ (u32)&g_lobbyTopOutlines[6], 0xe7 }, { (u32)&g_lobbyTopOutlines[10], 0xe7 }, { (u32)&g_lobbyTopOutlines[29], 0xe7 }, { (u32)&g_lobbyTopOutlines[1], 0xffffff65 }, { (u32)&g_lobbyTopOutlines[5], 0xffffff65 },
	{ (u32)&g_lobbyTopOutlines[3], 0xffffff7e }, { (u32)&g_lobbyTopOutlines[4], 0xfffffef2 }, { (u32)&g_lobbyTopOutlines[12], 0xfffffef2 }, { (u32)&g_lobbyTopOutlines[13], 0xffffff7e }, { (u32)&g_lobbyTopOutlines[16], 0xfffffef2 },
	{ (u32)&g_lobbyTopOutlines[25], 0x10e }, { (u32)&g_lobbyTopOutlines[35], 0x10e }, { (u32)&g_lobbyTopOutlines[17], 0xffffffc1 }, { (u32)&g_lobbyTopOutlines[21], 0xffffffc1 }, { (u32)&g_lobbyTopOutlines[40], 0xffffffc1 },
	{ OBJ(g_lobbyTopOutlines), 0x4 }, { (u32)&g_lobbyTopOutlines[2], 0xffffffb6 }, { (u32)&g_lobbyTopOutlines[7], 0x6e }, { (u32)&g_lobbyTopOutlines[8], 0x1f }, { (u32)&g_lobbyTopOutlines[9], 0x42 },
	{ (u32)&g_lobbyTopOutlines[11], 0x4 }, { (u32)&g_lobbyTopOutlines[18], 0xffffffe2 }, { (u32)&g_lobbyTopOutlines[14], 0xffffffb5 }, { (u32)&g_lobbyTopOutlines[19], 0xffffff90 }, { (u32)&g_lobbyTopOutlines[15], 0xffffff67 },
	{ (u32)&g_lobbyTopOutlines[20], 0xffffff1a }, { (u32)&g_lobbyTopOutlines[22], 0x4 }, { (u32)&g_lobbyTopOutlines[23], 0x49 }, { (u32)&g_lobbyTopOutlines[28], 0x70 }, { (u32)&g_lobbyTopOutlines[24], 0x9b },
	{ (u32)&g_lobbyTopOutlines[30], 0x42 }, { (u32)&g_lobbyTopOutlines[26], 0x82 }, { (u32)&g_lobbyTopOutlines[31], 0x1f }, { (u32)&g_lobbyTopOutlines[27], 0x49 }, { (u32)&g_lobbyTopOutlines[32], 0x70 },
	{ (u32)&g_lobbyTopOutlines[33], 0x4 }, { (u32)&g_lobbyTopOutlines[34], 0x82 }, { (u32)&g_lobbyTopOutlines[39], 0xffffffe2 }, { (u32)&g_lobbyTopOutlines[36], 0x9b }, { (u32)&g_lobbyTopOutlines[41], 0xffffff1a },
	{ (u32)&g_lobbyTopOutlines[37], 0x4b }, { (u32)&g_lobbyTopOutlines[42], 0xffffff90 }, { (u32)&g_lobbyTopOutlines[38], 0x82 }, { (u32)&g_lobbyTopOutlines[43], 0xffffffe2 } };

void (lobbyTop_initOutlines)(void) { apply_stores(k_lobbyTopOutlines, 44); }   /* 0x42f500: the lobby top menu's button outlines */

static const Store k_scanCharTable[57] = {
	{ OBJ(g_scanCharTable), 0x1b }, { (u32)&g_scanCharTable[1], 0x31 }, { (u32)&g_scanCharTable[2], 0x32 }, { (u32)&g_scanCharTable[3], 0x33 }, { (u32)&g_scanCharTable[4], 0x34 },
	{ (u32)&g_scanCharTable[5], 0x35 }, { (u32)&g_scanCharTable[6], 0x36 }, { (u32)&g_scanCharTable[7], 0x37 }, { (u32)&g_scanCharTable[8], 0x38 }, { (u32)&g_scanCharTable[9], 0x39 },
	{ (u32)&g_scanCharTable[10], 0x30 }, { (u32)&g_scanCharTable[11], 0x2d }, { (u32)&g_scanCharTable[12], 0x3d }, { (u32)&g_scanCharTable[13], 0x8 }, { (u32)&g_scanCharTable[14], 0x9 },
	{ (u32)&g_scanCharTable[15], 0x51 }, { (u32)&g_scanCharTable[16], 0x57 }, { (u32)&g_scanCharTable[17], 0x45 }, { (u32)&g_scanCharTable[18], 0x52 }, { (u32)&g_scanCharTable[19], 0x54 },
	{ (u32)&g_scanCharTable[20], 0x59 }, { (u32)&g_scanCharTable[21], 0x55 }, { (u32)&g_scanCharTable[22], 0x49 }, { (u32)&g_scanCharTable[23], 0x4f }, { (u32)&g_scanCharTable[24], 0x50 },
	{ (u32)&g_scanCharTable[25], 0x5b }, { (u32)&g_scanCharTable[26], 0x5d }, { (u32)&g_scanCharTable[27], 0xd }, { (u32)&g_scanCharTable[28], 0x0 }, { (u32)&g_scanCharTable[29], 0x41 },
	{ (u32)&g_scanCharTable[30], 0x53 }, { (u32)&g_scanCharTable[31], 0x44 }, { (u32)&g_scanCharTable[32], 0x46 }, { (u32)&g_scanCharTable[33], 0x47 }, { (u32)&g_scanCharTable[34], 0x48 },
	{ (u32)&g_scanCharTable[35], 0x4a }, { (u32)&g_scanCharTable[36], 0x4b }, { (u32)&g_scanCharTable[37], 0x4c }, { (u32)&g_scanCharTable[38], 0x3b }, { (u32)&g_scanCharTable[39], 0x27 },
	{ (u32)&g_scanCharTable[40], 0x60 }, { (u32)&g_scanCharTable[41], 0x10 }, { (u32)&g_scanCharTable[42], 0x5c }, { (u32)&g_scanCharTable[43], 0x5a }, { (u32)&g_scanCharTable[44], 0x58 },
	{ (u32)&g_scanCharTable[45], 0x43 }, { (u32)&g_scanCharTable[46], 0x56 }, { (u32)&g_scanCharTable[47], 0x42 }, { (u32)&g_scanCharTable[48], 0x4e }, { (u32)&g_scanCharTable[49], 0x4d },
	{ (u32)&g_scanCharTable[50], 0x2c }, { (u32)&g_scanCharTable[51], 0x2e }, { (u32)&g_scanCharTable[52], 0x2f }, { (u32)&g_scanCharTable[53], 0x10 }, { (u32)&g_scanCharTable[54], 0x2a },
	{ (u32)&g_scanCharTable[55], 0x0 }, { (u32)&g_scanCharTable[56], 0x20 } };

void (input_initScanCharTable)(void) { apply_stores(k_scanCharTable, 57); }   /* 0x431680 the scan code -> character table (g_scanCharTable) */

static const Store k_textColours[64] = {
	{ OBJ(g_textColours), 0x3f800000 }, { (u32)&g_textColours[0].g, 0x3f800000 }, { (u32)&g_textColours[0].b, 0x3f800000 }, { (u32)&g_textColours[0].a, 0x3f800000 }, { (u32)&g_textColours[1].r, 0x3f73f3f4 },
	{ (u32)&g_textColours[1].g, 0x3ea8a8a9 }, { (u32)&g_textColours[1].b, 0x3ea8a8a9 }, { (u32)&g_textColours[1].a, 0x3f800000 }, { (u32)&g_textColours[2].r, 0x3f7dfdfe }, { (u32)&g_textColours[2].g, 0x3f37b7b8 },
	{ (u32)&g_textColours[2].b, 0x3f67e7e8 }, { (u32)&g_textColours[2].a, 0x3f800000 }, { (u32)&g_textColours[3].r, 0x3ecccccd }, { (u32)&g_textColours[3].g, 0x3ea8a8a9 }, { (u32)&g_textColours[3].b, 0x3f73f3f4 },
	{ (u32)&g_textColours[3].a, 0x3f800000 }, { (u32)&g_textColours[4].r, 0x0 }, { (u32)&g_textColours[4].g, 0x3f4ccccd }, { (u32)&g_textColours[4].b, 0x3f800000 }, { (u32)&g_textColours[4].a, 0x3f800000 },
	{ (u32)&g_textColours[5].r, 0x3e70f0f1 }, { (u32)&g_textColours[5].g, 0x3f53d3d4 }, { (u32)&g_textColours[5].b, 0x3e0c8c8d }, { (u32)&g_textColours[5].a, 0x3f800000 }, { (u32)&g_textColours[6].r, 0x3f4ccccd },
	{ (u32)&g_textColours[6].g, 0x3f800000 }, { (u32)&g_textColours[6].b, 0x3f26a6a7 }, { (u32)&g_textColours[6].a, 0x3f800000 }, { (u32)&g_textColours[7].r, 0x3f800000 }, { (u32)&g_textColours[7].g, 0x3f70f0f1 },
	{ (u32)&g_textColours[7].b, 0x0 }, { (u32)&g_textColours[7].a, 0x3f800000 }, { (u32)&g_textColours[8].r, 0x3f48c8c9 }, { (u32)&g_textColours[8].g, 0x3f48c8c9 }, { (u32)&g_textColours[8].b, 0x3f53d3d4 },
	{ (u32)&g_textColours[8].a, 0x3f800000 }, { (u32)&g_textColours[9].r, 0x3f109091 }, { (u32)&g_textColours[9].g, 0x3f109091 }, { (u32)&g_textColours[9].b, 0x3f20a0a1 }, { (u32)&g_textColours[9].a, 0x3f800000 },
	{ (u32)&g_textColours[10].r, 0x3f189899 }, { (u32)&g_textColours[10].g, 0x3f1a9a9b }, { (u32)&g_textColours[10].b, 0x3f058586 }, { (u32)&g_textColours[10].a, 0x3f800000 }, { (u32)&g_textColours[11].r, 0x3f058586 },
	{ (u32)&g_textColours[11].g, 0x0 }, { (u32)&g_textColours[11].b, 0x0 }, { (u32)&g_textColours[11].a, 0x3f800000 }, { (u32)&g_textColours[12].r, 0x3d40c0c1 }, { (u32)&g_textColours[12].g, 0x0 },
	{ (u32)&g_textColours[12].b, 0x3f800000 }, { (u32)&g_textColours[12].a, 0x3f800000 }, { (u32)&g_textColours[13].r, 0x3f52d2d3 }, { (u32)&g_textColours[13].g, 0x0 }, { (u32)&g_textColours[13].b, 0x3f800000 },
	{ (u32)&g_textColours[13].a, 0x3f800000 }, { (u32)&g_textColours[14].r, 0x3e38b8b9 }, { (u32)&g_textColours[14].g, 0x3e48c8c9 }, { (u32)&g_textColours[14].b, 0x3e68e8e9 }, { (u32)&g_textColours[14].a, 0x3f800000 },
	{ (u32)&g_textColours[15].r, 0x0 }, { (u32)&g_textColours[15].g, 0x3f800000 }, { (u32)&g_textColours[15].b, 0x3f22a2a3 }, { (u32)&g_textColours[15].a, 0x3f800000 } };

void (colour_initTextColours)(void) { apply_stores(k_textColours, 64); }   /* 0x46d4d0: the 16 text colours (four floats each) */

static const Store k_mainMenuOutlines[66] = {
	{ (u32)&g_mainMenuOutlines[12], 0xfffffefc }, { (u32)&g_mainMenuOutlines[15], 0xfffffefc }, { (u32)&g_mainMenuOutlines[16], 0xfffffefc }, { (u32)&g_mainMenuOutlines[13], 0xffffff81 }, { (u32)&g_mainMenuOutlines[14], 0xffffff81 },
	{ (u32)&g_mainMenuOutlines[1], 0xffffff6f }, { (u32)&g_mainMenuOutlines[5], 0xffffff6f }, { (u32)&g_mainMenuOutlines[26], 0xffffff6f }, { OBJ(g_mainMenuOutlines), 0x4 }, { (u32)&g_mainMenuOutlines[6], 0xe8 },
	{ (u32)&g_mainMenuOutlines[10], 0xe8 }, { (u32)&g_mainMenuOutlines[11], 0x4 }, { (u32)&g_mainMenuOutlines[22], 0x4 }, { (u32)&g_mainMenuOutlines[23], 0xffffff01 }, { (u32)&g_mainMenuOutlines[27], 0xffffff01 },
	{ (u32)&g_mainMenuOutlines[33], 0x4 }, { (u32)&g_mainMenuOutlines[40], 0xe8 }, { (u32)&g_mainMenuOutlines[44], 0x4 }, { (u32)&g_mainMenuOutlines[55], 0x4 }, { (u32)&g_mainMenuOutlines[28], 0xffffff9c },
	{ (u32)&g_mainMenuOutlines[32], 0xffffff9c }, { (u32)&g_mainMenuOutlines[62], 0xffffff9c }, { (u32)&g_mainMenuOutlines[34], 0x46 }, { (u32)&g_mainMenuOutlines[38], 0x46 }, { (u32)&g_mainMenuOutlines[59], 0x46 },
	{ (u32)&g_mainMenuOutlines[2], 0xffffffba }, { (u32)&g_mainMenuOutlines[7], 0x6e }, { (u32)&g_mainMenuOutlines[3], 0xffffff86 }, { (u32)&g_mainMenuOutlines[8], 0x32 }, { (u32)&g_mainMenuOutlines[4], 0xffffff06 },
	{ (u32)&g_mainMenuOutlines[9], 0x64 }, { (u32)&g_mainMenuOutlines[17], 0x56 }, { (u32)&g_mainMenuOutlines[18], 0x28 }, { (u32)&g_mainMenuOutlines[19], 0xffffffd8 }, { (u32)&g_mainMenuOutlines[20], 0xffffffad },
	{ (u32)&g_mainMenuOutlines[21], 0x56 }, { (u32)&g_mainMenuOutlines[24], 0xffffff86 }, { (u32)&g_mainMenuOutlines[29], 0xffffffcf }, { (u32)&g_mainMenuOutlines[25], 0xffffffb8 }, { (u32)&g_mainMenuOutlines[30], 0xffffff91 },
	{ (u32)&g_mainMenuOutlines[31], 0xffffff1a }, { (u32)&g_mainMenuOutlines[39], 0x6f }, { (u32)&g_mainMenuOutlines[35], 0x91 }, { (u32)&g_mainMenuOutlines[36], 0xff }, { (u32)&g_mainMenuOutlines[41], 0x67 },
	{ (u32)&g_mainMenuOutlines[37], 0x78 }, { (u32)&g_mainMenuOutlines[42], 0x32 }, { (u32)&g_mainMenuOutlines[43], 0x6f }, { (u32)&g_mainMenuOutlines[45], 0x7d }, { (u32)&g_mainMenuOutlines[50], 0x28 },
	{ (u32)&g_mainMenuOutlines[46], 0x106 }, { (u32)&g_mainMenuOutlines[51], 0x56 }, { (u32)&g_mainMenuOutlines[47], 0x106 }, { (u32)&g_mainMenuOutlines[52], 0xffffffaa }, { (u32)&g_mainMenuOutlines[48], 0x7d },
	{ (u32)&g_mainMenuOutlines[53], 0xffffffd8 }, { (u32)&g_mainMenuOutlines[49], 0x7d }, { (u32)&g_mainMenuOutlines[54], 0x28 }, { (u32)&g_mainMenuOutlines[56], 0x78 }, { (u32)&g_mainMenuOutlines[61], 0xffffffce },
	{ (u32)&g_mainMenuOutlines[57], 0xff }, { (u32)&g_mainMenuOutlines[58], 0x92 }, { (u32)&g_mainMenuOutlines[63], 0xffffff1a }, { (u32)&g_mainMenuOutlines[64], 0xffffff91 }, { (u32)&g_mainMenuOutlines[60], 0x78 },
	{ (u32)&g_mainMenuOutlines[65], 0xffffffce } };

void (menu_initMainOutlines)(void) { apply_stores(k_mainMenuOutlines, 66); }   /* 0x42f2b0: the main menu's button outlines */

static const Store k_roomOutlines[66] = {
	{ (u32)&g_roomOutlines[12], 0xfffffefc }, { (u32)&g_roomOutlines[15], 0xfffffefc }, { (u32)&g_roomOutlines[16], 0xfffffefc }, { (u32)&g_roomOutlines[13], 0xffffff81 }, { (u32)&g_roomOutlines[14], 0xffffff81 },
	{ (u32)&g_roomOutlines[1], 0xffffff6f }, { (u32)&g_roomOutlines[5], 0xffffff6f }, { (u32)&g_roomOutlines[26], 0xffffff6f }, { OBJ(g_roomOutlines), 0x4 }, { (u32)&g_roomOutlines[6], 0xe8 },
	{ (u32)&g_roomOutlines[10], 0xe8 }, { (u32)&g_roomOutlines[11], 0x4 }, { (u32)&g_roomOutlines[22], 0x4 }, { (u32)&g_roomOutlines[23], 0xffffff01 }, { (u32)&g_roomOutlines[27], 0xffffff01 },
	{ (u32)&g_roomOutlines[33], 0x4 }, { (u32)&g_roomOutlines[40], 0xe8 }, { (u32)&g_roomOutlines[44], 0x4 }, { (u32)&g_roomOutlines[55], 0x4 }, { (u32)&g_roomOutlines[28], 0xffffff9c },
	{ (u32)&g_roomOutlines[32], 0xffffff9c }, { (u32)&g_roomOutlines[62], 0xffffff9c }, { (u32)&g_roomOutlines[34], 0x46 }, { (u32)&g_roomOutlines[38], 0x46 }, { (u32)&g_roomOutlines[59], 0x46 },
	{ (u32)&g_roomOutlines[2], 0xffffffba }, { (u32)&g_roomOutlines[7], 0x6e }, { (u32)&g_roomOutlines[3], 0xffffff86 }, { (u32)&g_roomOutlines[8], 0x32 }, { (u32)&g_roomOutlines[4], 0xffffff06 },
	{ (u32)&g_roomOutlines[9], 0x64 }, { (u32)&g_roomOutlines[17], 0x56 }, { (u32)&g_roomOutlines[18], 0x28 }, { (u32)&g_roomOutlines[19], 0xffffffd8 }, { (u32)&g_roomOutlines[20], 0xffffffad },
	{ (u32)&g_roomOutlines[21], 0x56 }, { (u32)&g_roomOutlines[24], 0xffffff86 }, { (u32)&g_roomOutlines[29], 0xffffffcf }, { (u32)&g_roomOutlines[25], 0xffffffb8 }, { (u32)&g_roomOutlines[30], 0xffffff91 },
	{ (u32)&g_roomOutlines[31], 0xffffff1a }, { (u32)&g_roomOutlines[39], 0x6f }, { (u32)&g_roomOutlines[35], 0x91 }, { (u32)&g_roomOutlines[36], 0xff }, { (u32)&g_roomOutlines[41], 0x67 },
	{ (u32)&g_roomOutlines[37], 0x78 }, { (u32)&g_roomOutlines[42], 0x32 }, { (u32)&g_roomOutlines[43], 0x6f }, { (u32)&g_roomOutlines[45], 0x7d }, { (u32)&g_roomOutlines[50], 0x28 },
	{ (u32)&g_roomOutlines[46], 0x106 }, { (u32)&g_roomOutlines[51], 0x56 }, { (u32)&g_roomOutlines[47], 0x106 }, { (u32)&g_roomOutlines[52], 0xffffffaa }, { (u32)&g_roomOutlines[48], 0x7d },
	{ (u32)&g_roomOutlines[53], 0xffffffd8 }, { (u32)&g_roomOutlines[49], 0x7d }, { (u32)&g_roomOutlines[54], 0x28 }, { (u32)&g_roomOutlines[56], 0x78 }, { (u32)&g_roomOutlines[61], 0xffffffce },
	{ (u32)&g_roomOutlines[57], 0xff }, { (u32)&g_roomOutlines[58], 0x92 }, { (u32)&g_roomOutlines[63], 0xffffff1a }, { (u32)&g_roomOutlines[64], 0xffffff91 }, { (u32)&g_roomOutlines[60], 0x78 },
	{ (u32)&g_roomOutlines[65], 0xffffffce } };

void (room_initOutlines)(void) { apply_stores(k_roomOutlines, 66); }   /* 0x42f690: the game room's button outlines */

static const Store k_dikCodes[118] = {
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
	{ ADDR(g_dikF1), 0x3b }, { ADDR(g_dikF2), 0x3c }, { ADDR(g_dikF3), 0x3d }, { ADDR(g_dikF4), 0x3e }, { ADDR(g_dikF5), 0x3f },
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
	{ ADDR(g_dikMouse3), 0xfc }, { ADDR(g_dikWheelUp), 0xfd }, { ADDR(g_dikWheelDown), 0xfe } };

void (input_initDikCodes)(void) { apply_stores(k_dikCodes, 118); }   /* 0x42fd40: the DirectInput key codes (DIK_*) into their globals */

static const CStore k_defaultBindings[68] = {
	{ ADDR(g_keyBackward), ADDR(g_dikS), 1 }, { ADDR(g_keyStepLeft), ADDR(g_dikA), 1 }, { ADDR(g_keyStepRight), ADDR(g_dikD), 1 }, { (u32)&g_controls[8], ADDR(g_dikLeft), 1 },
	{ (u32)&g_controls[10], ADDR(g_dikRight), 1 }, { (u32)&g_controls[12], ADDR(g_dikMouse2), 1 }, { (u32)&g_controls[14], ADDR(g_dikSpace), 1 }, { (u32)&g_controls[16], ADDR(g_dikR), 1 },
	{ (u32)&g_controls[18], ADDR(g_dikF), 1 }, { (u32)&g_controls[20], ADDR(g_dikMouse1), 1 }, { (u32)&g_controls[22], ADDR(g_dikQ), 1 }, { (u32)&g_controls[24], ADDR(g_dikE), 1 },
	{ (u32)&g_controls[30], ADDR(g_dik1), 1 }, { (u32)&g_controls[32], ADDR(g_dik2), 1 }, { (u32)&g_controls[34], ADDR(g_dik3), 1 }, { (u32)&g_controls[36], ADDR(g_dik4), 1 },
	{ (u32)&g_controls[26], ADDR(g_dik5), 1 }, { (u32)&g_controls[28], ADDR(g_dik6), 1 }, { (u32)&g_controls[38], ADDR(g_dikLShift), 1 }, { (u32)&g_controls[40], ADDR(g_dikRCtrl), 1 },
	{ ADDR(g_keyChat), ADDR(g_dikEnter), 1 }, { (u32)&g_controls[44], ADDR(g_dikC), 1 }, { ADDR(g_keyForward), ADDR(g_dikW), 1 }, { (u32)&g_controls[46], ADDR(g_dikX), 1 },
	{ (u32)&g_controls[48], ADDR(g_dikB), 1 }, { (u32)&g_controls[1], ADDR(g_dikNone), 1 }, { (u32)&g_controls[3], ADDR(g_dikNone), 1 }, { (u32)&g_controls[5], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[7], ADDR(g_dikNone), 1 }, { (u32)&g_controls[9], ADDR(g_dikNone), 1 }, { (u32)&g_controls[11], ADDR(g_dikNone), 1 }, { (u32)&g_controls[13], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[15], ADDR(g_dikNone), 1 }, { (u32)&g_controls[17], ADDR(g_dikNone), 1 }, { (u32)&g_controls[19], ADDR(g_dikNone), 1 }, { (u32)&g_controls[21], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[23], ADDR(g_dikNone), 1 }, { (u32)&g_controls[25], ADDR(g_dikNone), 1 }, { (u32)&g_controls[31], ADDR(g_dikNone), 1 }, { (u32)&g_controls[33], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[35], ADDR(g_dikNone), 1 }, { (u32)&g_controls[37], ADDR(g_dikNone), 1 }, { (u32)&g_controls[27], ADDR(g_dikNone), 1 }, { (u32)&g_controls[29], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[39], ADDR(g_dikNone), 1 }, { (u32)&g_controls[41], ADDR(g_dikNone), 1 }, { (u32)&g_controls[43], ADDR(g_dikNone), 1 }, { (u32)&g_controls[45], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[47], ADDR(g_dikNone), 1 }, { (u32)&g_controls[49], ADDR(g_dikNone), 1 }, { ADDR(g_keyGameMenu), ADDR(g_dikEscape_2), 1 }, { ADDR(g_keyGameMenu2), ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[52], ADDR(g_dikF4), 1 }, { (u32)&g_controls[54], ADDR(g_dikF5), 1 }, { (u32)&g_controls[53], ADDR(g_dikNone), 1 }, { (u32)&g_controls[55], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[56], ADDR(g_dikTab), 1 }, { (u32)&g_controls[57], ADDR(g_dikNone), 1 }, { (u32)&g_controls[58], ADDR(g_dikF10), 1 }, { (u32)&g_controls[59], ADDR(g_dikNone), 1 },
	{ (u32)&g_controls[61], ADDR(g_dikNone), 1 }, { (u32)&g_controls[63], ADDR(g_dikNone), 1 }, { (u32)&g_controls[60], ADDR(g_dikV), 1 }, { (u32)&g_controls[62], ADDR(g_dikF1), 1 },
	{ ADDR(g_mouseInvert), 0x0, 0 }, { ADDR(g_mouseSmooth), 0x0, 0 }, { ADDR(g_mouseSensitivity), 0x32, 0 }, { ADDR(g_crosshairSetting), 0x0, 0 } };

void (input_setDefaultBindings)(void) { apply_cstores(k_defaultBindings, 68); }   /* the default key bindings (g_controls) */

static const CStore k_defaultBindingsEdit[68] = {
	{ (u32)&g_controlsEdit[2], ADDR(g_dikS), 1 }, { (u32)&g_controlsEdit[4], ADDR(g_dikA), 1 }, { (u32)&g_controlsEdit[6], ADDR(g_dikD), 1 }, { (u32)&g_controlsEdit[8], ADDR(g_dikLeft), 1 },
	{ (u32)&g_controlsEdit[10], ADDR(g_dikRight), 1 }, { (u32)&g_controlsEdit[12], ADDR(g_dikMouse2), 1 }, { (u32)&g_controlsEdit[14], ADDR(g_dikSpace), 1 }, { (u32)&g_controlsEdit[16], ADDR(g_dikR), 1 },
	{ (u32)&g_controlsEdit[18], ADDR(g_dikF), 1 }, { (u32)&g_controlsEdit[20], ADDR(g_dikMouse1), 1 }, { (u32)&g_controlsEdit[22], ADDR(g_dikQ), 1 }, { (u32)&g_controlsEdit[24], ADDR(g_dikE), 1 },
	{ (u32)&g_controlsEdit[30], ADDR(g_dik1), 1 }, { (u32)&g_controlsEdit[32], ADDR(g_dik2), 1 }, { (u32)&g_controlsEdit[34], ADDR(g_dik3), 1 }, { (u32)&g_controlsEdit[36], ADDR(g_dik4), 1 },
	{ (u32)&g_controlsEdit[26], ADDR(g_dik5), 1 }, { (u32)&g_controlsEdit[28], ADDR(g_dik6), 1 }, { (u32)&g_controlsEdit[38], ADDR(g_dikLShift), 1 }, { (u32)&g_controlsEdit[40], ADDR(g_dikLCtrl), 1 },
	{ (u32)&g_controlsEdit[42], ADDR(g_dikEnter), 1 }, { (u32)&g_controlsEdit[44], ADDR(g_dikC), 1 }, { OBJ(g_controlsEdit), ADDR(g_dikW), 1 }, { (u32)&g_controlsEdit[46], ADDR(g_dikX), 1 },
	{ (u32)&g_controlsEdit[48], ADDR(g_dikB), 1 }, { (u32)&g_controlsEdit[1], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[3], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[5], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[7], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[9], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[11], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[13], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[15], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[17], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[19], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[21], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[23], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[25], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[31], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[33], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[35], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[37], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[27], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[29], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[39], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[41], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[43], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[45], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[47], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[49], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[50], ADDR(g_dikEscape_2), 1 }, { (u32)&g_controlsEdit[51], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[52], ADDR(g_dikF4), 1 }, { (u32)&g_controlsEdit[54], ADDR(g_dikF5), 1 }, { (u32)&g_controlsEdit[53], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[55], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[56], ADDR(g_dikTab), 1 }, { (u32)&g_controlsEdit[57], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[58], ADDR(g_dikF10), 1 }, { (u32)&g_controlsEdit[59], ADDR(g_dikNone), 1 },
	{ (u32)&g_controlsEdit[61], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[63], ADDR(g_dikNone), 1 }, { (u32)&g_controlsEdit[60], ADDR(g_dikV), 1 }, { (u32)&g_controlsEdit[62], ADDR(g_dikF1), 1 },
	{ OBJ(g_mouseSwitchesEdit), 0x0, 0 }, { (OBJ(g_mouseSwitchesEdit) + 0x4), 0x0, 0 }, { ADDR(g_sensitivitySlider), 0x32, 0 }, { ADDR(g_crosshairEdit), 0x0, 0 } };

void (setup_defaultBindings)(void) { apply_cstores(k_defaultBindingsEdit, 68); }   /* the setup page's DEFAULT: the defaults into its edit copy (g_controlsEdit) */

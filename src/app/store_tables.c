/* store_tables.c: initialisers that set many globals to constants (or copy them from other globals): kept as tables of {address, value} stores, applied in order. Tables made by tools/straightline.py from the original code. */
#include "../game.h"

#define GAME_I32(a) GAME_VAR(int, a)
#define GAME_U32(a) GAME_VAR(u32, a)
#define GAME_F32(a) GAME_VAR(float, a)
#define FIELD_I32(p, o) GAME_VAR(int, (u8 *)RELOC(p) + (o))

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
	{ 0xa1f298, 0xffffffff }, { 0xa1f29c, 0xff5454f3 }, { 0xa1f2a4, 0xfff35466 }, { 0xa1f2a0, 0xffe7b7fd }, { 0xa1f2a8, 0xffffcc00 },
	{ 0xa1f2b0, 0xffa6ffcc }, { 0xa1f2b4, 0xff00f0ff }, { 0xa1f2b8, 0xffd3c8c8 }, { 0xa1f2bc, 0xffa09090 }, { 0xa1f2ac, 0xff23d33c },
	{ 0xa1f2c0, 0xff859a98 }, { 0xa1f2c4, 0xff000085 }, { 0xa1f2c8, 0xffff000c }, { 0xa1f2cc, 0xffff00d2 }, { 0xa1f2d0, 0xff3a322e },
	{ 0xa1f2d4, 0xffa2ff00 } };

void (color_initDefaultColours)(void) { apply_stores(k_color_initDefaultColours, 16); }   /* 0x46dc50 default RGBA colours (bytes) */

static const Store k_intro_42f500[44] = {
	{ IMG(0x5b1d10), 0xe7 }, { IMG(0x5b1d20), 0xe7 }, { IMG(0x5b1d6c), 0xe7 }, { IMG(0x5b1cfc), 0xffffff65 }, { IMG(0x5b1d0c), 0xffffff65 },
	{ IMG(0x5b1d04), 0xffffff7e }, { IMG(0x5b1d08), 0xfffffef2 }, { IMG(0x5b1d28), 0xfffffef2 }, { IMG(0x5b1d2c), 0xffffff7e }, { IMG(0x5b1d38), 0xfffffef2 },
	{ IMG(0x5b1d5c), 0x10e }, { IMG(0x5b1d84), 0x10e }, { IMG(0x5b1d3c), 0xffffffc1 }, { IMG(0x5b1d4c), 0xffffffc1 }, { IMG(0x5b1d98), 0xffffffc1 },
	{ IMG(0x5b1cf8), 0x4 }, { IMG(0x5b1d00), 0xffffffb6 }, { IMG(0x5b1d14), 0x6e }, { IMG(0x5b1d18), 0x1f }, { IMG(0x5b1d1c), 0x42 },
	{ IMG(0x5b1d24), 0x4 }, { IMG(0x5b1d40), 0xffffffe2 }, { IMG(0x5b1d30), 0xffffffb5 }, { IMG(0x5b1d44), 0xffffff90 }, { IMG(0x5b1d34), 0xffffff67 },
	{ IMG(0x5b1d48), 0xffffff1a }, { IMG(0x5b1d50), 0x4 }, { IMG(0x5b1d54), 0x49 }, { IMG(0x5b1d68), 0x70 }, { IMG(0x5b1d58), 0x9b },
	{ IMG(0x5b1d70), 0x42 }, { IMG(0x5b1d60), 0x82 }, { IMG(0x5b1d74), 0x1f }, { IMG(0x5b1d64), 0x49 }, { IMG(0x5b1d78), 0x70 },
	{ IMG(0x5b1d7c), 0x4 }, { IMG(0x5b1d80), 0x82 }, { IMG(0x5b1d94), 0xffffffe2 }, { IMG(0x5b1d88), 0x9b }, { IMG(0x5b1d9c), 0xffffff1a },
	{ IMG(0x5b1d8c), 0x4b }, { IMG(0x5b1da0), 0xffffff90 }, { IMG(0x5b1d90), 0x82 }, { IMG(0x5b1da4), 0xffffffe2 } };

void (menu_initKeyRepeatDefaults)(void) { apply_stores(k_intro_42f500, 44); }   /* 0x42f500 intro table */

static const Store k_input_initVkTable[57] = {
	{ 0x4df054, 0x1b }, { 0x4df058, 0x31 }, { 0x4df05c, 0x32 }, { 0x4df060, 0x33 }, { 0x4df064, 0x34 },
	{ 0x4df068, 0x35 }, { 0x4df06c, 0x36 }, { 0x4df070, 0x37 }, { 0x4df074, 0x38 }, { 0x4df078, 0x39 },
	{ 0x4df07c, 0x30 }, { 0x4df080, 0x2d }, { 0x4df084, 0x3d }, { 0x4df088, 0x8 }, { 0x4df08c, 0x9 },
	{ 0x4df090, 0x51 }, { 0x4df094, 0x57 }, { 0x4df098, 0x45 }, { 0x4df09c, 0x52 }, { 0x4df0a0, 0x54 },
	{ 0x4df0a4, 0x59 }, { 0x4df0a8, 0x55 }, { 0x4df0ac, 0x49 }, { 0x4df0b0, 0x4f }, { 0x4df0b4, 0x50 },
	{ 0x4df0b8, 0x5b }, { 0x4df0bc, 0x5d }, { 0x4df0c0, 0xd }, { 0x4df0c4, 0x0 }, { 0x4df0c8, 0x41 },
	{ 0x4df0cc, 0x53 }, { 0x4df0d0, 0x44 }, { 0x4df0d4, 0x46 }, { 0x4df0d8, 0x47 }, { 0x4df0dc, 0x48 },
	{ 0x4df0e0, 0x4a }, { 0x4df0e4, 0x4b }, { 0x4df0e8, 0x4c }, { 0x4df0ec, 0x3b }, { 0x4df0f0, 0x27 },
	{ 0x4df0f4, 0x60 }, { 0x4df0f8, 0x10 }, { 0x4df0fc, 0x5c }, { 0x4df100, 0x5a }, { 0x4df104, 0x58 },
	{ 0x4df108, 0x43 }, { 0x4df10c, 0x56 }, { 0x4df110, 0x42 }, { 0x4df114, 0x4e }, { 0x4df118, 0x4d },
	{ 0x4df11c, 0x2c }, { 0x4df120, 0x2e }, { 0x4df124, 0x2f }, { 0x4df128, 0x10 }, { 0x4df12c, 0x2a },
	{ 0x4df130, 0x0 }, { 0x4df134, 0x20 } };

void (input_initVkTable)(void) { apply_stores(k_input_initVkTable, 57); }   /* 0x431680 scan-code row -> virtual key table */

static const Store k_replay_46d4d0[64] = {
	{ IMG(0xa1f100), 0x3f800000 }, { IMG(0xa1f104), 0x3f800000 }, { IMG(0xa1f108), 0x3f800000 }, { IMG(0xa1f10c), 0x3f800000 }, { IMG(0xa1f110), 0x3f73f3f4 },
	{ IMG(0xa1f114), 0x3ea8a8a9 }, { IMG(0xa1f118), 0x3ea8a8a9 }, { IMG(0xa1f11c), 0x3f800000 }, { IMG(0xa1f120), 0x3f7dfdfe }, { IMG(0xa1f124), 0x3f37b7b8 },
	{ IMG(0xa1f128), 0x3f67e7e8 }, { IMG(0xa1f12c), 0x3f800000 }, { IMG(0xa1f130), 0x3ecccccd }, { IMG(0xa1f134), 0x3ea8a8a9 }, { IMG(0xa1f138), 0x3f73f3f4 },
	{ IMG(0xa1f13c), 0x3f800000 }, { IMG(0xa1f140), 0x0 }, { IMG(0xa1f144), 0x3f4ccccd }, { IMG(0xa1f148), 0x3f800000 }, { IMG(0xa1f14c), 0x3f800000 },
	{ IMG(0xa1f150), 0x3e70f0f1 }, { IMG(0xa1f154), 0x3f53d3d4 }, { IMG(0xa1f158), 0x3e0c8c8d }, { IMG(0xa1f15c), 0x3f800000 }, { IMG(0xa1f160), 0x3f4ccccd },
	{ IMG(0xa1f164), 0x3f800000 }, { IMG(0xa1f168), 0x3f26a6a7 }, { IMG(0xa1f16c), 0x3f800000 }, { IMG(0xa1f170), 0x3f800000 }, { IMG(0xa1f174), 0x3f70f0f1 },
	{ IMG(0xa1f178), 0x0 }, { IMG(0xa1f17c), 0x3f800000 }, { IMG(0xa1f180), 0x3f48c8c9 }, { IMG(0xa1f184), 0x3f48c8c9 }, { IMG(0xa1f188), 0x3f53d3d4 },
	{ IMG(0xa1f18c), 0x3f800000 }, { IMG(0xa1f190), 0x3f109091 }, { IMG(0xa1f194), 0x3f109091 }, { IMG(0xa1f198), 0x3f20a0a1 }, { IMG(0xa1f19c), 0x3f800000 },
	{ IMG(0xa1f1a0), 0x3f189899 }, { IMG(0xa1f1a4), 0x3f1a9a9b }, { IMG(0xa1f1a8), 0x3f058586 }, { IMG(0xa1f1ac), 0x3f800000 }, { IMG(0xa1f1b0), 0x3f058586 },
	{ IMG(0xa1f1b4), 0x0 }, { IMG(0xa1f1b8), 0x0 }, { IMG(0xa1f1bc), 0x3f800000 }, { IMG(0xa1f1c0), 0x3d40c0c1 }, { IMG(0xa1f1c4), 0x0 },
	{ IMG(0xa1f1c8), 0x3f800000 }, { IMG(0xa1f1cc), 0x3f800000 }, { IMG(0xa1f1d0), 0x3f52d2d3 }, { IMG(0xa1f1d4), 0x0 }, { IMG(0xa1f1d8), 0x3f800000 },
	{ IMG(0xa1f1dc), 0x3f800000 }, { IMG(0xa1f1e0), 0x3e38b8b9 }, { IMG(0xa1f1e4), 0x3e48c8c9 }, { IMG(0xa1f1e8), 0x3e68e8e9 }, { IMG(0xa1f1ec), 0x3f800000 },
	{ IMG(0xa1f1f0), 0x0 }, { IMG(0xa1f1f4), 0x3f800000 }, { IMG(0xa1f1f8), 0x3f22a2a3 }, { IMG(0xa1f1fc), 0x3f800000 } };

void (color_initTextColours)(void) { apply_stores(k_replay_46d4d0, 64); }   /* 0x46d4d0 64-entry table */

static const Store k_intro_42f2b0[66] = {
	{ IMG(0x4debb0), 0xfffffefc }, { IMG(0x4debbc), 0xfffffefc }, { IMG(0x4debc0), 0xfffffefc }, { IMG(0x4debb4), 0xffffff81 }, { IMG(0x4debb8), 0xffffff81 },
	{ IMG(0x4deb84), 0xffffff6f }, { IMG(0x4deb94), 0xffffff6f }, { IMG(0x4debe8), 0xffffff6f }, { IMG(0x4deb80), 0x4 }, { IMG(0x4deb98), 0xe8 },
	{ IMG(0x4deba8), 0xe8 }, { IMG(0x4debac), 0x4 }, { IMG(0x4debd8), 0x4 }, { IMG(0x4debdc), 0xffffff01 }, { IMG(0x4debec), 0xffffff01 },
	{ IMG(0x4dec04), 0x4 }, { IMG(0x4dec20), 0xe8 }, { IMG(0x4dec30), 0x4 }, { IMG(0x4dec5c), 0x4 }, { IMG(0x4debf0), 0xffffff9c },
	{ IMG(0x4dec00), 0xffffff9c }, { IMG(0x4dec78), 0xffffff9c }, { IMG(0x4dec08), 0x46 }, { IMG(0x4dec18), 0x46 }, { IMG(0x4dec6c), 0x46 },
	{ IMG(0x4deb88), 0xffffffba }, { IMG(0x4deb9c), 0x6e }, { IMG(0x4deb8c), 0xffffff86 }, { IMG(0x4deba0), 0x32 }, { IMG(0x4deb90), 0xffffff06 },
	{ IMG(0x4deba4), 0x64 }, { IMG(0x4debc4), 0x56 }, { IMG(0x4debc8), 0x28 }, { IMG(0x4debcc), 0xffffffd8 }, { IMG(0x4debd0), 0xffffffad },
	{ IMG(0x4debd4), 0x56 }, { IMG(0x4debe0), 0xffffff86 }, { IMG(0x4debf4), 0xffffffcf }, { IMG(0x4debe4), 0xffffffb8 }, { IMG(0x4debf8), 0xffffff91 },
	{ IMG(0x4debfc), 0xffffff1a }, { IMG(0x4dec1c), 0x6f }, { IMG(0x4dec0c), 0x91 }, { IMG(0x4dec10), 0xff }, { IMG(0x4dec24), 0x67 },
	{ IMG(0x4dec14), 0x78 }, { IMG(0x4dec28), 0x32 }, { IMG(0x4dec2c), 0x6f }, { IMG(0x4dec34), 0x7d }, { IMG(0x4dec48), 0x28 },
	{ IMG(0x4dec38), 0x106 }, { IMG(0x4dec4c), 0x56 }, { IMG(0x4dec3c), 0x106 }, { IMG(0x4dec50), 0xffffffaa }, { IMG(0x4dec40), 0x7d },
	{ IMG(0x4dec54), 0xffffffd8 }, { IMG(0x4dec44), 0x7d }, { IMG(0x4dec58), 0x28 }, { IMG(0x4dec60), 0x78 }, { IMG(0x4dec74), 0xffffffce },
	{ IMG(0x4dec64), 0xff }, { IMG(0x4dec68), 0x92 }, { IMG(0x4dec7c), 0xffffff1a }, { IMG(0x4dec80), 0xffffff91 }, { IMG(0x4dec70), 0x78 },
	{ IMG(0x4dec84), 0xffffffce } };

void (menu_initMainButtons)(void) { apply_stores(k_intro_42f2b0, 66); }   /* 0x42f2b0 intro table */

static const Store k_intro_42f690[66] = {
	{ IMG(0x9dafb8), 0xfffffefc }, { IMG(0x9dafc4), 0xfffffefc }, { IMG(0x9dafc8), 0xfffffefc }, { IMG(0x9dafbc), 0xffffff81 }, { IMG(0x9dafc0), 0xffffff81 },
	{ IMG(0x9daf8c), 0xffffff6f }, { IMG(0x9daf9c), 0xffffff6f }, { IMG(0x9daff0), 0xffffff6f }, { IMG(0x9daf88), 0x4 }, { IMG(0x9dafa0), 0xe8 },
	{ IMG(0x9dafb0), 0xe8 }, { IMG(0x9dafb4), 0x4 }, { IMG(0x9dafe0), 0x4 }, { IMG(0x9dafe4), 0xffffff01 }, { IMG(0x9daff4), 0xffffff01 },
	{ IMG(0x9db00c), 0x4 }, { IMG(0x9db028), 0xe8 }, { IMG(0x9db038), 0x4 }, { IMG(0x9db064), 0x4 }, { IMG(0x9daff8), 0xffffff9c },
	{ IMG(0x9db008), 0xffffff9c }, { IMG(0x9db080), 0xffffff9c }, { IMG(0x9db010), 0x46 }, { IMG(0x9db020), 0x46 }, { IMG(0x9db074), 0x46 },
	{ IMG(0x9daf90), 0xffffffba }, { IMG(0x9dafa4), 0x6e }, { IMG(0x9daf94), 0xffffff86 }, { IMG(0x9dafa8), 0x32 }, { IMG(0x9daf98), 0xffffff06 },
	{ IMG(0x9dafac), 0x64 }, { IMG(0x9dafcc), 0x56 }, { IMG(0x9dafd0), 0x28 }, { IMG(0x9dafd4), 0xffffffd8 }, { IMG(0x9dafd8), 0xffffffad },
	{ IMG(0x9dafdc), 0x56 }, { IMG(0x9dafe8), 0xffffff86 }, { IMG(0x9daffc), 0xffffffcf }, { IMG(0x9dafec), 0xffffffb8 }, { IMG(0x9db000), 0xffffff91 },
	{ IMG(0x9db004), 0xffffff1a }, { IMG(0x9db024), 0x6f }, { IMG(0x9db014), 0x91 }, { IMG(0x9db018), 0xff }, { IMG(0x9db02c), 0x67 },
	{ IMG(0x9db01c), 0x78 }, { IMG(0x9db030), 0x32 }, { IMG(0x9db034), 0x6f }, { IMG(0x9db03c), 0x7d }, { IMG(0x9db050), 0x28 },
	{ IMG(0x9db040), 0x106 }, { IMG(0x9db054), 0x56 }, { IMG(0x9db044), 0x106 }, { IMG(0x9db058), 0xffffffaa }, { IMG(0x9db048), 0x7d },
	{ IMG(0x9db05c), 0xffffffd8 }, { IMG(0x9db04c), 0x7d }, { IMG(0x9db060), 0x28 }, { IMG(0x9db068), 0x78 }, { IMG(0x9db07c), 0xffffffce },
	{ IMG(0x9db06c), 0xff }, { IMG(0x9db070), 0x92 }, { IMG(0x9db084), 0xffffff1a }, { IMG(0x9db088), 0xffffff91 }, { IMG(0x9db078), 0x78 },
	{ IMG(0x9db08c), 0xffffffce } };

void (room_initMenuButtons)(void) { apply_stores(k_intro_42f690, 66); }   /* 0x42f690 intro table */

static const Store k_input_setDefaultKeyBindings[118] = {
	{ ADDR(g_dikNone), 0x0 }, { ADDR(g_dikEscape), 0x1 }, { ADDR(g_dik1), 0x2 }, { ADDR(g_dik2), 0x3 }, { ADDR(g_dik3), 0x4 },
	{ ADDR(g_dik4), 0x5 }, { IMG(0x4e0c78), 0x6 }, { IMG(0x4e0c7c), 0x7 }, { IMG(0x4e0c80), 0x8 }, { IMG(0x4e0c84), 0x9 },
	{ IMG(0x4e0c88), 0xa }, { IMG(0x4e0460), 0xb }, { ADDR(g_dikA), 0x1e }, { IMG(0x4e0cd8), 0x30 }, { ADDR(g_dikC), 0x2e },
	{ ADDR(g_dikD), 0x20 }, { IMG(0x4e10e4), 0x12 }, { IMG(0x4e14e8), 0x21 }, { ADDR(g_dikG), 0x22 }, { IMG(0x4e14f0), 0x23 },
	{ ADDR(g_dikI), 0x17 }, { ADDR(g_dikJ), 0x24 }, { IMG(0x4e1500), 0x25 }, { ADDR(g_dikL), 0x26 }, { ADDR(g_dikM), 0x32 },
	{ ADDR(g_dikN), 0x31 }, { ADDR(g_dikO), 0x18 }, { ADDR(g_dikP), 0x19 }, { IMG(0x4e1518), 0x10 }, { ADDR(g_dikR), 0x13 },
	{ ADDR(g_dikS), 0x1f }, { ADDR(g_dikT), 0x14 }, { IMG(0x4e1530), 0x16 }, { IMG(0x4e1534), 0x2f }, { ADDR(g_dikW), 0x11 },
	{ ADDR(g_dikX), 0x2d }, { IMG(0x4e1540), 0x15 }, { IMG(0x4e1544), 0x2c }, { ADDR(g_dikEnter), 0x1c }, { IMG(0x76d374), 0xc },
	{ IMG(0x9dae18), 0xd }, { IMG(0x76d378), 0xe }, { ADDR(g_dikTab), 0xf }, { IMG(0x4df8fc), 0x1a }, { IMG(0x76d380), 0x1b },
	{ IMG(0x76d470), 0x27 }, { IMG(0x76d334), 0x29 }, { IMG(0x9dae78), 0x2b }, { IMG(0x680368), 0x33 }, { IMG(0x4deda4), 0x34 },
	{ IMG(0x5b1974), 0x35 }, { IMG(0x74de20), 0x28 }, { ADDR(g_dikRCtrl), 0x9d }, { ADDR(g_dikLCtrl), 0x1d }, { ADDR(g_dikLShift), 0x2a },
	{ ADDR(g_dikRShift), 0x36 }, { ADDR(g_dikLAlt), 0x38 }, { ADDR(g_dikRAlt), 0xb8 }, { ADDR(g_dikSpace), 0x39 }, { IMG(0x76d420), 0x3a },
	{ ADDR(g_excludedKey), 0x3b }, { IMG(0x9da44c), 0x3c }, { IMG(0x9da448), 0x3d }, { IMG(0x9da454), 0x3e }, { IMG(0x9da450), 0x3f },
	{ IMG(0x9da474), 0x40 }, { IMG(0x9da458), 0x41 }, { IMG(0x9da47c), 0x42 }, { IMG(0x9da478), 0x43 }, { IMG(0x4df8dc), 0x44 },
	{ ADDR(g_dikF11), 0x57 }, { IMG(0x4df8d4), 0x58 }, { IMG(0x4dec94), 0x45 }, { IMG(0x67ef10), 0x46 }, { IMG(0x67fb40), 0xb7 },
	{ IMG(0x4dec90), 0x4f }, { IMG(0x4dec8c), 0x50 }, { IMG(0x4deb5c), 0x51 }, { IMG(0x4deb58), 0x4b }, { IMG(0x4deb64), 0x4c },
	{ IMG(0x4deb60), 0x4d }, { IMG(0x4deb6c), 0x47 }, { IMG(0x4deb68), 0x48 }, { IMG(0x4deb70), 0x49 }, { IMG(0x4deb78), 0x52 },
	{ IMG(0x76d3f4), 0x4a }, { IMG(0x67ef08), 0x4e }, { IMG(0x4dec88), 0x53 }, { IMG(0x6803a4), 0x9c }, { IMG(0x9db0a8), 0x37 },
	{ IMG(0x4e0ca0), 0xb5 }, { ADDR(g_dikUp), 0xc8 }, { ADDR(g_dikDown), 0xd0 }, { ADDR(g_dikLeft), 0xcb }, { ADDR(g_dikRight), 0xcd },
	{ ADDR(g_dikPageUp), 0xc9 }, { IMG(0x5b1980), 0xd1 }, { IMG(0x90d1c0), 0xc7 }, { IMG(0x5ae9c0), 0xcf }, { IMG(0x4deda0), 0xd2 },
	{ ADDR(g_dikDelete), 0xd3 }, { IMG(0x4df038), 0xdb }, { IMG(0x76d338), 0xdc }, { IMG(0x67ef28), 0xdd }, { ADDR(g_dikEscape_2), 0x1 },
	{ IMG(0x4df04c), 0xd2 }, { IMG(0x5b1db0), 0xc9 }, { IMG(0x9dae6c), 0xc7 }, { IMG(0x76d32c), 0xcf }, { IMG(0x907b28), 0xd3 },
	{ IMG(0x76d370), 0xd1 }, { ADDR(g_dikZ_2), 0x2c }, { IMG(0x67ef2c), 0x1c }, { ADDR(g_dikMouse1), 0xfa }, { ADDR(g_dikMouse2), 0xfb },
	{ IMG(0x680bbc), 0xfc }, { ADDR(g_dikWheelDown), 0xfd }, { ADDR(g_dikWheelUp), 0xfe } };

void (input_setDefaultKeyBindings)(void) { apply_stores(k_input_setDefaultKeyBindings, 118); }   /* 0x42fd40 default key bindings */

static const CStore k_input_applyKeyBindings[68] = {
	{ ADDR(g_keyFreeCam1), ADDR(g_dikS), 1 }, { ADDR(g_keyFreeCam2), ADDR(g_dikA), 1 }, { ADDR(g_keyFreeCam3), ADDR(g_dikD), 1 }, { (OBJ(g_controls) + 0x20), ADDR(g_dikLeft), 1 },
	{ (OBJ(g_controls) + 0x28), ADDR(g_dikRight), 1 }, { (OBJ(g_controls) + 0x30), ADDR(g_dikMouse2), 1 }, { (OBJ(g_controls) + 0x38), ADDR(g_dikSpace), 1 }, { (OBJ(g_controls) + 0x40), ADDR(g_dikR), 1 },
	{ (OBJ(g_controls) + 0x48), IMG(0x4e14e8), 1 }, { (OBJ(g_controls) + 0x50), ADDR(g_dikMouse1), 1 }, { (OBJ(g_controls) + 0x58), IMG(0x4e1518), 1 }, { (OBJ(g_controls) + 0x60), IMG(0x4e10e4), 1 },
	{ (OBJ(g_controls) + 0x78), ADDR(g_dik1), 1 }, { (OBJ(g_controls) + 0x80), ADDR(g_dik2), 1 }, { (OBJ(g_controls) + 0x88), ADDR(g_dik3), 1 }, { (OBJ(g_controls) + 0x90), ADDR(g_dik4), 1 },
	{ (OBJ(g_controls) + 0x68), IMG(0x4e0c78), 1 }, { (OBJ(g_controls) + 0x70), IMG(0x4e0c7c), 1 }, { (OBJ(g_controls) + 0x98), ADDR(g_dikLShift), 1 }, { (OBJ(g_controls) + 0xa0), ADDR(g_dikRCtrl), 1 },
	{ ADDR(g_keyWatchChat), ADDR(g_dikEnter), 1 }, { (OBJ(g_controls) + 0xb0), ADDR(g_dikC), 1 }, { ADDR(g_keyFreeCam0), ADDR(g_dikW), 1 }, { (OBJ(g_controls) + 0xb8), ADDR(g_dikX), 1 },
	{ (OBJ(g_controls) + 0xc0), IMG(0x4e0cd8), 1 }, { (OBJ(g_controls) + 0x4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xc), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x14), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x1c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x24), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x2c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x34), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x3c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x44), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x4c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x54), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x5c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x64), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x7c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x84), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x8c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x94), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x6c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0x74), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0x9c), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xa4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xac), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xb4), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xbc), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xc4), ADDR(g_dikNone), 1 }, { ADDR(g_keyLoadingSkip), ADDR(g_dikEscape_2), 1 }, { ADDR(g_keyLoadingSkip2), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xd0), IMG(0x9da454), 1 }, { (OBJ(g_controls) + 0xd8), IMG(0x9da450), 1 }, { (OBJ(g_controls) + 0xd4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xdc), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xe0), ADDR(g_dikTab), 1 }, { (OBJ(g_controls) + 0xe4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xe8), IMG(0x4df8dc), 1 }, { (OBJ(g_controls) + 0xec), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controls) + 0xf4), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xfc), ADDR(g_dikNone), 1 }, { (OBJ(g_controls) + 0xf0), IMG(0x4e1534), 1 }, { (OBJ(g_controls) + 0xf8), ADDR(g_excludedKey), 1 },
	{ ADDR(g_mouseInvert), 0x0, 0 }, { ADDR(g_mouseSmooth), 0x0, 0 }, { ADDR(g_mouseSensitivity), 0x32, 0 }, { ADDR(g_crosshairSetting), 0x0, 0 } };

void (input_applyKeyBindings)(void) { apply_cstores(k_input_applyKeyBindings, 68); }

static const CStore k_setup_controlTabHelper_420c10[68] = {
	{ (OBJ(g_controlsEdit) + 0x8), ADDR(g_dikS), 1 }, { (OBJ(g_controlsEdit) + 0x10), ADDR(g_dikA), 1 }, { (OBJ(g_controlsEdit) + 0x18), ADDR(g_dikD), 1 }, { (OBJ(g_controlsEdit) + 0x20), ADDR(g_dikLeft), 1 },
	{ (OBJ(g_controlsEdit) + 0x28), ADDR(g_dikRight), 1 }, { (OBJ(g_controlsEdit) + 0x30), ADDR(g_dikMouse2), 1 }, { (OBJ(g_controlsEdit) + 0x38), ADDR(g_dikSpace), 1 }, { (OBJ(g_controlsEdit) + 0x40), ADDR(g_dikR), 1 },
	{ (OBJ(g_controlsEdit) + 0x48), IMG(0x4e14e8), 1 }, { (OBJ(g_controlsEdit) + 0x50), ADDR(g_dikMouse1), 1 }, { (OBJ(g_controlsEdit) + 0x58), IMG(0x4e1518), 1 }, { (OBJ(g_controlsEdit) + 0x60), IMG(0x4e10e4), 1 },
	{ (OBJ(g_controlsEdit) + 0x78), ADDR(g_dik1), 1 }, { (OBJ(g_controlsEdit) + 0x80), ADDR(g_dik2), 1 }, { (OBJ(g_controlsEdit) + 0x88), ADDR(g_dik3), 1 }, { (OBJ(g_controlsEdit) + 0x90), ADDR(g_dik4), 1 },
	{ (OBJ(g_controlsEdit) + 0x68), IMG(0x4e0c78), 1 }, { (OBJ(g_controlsEdit) + 0x70), IMG(0x4e0c7c), 1 }, { (OBJ(g_controlsEdit) + 0x98), ADDR(g_dikLShift), 1 }, { (OBJ(g_controlsEdit) + 0xa0), ADDR(g_dikLCtrl), 1 },
	{ (OBJ(g_controlsEdit) + 0xa8), ADDR(g_dikEnter), 1 }, { (OBJ(g_controlsEdit) + 0xb0), ADDR(g_dikC), 1 }, { OBJ(g_controlsEdit), ADDR(g_dikW), 1 }, { (OBJ(g_controlsEdit) + 0xb8), ADDR(g_dikX), 1 },
	{ (OBJ(g_controlsEdit) + 0xc0), IMG(0x4e0cd8), 1 }, { (OBJ(g_controlsEdit) + 0x4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xc), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x14), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x1c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x24), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x2c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x34), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x3c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x44), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x4c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x54), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x5c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x64), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x7c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x84), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x8c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x94), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x6c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0x74), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0x9c), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xa4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xac), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xb4), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xbc), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xc4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xc8), ADDR(g_dikEscape_2), 1 }, { (OBJ(g_controlsEdit) + 0xcc), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xd0), IMG(0x9da454), 1 }, { (OBJ(g_controlsEdit) + 0xd8), IMG(0x9da450), 1 }, { (OBJ(g_controlsEdit) + 0xd4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xdc), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xe0), ADDR(g_dikTab), 1 }, { (OBJ(g_controlsEdit) + 0xe4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xe8), IMG(0x4df8dc), 1 }, { (OBJ(g_controlsEdit) + 0xec), ADDR(g_dikNone), 1 },
	{ (OBJ(g_controlsEdit) + 0xf4), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xfc), ADDR(g_dikNone), 1 }, { (OBJ(g_controlsEdit) + 0xf0), IMG(0x4e1534), 1 }, { (OBJ(g_controlsEdit) + 0xf8), ADDR(g_excludedKey), 1 },
	{ OBJ(g_setupToggles), 0x0, 0 }, { (OBJ(g_setupToggles) + 0x4), 0x0, 0 }, { ADDR(g_sensitivitySlider), 0x32, 0 }, { ADDR(g_crosshair), 0x0, 0 } };

void (setup_keepKeyBindings)(void) { apply_cstores(k_setup_controlTabHelper_420c10, 68); }

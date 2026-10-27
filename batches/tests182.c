/* batch 181: generated tests (tools/gentests.py, gen_setup from batch 172) */
static const DWORD g_gs_443530[] = { 0x40ce70, 0, 0x441250, 1, 0x441740, 0, 0x442050, 0, 0x4434f0, 0, 0 };
static const DWORD g_gi_443530[] = { 0x67ef14, 0x67ef20, 0x9eeab4, 0 };
static const DWORD g_gb_443530[] = { 0 };
T_PLAIN(menuState300_frame, 0x443530, gen_setup(g_gs_443530, g_gi_443530, g_gb_443530);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_427920[] = { 0x4230e0, 0, 0x423330, 0, 0x4277c0, 0, 0x427830, 0, 0x427880, 0, 0x4278d0, 0, 0x441740, 0, 0 };
static const DWORD g_gi_427920[] = { 0x4ddac8, 0 };
static const DWORD g_gb_427920[] = { 0 };
T_PLAIN(menuState600_setup, 0x427920, gen_setup(g_gs_427920, g_gi_427920, g_gb_427920);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_445be0[] = { 0x428c30, 4, 0x441740, 0, 0x444130, 0, 0x4445a0, 0, 0x445bc0, 0, 0x445bd0, 0, 0 };
static const DWORD g_gi_445be0[] = { 0x90d1c4, 0x9eeba8, 0x9ef1f0, 0x9ef1f8, 0x9f16a8, 0x9f16ac, 0x9f16b0, 0x9f16b4, 0 };
static const DWORD g_gb_445be0[] = { 0 };
T_PLAIN(menuState900_skirmishSetup, 0x445be0, gen_setup(g_gs_445be0, g_gi_445be0, g_gb_445be0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_44f860[] = { 0x42b590, 0, 0x441740, 0, 0x44f410, 0, 0x44f4b0, 0, 0x44f5f0, 0, 0x44f6c0, 0, 0x44f740, 0, 0x44f810, 0, 0x44f850, 0, 0 };
static const DWORD g_gi_44f860[] = { 0x4dda48, 0x9f6838, 0x9f8f10, 0 };
static const DWORD g_gb_44f860[] = { 0x9f9070, 0 };
T_PLAIN(menuState210_frame, 0x44f860, gen_setup(g_gs_44f860, g_gi_44f860, g_gb_44f860);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_452ec0[] = { 0x4515a0, 0, 0x452fe0, 0, 0x4547d0, 1, 0x454940, 1, 0x454a50, 1, 0x454b70, 1, 0x454c80, 1, 0 };
static const DWORD g_gi_452ec0[] = { 0xa0b384, 0xa0b388, 0xa0b390, 0xa0b418, 0xa0b41c, 0xa0b420, 0xa0b424, 0xa0b428, 0 };
static const DWORD g_gb_452ec0[] = { 0xa0d320, 0 };
T_PLAIN(arena_452ec0, 0x452ec0, gen_setup(g_gs_452ec0, g_gi_452ec0, g_gb_452ec0); /* the stored address 0xa0d320 is copied into a 16-byte buffer (an IP address fits) */ fill_str((char *)0xa0d320, 15, '0', '9');, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* skirmish_445bc0: a jump stub (to skirmish_drawScreenA), its target stubbed */
static const DWORD g_stubSkirmishA[] = { 0x444f40, 0, 0 };
T_PLAIN(skirmish_445bc0, 0x445bc0, callee_stubs(g_stubSkirmishA, 0);, 0, 0, 0, 0, 0)

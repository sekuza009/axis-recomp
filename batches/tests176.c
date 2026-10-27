/* batch 175: generated tests (tools/gentests.py, gen_setup from batch 172) */
/* FUN_0041edc0 / FUN_0041ed70 free the list at 0x67fb3c one node at a time (FUN_00441190, real: a stub would never
   empty it) before returning to the menus: 0..4 nodes in BUF, the next pointer at +0x3534 */
static void freelist_setup(const DWORD *gs, const DWORD *gi, const DWORD *gb)
{
	gen_setup(gs, gi, gb);
	int n = irnd(0, 4);
	for (int i = 0; i < n; i++) S32(BUF + 0x10000 + i * 0x4000, 0x3534) = i + 1 < n ? (int)(BUF + 0x10000 + (i + 1) * 0x4000) : 0;
	G32(0x67fb3c) = n ? (int)(BUF + 0x10000) : 0;
}
static const DWORD g_gs_41edc0[] = { 0x41e9d0, 0, 0 };
static const DWORD g_gi_41edc0[] = { 0x67fb3c, 0x76d3e8, 0 };
static const DWORD g_gb_41edc0[] = { 0 };
T_PLAIN(FUN_0041edc0, 0x41edc0, freelist_setup(g_gs_41edc0, g_gi_41edc0, g_gb_41edc0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_41ed70[] = { 0x41e8b0, 0, 0 };
static const DWORD g_gi_41ed70[] = { 0x67fb3c, 0x76d3e8, 0x9dd1b0, 0x9dd6a4, 0x9dd6d4, 0x9dd838, 0 };
static const DWORD g_gb_41ed70[] = { 0 };
T_PLAIN(FUN_0041ed70, 0x41ed70, freelist_setup(g_gs_41ed70, g_gi_41ed70, g_gb_41ed70);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_453180[] = { 0x4532b0, 1, 0x454a20, 4, 0x454b40, 4, 0x454c50, 4, 0x454d60, 4, 0 };
static const DWORD g_gi_453180[] = { 0xa0b418, 0 };
static const DWORD g_gb_453180[] = { 0 };
T_PLAIN(arena_453180, 0x453180, gen_setup(g_gs_453180, g_gi_453180, g_gb_453180); /* 0x4532b0 gives a session record */ fill(BUF + 0x5000, 0x40); callee_ret(0x4532b0, irnd(0, 3) ? (DWORD)(BUF + 0x5000) : 0); G32(0xa0b418) = irnd(0, 4);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_41f970[] = { 0x404640, 0, 0x41fd40, 0, 0x420770, 0, 0x432ff0, 0, 0x440bb0, 0, 0x443950, 0, 0x447750, 0, 0x44b420, 0, 0 };
static const DWORD g_gi_41f970[] = { 0x4deb48, 0x67ef0c, 0x76d3e8, 0 };
static const DWORD g_gb_41f970[] = { 0 };
T_PLAIN(menu_enterState, 0x41f970, gen_setup(g_gs_41f970, g_gi_41f970, g_gb_41f970);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_435b00[] = { 0x401310, 1, 0x41e760, 1, 0x431590, 0, 0x432200, 2, 0x4338c0, 0, 0x433b00, 0, 0x433bb0, 0, 0x433c70, 0, 0x441250, 1, 0x451e60, 0, 0x48b420, 0, 0 };
static const DWORD g_gi_435b00[] = { 0x4ded18, 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0x4e1868, 0x67ef20, 0x68039c, 0x9dd198, 0x9dd1c8, 0x9dd1cc, 0x9dd6b0, 0x9dd834, 0x9dd838, 0x9dd850, 0 };
static const DWORD g_gb_435b00[] = { 0 };
T_PLAIN(room_435b00, 0x435b00, gen_setup(g_gs_435b00, g_gi_435b00, g_gb_435b00);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4346c0[] = { 0x41ee40, 1, 0x433980, 0, 0x433d30, 0, 0x4343b0, 1, 0x434400, 1, 0 };
static const DWORD g_gi_4346c0[] = { 0x68039c, 0x9dc428, 0x9dd348, 0x9dd3f8, 0x9dd6cc, 0 };
static const DWORD g_gb_4346c0[] = { 0x9dd1d8, 0x9dd1f6, 0x9dd202, 0x9dd20e, 0 };
T_PLAIN(room_4346c0, 0x4346c0, gen_setup(g_gs_4346c0, g_gi_4346c0, g_gb_4346c0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_436620[] = { 0x41e760, 1, 0x4323c0, 2, 0x435970, 0, 0x4359b0, 0, 0x4359f0, 0, 0 };
static const DWORD g_gi_436620[] = { 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0x76d40c, 0x90d1c4, 0x9dce48, 0x9dd1b4, 0x9dd1d0, 0x9dd300, 0x9dd350, 0x9dd3b0, 0x9dd6ac, 0x9dd6b8, 0xa0b350, 0xa0b35c, 0 };
static const DWORD g_gb_436620[] = { 0 };
T_PLAIN(room_436620, 0x436620, gen_setup(g_gs_436620, g_gi_436620, g_gb_436620);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_40fd30[] = { 0x40e490, 2, 0x40f0f0, 1, 0x40f200, 0, 0x40f320, 0, 0x40f830, 1, 0x40f870, 1, 0x40f950, 0, 0x40f9e0, 0, 0x41e760, 1, 0 };
static const DWORD g_gi_40fd30[] = { 0x4dbe48, 0x4dc244, 0x4dc77c, 0x4dc798, 0x4dceac, 0x4ded68, 0x4ded6c, 0x4ded88, 0 };
static const DWORD g_gb_40fd30[] = { 0 };
T_PLAIN(armc_40fd30, 0x40fd30, gen_setup(g_gs_40fd30, g_gi_40fd30, g_gb_40fd30);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_40ff40[] = { 0x40e4d0, 2, 0x40f0f0, 1, 0x40f200, 0, 0x40f220, 0, 0x40f320, 0, 0x40f590, 0, 0x40f5d0, 0, 0x40f670, 0, 0x40f6b0, 0, 0x40f6f0, 0, 0x40f790, 0, 0x40f7e0, 0, 0x41e760, 1, 0 };
static const DWORD g_gi_40ff40[] = { 0x4dc4b0, 0x4dc798, 0x4dceac, 0x4ded68, 0x4ded6c, 0x4ded88, 0 };
static const DWORD g_gb_40ff40[] = { 0 };
T_PLAIN(armc_colourScreenInput, 0x40ff40, gen_setup(g_gs_40ff40, g_gi_40ff40, g_gb_40ff40);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_436400[] = { 0x401590, 1, 0x403490, 0, 0x41e760, 1, 0x432380, 2, 0x4339e0, 0, 0x433a80, 0, 0x4351c0, 0, 0x4356f0, 1, 0 };
static const DWORD g_gi_436400[] = { 0x4df9e9, 0x4df9eb, 0x4df9ec, 0x4df9ed, 0x4ded54, 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0x67ef24, 0x6803a8, 0x90d1c4, 0x9dad8c, 0x9db0ac, 0x9dce48, 0x9dd380, 0x9dd388, 0x9dd568, 0x9dd6a8, 0 };
static const DWORD g_gb_436400[] = { 0 };
T_PLAIN(room_436400, 0x436400, gen_setup(g_gs_436400, g_gi_436400, g_gb_436400);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_437630[] = { 0x401600, 1, 0x41e760, 1, 0x4343b0, 1, 0x4351c0, 0, 0 };
static const DWORD g_gi_437630[] = { 0x4df9ee, 0x4df9ec, 0x4df9ed, 0x4ded54, 0x4df9f2, 0x4e0cdc, 0x4e1510, 0x4e1868, 0x68039c, 0x76d48c, 0x90d1c4, 0x9dce48, 0x9dd380, 0x9dd388, 0x9dd568, 0x9dd6a8, 0 };
static const DWORD g_gb_437630[] = { 0x4df9c8, 0x9dc92c, 0 };
T_PLAIN(menu_437630, 0x437630, gen_setup(g_gs_437630, g_gi_437630, g_gb_437630);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_441c00[] = { 0x401590, 1, 0x401600, 1, 0x41e760, 1, 0x440df0, 0, 0x441770, 0, 0x4417f0, 0, 0 };
static const DWORD g_gi_441c00[] = { 0x4b071c, 0x680bb4, 0x76d37c, 0x4dda44, 0x4e0cd4, 0x4e0cdc, 0x4e0ce0, 0x4e1510, 0x4e151c, 0x76d330, 0x76d48c, 0x9db0a0, 0x9dd928, 0x9dd92c, 0x9eeab4, 0x9eeac0, 0 };
static const DWORD g_gb_441c00[] = { 0 };
T_PLAIN(mainmenu_441c00, 0x441c00, gen_setup(g_gs_441c00, g_gi_441c00, g_gb_441c00);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_422480[] = { 0x41e760, 1, 0x41e7a0, 1, 0x4206b0, 2, 0x42d730, 0, 0 };
static const DWORD g_gi_422480[] = { 0x4ddba0, 0x83a9c0, 0x4ddba4, 0x4ddba8, 0x4ddbac, 0x4ddbb0, 0x4ddbb4, 0x4ddbb8, 0x4ddcec, 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0x83a9c4, 0x83a9cc, 0x83a9d0, 0x90d1c4, 0x9da494, 0 };
static const DWORD g_gb_422480[] = { 0 };
T_PLAIN(setup_drawGraphicTab, 0x422480, gen_setup(g_gs_422480, g_gi_422480, g_gb_422480);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_43e7b0[] = { 0x428c30, 4, 0x433610, 0, 0x434020, 0, 0x4340e0, 0, 0x4341a0, 0, 0x434260, 0, 0x4388e0, 0, 0x43a420, 0, 0 };
static const DWORD g_gi_43e7b0[] = { 0x9dd1f6, 0x9dd202, 0x9dd6d8, 0x4e1868, 0x68039c, 0x90d1c4, 0x9dc428, 0x9dce48, 0x9dd1fa, 0x9dd1fe, 0x9dd206, 0x9dd20a, 0x9dd304, 0x9dd354, 0x9dd368, 0x9dd36c, 0x9dd370, 0x9dd374, 0x9dd378, 0x9dd37c, 0x9dd69c, 0x9dd6d4, 0x9dd6dc, 0x9dd6e0, 0x9dd834, 0 };
static const DWORD g_gb_43e7b0[] = { 0x9dc92c, 0x9dd20e, 0 };
T_PLAIN(room_43e7b0, 0x43e7b0, gen_setup(g_gs_43e7b0, g_gi_43e7b0, g_gb_43e7b0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4221d0[] = { 0x41e760, 1, 0x420670, 2, 0x42d730, 0, 0x457150, 1, 0x457310, 0, 0 };
static const DWORD g_gi_4221d0[] = { 0x4dda44, 0x4dd984, 0x4ddad0, 0x4ddb98, 0x4ddcec, 0x4dde90, 0x4dde98, 0x4dde9c, 0x4ddea0, 0x4ddea4, 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0x4ded94, 0x4e0c90, 0x4e0c94, 0x4e0c98, 0x4e0c9c, 0x90d1c4, 0 };
static const DWORD g_gb_4221d0[] = { 0 };
T_PLAIN(setup_drawSoundTab, 0x4221d0, gen_setup(g_gs_4221d0, g_gi_4221d0, g_gb_4221d0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_422e10[] = { 0x401600, 1, 0x41e760, 1, 0x420c10, 0, 0x421680, 1, 0x42d730, 0, 0 };
static const DWORD g_gi_422e10[] = { 0x4ddce8, 0x4ddcec, 0x4dddc8, 0x4de040, 0x4de1c0, 0x4e0cd4, 0x4e0cdc, 0x4e0ce0, 0x4e14f4, 0x4e1508, 0x4e1524, 0x4e1530, 0x76d330, 0x76d48c, 0x9da440, 0x9dae70, 0x9db0a0, 0 };
static const DWORD g_gb_422e10[] = { 0x4de0c0, 0x4def00, 0 };
T_PLAIN(setup_controlTabKeys, 0x422e10, gen_setup(g_gs_422e10, g_gi_422e10, g_gb_422e10);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_422830[] = { 0x41e760, 1, 0x4206f0, 2, 0x420c10, 0, 0x421680, 1, 0x4226b0, 0, 0x42d730, 0, 0 };
static const DWORD g_gi_422830[] = { 0x4dda44, 0x4ddce8, 0x4ddcec, 0x4dddc8, 0x4de040, 0x4de1c0, 0x4de1c4, 0x4de1cc, 0x4de73c, 0x4ded68, 0x4ded6c, 0x4ded70, 0x4ded7c, 0x4ded88, 0x4ded8c, 0x4ded94, 0x76d424, 0x76d490, 0x90d1c4, 0x9da490, 0 };
static const DWORD g_gb_422830[] = { 0x4de0c0, 0x4def00, 0 };
T_PLAIN(setup_drawControlTab, 0x422830, gen_setup(g_gs_422830, g_gi_422830, g_gb_422830);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_43df80[] = { 0x41ee40, 0, 0x432400, 0, 0x432be0, 0, 0x432db0, 0, 0x433b00, 0, 0x433bb0, 0, 0x433c70, 0, 0x434490, 0, 0 };
static const DWORD g_gi_43df80[] = { 0x9dd1f6, 0x4e1868, 0x67ef34, 0x67fb38, 0x68039c, 0x680bc0, 0x74de1c, 0x76d42c, 0x9da4a4, 0x9dc428, 0x9dced0, 0x9dd198, 0x9dd1c8, 0x9dd1cc, 0x9dd1fa, 0x9dd1fe, 0x9dd358, 0x9dd364, 0x9dd38c, 0x9dd6b0, 0x9dd830, 0x9dd834, 0x9dd838, 0x9dd850, 0xa0b378, 0 };
static const DWORD g_gb_43df80[] = { 0x9dc92c, 0x9dd1d8, 0 };
T_PLAIN(room_43df80, 0x43df80, gen_setup(g_gs_43df80, g_gi_43df80, g_gb_43df80);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_40ee20[] = { 0x40da40, 0, 0x40ddb0, 0, 0x40de80, 0, 0x40dfa0, 0, 0x40e060, 0, 0x40e1c0, 0, 0x40e300, 0, 0x40e510, 0, 0x40e6c0, 0, 0x40ed20, 0, 0x41e760, 1, 0x4463a0, 0, 0x457150, 1, 0 };
static const DWORD g_gi_40ee20[] = { 0x4df02c, 0x9db098, 0x4dbc00, 0x4dbc04, 0x4dbc58, 0x4dbc5c, 0x4dbc60, 0x4dbc64, 0x4dbc68, 0x4dbc6c, 0x4dbe48, 0x4dc1d0, 0x4dc1d4, 0x4dc1d8, 0x4dc1dc, 0x4dc1e0, 0x4dc24c, 0x4dc4b0, 0x4dc4b4, 0x4dc54c, 0x4dc788, 0x4dc790, 0x4dc798, 0x4dc868, 0x4dc86c, 0x4dcc58, 0x4dcc90, 0x4dcc94, 0x4dcc98, 0x4dcc9c, 0x4dce38, 0x4dceac, 0x4dcf10, 0x4dcf34, 0x4dcfd8, 0x4dd078, 0x4df024, 0x4df028, 0x4df870, 0x4df874, 0x4df878, 0x67ef0c, 0x67ef20, 0x680378, 0x68037c, 0x680380, 0x76d388, 0x76d38c, 0x76d390, 0x76d3e8, 0x76d3f8, 0x76d3fc, 0x76d400, 0x9db090, 0x9db094, 0x9dd5d8, 0x9f181c, 0 };
static const DWORD g_gb_40ee20[] = { 0 };
T_PLAIN(menu_enterMenus, 0x40ee20, gen_setup(g_gs_40ee20, g_gi_40ee20, g_gb_40ee20);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4372f0[] = { 0x401590, 1, 0x401600, 1, 0x41e760, 1, 0x434d00, 0, 0x434da0, 0, 0x452fe0, 0, 0 };
static const DWORD g_gi_4372f0[] = { 0x4dda44, 0x4db8b4, 0x4dba80, 0x4dbb10, 0x4dbb78, 0x4ded18, 0x4df818, 0x4e0cdc, 0x4e14f8, 0x4e151c, 0x4e1524, 0x67ef30, 0x680bb0, 0x680bb8, 0x76d330, 0x76d41c, 0x76d48c, 0x9da498, 0x9dae70, 0x9db0a0, 0x9dce48, 0x9dd3fc, 0x9dd4bc, 0x9dd56c, 0x9dd6a0, 0x9dd6b4, 0xa0b34c, 0xa0b358, 0xa0b364, 0xa0d7a0, 0 };
static const DWORD g_gb_4372f0[] = { 0 };
T_PLAIN(menu_4372f0, 0x4372f0, gen_setup(g_gs_4372f0, g_gi_4372f0, g_gb_4372f0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_435fc0[] = { 0x41e760, 0, 0x432300, 2, 0x434d00, 0, 0x434da0, 0, 0 };
static const DWORD g_gi_435fc0[] = { 0x4dda44, 0x4dba80, 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0x4ded94, 0x4df818, 0x67ef30, 0x680bb0, 0x680bb8, 0x76d41c, 0x90d1c4, 0x9da498, 0x9dcd40, 0x9dce48, 0x9dd34c, 0x9dd3fc, 0x9dd4bc, 0x9dd56c, 0x9dd6a0, 0x9dd6b4, 0xa0b34c, 0xa0b358, 0xa0b364, 0xa0d7a0, 0 };
static const DWORD g_gb_435fc0[] = { 0 };
T_PLAIN(room_435fc0, 0x435fc0, gen_setup(g_gs_435fc0, g_gi_435fc0, g_gb_435fc0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_436990[] = { 0x401590, 1, 0x401600, 1, 0x41e760, 1, 0x432200, 2, 0x4338c0, 0, 0x433b00, 0, 0x433bb0, 0, 0x441250, 1, 0x451e60, 0, 0x48b420, 0, 0 };
static const DWORD g_gi_436990[] = { 0x4ded68, 0x4ded6c, 0x4e0cdc, 0x4e14f4, 0x4e150c, 0x4e1868, 0x67ef20, 0x67ef24, 0x67ef34, 0x67fb38, 0x680390, 0x68039c, 0x680bc0, 0x74de1c, 0x76d42c, 0x76d48c, 0x9da4a4, 0x9dae70, 0x9db0ac, 0x9dc428, 0x9dd198, 0x9dd1c8, 0x9dd1cc, 0x9dd358, 0x9dd35c, 0x9dd364, 0x9dd6b0, 0x9dd834, 0x9dd838, 0xa0b378, 0 };
static const DWORD g_gb_436990[] = { 0 };
T_PLAIN(menu_436990, 0x436990, gen_setup(g_gs_436990, g_gi_436990, g_gb_436990);, 0, g_a[0], g_a[1], g_a[2], g_a[3])

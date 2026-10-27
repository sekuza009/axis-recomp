/* batch 172 */
/* generated tests (tools/gentests.py): every callee stubbed (the key tests in key mode for the codes 0..3, the
   others answering 0 or 1), the function's integer globals small values (key bindings among them), its buffer
   globals random strings, its four argument slots pointers to random strings */
static void gen_setup(const DWORD *gs, const DWORD *gi, const DWORD *gb)
{
	for (const DWORD *p = gi; *p; p++) G32(*p) = irnd(0, 3) ? irnd(0, 3) : irnd(-2, 40);
	for (const DWORD *p = gb; *p; p++) fill_str((char *)*p, 30, 32, 126);
	for (int i = 0; i < 4; i++) { fill_str(BUF + 0x100 * i, 30, 32, 126); g_a[i] = (int)(BUF + 0x100 * i); }
	callee_stubs(gs, (DWORD)irnd(0, 1));
	callee_key(0x401600, irnd(-1, 3)); callee_key(0x401590, irnd(-1, 3));
}
static const DWORD g_gs_404f90[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_404f90[] = { 0x4dbacc, 0x4dbb00, 0x4dbb04, 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0 };
static const DWORD g_gb_404f90[] = { 0x9dc92c, 0 };
T_PLAIN(arena_editTextField_404f90, 0x404f90, gen_setup(g_gs_404f90, g_gi_404f90, g_gb_404f90);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_433a80[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_433a80[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd1b8, 0x9dd1bc, 0x9dd6a8, 0 };
static const DWORD g_gb_433a80[] = { 0x9dc92c, 0 };
T_PLAIN(room_433a80, 0x433a80, gen_setup(g_gs_433a80, g_gi_433a80, g_gb_433a80);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_456e50[] = { 0x467d70, 1, 0x467db0, 2, 0 };
static const DWORD g_gi_456e50[] = { 0xa0e66c, 0xa0e80c, 0 };
static const DWORD g_gb_456e50[] = { 0 };
T_PLAIN(sound_playVolume, 0x456e50, gen_setup(g_gs_456e50, g_gi_456e50, g_gb_456e50); /* (sound index, volume) */ fill((void *)0xa0e02c, 0x40); g_a[0] = irnd(0, 15); g_a[1] = irnd(-10, 120);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_431600[] = { 0x401310, 1, 0x431590, 0, 0x4315c0, 0, 0 };
static const DWORD g_gi_431600[] = { 0x4ded18, 0x68039c, 0x9da434, 0x9dbf10, 0x9dcd30, 0 };
static const DWORD g_gb_431600[] = { 0x9dc92c, 0 };
T_PLAIN(room_431600, 0x431600, gen_setup(g_gs_431600, g_gi_431600, g_gb_431600);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_431950[] = { 0x401600, 1, 0 };
static const DWORD g_gi_431950[] = { 0x4dda44, 0x4df900, 0x5b1da8, 0x6803a0, 0x9dae70, 0 };
static const DWORD g_gb_431950[] = { 0 };
T_PLAIN(menu_431950, 0x431950, gen_setup(g_gs_431950, g_gi_431950, g_gb_431950);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_403640[] = { 0x41e760, 0, 0 };
static const DWORD g_gi_403640[] = { 0x4d7408, 0x4d7410, 0x4d7418, 0x4d94fc, 0x4db508, 0x67ef00, 0 };
static const DWORD g_gb_403640[] = { 0x4d7358, 0 };
T_PLAIN(room_403640, 0x403640, gen_setup(g_gs_403640, g_gi_403640, g_gb_403640);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4512c0[] = { 0x450bf0, 5, 0x451350, 2, 0 };
static const DWORD g_gi_4512c0[] = { 0xa0b424, 0 };
static const DWORD g_gb_4512c0[] = { 0x9fd944, 0 };
T_PLAIN(match_4512c0, 0x4512c0, gen_setup(g_gs_4512c0, g_gi_4512c0, g_gb_4512c0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_405230[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_405230[] = { 0x4db714, 0x4db8c8, 0x4db8cc, 0x4dbbd4, 0x4dbbd8, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0 };
static const DWORD g_gb_405230[] = { 0x9dc92c, 0 };
T_PLAIN(lobby_editTextField_405230, 0x405230, gen_setup(g_gs_405230, g_gi_405230, g_gb_405230);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4318b0[] = { 0x401600, 1, 0 };
static const DWORD g_gi_4318b0[] = { 0x4df01c, 0x4e0458, 0x5b1da8, 0x6803a0, 0x9dae70, 0 };
static const DWORD g_gb_4318b0[] = { 0 };
T_PLAIN(menu_4318b0, 0x4318b0, gen_setup(g_gs_4318b0, g_gi_4318b0, g_gb_4318b0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_452fe0[] = { 0x451270, 3, 0x454130, 0, 0x4549a0, 0, 0x454ac0, 0, 0x454bd0, 0, 0x454ce0, 0, 0 };
static const DWORD g_gi_452fe0[] = { 0x9f941c, 0xa0b384, 0xa0b388, 0xa0b390, 0xa0b418, 0xa0baf8, 0 };
static const DWORD g_gb_452fe0[] = { 0x9f9418, 0 };
T_PLAIN(arena_452fe0, 0x452fe0, gen_setup(g_gs_452fe0, g_gi_452fe0, g_gb_452fe0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_404cd0[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_404cd0[] = { 0x4dbb68, 0x4dbb6c, 0x4dbbd0, 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0 };
static const DWORD g_gb_404cd0[] = { 0x4db560, 0x9dc92c, 0 };
T_PLAIN(arena_editTextField_404cd0, 0x404cd0, gen_setup(g_gs_404cd0, g_gi_404cd0, g_gb_404cd0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_404d70[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_404d70[] = { 0x4dbab0, 0x4dbb00, 0x4dbb04, 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0 };
static const DWORD g_gb_404d70[] = { 0x4db528, 0x9dc92c, 0 };
T_PLAIN(arena_editTextField_404d70, 0x404d70, gen_setup(g_gs_404d70, g_gi_404d70, g_gb_404d70);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4339e0[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_4339e0[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd1b8, 0x9dd1bc, 0x9dd380, 0 };
static const DWORD g_gb_4339e0[] = { 0x4df9c8, 0x9dc92c, 0 };
T_PLAIN(room_4339e0, 0x4339e0, gen_setup(g_gs_4339e0, g_gi_4339e0, g_gb_4339e0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_42bd40[] = { 0x467b90, 1, 0 };
static const DWORD g_gi_42bd40[] = { 0x4dd4d4, 0x4dd4d8, 0x4dd4dc, 0x4dd4e0, 0x4dd4e4, 0x4dd4e8, 0x4dd4ec, 0x4dd4f0, 0x4dd4f4, 0x4dd4f8, 0 };
static const DWORD g_gb_42bd40[] = { 0 };
T_PLAIN(sound_loadMenuSounds, 0x42bd40, gen_setup(g_gs_42bd40, g_gi_42bd40, g_gb_42bd40);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_437240[] = { 0x401600, 1, 0x41e760, 1, 0x41ee40, 1, 0x434b90, 0, 0 };
static const DWORD g_gi_437240[] = { 0x4e0cdc, 0x4e1510, 0x68039c, 0x76d48c, 0x9dce48, 0x9dd6d4, 0 };
static const DWORD g_gb_437240[] = { 0 };
T_PLAIN(menu_437240, 0x437240, gen_setup(g_gs_437240, g_gi_437240, g_gb_437240);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_403590[] = { 0x401590, 1, 0 };
static const DWORD g_gi_403590[] = { 0x67ef24, 0x6803a8, 0x9dad8c, 0x9db0ac, 0 };
static const DWORD g_gb_403590[] = { 0 };
T_PLAIN(room_403590, 0x403590, gen_setup(g_gs_403590, g_gi_403590, g_gb_403590); /* (setting index: 8 bytes from 0x4d7358) */ g_a[0] = irnd(0, 30);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_433b00[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_433b00[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd358, 0x9dd35c, 0x9dd38c, 0x9dd830, 0 };
static const DWORD g_gb_433b00[] = { 0x9dc92c, 0x9dd1d8, 0 };
T_PLAIN(room_433b00, 0x433b00, gen_setup(g_gs_433b00, g_gi_433b00, g_gb_433b00);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_404ed0[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_404ed0[] = { 0x4db54d, 0x4db518, 0x4dbb00, 0x4dbb04, 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0 };
static const DWORD g_gb_404ed0[] = { 0x9dc92c, 0 };
T_PLAIN(arena_editNumberField_404ed0, 0x404ed0, gen_setup(g_gs_404ed0, g_gi_404ed0, g_gb_404ed0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_422c60[] = { 0x401600, 1, 0x41e760, 1, 0x42d730, 0, 0x457150, 1, 0x457310, 0, 0 };
static const DWORD g_gi_422c60[] = { 0x4dd984, 0x4ddcec, 0x4dde98, 0x4dde9c, 0x4ddea0, 0x4ddea4, 0x4e0c90, 0x4e0c94, 0x4e0c98, 0x4e0c9c, 0x4e0cd4, 0x4e0cdc, 0x76d48c, 0 };
static const DWORD g_gb_422c60[] = { 0 };
T_PLAIN(setup_soundTabKeys, 0x422c60, gen_setup(g_gs_422c60, g_gi_422c60, g_gb_422c60);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_404e10[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_404e10[] = { 0x4db54c, 0x4db850, 0x4dbb00, 0x4dbb04, 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0 };
static const DWORD g_gb_404e10[] = { 0x9dc92c, 0 };
T_PLAIN(arena_editNumberField_404e10, 0x404e10, gen_setup(g_gs_404e10, g_gi_404e10, g_gb_404e10);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_434260[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_434260[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd304, 0x9dd368, 0x9dd36c, 0x9dd378, 0x9dd37c, 0x9dd69c, 0 };
static const DWORD g_gb_434260[] = { 0x9dc92c, 0x9dd20e, 0 };
T_PLAIN(room_434260, 0x434260, gen_setup(g_gs_434260, g_gi_434260, g_gb_434260);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_457080[] = { 0x467b90, 1, 0x467d60, 1, 0x467d70, 1, 0x467db0, 2, 0 };
static const DWORD g_gi_457080[] = { 0xa0e66c, 0xa0e80c, 0 };
static const DWORD g_gb_457080[] = { 0 };
T_PLAIN(sound_playFile, 0x457080, gen_setup(g_gs_457080, g_gi_457080, g_gb_457080); /* (file, volume) */ g_a[1] = irnd(-10, 120);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_434020[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_434020[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd304, 0x9dd368, 0x9dd36c, 0x9dd378, 0x9dd37c, 0x9dd69c, 0 };
static const DWORD g_gb_434020[] = { 0x9dc92c, 0x9dd6d8, 0 };
T_PLAIN(room_434020, 0x434020, gen_setup(g_gs_434020, g_gi_434020, g_gb_434020);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4340e0[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_4340e0[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd304, 0x9dd368, 0x9dd36c, 0x9dd378, 0x9dd37c, 0x9dd69c, 0 };
static const DWORD g_gb_4340e0[] = { 0x9dc92c, 0x9dd1f6, 0 };
T_PLAIN(room_4340e0, 0x4340e0, gen_setup(g_gs_4340e0, g_gi_4340e0, g_gb_4340e0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_4341a0[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_4341a0[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dd304, 0x9dd368, 0x9dd36c, 0x9dd378, 0x9dd37c, 0x9dd69c, 0 };
static const DWORD g_gb_4341a0[] = { 0x9dc92c, 0x9dd202, 0 };
T_PLAIN(room_4341a0, 0x4341a0, gen_setup(g_gs_4341a0, g_gi_4341a0, g_gb_4341a0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_433bb0[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_gi_433bb0[] = { 0x4e1868, 0x68039c, 0x9da3d8, 0x9da3dc, 0x9da434, 0x9dbf10, 0x9dced0, 0x9dd358, 0x9dd35c, 0x9dd38c, 0x9dd830, 0 };
static const DWORD g_gb_433bb0[] = { 0x9dc92c, 0x9dd1f6, 0 };
T_PLAIN(room_433bb0, 0x433bb0, gen_setup(g_gs_433bb0, g_gi_433bb0, g_gb_433bb0);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_437810[] = { 0x401600, 1, 0x41e760, 1, 0 };
static const DWORD g_gi_437810[] = { 0x4e0cdc, 0x4e1524, 0x76d40c, 0x76d48c, 0x9dce48, 0x9dd1b4, 0x9dd1d0, 0x9dd300, 0x9dd3b0, 0x9dd6ac, 0x9dd6b8, 0 };
static const DWORD g_gb_437810[] = { 0 };
T_PLAIN(menu_437810, 0x437810, gen_setup(g_gs_437810, g_gi_437810, g_gb_437810);, 0, g_a[0], g_a[1], g_a[2], g_a[3])

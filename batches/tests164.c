/* batch 163 */
/* screen dispatchers: every callee stubbed (callee_stubs: the test compares which is reached with what arguments);
   the state each dispatches on, in and out of range; the dialog flag */
static const DWORD g_stubSetupDraw[] = { 0x422480, 0, 0x4221d0, 0, 0x422830, 0, 0x4220c0, 0, 0 };
static const DWORD g_stubSetupKeys[] = { 0x422d20, 0, 0x422c60, 0, 0x422e10, 0, 0x422b70, 0, 0 };
static const DWORD g_stubLobby[] = { 0x407750, 0, 0x407840, 0, 0x407970, 0, 0x4079c0, 0, 0x4080c0, 0, 0x403870, 0,
	0x408110, 0, 0x407e40, 0, 0 };
static const DWORD g_stubRoomMouse[] = { 0x436940, 0, 0x436990, 0, 0x436e10, 0, 0x4370e0, 0, 0x437140, 0, 0x437240, 0,
	0x4372f0, 0, 0x403870, 0, 0x437630, 0, 0x437810, 0, 0 };
static const DWORD g_stubRoomKeys[] = { 0x435ab0, 0, 0x435b00, 0, 0x435c20, 0, 0x435ce0, 0, 0x435d30, 0, 0x435e70, 0,
	0x435f40, 0, 0x435fc0, 0, 0x4036c0, 0, 0x436400, 0, 0x436620, 0, 0 };
static const DWORD g_stubProfile[] = { 0x428c30, 4, 0x44b600, 0, 0x44bd20, 0, 0x44d720, 0, 0 };
static const DWORD g_stubRoomDraw[] = { 0x4388e0, 0, 0x428c30, 4, 0x43bfe0, 0, 0x4038e0, 0, 0x4355b0, 0, 0 };
static const DWORD g_stubCreateDraw[] = { 0x4091b0, 0, 0x428c30, 4, 0x40b750, 0, 0x4038e0, 0, 0x405b80, 0, 0 };
static void disp_state(void)
{
	g_menuDialogOpen = !irnd(0, 3);
	static const int tabs[] = { -1, 0, 1, 2, 3, 0x29a, 0x29b };
	G32(0x4ddac8) = tabs[irnd(0, 6)];
	G32(0x4db51c) = irnd(-1, 6); G32(0x907b2c) = irnd(0, 1); G32(0x4db508) = irnd(0, 2) ? 0 : irnd(1, 2);
	G32(0x4db55c) = irnd(0, 1);
	G32(0x9dd834) = irnd(0, 4) ? irnd(0, 0x63) : irnd(0, 1) ? 0x63 : irnd(-3, 0x70);
	G32(0x9dd850) = irnd(0, 2); G32(0x9dd7d8) = irnd(0, 2) ? 0 : 1; G32(0x4db8b4) = irnd(0, 1);
	G32(0x9f900c) = irnd(0, 1); GF(0x9f8f18) = (float)irnd(0, 400) / 100.0f;
	for (int i = 0; i < 4; i++) { G32(0x9f8e48 + 4 * i) = irnd(-50, 700); G32(0x9dd1b8 + 4 * i) = irnd(-50, 700); G32(0x4dbb00 + 4 * i) = irnd(-50, 700); }
	G32(0x9f8ea0) = irnd(-50, 700); G32(0x9f8ea4) = irnd(-50, 700); G32(0x9f8d70) = irnd(0, 1); G32(0x9f8d68) = irnd(0, 1);
	G32(0x9dce48) = irnd(-1, 3); G32(0x4dbb3c) = irnd(-1, 3); G32(0x4dba88) = irnd(0, 1);
	fill((void *)0x5b1b50, 8); fill((void *)0x4ded40, 8);
}
T_PLAIN(setup_drawTab, 0x422b30, disp_state(); callee_stubs(g_stubSetupDraw, 0);, 0, 0, 0, 0, 0)
T_PLAIN(setup_processTabKeys, 0x4230a0, disp_state(); callee_stubs(g_stubSetupKeys, 0);, 0, 0, 0, 0, 0)
T_PLAIN(lobby_processKeys, 0x4081f0, disp_state(); callee_stubs(g_stubLobby, 0);, 0, 0, 0, 0, 0)
T_PLAIN(menu_4378e0, 0x4378e0, disp_state(); callee_stubs(g_stubRoomMouse, 0);, 0, 0, 0, 0, 0)
T_PLAIN(room_processKeys, 0x436800, disp_state(); callee_stubs(g_stubRoomKeys, 0);, 0, 0, 0, 0, 0)
T_PLAIN(profile_44f410, 0x44f410, disp_state(); callee_stubs(g_stubProfile, 0);, 0, 0, 0, 0, 0)
T_PLAIN(room_43ed20, 0x43ed20, disp_state(); callee_stubs(g_stubRoomDraw, 0);, 0, 0, 0, 0, 0)
T_PLAIN(lobbyCreate_draw, 0x40d390, disp_state(); callee_stubs(g_stubCreateDraw, 0);, 0, 0, 0, 0, 0)

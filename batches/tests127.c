/* batch 126 */
/* missionbg_setup's tunnel, every texture slot these screens bind bindable (0x4df900..0x4df910, 0x4df03c..
   0x4df04c), the room's and the arena's depths */
static void tunnels_setup(void)
{
	missionbg_setup();
	for (DWORD a = 0x4df900; a <= 0x4df910; a += 4) G32(a) = G32(0x4e0cd0);
	for (DWORD a = 0x4df03c; a <= 0x4df04c; a += 4) G32(a) = G32(0x4e0cd0);
	GF(0x9dd698) = (float)irnd(-20000, 0) / 10.0f; GF(0x4dba68) = (float)irnd(-20000, 0) / 10.0f;
}
T_PLAIN(armc_411110, 0x411110, tunnels_setup();, 0, 0, 0, 0, 0)
T_PLAIN(skirmish_4445a0, 0x4445a0, tunnels_setup();, 0, 0, 0, 0, 0)
T_PLAIN(armc_411ab0, 0x411ab0, tunnels_setup();, 0, 0, 0, 0, 0)
T_PLAIN(room_4388e0, 0x4388e0, tunnels_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_4091b0, 0x4091b0, tunnels_setup();, 0, 0, 0, 0, 0)

/* batch 168 */
/* the mission settings screen: missionscreen_setup's state (missions, preview, textures, texts, records), the
   unlocked count, the settings buttons with the cursor often on one */
static void missionsettings_setup(void)
{
	missionscreen_setup();
	G32(0x9f181c) = irnd(0, 16);
	rect_table(0x9f6338, 0x9f6378);
	if (irnd(0, 1)) { point_in_table(0x9f6338, 0x9f6378); G32(0x4ded68) = g_a[0]; G32(0x4ded6c) = g_a[1]; }
}
T_PLAIN(missionsel_448ac0, 0x448ac0, missionsettings_setup();, 0, 0, 0, 0, 0)
T_PLAIN(missionsel_44aa20, 0x44aa20, missionsettings_setup();, 0, 0, 0, 0, 0)

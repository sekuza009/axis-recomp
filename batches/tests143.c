/* batch 142 */
/* the pilot-select dispatcher: profcol_setup's colour data, then pilotselect_setup (which keeps the pilot 0..8),
   the refresh flag, a message open now and then */
static void pilotselect2_setup(void)
{
	profcol_setup();
	pilotselect_setup();
	G32(0x9f8d68) = irnd(0, 1); G32(0x90d1c4) = irnd(0, 3) ? 0 : 1;
}
T_PLAIN(profile_44f810, 0x44f810, pilotselect2_setup();, 0, 0, 0, 0, 0)
/* the ranking dispatcher: netstate_setup's packet buffers (0xa0b324 among them), the room tunnel, the ranking table
   (its setup rebuilds the texture set: the tunnel's slots from the new one), the room list room_435770 reads, a
   request pending or not for columns 0..3, waiting, an answer in, room modes and sub-states, a message open */
static void rankpage_setup(void)
{
	netstate_setup();
	tunnels_setup();
	ranking_setup();
	G32(0x4e0cd0) = G32(0x9db0a4); for (DWORD a = 0x4df900; a <= 0x4df910; a += 4) G32(a) = G32(0x9db0a4);
	roomlist_setup();
	G32(0x9dd350) = irnd(0, 1); G32(0x9dd1d0) = irnd(0, 3); G32(0x76d40c) = irnd(0, 1);
	G32(0x9dce48) = irnd(0, 3); G32(0x9dd834) = irnd(0, 4) ? irnd(0, 10) : 99;
	G32(0x90d1c4) = irnd(0, 3) ? 0 : 1; GF(0x4ad498) = (float)irnd(1, 100);
	GF(0x4dba80) = irnd(0, 3) ? (float)irnd(0, 10000) / 10.0f : (float)irnd(-10, 10) / 10.0f;
}
T_PLAIN(room_43ede0, 0x43ede0, rankpage_setup();, 0, 0, 0, 0, 0)

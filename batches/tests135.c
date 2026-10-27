/* batch 134 */
/* the pilot-select dialog: pilotpanel_setup's pilots, labels and textures (every texture this dialog binds from
   the same set), the chosen pilot 0..8, the dialog window, the highlight pulse and reveal timers anywhere in their
   ranges, short button texts, the cursor sometimes on a button */
static void pilotselect_setup(void)
{
	pilotpanel_setup();
	int id = G32(0x9db0a4);
	G32(0x4deb50) = id; G32(0x4deb4c) = id; G32(0x9dad90) = id;
	G32(0x9f8d30) = irnd(0, 8);
	G32(0x9f8c54) = irnd(-30, 80); G32(0x9f8c50) = irnd(-30, 60);
	G32(0x9f6830) = G32(0x9f8c54) + irnd(400, 600); G32(0x9f682c) = G32(0x9f8c50) + irnd(300, 420);
	fill_str((char *)0x75e7a4, 12, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x7517a4 + k * 0x80, 8, 32, 126);
	GF(0x9f8f08) = (float)irnd(0, 400) / 10.0f; GF(0x9f8c48) = irnd(0, 1) ? 1.0f : -1.0f;
	G32(0x9f6828) = irnd(0, 9); GF(0x9f8ee4) = (float)irnd(0, 15) / 10.0f;
	fill((void *)0x9f8d58, 16);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9f8c54) + irnd(0x40, 0x200); G32(0x4ded6c) = G32(0x9f682c) - irnd(0x10, 0x30); }
}
T_PLAIN(profile_44e640, 0x44e640, pilotselect_setup();, 0, 0, 0, 0, 0)

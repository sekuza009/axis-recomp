/* batch 151 */
/* the controls dialog as controls_setup sets it (its crosshair lookup indexed or not), the setup tunnel's values
   with its textures from the dialog's set (setuptunnel_setup would rebuild the set and lose the index: its values
   are set here instead), the tab, a message open now and then */
static void controlsdlg_setup(void)
{
	controls_setup();
	int id = G32(0x9dae1c);
	G32(0x4e0cd0) = id; G32(0x5b197c) = id; G32(0x5b1978) = id; G32(0x5b1980) = id; G32(0x5b1984) = id;
	G32(0x4ddcec) = irnd(0, 3);
	GF(0x4de038) = (float)irnd(0, 100) / 100.0f; GF(0x4ddd90) = (float)irnd(-1000, 0) / 10.0f;
	GF(0x9db978) = (float)irnd(0, 1000) / 10.0f; GF(0x4df010) = irnd(0, 1) ? 1.0f : -1.0f;
	GF(0x4e14fc) = (float)irnd(0, 1990) / 10.0f; GF(0x4deda8) = (float)irnd(0, 50) / 10.0f; GF(0x4b071c) = (float)irnd(1, 30) / 10.0f;
	G32(0x4ddac8) = irnd(0, 3) ? irnd(0, 0x300) : 0x29a; G32(0x90d1c4) = irnd(0, 3) ? 0 : 1;
}
T_PLAIN(setup_4278d0, 0x4278d0, controlsdlg_setup();, 0, 0, 0, 0, 0)

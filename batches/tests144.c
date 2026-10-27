/* batch 143 */
/* the controls dialog: the crosshair either unchanged (menutex_setup's set, a bindable 0x4e0c8c) or changed (its
   path indexed by texpath_index, sometimes left out: fatal; a choice outside 0..7 keeps the path already in
   0x4ddb58), every texture of the final set; tabs 0..3, bindings in 0..511 or unbound, the switches, the slider
   0..100, an arrow flash running now and then, the edited row, short texts */
static void controls_setup(void)
{
	textpass_setup();
	int c = irnd(0, 9) ? irnd(0, 7) : irnd(8, 10);
	char path[64];
	sprintf(path, "texture/crosshair/crosshair%d", c < 8 ? c : 0);
	strcpy((char *)0x4ddb58, path);
	G32(0x4de1cc) = c;
	if (irnd(0, 1)) { G32(0x4b04f8) = c; menutex_setup(); }
	else { G32(0x4b04f8) = c + 1; texpath_index(path); }
	menutex_fonts(0);
	int id = G32(0x9dae1c);
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id; G32(0x4e0c8c) = id;
	G32(0x4dde80) = irnd(-30, 80); G32(0x4dde84) = irnd(-30, 60);
	G32(0x4dde88) = G32(0x4dde80) + irnd(400, 580); G32(0x4dde8c) = G32(0x4dde84) + irnd(320, 420);
	fill((void *)0x4de048, 16); fill((void *)0x4ddae0, 16);
	for (DWORD s = 0x754324; s <= 0x756224; s += 0x80) fill_str((char *)s, 6, 32, 126);
	fill_str((char *)0x751924, 4, 32, 126); fill_str((char *)0x7519a4, 4, 32, 126);
	G32(0x4ddce8) = irnd(0, 4) ? irnd(0, 3) : irnd(-1, 5);
	G32(0x4df8e4) = irnd(0, 511);
	for (DWORD a = 0x4de0c0; a <= 0x4de1bc; a += 4) G32(a) = irnd(0, 3) ? irnd(0, 511) : G32(0x4df8e4);
	G32(0x4de1c0) = irnd(0, 2); G32(0x4de1c4) = irnd(0, 2); G32(0x4de1c8) = irnd(0, 100);
	G32(0x4dde90) = irnd(-1, 2); GF(0x4ddb98) = irnd(0, 2) ? 0.0f : (float)irnd(-10, 300) / 10.0f;
	G32(0x4dddc8) = irnd(0, 3) ? 0 : 1; G32(0x4de040) = irnd(-1, 10);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x4dde80) + irnd(0x24, 0x200); G32(0x4ded6c) = G32(0x4dde84) + 0x58 + irnd(0, 10) * 0x18 + irnd(0, 20); }
}
T_PLAIN(setup_crosshairScreen, 0x425cd0, controls_setup();, 0, 0, 0, 0, 0)

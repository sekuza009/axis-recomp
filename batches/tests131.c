/* batch 130 */
/* the sound dialog: dlgwin_setup's window at 0x4ddad0, the volume 0..100, an arrow flash sometimes running (any
   arrow, the timer about to run out now and then), the switches on / off, short texts, the cursor sometimes on a
   switch */
static void sound_setup(void)
{
	dlgwin_setup(0x4ddad0);
	fill((void *)0x4de048, 16); fill((void *)0x4ddae0, 16);
	G32(0x4dde98) = irnd(0, 100); G32(0x4dde9c) = irnd(-1, 2); G32(0x4ddea0) = irnd(0, 1); G32(0x4ddea4) = irnd(0, 1);
	G32(0x4dde90) = irnd(-1, 4); GF(0x4ddb98) = irnd(0, 2) ? (float)irnd(-10, 300) / 10.0f : 0.0f;
	fill_str((char *)0x7533a4, 12, 32, 126); fill_str((char *)0x753424, 12, 32, 126);
	for (int k = 0; k < 4; k++) fill_str((char *)0x7534a4 + k * 0x80, 10, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x753624 + k * 0x80, 6, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x753724 + k * 0x80, 10, 32, 126);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x4ddad0) + irnd(0x120, 0x180); G32(0x4ded6c) = G32(0x4ddad4) + 0x9c + irnd(0, 2) * 0x28 + irnd(0, 12); }
}
T_PLAIN(setup_424810, 0x424810, sound_setup();, 0, 0, 0, 0, 0)

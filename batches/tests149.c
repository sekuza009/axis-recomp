/* batch 148 */
/* the intro set-up: loading_setup's screen (its picture bindable, progress from 0..28 kept low: six more frames),
   the tables' areas random, the wait's frame counter as intro_41e730's test sets it */
static void introsetup_setup(void)
{
	loading_setup();
	G32(0x4dda34) = irnd(0, 10);
	fill((void *)0x67ef38, 0xc00); fill((void *)0x9dada0, 0x70); fill((void *)0x5b1cfc, 0xd0);
	g_frames = irnd(0, 3) ? irnd(-2, 400) / 3.0 : irnd(0, 100000);
}
T_PLAIN(intro_430bf0, 0x430bf0, introsetup_setup();, 0, 0, 0, 0, 0)

/* batch 146 */
/* network mode or not, player levels 0..16, progress values 0..20 and now and then above 0x7f, the current
   choices and list areas random */
static void partlists_setup(void)
{
	G32(0x4dc24c) = irnd(0, 3) ? irnd(0, 2) : 3;
	G32(0x9dd5d8) = irnd(0, 16);   /* level 1..16 -> tables 0..15 (higher levels read past the unlock tables) */
	G32(0x9f181c) = irnd(0, 9) ? irnd(0, 20) : irnd(0x7f, 0x90);
	fill((void *)0x4dc244, 4); fill((void *)0x4dc778, 4); fill((void *)0x4dc79c, 0x18); fill((void *)0x4dcca4, 0x18);
	fill((void *)0x4dc3e8, 0x200); fill((void *)0x4dcd6c, 0x100); fill((void *)0x4dc964, 0x100); fill((void *)0x4dc89c, 0xc0);
	fill((void *)0x4dbd7c, 0x100);
}
T_PLAIN(armc_buildPartLists, 0x40da40, partlists_setup();, 0, 0, 0, 0, 0)

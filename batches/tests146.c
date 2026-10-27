/* batch 145 */
/* armc_45ddc0's player and actor (ownslot_setup: the actor is the player's own index), the game's lobby slot that
   player (sometimes none), local or not, and an item record for the slot asked (-1..7) and for the actor's stored
   slot, as itempart_setup builds them */
static void reequip_part(char *ac, int slot)
{
	char *pl = BUF + 0x1561b68 + S32(ac, 0x10c) * 0x47fd2; int var = irnd(0, 3), it = irnd(0, 5) ? irnd(0, 3) : -1;
	if (slot < 0 || slot > 5) return;
	S32(pl, 0x320 + slot * 4) = it;
	if (it >= 0) {
		char *rec = BUF + 0x14d1ab4 + it * 0x2e18;
		memset(rec, 0, 0x2e18);
		part_counts(rec, var, 0x40, 0x12dc, 15);
		part_counts(rec, var, 0x16fc, 0x2998, 15);
		S32(rec, 0x2dc0) = irnd(-1, 9);
	}
}
static void reequip_setup(void)
{
	ownslot_setup();
	char *ac = BUF + 0x1cd93a8 + g_spf * 0x8888;
	int idx = irnd(0, 9) ? g_spf : -1;
	memcpy(SCENE + 0x234240d, &idx, 4);
	S32(SCENE, 0x2221fa0) = irnd(0, 1) ? g_spf : g_spf + 1;
	S32(ac, 0x140) = irnd(0, 5); S32(ac, 0x144) = irnd(0, 5);
	fill(ac + 0x4cc, 4); fill(ac + 0x587c, 0x30); fill(ac + 0x701c, 0x30); fill(ac + 0x40dc, 0x30);
	g_a[0] = irnd(0, 4) ? irnd(0, 7) : -1;
	reequip_part(ac, g_a[0] < 0 ? S32(ac, 0x140) : g_a[0]);
	reequip_part(ac, S32(ac, 0x144));
}
ST(armc_461540, reequip_setup();, (TC(void, 0x461540, char *, int)(SCENE, g_a[0]), 0), (armc_461540(SCENE, (DWORD)g_a[0]), 0))

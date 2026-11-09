/* armc_state.c: the ARM CENTER's working copy of the mech: loading the saved mech into it, the VIEW ALL colour slot,
   the list cursors on the chosen parts, and the menu camera kept while the screen is open. Values are copied as
   their 32 bits (floats included). */
#include "../game.h"

#define g_armcColourBits (AP(u32, OBJ(g_armcColours)))           /* the six colour slots, six values each (see g_armcColours) */
#define g_allPartsSlot ((u32 *)(OBJ(g_armcColours) + 0x78))            /* colour slot 5 (VIEW ALL): its six values */
#define g_savedParts (AP(const u32, ADDR(g_savedMechHead)))         /* the saved mech: head, chest, arm, leg, booster */
#define g_workParts (AP(u32, OBJ(g_armcParts)))                /* the working copy, same order */

static void copy(u32 *to, const u32 *from, int n)
{
	for (int i = 0; i < n; i++)
		to[i] = from[i];
}

/* 0x40f590: colour slot 5 (VIEW ALL, g_armcColours + 0x78) seeded from slot 1 (the chest): its six values copied, the
   fifth from slot 1's second (sic). Called when slot 5 is chosen (keys A / up past 0, click on button 10). Leaves
   slot 1's fourth value in eax (armc_colourPageClicks returns it) */
void (armc_seedAllColourSlot)(void)
{
	const u32 *slot1 = g_armcColourBits + 6;
	g_allPartsSlot[0] = slot1[0];
	g_allPartsSlot[2] = slot1[2];
	g_allPartsSlot[1] = slot1[1];
	g_allPartsSlot[3] = slot1[3];
	g_allPartsSlot[4] = slot1[1];
	g_allPartsSlot[5] = slot1[5];
}

/* 0x41ced0: colour slot 5's (VIEW ALL) six values copied into slots 0 .. 4, so every part takes the all-parts colour */
void (armc_spreadAllColourSlot)(void)
{
	for (int s = 0; s < 5; s++)
		copy(g_armcColourBits + s * 6, g_allPartsSlot, 6);
}

/* 0x40ed20: each part list's cursor onto the chosen part (its first place in the unlocked list; 0 when not
   listed) */
void (armc_syncPartCursors)(void)
{
	static const struct { u32 cursor, count, list, chosen; } kinds[] = {
		{ ADDR(g_headCursor), ADDR(g_headCount), OBJ(g_headList), OBJ(g_armcParts) }, { ADDR(g_chestCursor), ADDR(g_chestCount), OBJ(g_chestList), ADDR_AT(g_armcParts, 1) },
		{ ADDR(g_armCursor), ADDR(g_armCount), OBJ(g_armList), ADDR_AT(g_armcParts, 2) }, { ADDR(g_legCursor), ADDR(g_legCount), OBJ(g_legList), ADDR_AT(g_armcParts, 3) },
		{ ADDR(g_boosterCursor), ADDR(g_boosterCount), OBJ(g_boosterList), ADDR_AT(g_armcParts, 4) } };   /* head, chest, arm, leg, booster */
	for (int k = 0; k < 5; k++) {
		int *cursor = AP(int, kinds[k].cursor);
		const int *list = AP(const int, kinds[k].list);
		*cursor = 0;
		for (int i = 0; i < GAME_VAR(int, kinds[k].count); i++)
			if (GAME_VAR(int, kinds[k].chosen) == list[i]) {
				*cursor = i;
				break;
			}
	}
}

/* 0x40e670: the menu camera's eye and look-at points (g_menuEyeX.., g_menuCameraLook..) set to camera point 0
   (g_camPoint0X.., g_camAim0X..: the ARM CENTER's own, set when it was entered), the preview off (g_armcPreview 0) */
void (armc_snapCameraToPoint0)(void)
{
	copy(AP(u32, ADDR(g_menuEyeX)), AP(const u32, ADDR(g_camPoint0X)), 3);
	copy(AP(u32, ADDR(g_menuCameraLook)), AP(const u32, ADDR(g_camAim0X)), 3);
	g_armcPreview = 0;
}

/* 0x40e6c0: the saved mech (parts, the six items, the colours) into the working copy */
void (armc_loadSavedMech)(void)
{
	g_workParts[0] = g_savedParts[0];
	g_workParts[1] = g_savedParts[1];
	g_workParts[3] = g_savedParts[3];
	g_workParts[2] = g_savedParts[2];
	g_workParts[4] = g_savedParts[4];
	g_mechWeaponSlot1 = (*(u32 *)&g_savedMechWeaponSlot1);
	g_mechWeaponSlot0 = (*(u32 *)&g_savedMechWeaponSlot0);
	g_mechWeaponSlot2 = (*(u32 *)&g_savedMechWeaponSlot2);
	(*(u32 *)&g_itemSlot5) = (*(u32 *)&g_savedMechItemSlot5);
	g_mechWeaponSlot3 = (*(u32 *)&g_savedMechWeaponSlot3);
	(*(u32 *)&g_itemSlot4) = (*(u32 *)&g_savedMechItemSlot4);
	copy(g_armcColourBits, AP(const u32, OBJ(g_savedColourChoices)), 0x90 / 4);
}

/* 0x40f830: 1 if extra-list entry i (g_extraListTable) is a special item (actorItems 27 and up: EXPANSION MAGAZINE ..
   FORCEFIELD BOOSTER, MSG 711 + it) already in one of the two item slots (g_itemSlot4 / g_itemSlot5), so it can't be
   taken twice */
int (armc_extraItemEquipped)(int i)
{
	int item = (g_extraListTable)[i];
	return item >= 0x1b && (item == g_itemSlot4 || item == g_itemSlot5);
}

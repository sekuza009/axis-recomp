/* armc_state.c: the ARM CENTER's working copy of the mech: loading the saved mech into it, the colour undo buffer,
   the list cursors on the chosen parts, and the menu camera kept while the screen is open. Values are copied as
   their 32 bits (floats included). */
#include "../game.h"

#define g_armcColourBits ((u32 *)OBJ(g_armcColours))           /* the six colour slots, six values each (see g_armcColours) */
#define g_colourUndo ((u32 *)(OBJ(g_armcColours) + 0x78))               /* one slot's six values, for undo */
#define g_savedParts ((const u32 *)ADDR(g_savedMechParts))         /* the saved mech: head, chest, arm, leg, booster */
#define g_workParts ((u32 *)OBJ(g_armcParts))                /* the working copy, same order */

static void copy(u32 *to, const u32 *from, int n)
{
	for (int i = 0; i < n; i++)
		to[i] = from[i];
}

/* 0x40f590: colour slot 1 into the undo buffer; the fifth value is taken from the second (sic) */
void (armc_backupColours)(void)
{
	const u32 *slot1 = g_armcColourBits + 6;
	g_colourUndo[0] = slot1[0];
	g_colourUndo[2] = slot1[2];
	g_colourUndo[1] = slot1[1];
	g_colourUndo[3] = slot1[3];
	g_colourUndo[4] = slot1[1];
	g_colourUndo[5] = slot1[5];
}

/* 0x41ced0: the undo buffer into colour slots 0 .. 4 */
void (armc_restoreColourUndo)(void)
{
	for (int s = 0; s < 5; s++)
		copy(g_armcColourBits + s * 6, g_colourUndo, 6);
}

/* 0x40ed20: each part list's cursor onto the chosen part (its first place in the unlocked list; 0 when not
   listed) */
void (armc_syncPartCursors)(void)
{
	static const struct { u32 cursor, count, list, chosen; } kinds[] = {
		{ ADDR(g_headCursor), ADDR(g_headCount), OBJ(g_headList), OBJ(g_armcParts) }, { ADDR(g_chestCursor), ADDR(g_chestCount), OBJ(g_chestList), (OBJ(g_armcParts) + 0x4) },
		{ ADDR(g_armCursor), ADDR(g_armCount), OBJ(g_armList), (OBJ(g_armcParts) + 0x8) }, { (OBJ(g_boosterStats) + 0x24), ADDR(g_legCount), OBJ(g_legList), (OBJ(g_armcParts) + 0xc) },
		{ ADDR(g_boosterCursor), ADDR(g_armcLastPart), OBJ(g_boosterList), (OBJ(g_armcParts) + 0x10) } };   /* head, chest, arm, leg, booster */
	for (int k = 0; k < 5; k++) {
		int *cursor = (int *)kinds[k].cursor;
		const int *list = (const int *)kinds[k].list;
		*cursor = 0;
		for (int i = 0; i < GAME_VAR(int, kinds[k].count); i++)
			if (GAME_VAR(int, kinds[k].chosen) == list[i]) {
				*cursor = i;
				break;
			}
	}
}

/* 0x40e670: the menu camera put back as it was before the screen (angles and position), the preview off */
void (armc_restoreMenuCamera)(void)
{
	copy((u32 *)ADDR(g_menuCameraPos), (const u32 *)ADDR(g_camPoint0X), 3);
	copy((u32 *)ADDR(g_menuCameraLook), (const u32 *)ADDR(g_camAim0X), 3);
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
	g_mechItem3 = (*(u32 *)&g_savedMechItem3);
	g_mechItem2 = (*(u32 *)&g_savedMechItem2);
	g_mechItem4 = (*(u32 *)&g_savedMechItem4);
	(*(u32 *)&g_itemSlot5) = (*(u32 *)&g_savedMechItem1);
	g_mechItem5 = (*(u32 *)&g_savedMechItem5);
	(*(u32 *)&g_itemSlot4) = (*(u32 *)&g_savedMechWeapons);
	copy(g_armcColourBits, (const u32 *)OBJ(g_savedColourChoices), 0x90 / 4);
}

/* 0x40f830: 1 if item list entry i is a colour part (27 and up) already in one of the two item slots */
int (armc_colourPartEquipped)(int i)
{
	int item = (g_extraListTable)[i];
	return item >= 0x1b && (item == g_itemSlot4 || item == g_itemSlot5);
}

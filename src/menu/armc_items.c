/* armc_items.c: the ARM CENTER's item slots: four weapon slots (0 .. 3) and two other items (4, 5), each picked
   from its list with a cursor; the chosen items go to the mech (mech_setAll) and the preview. */
#include "../game.h"

#define g_weaponList ((const int *)0x4dc79c)          /* the weapons on offer */
#define g_weaponCount GAME_VAR(int, 0x4dc244)
#define g_extraList ((const int *)0x4dcca4)           /* the other items on offer */
#define g_extraCount GAME_VAR(int, 0x4dc778)
#define g_armcParts ((const int *)0x4dc760)           /* the mech's head, chest, arm, leg, booster */

/* the item in slot (0 .. 3 at 0x4dcb20, 4 .. 5 at 0x4dcb18) */
static int *slot_item(int slot)
{
	return slot < 4 ? (int *)0x4dcb20 + slot : (int *)0x4dcb18 + (slot - 4);
}

/* the whole mech handed to the scene, with name */
static void set_mech(const char *name)
{
	mech_setAll(g_scene, name, g_armcValue, 0, g_armcParts[0], g_armcParts[1], g_armcParts[2], g_armcParts[3],
	            g_armcParts[4], *slot_item(0), *slot_item(1), *slot_item(2), *slot_item(3), *slot_item(4),
	            *slot_item(5));
}

/* the cursor onto item in list (the last place it is found; unchanged if it is not there) */
static void find(const int *list, int count, int item)
{
	for (int i = 0; i < count; i++)
		if (list[i] == item)
			g_armcCursor = i;
}

/* 0x40f870: pick slot (nothing if it is already being picked): the cursor onto its item, the weapon selected on
   the preview (slots 0 .. 3), then the cursor's item shown (armc_showCursorItem) */
void (armc_pickSlot)(int slot)
{
	if (g_armcSlot == slot)
		return;
	g_armcSlot = slot;
	if (slot >= 0 && slot <= 5) {
		if (slot < 4)
			find(g_weaponList, g_weaponCount, *slot_item(slot));
		else
			find(g_extraList, g_extraCount, *slot_item(slot));
	} else if (slot > 3) {
		find(g_extraList, g_extraCount, -1);
	} else {
		find(g_weaponList, g_weaponCount, -1);
	}
	if (slot <= 3)
		actor_selectWeapon(STAGE(g_scene), 0, slot);
	armc_showCursorItem();
}

/* 0x40f950: the cursor wrapped round its list, and the item under it shown on the preview (with a new snapshot of
   the mech) */
void (armc_showCursorItem)(void)
{
	int item;
	if (g_armcSlot <= 3) {
		if (g_armcCursor >= g_weaponCount)
			g_armcCursor = 0;
		else if (g_armcCursor < 0)
			g_armcCursor = g_weaponCount - 1;
		item = g_weaponList[g_armcCursor];
	} else {
		if (g_armcCursor >= g_extraCount)
			g_armcCursor = 0;
		else if (g_armcCursor < 0)
			g_armcCursor = g_extraCount - 1;
		item = g_extraList[g_armcCursor];
	}
	armc_viewedPartRecord(item);
	armc_snapshot(6);
	armc_giveShownActorWeapon(g_scene, g_armcSlot);
	armc_readMechStats();
}

/* 0x40f9e0: take the item under the cursor into the slot being picked; the mech updated and the slot picked again
   from scratch */
void (armc_takeCursorItem)(void)
{
	int item = -1;
	int slot = g_armcSlot;
	if (slot >= 0 && slot <= 5) {
		item = slot < 4 ? g_weaponList[g_armcCursor] : g_extraList[g_armcCursor];
		*slot_item(slot) = item;
	}
	g_armcChanged = 1;
	armc_weaponSlotRecord(g_armcSlot, item);
	armc_snapshot(g_armcSlot);
	slot = g_armcSlot;
	set_mech((const char *)0x4dedd8);
	g_armcSlot = -1;
	armc_pickSlot(slot);
}

/* 0x40e5d0: entering the screen: the CD checked, the mech set up from the screen's state, the player's actor made
   again, the preview on */
void (armc_enterScreen)(void)
{
	app_requireCd(g_scene, 0, 2);
	set_mech((const char *)0x4dedb0);
	stage_remakePlayerActor(STAGE(g_scene));
	g_armcPreview = 1;
	g_armcSessionMade = 1;
	g_colourChanged = 1;
}

/* 0x40f220: the weapons page: every slot's item handed to the parts list, the cursor on slot 0's weapon (its first
   place in the list, else 0), all seven snapshots of the mech taken, then slot 0 picked and the camera moved */
void (armc_drawPartScreen)(void)
{
	g_armcMode = 2;
	g_armcSlot = 0;
	g_unusedArmcWord1 = 0;
	for (int slot = 0; slot < 6; slot++)
		armc_weaponSlotRecord(slot, *slot_item(slot));
	g_armcCursor = 0;
	for (int i = 0; i < g_weaponCount; i++)
		if (g_weaponList[i] == *slot_item(0)) {
			g_armcCursor = i;
			break;
		}
	armc_viewedPartRecord(g_weaponList[g_armcCursor]);
	for (int k = 0; k < 7; k++)
		armc_snapshot(k);
	g_armcChanged = 0;
	g_unusedArmcWord2 = 1;
	g_armcSlot = -1;
	armc_pickSlot(0);
	armc_easeCamera();
}

/* 0x40fd30: the part screen clicked (armcParts_hitTest's buttons 0 .. 14): 0 / 2 the main and colour pages (the slot
   closed first; unless already there), 3 / 4 the screen's two sides (armc_40f0f0), 6 .. 11 slot 0 .. 5 picked,
   12 / 13 the cursor back / on (weapons wrap past the first entry; for the other items a step the slot cannot take
   (armc_colourPartEquipped) is skipped) with the item shown and taken, 14 the rotation toggle. Each with its sound. Returns
   what the original leaves in eax */
u32 (armc_partScreenClicks)(void)
{
	if (!g_mouseClick)
		return 0;
	u32 button = GAME_FN(armcParts_hitTest, 0x40e490, u32, int, int)(g_mouseX, g_mouseY);   /* armcParts_hitTest */
	u32 r;
	int step;
	switch (button) {
	case 0: case 2:
		if (g_armcMode == (button == 0 ? 1 : 3))
			return button;
		sound_playMenu(2);
		armc_pickSlot(0);
		return GAME_CDECL(button == 0 ? FN_ADDR(armc_showPartsPage, 0x40f200) : FN_ADDR(armc_showColourPage, 0x40f320), u32, void)();
	case 3: case 4:
		sound_playMenu(0);
		return GAME_FN(armc_exit, 0x40f0f0, u32, int)(button == 3);
	case 6: case 7: case 8: case 9: case 10: case 11:
		armc_pickSlot(button - 6);   /* armc_pickSlot: the slot picked */
		return GAME_FN(sound_playMenu, 0x41e760, u32, int)(2);
	case 12: case 13:
		step = button == 12 ? -1 : 1;
		g_armcCursor += step;
		if (g_armcSlot == 0) {
			if (step < 0 && g_armcCursor == 0)
				g_armcCursor = g_weaponCount - 1;
			else if (step > 0 && g_armcCursor >= g_weaponCount)
				g_armcCursor = 1;
		} else if (g_armcSlot > 3 && armc_colourPartEquipped(g_armcCursor) == 1)   /* armc_colourPartEquipped */
			g_armcCursor += step;
		sound_playMenu(8);
		armc_showCursorItem();          /* armc_showCursorItem: the item shown */
		return GAME_FN(armc_takeCursorItem, 0x40f9e0, u32, void)();    /* armc_takeCursorItem: and taken */
	case 14:
		sound_playMenu(2);
		r = 1 - (*(u32 *)&g_armcSpin);
		(*(u32 *)&g_armcSpin) = r;
		return r;
	}
	return button;
}

/* 0x41dcf0: the bonuses of the mech's two extra items (slots 5 and 4, 0x4dcb1c / 0x4dcb18): items 27 .. 35 each
   raise a flag of their own (0x4dcb10 ...); the flags set, their values (as floats): 27 0x4dbc70 0.3; 28, 29, 30
   100 into 0x4dc248, 0x4dcc6c, 0x4dc548; 31 0x4dcb34 50; 32 0x4dbc78 100, 0x4dc898 0.5, 0x4dceb4 3, 0x4dc88c 1;
   33 0x4dcca0 0.5, 0x4dc894 -0.1; 34 0x4dceb0 0.2; 35 0x4dcc68 0.3, 0x4dbc74 1. Every flag and value is cleared
   first. The caller ignores the eax it leaves */
void (armc_extraItemBonuses)(void)
{
	static const u32 flag[9] = { 0x4dcb10, 0x4dcea8, 0x4dcc5c, 0x4dbc54, 0x4dbe44, 0x4dc794, 0x4dbd78, 0x4dc774, 0x4dcf30 };
	static const u32 value[14] = { 0x4dbc70, 0x4dc248, 0x4dcc6c, 0x4dc548, 0x4dcb34, 0x4dbc78, 0x4dc898, 0x4dceb4, 0x4dc88c,
	                               0x4dcca0, 0x4dc894, 0x4dceb0, 0x4dcc68, 0x4dbc74 };
	static const struct { u8 item; u32 at, bits; } bonus[14] = {
		{ 0, 0x4dbc70, 0x3e99999a }, { 1, 0x4dc248, 0x42c80000 }, { 2, 0x4dcc6c, 0x42c80000 }, { 3, 0x4dc548, 0x42c80000 },
		{ 4, 0x4dcb34, 0x42480000 }, { 5, 0x4dbc78, 0x42c80000 }, { 5, 0x4dc898, 0x3f000000 }, { 5, 0x4dceb4, 0x40400000 },
		{ 5, 0x4dc88c, 0x3f800000 }, { 6, 0x4dcca0, 0x3f000000 }, { 6, 0x4dc894, 0xbdcccccd }, { 7, 0x4dceb0, 0x3e4ccccd },
		{ 8, 0x4dcc68, 0x3e99999a }, { 8, 0x4dbc74, 0x3f800000 } };
	for (int k = 0; k < 9; k++)
		GAME_VAR(int, flag[k]) = 0;
	for (int k = 0; k < 14; k++)
		GAME_VAR(u32, value[k]) = 0;
	static const u32 items[2] = { 0x4dcb1c, 0x4dcb18 };
	for (int k = 0; k < 2; k++) {
		u32 bonusItem = (u32)(GAME_VAR(int, items[k]) - 27);
		if (bonusItem <= 8)
			GAME_VAR(int, flag[bonusItem]) = 1;
	}
	for (int k = 0; k < 14; k++)
		if (GAME_VAR(int, flag[bonus[k].item]) == 1)
			GAME_VAR(u32, bonus[k].at) = bonus[k].bits;
}

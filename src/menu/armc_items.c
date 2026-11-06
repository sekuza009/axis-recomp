/* armc_items.c: the ARM CENTER's item slots: four weapon slots (0 .. 3) and two other items (4, 5), each picked
   from its list with a cursor; the chosen items go to the mech (mech_setAll) and the preview. */
#include "../game.h"

#define g_weaponList (g_weaponListTable)          /* the weapons on offer */
#define g_extraList (g_extraListTable)           /* the other items on offer */

/* the item in slot (0 .. 3 at g_mechWeaponSlot0, 4 .. 5 at g_itemSlot4) */
static int *slot_item(int slot)
{
	return slot < 4 ? (int *)ADDR(g_mechWeaponSlot0) + slot : (int *)ADDR(g_itemSlot4) + (slot - 4);
}

/* the whole mech handed to the scene, with name */
static void set_mech(const char *name)
{
	mech_setAll(g_scene, name, g_selectedCharacter, 0, g_armcParts[0], g_armcParts[1], g_armcParts[2], g_armcParts[3],
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
	set_mech(g_matchPlayerName);
	g_armcSlot = -1;
	armc_pickSlot(slot);
}

/* 0x40e5d0: entering the screen: the CD checked, the mech set up from the screen's state, the player's actor made
   again, the preview on */
void (armc_enterScreen)(void)
{
	scene_startSession(g_scene, 0, 2);
	set_mech(g_cfgPlayerName);
	stage_remakePlayerActor(STAGE(g_scene));
	g_armcPreview = 1;
	g_armcSessionMade = 1;
	g_colourChanged = 1;
}

/* 0x40f220: the weapons page: every slot's item handed to the parts list, the cursor on slot 0's weapon (its first
   place in the list, else 0), all seven snapshots of the mech taken, then slot 0 picked and the camera moved */
void (armc_openWeaponsPage)(void)
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

/* 0x40fd30: the weapons page clicked (armcWeaponsPage_hitTest's buttons 0 .. 14): 0 / 2 the parts and colour pages (the slot
   closed first; unless already there), 3 / 4 the screen's two exits (armc_exit), 6 .. 11 slot 0 .. 5 picked,
   12 / 13 the cursor back / on (weapons wrap past the first entry; for the other items a step the slot cannot take
   (armc_colourPartEquipped) is skipped) with the item shown and taken, 14 the rotation toggle. Each with its sound. Returns
   what the original leaves in eax */
u32 (armc_weaponsPageClicks)(void)
{
	if (!g_mouseClick)
		return 0;
	u32 button = armcWeaponsPage_hitTest(g_mouseX, g_mouseY);   /* armcWeaponsPage_hitTest */
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
		return armc_exit(button == 3);
	case 6: case 7: case 8: case 9: case 10: case 11:
		armc_pickSlot(button - 6);   /* armc_pickSlot: the slot picked */
		return sound_playMenu(2);
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
		return armc_takeCursorItem();    /* armc_takeCursorItem: and taken */
	case 14:
		sound_playMenu(2);
		r = 1 - (*(u32 *)&g_armcSpin);
		(*(u32 *)&g_armcSpin) = r;
		return r;
	}
	return button;
}

/* 0x41dcf0: the bonuses of the mech's two extra items (slots 5 and 4, g_itemSlot5 / g_itemSlot4): items 27 .. 35 each
   raise a flag of their own (g_hasItemCapacity ..); the flags set, their values (as floats): 27 g_itemBonusCapacityPerLevel 0.3; 28, 29, 30
   100 into g_itemBonusEpak, g_itemBonus30mm, g_itemBonus60mm; 31 g_itemBonusMissile 50; 32 g_itemBonusDetectionRange 100, g_itemBonusLockOn 0.5, g_itemBonusHacking 3, g_itemBonusTargetKeep 1;
   33 g_itemBonusActiveTime 0.5, g_itemBonusRechargeTime -0.1; 34 g_itemBonusWeightLimit 0.2; 35 g_itemBonusShield 0.3, g_itemBonusShieldUnread 1. Every flag and value is cleared
   first. The caller ignores the eax it leaves */
void (armc_extraItemBonuses)(void)
{
	static const u32 flag[9] = { ADDR(g_hasItemCapacity), ADDR(g_hasItemEpak), ADDR(g_hasItem30mm), ADDR(g_hasItem60mm), ADDR(g_hasItemMissile), ADDR(g_hasItemSensor), ADDR(g_hasItemBooster), ADDR(g_hasItemWeight), ADDR(g_hasItemShield) };
	static const u32 value[14] = { ADDR(g_itemBonusCapacityPerLevel), ADDR(g_itemBonusEpak), ADDR(g_itemBonus30mm), ADDR(g_itemBonus60mm), ADDR(g_itemBonusMissile), ADDR(g_itemBonusDetectionRange), ADDR(g_itemBonusLockOn), ADDR(g_itemBonusHacking), ADDR(g_itemBonusTargetKeep),
	                               ADDR(g_itemBonusActiveTime), ADDR(g_itemBonusRechargeTime), ADDR(g_itemBonusWeightLimit), ADDR(g_itemBonusShield), ADDR(g_itemBonusShieldUnread) };
	static const struct { u8 item; u32 at, bits; } bonus[14] = {
		{ 0, ADDR(g_itemBonusCapacityPerLevel), 0x3e99999a }, { 1, ADDR(g_itemBonusEpak), 0x42c80000 }, { 2, ADDR(g_itemBonus30mm), 0x42c80000 }, { 3, ADDR(g_itemBonus60mm), 0x42c80000 },
		{ 4, ADDR(g_itemBonusMissile), 0x42480000 }, { 5, ADDR(g_itemBonusDetectionRange), 0x42c80000 }, { 5, ADDR(g_itemBonusLockOn), 0x3f000000 }, { 5, ADDR(g_itemBonusHacking), 0x40400000 },
		{ 5, ADDR(g_itemBonusTargetKeep), 0x3f800000 }, { 6, ADDR(g_itemBonusActiveTime), 0x3f000000 }, { 6, ADDR(g_itemBonusRechargeTime), 0xbdcccccd }, { 7, ADDR(g_itemBonusWeightLimit), 0x3e4ccccd },
		{ 8, ADDR(g_itemBonusShield), 0x3e99999a }, { 8, ADDR(g_itemBonusShieldUnread), 0x3f800000 } };
	for (int k = 0; k < 9; k++)
		GAME_VAR(int, flag[k]) = 0;
	for (int k = 0; k < 14; k++)
		GAME_VAR(u32, value[k]) = 0;
	static const u32 items[2] = { ADDR(g_itemSlot5), ADDR(g_itemSlot4) };
	for (int k = 0; k < 2; k++) {
		u32 bonusItem = (u32)(GAME_VAR(int, items[k]) - 27);
		if (bonusItem <= 8)
			GAME_VAR(int, flag[bonusItem]) = 1;
	}
	for (int k = 0; k < 14; k++)
		if (GAME_VAR(int, flag[bonus[k].item]) == 1)
			GAME_VAR(u32, bonus[k].at) = bonus[k].bits;
}

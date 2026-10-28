/* armc_items.c: the ARM CENTER's item slots: four weapon slots (0 .. 3) and two other items (4, 5), each picked
   from its list with a cursor; the chosen items go to the mech (armc_461250) and the preview. */
#include "../game.h"

#define g_armcSlot GAME_VAR(int, 0x4dbe48)            /* the slot being picked (-1 none) */
#define g_armcCursor GAME_VAR(int, 0x4dc77c)          /* the cursor in that slot's list */
#define g_weaponList ((const int *)0x4dc79c)          /* the weapons on offer */
#define g_weaponCount GAME_VAR(int, 0x4dc244)
#define g_extraList ((const int *)0x4dcca4)           /* the other items on offer */
#define g_extraCount GAME_VAR(int, 0x4dc778)
#define g_armcParts ((const int *)0x4dc760)           /* the mech's head, chest, arm, leg, booster */
#define g_armcValue GAME_VAR(int, 0x9f1818)           /* (unclear) the mech's value (armc_461370) */
#define g_armcChanged GAME_VAR(int, 0x4dcc64)         /* (by use) the mech was changed */

/* the item in slot (0 .. 3 at 0x4dcb20, 4 .. 5 at 0x4dcb18) */
static int *slot_item(int slot)
{
	return slot < 4 ? (int *)0x4dcb20 + slot : (int *)0x4dcb18 + (slot - 4);
}

/* the whole mech handed to the scene, with name */
static void set_mech(const char *name)
{
	armc_461250(g_scene, name, g_armcValue, 0, g_armcParts[0], g_armcParts[1], g_armcParts[2], g_armcParts[3],
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
   the preview (slots 0 .. 3), then the cursor's item shown (armc_40f950) */
void (armc_40f870)(int slot)
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
	armc_40f950();
}

/* 0x40f950: the cursor wrapped round its list, and the item under it shown on the preview (with a new snapshot of
   the mech) */
void (armc_40f950)(void)
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
	armc_41cca0(item);
	armc_snapshot(6);
	armc_461540(g_scene, g_armcSlot);
	armc_41c510();
}

/* 0x40f9e0: take the item under the cursor into the slot being picked; the mech updated and the slot picked again
   from scratch */
void (armc_40f9e0)(void)
{
	int item = -1;
	int slot = g_armcSlot;
	if (slot >= 0 && slot <= 5) {
		item = slot < 4 ? g_weaponList[g_armcCursor] : g_extraList[g_armcCursor];
		*slot_item(slot) = item;
	}
	g_armcChanged = 1;
	armc_41ca50(g_armcSlot, item);
	armc_snapshot(g_armcSlot);
	slot = g_armcSlot;
	set_mech((const char *)0x4dedd8);
	g_armcSlot = -1;
	armc_40f870(slot);
}

/* 0x40e5d0: entering the screen: the CD checked, the mech set up from the screen's state, the player's actor made
   again, the preview on */
void (armc_40e5d0)(void)
{
	app_requireCd(g_scene, 0, 2);
	set_mech((const char *)0x4dedb0);
	armc_45ddc0(STAGE(g_scene));
	GAME_VAR(int, 0x4dbc68) = 1;
	GAME_VAR(int, 0x4dc54c) = 1;
	GAME_VAR(int, 0x4dd074) = 1;
}

/* 0x40f220: the weapons page: every slot's item handed to the parts list, the cursor on slot 0's weapon (its first
   place in the list, else 0), all seven snapshots of the mech taken, then slot 0 picked and the camera moved */
void (armc_drawPartScreen)(void)
{
	g_armcMode = 2;
	g_armcSlot = 0;
	GAME_VAR(int, 0x4dc864) = 0;
	for (int slot = 0; slot < 6; slot++)
		armc_41ca50(slot, *slot_item(slot));
	g_armcCursor = 0;
	for (int i = 0; i < g_weaponCount; i++)
		if (g_weaponList[i] == *slot_item(0)) {
			g_armcCursor = i;
			break;
		}
	armc_41cca0(g_weaponList[g_armcCursor]);
	for (int k = 0; k < 7; k++)
		armc_snapshot(k);
	g_armcChanged = 0;
	GAME_VAR(int, 0x4dcf14) = 1;
	g_armcSlot = -1;
	armc_40f870(0);
	armc_41b300();
}

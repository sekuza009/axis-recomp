/* armc_keys.c: the ARM CENTER's keys on its main (parts) page and its colour page. Five keys pick a part or colour
   slot directly; up / down step through the six with wrap-around. */
#include "../game.h"

#define g_armcZoom GAME_VAR(float, 0x4dcfd8)          /* the view's zoom, back to 1 when the part in view changes */
#define g_armcSpin GAME_VAR(int, 0x4dceac)            /* the preview spins */

/* the keys of slots 0 .. 4 */
static const u32 slot_keys[5] = { 0x4e14f0, 0x4e10e4, 0x4e1524, 0x4e14ec, 0x4e0cd8 };

/* 0x4101e0: the parts page: 0x4e1538 / 0x4e1504 to the weapons / third page, 0x4e151c toggles the spin; the part in
   view picked (slot keys, 0x4e0cd4 the weapons) or stepped (up / down); left / right change that part; OK keeps the
   mech, back or cancel leaves (the original leaves eax to callers that ignore it) */
void (armc_partsPageKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e1538))) {
		if (g_armcMode != 2) {
			sound_playMenu(2);
			armc_drawPartScreen();
		}
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1504))) {
		if (g_armcMode != 3) {
			sound_playMenu(2);
			set_4dc798_40f320();
		}
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e151c))) {
		sound_playMenu(2);
		g_armcSpin = 1 - g_armcSpin;
		return;
	}
	for (int k = 0; k < 5; k++)
		if (input_justPressed(GAME_VAR(int, slot_keys[k]))) {
			if (g_armcPartSlot != k) {
				sound_playMenu(2);
				g_armcPartSlot = k;
				g_armcZoom = 1.0f;
			}
			return;
		}
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4))) {
		sound_playMenu(2);
		g_armcPartSlot = 5;
		return;
	}
	if (input_justPressed(g_keyUp)) {
		sound_playMenu(2);
		if (--g_armcPartSlot < 0)
			g_armcPartSlot = 5;
		g_armcZoom = 1.0f;
		return;
	}
	if (input_justPressed(g_keyDown)) {
		sound_playMenu(2);
		if (++g_armcPartSlot > 5)
			g_armcPartSlot = 0;
		g_armcZoom = 1.0f;
		return;
	}
	if (input_justPressed(g_keyLeft)) {
		if (g_armcPartSlot != 5) {
			sound_playMenu(8);
			armc_stepPart(g_armcPartSlot, 1);
		}
		return;
	}
	if (input_justPressed(g_keyRight)) {
		if (g_armcPartSlot != 5) {
			sound_playMenu(8);
			armc_stepPart(g_armcPartSlot, 2);
		}
		return;
	}
	if (input_justPressed(g_keyOk)) {
		sound_playMenu(0);
		armc_exit(1);
		return;
	}
	if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		armc_exit(0);
	}
}

#define g_armcSlot GAME_VAR(int, 0x4dbe48)            /* the item slot being picked */
#define g_armcCursor GAME_VAR(int, 0x4dc77c)          /* the cursor in that slot's list */
#define g_weaponCount GAME_VAR(int, 0x4dc244)

/* 0x410500: the weapons page: cancel / back leave, OK keeps the mech; 0x4e1514 / 0x4e1504 to the parts / third page
   (slot 0 picked first), 0x4e151c toggles the spin; six keys pick an item slot; right / left move the cursor in its
   list (slot 0's weapons wrap between 1 and the last; slots 4 / 5 skip a colour part already in the other slot),
   up and then down step the slot (the original leaves eax to callers that ignore it) */
void (armc_weaponsPageKeys)(void)
{
	static const u32 item_keys[6] = { 0x4e0468, 0x4e046c, 0x4e0470, 0x4e0874, 0x4e0c78, 0x4e0c7c };
	if (input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		armc_exit(0);
		return;
	}
	if (input_justPressed(g_keyOk)) {
		sound_playMenu(0);
		armc_exit(1);
		return;
	}
	if (input_justPressed(g_keyBack)) {
		sound_playMenu(0);
		armc_exit(0);
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1514))) {
		if (g_armcMode != 1) {
			armc_pickSlot(0);
			sound_playMenu(2);
			set_4dc798_40f200();
		}
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1504))) {
		if (g_armcMode != 3) {
			armc_pickSlot(0);
			sound_playMenu(2);
			set_4dc798_40f320();
		}
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e151c))) {
		sound_playMenu(2);
		g_armcSpin = 1 - g_armcSpin;
		return;
	}
	for (int k = 0; k < 6; k++)
		if (input_justPressed(GAME_VAR(int, item_keys[k]))) {
			armc_pickSlot(k);
			return;
		}
	if (input_justPressed(g_keyRight)) {
		int cursor = ++g_armcCursor;
		if (g_armcSlot == 0) {
			if (cursor >= g_weaponCount)
				g_armcCursor = 1;
		} else if (g_armcSlot > 3 && armc_colourPartEquipped(cursor) == 1)
			g_armcCursor++;
		sound_playMenu(8);
		armc_showCursorItem();
		armc_takeCursorItem();
		return;
	}
	if (input_justPressed(g_keyLeft)) {
		int cursor = --g_armcCursor;
		if (g_armcSlot == 0) {
			if (cursor == 0)
				g_armcCursor = g_weaponCount - 1;
		} else if (g_armcSlot > 3 && armc_colourPartEquipped(cursor) == 1)
			g_armcCursor--;
		sound_playMenu(8);
		armc_showCursorItem();
		armc_takeCursorItem();
		return;
	}
	if (input_justPressed(g_keyUp)) {
		int slot = g_armcSlot - 1;
		if (slot < 0)
			slot = 5;
		sound_playMenu(2);
		armc_pickSlot(slot);
	}
	if (input_justPressed(g_keyDown)) {
		int slot = g_armcSlot + 1;
		if (slot > 5)
			slot = 0;
		sound_playMenu(2);
		armc_pickSlot(slot);
	}
}

/* 0x410810: the colour page: OK keeps the mech, back or cancel leaves; 0x4e1514 / 0x4e1538 to the parts / weapons
   page; the colour slot picked (slot keys, 0x4e0cd4 slot 5, kept for undo) or stepped (up / down; wrapping up to
   slot 5 keeps it for undo too); 0x4e151c toggles the spin (the original leaves eax to callers that ignore it) */
void (armc_colourPageKeys)(void)
{
	if (input_justPressed(g_keyOk)) {
		sound_playMenu(0);
		armc_exit(1);
		return;
	}
	if (input_justPressed(g_keyBack))
		goto leave;
	if (input_justPressed(GAME_VAR(int, 0x4e1514))) {
		sound_playMenu(2);
		set_4dc798_40f200();
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1538))) {
		if (g_armcMode != 2) {
			sound_playMenu(2);
			armc_drawPartScreen();
		}
		return;
	}
	for (int k = 0; k < 5; k++)
		if (input_justPressed(GAME_VAR(int, slot_keys[k]))) {
			if (g_armcColourSlot != k) {
				sound_playMenu(2);
				g_armcColourSlot = k;
			}
			return;
		}
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4))) {
		sound_playMenu(2);
		g_armcColourSlot = 5;
		armc_backupColours();
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e151c))) {
		sound_playMenu(2);
		g_armcSpin = 1 - g_armcSpin;
		return;
	}
	if (input_justPressed(g_keyUp)) {
		sound_playMenu(2);
		if (--g_armcColourSlot < 0) {
			g_armcColourSlot = 5;
			armc_backupColours();
		}
		return;
	}
	if (input_justPressed(g_keyDown)) {
		sound_playMenu(2);
		if (++g_armcColourSlot > 5)
			g_armcColourSlot = 0;
		return;
	}
	if (!input_justPressed(g_keyCancel2))
		return;
leave:
	sound_playMenu(0);
	armc_exit(0);
}

/* 0x410ab0: the arm screen's keys (in its modes other than 0 / 1, without a message box): the keys 0x6803a8 and
   0x9da4a0 held with 0x4e1508 pressed switch 0x4dd078; else the page's own keys (0x4dc798: 1 .. 3; page 4's are
   an empty function). The caller ignores the eax it leaves */
void (armc_processInput)(void)
{
	int mode = GAME_VAR(int, 0x4dc790);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x90d1c4))
		return;
	if (input_isDown(GAME_VAR(int, 0x6803a8)) && input_isDown(GAME_VAR(int, 0x9da4a0)) && input_justPressed(GAME_VAR(int, 0x4e1508))) {
		GAME_VAR(int, 0x4dd078) = 1 - GAME_VAR(int, 0x4dd078);
		return;
	}
	switch (GAME_VAR(int, 0x4dc798)) {
	case 1: armc_partsPageKeys(); break;
	case 2: armc_weaponsPageKeys(); break;
	case 3: armc_colourPageKeys(); break;
	case 4: nullsub_48b420(GAME_VAR(Scene *, 0x4dc798)); break;   /* (its ecx: the original jumps there with the page in ecx) */
	}
}

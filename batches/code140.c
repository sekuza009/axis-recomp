/* batch 139 (lifted/grp85.c): the armour build screen */
#include "lifted/grp85.c"
/* 0x419160 armc_419160(): the armour build screen: three buttons (0x7517a4; the hovered one, armc_40e490, bright),
   six part slots (texture 0x9db0a4, the selected one 0x4dbe48 bright), the snapshot when asked (0x4dcc64:
   armc_snapshot), each named slot's picture (texture 0x4dcc70 + k * 4) and label (0x756fa4) with its name
   (0x4dbe50, 0x80 apart; one character or none: 0x757da4); the part box: name 0x4dc150 and its type (0x7641a4,
   by 0x4dc79c / 0x4dcca4 of 0x4dc77c), the arrows (0x4dcc88); the weight button with "total / limit"; the stats
   panel: nothing chosen (0x4dc190 == -1: 0x757da4), a part type only (0x4dc194 == -1: 0x765fa4 and its kind), or
   the 16 stats (0x4dc190..0x4dc1cc) with labels 0x7574a4: counts, a pilot-scaled bonus " +%d" / " %d" (skill of
   pilot 0x9f1818 by kind 0x4dc194), "%.0f" / "%.1f" values with units (0x765624..0x7657a4), right-aligned */
LIFT_PLAIN(armc_419160, 419160)

/* batch 144 (lifted/grp90.c): the armour screen's stats panel, the largest function in the game */
#include "lifted/grp90.c"
/* 0x412650 armc_drawStatsPanel(): the armour screen with the stats of the part in slot 0x4dbc6c (0..5): the
   preview arrows, the slot buttons and their labels (as armc_41a280, part names when 0x4dbc68), three buttons, the
   weight button, the "detail" button 0x7568a4; then a panel of the part's stats (taller in Korean, 0x9dae74): one
   section per slot type, each line "<label> <value>" built with sprintf from the part's numbers (floats such as
   0x4dce84..0x4dcf0c and 0x4dc228..0x4dc248, counts such as 0x4dcab4..0x4dcacc), several scaled by the pilot's
   skills (0x9f9078..0x9f9088 of pilot 0x9f1818), with units (0x7655a4..0x765aa4), the type names 0x7623a4 by
   0x4dce80 and on / off by 0x4dceac; English and Korean layouts are separate switches on the slot */
LIFT_PLAIN(armc_drawStatsPanel, 412650)

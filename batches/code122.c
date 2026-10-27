/* batch 121 (lifted/grp67.c): the arena slot list and the map-select dialog */
#include "lifted/grp67.c"
/* 0x4038e0 arena_4038e0(): the arena's slot list over a dimmed screen: two column heads (0x75d924, 0x75d9a4), up
   to 10 rows from slot 0x4d7350 (count 0x67ef00; slots 22..24 skipped): the number, the map name (0x907b30, 0x20
   apart) and the kind (0x4db8d8, 5 apart, by the slot's +4), on red bars when the slot is taken (0x4d7358, 8
   apart); the row under the cursor highlighted; scroll arrows; two pairs of buttons (0x75db24, 0x75da24) */
LIFT_PLAIN(arena_4038e0, 4038e0)
/* 0x442e10 mainmenu_442e10(): the map-select dialog: frame, title 0x74e8a4, the list box with its scroll arrows,
   two checkboxes (0x4b2a7c / 0x9eeac0 ticked: 0x74e924 / 0x74e9a4), two button rows (0x74ea24, 0x74eb24), the
   hovered list row highlighted, the map list (mainmenu_442d10), the border */
LIFT_PLAIN(mainmenu_442e10, 442e10)

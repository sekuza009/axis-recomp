/* batch 168 (lifted/grp114.c): the mission settings screen */
#include "lifted/grp114.c"
/* 0x448ac0 missionsel_448ac0(): the mission settings screen (the mission select's sibling): the frame and panels,
   the chosen mission's name, preview and texts (the strings at 0x75bfa4 .. 0x75f6a4), its record (0x9db99c +
   0x5c * mission: allies and enemies with portraits, kind, values), the mission number with the arrows (greyed
   at 0 and at the unlocked count 0x9f181c), the buttons (missionsel_447710) lit under the cursor */
LIFT_PLAIN(missionsel_448ac0, 448ac0)
/* 0x44aa20 missionsel_44aa20: jump to missionsel_448ac0 */
LIFT_PLAIN(missionsel_44aa20, 44aa20)

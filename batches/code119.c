/* batch 118 (lifted/grp64.c): profile dialogs and the armour weight line */
#include "lifted/grp64.c"
/* 0x44e180 profile_44e180() / 0x44e3e0 profile_44e3e0(): two-button profile dialogs (window 0x9f8f1c.. /
   0x9f6834..; titles 0x751da4 / 0x751e24): frame, title, two textured buttons (texture 0x9db0a4) labelled 0x7517a4 /
   0x751824, the one under the cursor (profile_44b320 / profile_44b360) bright, the frame's border */
LIFT_PLAIN(profile_44e180, 44e180)
LIFT_PLAIN(profile_44e3e0, 44e3e0)
/* 0x44de00 profile_44de00(): the new-profile dialog: frame, title 0x751ca4, the name field (profile_4283e0), two
   buttons (the first dimmed while the name 0x9dc92c is empty), the border */
LIFT_PLAIN(profile_44de00, 44de00)
/* 0x41dab0 armc_41dab0(): the armour screen's weight line: the label 0x7573a4 right-aligned (8 or 14 units a
   character by language), the total of the ten part weights (stored at 0x4dc78c) " / " the limit 0x4dcb0c, the
   total red when over the limit, else green */
LIFT_PLAIN(armc_41dab0, 41dab0)

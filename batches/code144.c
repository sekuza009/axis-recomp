/* batch 143 (lifted/grp89.c): the controls / crosshair screen */
#include "lifted/grp89.c"
/* 0x425cd0 setup_crosshairScreen(): the controls dialog (window 0x4dde80..): frame, lines, column heads
   (0x754524..0x754624), four tab titles (0x754324, the current one 0x4ddce8 again brighter); the row under the
   cursor (setup_4206f0, rows 7..17 of the tab; 0x4de040) or the row being edited (0x4dddc8) highlighted; the tab's
   rows: tabs 0..2 list their labels (0x754a24 / 0x7551a4 / 0x755924) with two key names each (the bindings
   0x4de0c0..0x4de1bc index the 512 key names at 0x4b0750; the unbound value 0x4df8e4 shows nothing); tab 3: two
   on / off switches (0x4de1c0 / 0x4de1c4: 0x7519a4 / 0x751924), the sensitivity slider 0x4de1c8 with flashing
   arrows (0x4ddb98 / 0x4dde90, counting down by 0x4b071c), and the crosshair 0x4de1cc: a changed choice (cached
   0x4b04f8) looks up "texture/crosshair/crosshair<n>" (0..7; others keep the path in 0x4ddb58) into 0x4e0c8c,
   drawn in a box; three buttons (0x7546a4), the border */
LIFT_PLAIN(setup_crosshairScreen, 425cd0)

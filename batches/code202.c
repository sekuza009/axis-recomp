/* batch 201 (lifted/grp160.c): the profile screen's key handlers, one per page (split out of profile_processInput
   in functions.csv: menu_44cdd0 reaches them through its jump table) */
#include "lifted/grp160.c"
/* 0x44c600 profile_44c600(): page 1, the profile list: up / down held with key repeat (0x76d37c / 0x680bb4) move
   the cursor 0x9f8d30 over the 3 x 3 grid (sound 2), Enter picks (profile_44b600), the delete / copy keys
   (profile_44b670, profile_44b6e0) */
LIFT_PLAIN(profile_44c600, 44c600)
/* 0x44c850 profile_44c850(): page 2: Enter or Esc back to the list (profile_44b600) */
LIFT_PLAIN(profile_44c850, 44c850)
/* 0x44c8c0 profile_44c8c0(): page 3, the name edit: Esc cancels (profile_44ba60), Enter checks the name
   (profile_44b320) and takes it, up / down move between the fields (sound 2) */
LIFT_PLAIN(profile_44c8c0, 44c8c0)
/* 0x44ca90 profile_44ca90(): page 4, as page 3 for the second form (profile_44b360, profile_44bc00) */
LIFT_PLAIN(profile_44ca90, 44ca90)
/* 0x44cc60 profile_44cc60(): page 5, the 3 x 3 emblem grid: Esc (profile_44b990), the arrows wrap the cursor
   0x9f8d30 by rows and columns (sound 2) */
LIFT_PLAIN(profile_44cc60, 44cc60)
/* batch 201 (lifted/grp158.c, grp159.c): the menu's key dispatch */
#include "lifted/grp158.c"
/* 0x44cdd0 menu_44cdd0(): the profile screen's keys: none with a dialog (0x90d1c4); during the intro animation
   (0x9f6838, state 0x9f8e54 != 5) Enter / Esc skip it (state 5, the fade values set); else page 0x9f8f10 (1..6)
   picks its handler by an inline jump table (profile_44c600 .. profile_44cc60) */
LIFT_PLAIN(menu_44cdd0, 44cdd0)
#include "lifted/grp159.c"
/* 0x4319d0 menu_processKeys(): the menus' keys: none while 0x68039c; the input poll (0x4012c0); none while
   0x680370 or the fade 0x9da434 above its limit; a pending dialog (0x4df900) takes them (0x431950); else the
   screen 0x76d3e8 (200, 210, 300, 400, 500, 600, 700, 800, 900, 9999) picks its key handler by tail call */
LIFT_PLAIN(menu_processKeys, 4319d0)

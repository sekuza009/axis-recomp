/* batch 166 (lifted/grp112.c): the profile screen's input */
#include "lifted/grp112.c"
/* 0x44be00 profile_44be00(): the profile list page's mouse: a left click on the list (profile_44b3a0, 7 kinds:
   a profile, scroll, new / delete / load / back ...) or the bottom buttons (profile_44b260), sounds; opens the name
   edit (profile_44b600) or the delete / load confirmations (profile_44b670 / profile_44b6e0) */
LIFT_PLAIN(profile_44be00, 44be00)
/* 0x44c190 profile_44c190(): the name edit page: OK / cancel buttons (profile_44b2a0, profile_44b2e0) and Enter:
   the name checked (profile_4343b0, profile_44b7e0) and taken (profile_44b870) or a message (FUN_0041ee40); the
   keyboard re-initialised (input_initKeyboard) and the input buffer reset (match_431590) when leaving */
LIFT_PLAIN(profile_44c190, 44c190)
/* 0x44c560 profile_processInput(): the profile screen: a click skips the intro animation (0x9f6838, state
   0x9f8e54); else, no dialog: by page 0x9f8f10 (1..6) the page's mouse handler (profile_44be00, profile_44c190,
   profile_44c390, profile_44c400, profile_44c480) and its keys: up / down held with key repeat (0x76d37c /
   0x680bb4), Enter / Esc, and on the list the arrows move the cursor 0x9f8d30 over the 3 x 3 grid (sound 2) */
LIFT_PLAIN(profile_processInput, 44c560)

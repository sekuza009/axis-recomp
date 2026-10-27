/* batch 133 (lifted/grp79.c): the mission-select screen */
#include "lifted/grp79.c"
/* 0x449a50 missionsel_drawScreen(): the mission-select screen for mission 0x9f63b4 (no direct callers: reached
   through a screen table): frame (window 0x9f6308..), the title "<n>ST / ND / RD / TH <0x75f1a4>  [ <map> ]" (map
   names 0x907b30, 0x20 apart); the map preview, looked up first ("<0x680bc4><map>/<map>", tex_getIdByName into
   0x9da324) when 0x9f63b0 asks for it, in a yellow frame with arrows; three lines "<label> : <value>" from the
   0x5c-byte mission record (0x9db99c): its kind (+0x48, a 0x75c9a4 string) and two values (+0x50, +0x4c; zero
   shows a text); the allies (+0x24 count, +0x28 portraits from the 3 x 3 atlas 0x4dfa00) and the enemies (+0
   count, +4 portraits; outside 0..8 "???") in framed rows; two buttons (0x75f6a4); the border; then a dimmed
   screen with the message 0x75f7a4 / 0x74de24 */
LIFT_PLAIN(missionsel_drawScreen, 449a50)

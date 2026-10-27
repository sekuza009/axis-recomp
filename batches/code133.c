/* batch 132 (lifted/grp78.c): the main menu */
#include "lifted/grp78.c"
/* 0x442050 menu_mainMenu(): the main menu: unless it is flying in (0x9eeaa8) the cursor is tested against six
   panels (0x4deb80, 11 dwords each): a hit (unless locked, 0x9eeab4) lights the panel (0x680398, glow restarted
   when it changes, 0x907b24) and resets the idle time 0x9dda80 and the hint fade (0x9eea8c, 0x9dd948); no hit
   adds to the idle time. Flying in counts frames (0x9eeab0) and eases the depth 0x9eea90 to -550. The tunnel
   (missionsel_448140's layout at depth 0x9eea90), then the hovered panel's caption (0x7501a4, 0x80 apart) or,
   idle for long enough and nothing else open (0x680370, 0x9eeab4), the "AUTOPLAY-F1" hint fading in and out */
LIFT_PLAIN(menu_mainMenu, 442050)

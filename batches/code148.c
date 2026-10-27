/* batch 147 (lifted/grp93.c): the menu textures */
#include "lifted/grp93.c"
/* 0x430ca0 menu_loadIntroTextures(): the menu's textures by name ("iftex/m_intro1".."4", "m2_intro1".."4", the
   spirals, menu pairs, cursor, option, cylinder, corner, character, boxscreen, gameconnect, ...) into their globals
   (the intro frames, 0x9db0a4 the button texture, 0x4e0cd0 the tunnel, 0x4dfa00 the portraits, 0x76d36c, ...),
   drawing the loading screen (intro_41f100, progress 0x4dda34 + 1 each step) between the groups and waiting 2.0
   once (intro_41e730) */
LIFT_PLAIN(menu_loadIntroTextures, 430ca0)

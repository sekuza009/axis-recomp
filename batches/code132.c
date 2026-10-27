/* batch 131 (lifted/grp77.c): screen dispatchers over the rebuilt screens */
#include "lifted/grp77.c"
/* 0x4434f0 mainmenu_4434f0(): the map-select dialog (mainmenu_442e10), or only its frame while a message is open */
LIFT_PLAIN(mainmenu_4434f0, 4434f0)
/* 0x40cf80 lobbyPlayer_draw(): the arena tunnel (arena_4091b0), then in modes other than 0 / 1 (0x4dbb3c) and
   outside sub-state 5 (0x4db51c) the arena name dialog (arena_409bc0) or, while a message is open, its frame */
LIFT_PLAIN(lobbyPlayer_draw, 40cf80)
/* 0x427830 setup_427830() / 0x427880 setup_427880(): the setup tunnel (setup_423e50), then in modes other than
   0 / 1 (0x4ddcec) and not on tab 0x29a (0x4ddac8) the sound (setup_424810) / options (setup_425460) dialog or,
   while a message is open, its frame */
LIFT_PLAIN(setup_427830, 427830)
LIFT_PLAIN(setup_427880, 427880)
/* 0x44f5f0 profile_44f5f0() / 0x44f740 profile_44f740(): while the cursor glides (0x76d42c) it moves a share of
   the way to (0x67ef34, 0x67fb38) by 0x4b071c and the glide time 0x680bc0 runs down (then ends); the profile
   screen (mainmenu_drawScreen), then the two-button dialog (profile_44e180 / profile_44e3e0) or, while a message
   is open, its frame */
LIFT_PLAIN(profile_44f5f0, 44f5f0)
LIFT_PLAIN(profile_44f740, 44f740)

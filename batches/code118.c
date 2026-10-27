/* batch 117 (lifted/grp63.c): more menu screens over the native text passes */
#include "lifted/grp63.c"
/* 0x412450 armc_412450(): the armour screen's three mode tabs: a textured tab each (texture 0x9db0a4), the current
   mode (0x4dc798) brighter, and their labels (0x7565a4, 0x80 apart) in the selected / normal colours */
LIFT_PLAIN(armc_412450, 412450)
/* 0x445520 skirmish_445520(): the briefing typewriter: while text is shown (offset 0x9ef1ec into 0x9eeba4) and not
   finished (0x9f105c) or skipped (0x4d7348), every 1.4 of the timer 0x9f16b8 shows one more character (a CR LF or a
   double-byte character at once) by copying the text so far to 0x9f1064; drawn in the briefing window, with a
   blinking cursor bar while still typing */
LIFT_PLAIN(skirmish_445520, 445520)
/* 0x44dc60 profile_44dc60(): the profile message window: frame (0x4deb50), title 0x751d24, the OK button
   (texture 0x9db0a4) and its label 0x7517a4, the frame's border */
LIFT_PLAIN(profile_44dc60, 44dc60)
/* 0x40b550 arena_drawCustomOption() / 0x43bde0 room_drawCustomOption(): the map preview (reloaded first when
   0x680cd0 is set: arena_40b420 / room_43bcb0) or, for custom rules (0x4db54a / 0x4df9ea), a dark box saying
   "CUSTOM"; a yellow frame round it */
LIFT_PLAIN(arena_drawCustomOption, 40b550)
LIFT_PLAIN(room_drawCustomOption, 43bde0)

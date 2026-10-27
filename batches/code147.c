/* batch 146 (lifted/grp92.c): the armour screen's part lists */
#include "lifted/grp92.c"
/* 0x40da40 armc_buildPartLists(): the unlocked part lists up to a level (0x4dc784, also 0x4dc870): in network mode
   (0x4dc24c == 3) the player level 0x9dd5d8 - 1, else the progress (our patch's helper at 0xb68e80 reads 0x9f181c,
   clamped; 0x7f and above become 14): for each level up to it the five static tables (0x4aebd0.., 0x28 bytes a
   level: a count and the part numbers) are appended to the five lists (0x4dc3e8 / 0x4dcd6c / 0x4dc964 / 0x4dc89c /
   0x4dbd7c, counts 0x4dc780 / 0x4dcc60 / 0x4dca90 / 0x4dca94 / 0x4dc890); then the current choices are checked
   against them */
LIFT_PLAIN(armc_buildPartLists, 40da40)

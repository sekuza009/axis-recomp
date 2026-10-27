/* batch 192 (lifted/grp148.c): item pickups */
#include "lifted/grp148.c"
/* 0x48ed90 item_update(dt) (thiscall on the scene, ret 4): the actors' pickup flags cleared; every item (0x28-byte
   records from +0x20fadf8, count +0x20fcd38; its type +0 into the 0x90-byte type table +0x20f3ae0, state +0x20,
   timer +0x24, position +0xc): a taken item respawns after its type's time (+0x48, with its sound), a present one
   is taken by the first live actor near enough, by type: health, armour, ammo, weapons, power-ups, the message
   formatted (0x46c5f0 / 0x46c710, stubbed) and the pickup sound (sound_play3D, stubbed) */
static THISCALL DWORD item_update(char *s, DWORD dt) { DWORD v[1] = { dt }; return run_lifted(lift_48ed90, (DWORD)s, 1, v); }

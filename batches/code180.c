/* batch 179 (lifted/grp129.c): the king-of-the-hill ranking and a bullet's damage, both on the scene's actor records */
#include "lifted/grp129.c"
/* 0x462150 msg_newKing() (thiscall on the scene, BUF in the tests): the teams' counts from the 16 player records
   (+0x1eccb88, stride 0x8888; empty slots by the player table 0x9f9840), the ranking of the players by frags
   (+0x1eccb54) and deaths (+0x1eccb58) into the tables +0x23428f6 / +0x2342936, a new leader announced */
LIFT_PLAIN(msg_newKing, 462150)
/* 0x460000 bullet_playImpactSound(target, attacker, damage, kind, a5, a6) (thiscall on the scene, ret 0x18): an active
   target's damage scaled by the attacker's weapon kind (0..9: the player's levels at 0x9f9068) and their flags
   (+0x1cd9798), taken from its shield and armour (+0x1cd94d0 / +0x1cd94d4), the hit recorded, a sound */
static THISCALL DWORD bullet_playImpactSound(char *scene, DWORD t, DWORD a, DWORD d, DWORD k, DWORD a5, DWORD a6)
{
	DWORD v[6] = { t, a, d, k, a5, a6 };
	return run_lifted(lift_460000, (DWORD)scene, 6, v);
}

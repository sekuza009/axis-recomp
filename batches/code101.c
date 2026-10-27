/* batch 100 (lifted/grp46.c) */
#include "lifted/grp46.c"
/* 0x461250 (thiscall on the scene) armc_461250(name, v, team, head, chest, arm, leg, booster, item0..5): the
   arm-customise screen's whole mech at once (armc_461320 / armc_461370 / match_4613a0, the five part pickers, the six
   item slots), and the edited player marked used (FUN_00474390) */
static THISCALL DWORD armc_461250(char *sc, DWORD name, DWORD v, DWORD team, DWORD head, DWORD chest, DWORD arm, DWORD leg,
                                  DWORD booster, DWORD i0, DWORD i1, DWORD i2, DWORD i3, DWORD i4, DWORD i5)
{
	DWORD a[14] = { name, v, team, head, chest, arm, leg, booster, i0, i1, i2, i3, i4, i5 };   /* the hook's real arguments */
	return run_lifted(lift_461250, (DWORD)sc, 14, a);
}
/* 0x4351c0 lobby_checkReservedName3() / 0x405cf0 lobby_checkReservedName2(): the player name the lobby sends
   (0x5b1b30 / 0x4ded20) against the reserved names (the developer's, 0x4ad4b8..0x4ad554): a reserved one gives
   status 0x18 / 0x16 (0x5b1b50 / 0x4ded40); otherwise the login packet is filled in (name, mech bytes, address via
   0x4532e0, the version strings) in the send buffer (0xa0b328 / 0xa0b310) and sent (net_4521c0); Name2 first
   connects (net_connect, messages through FUN_0041ee40 on failure) */
LIFT_PLAIN(lobby_checkReservedName3, 4351c0)
LIFT_PLAIN(lobby_checkReservedName2, 405cf0)

/* batch 91 (lifted/grp37.c) */
#include "lifted/grp37.c"
/* (thiscall on the scene; engine at +0x1f36c8) armc_set{Head,Chest,Arm,Leg,Booster}Index(i): the arm-customise
   screen's part choice, wrapped by the part table's count ((i % n + n) % n), kept at +0x234244a..+0x234245a and,
   with an edited player (+0x234240d >= 0), set on it (actor_setActorType...InfoBy) */
static THISCALL DWORD armc_setHeadIndex(char *sc, DWORD i) { DWORD v[1] = { i }; return run_lifted(lift_4613d0, (DWORD)sc, 1, v); }
static THISCALL DWORD armc_setChestIndex(char *sc, DWORD i) { DWORD v[1] = { i }; return run_lifted(lift_461410, (DWORD)sc, 1, v); }
static THISCALL DWORD armc_setArmIndex(char *sc, DWORD i) { DWORD v[1] = { i }; return run_lifted(lift_461450, (DWORD)sc, 1, v); }
static THISCALL DWORD armc_setLegIndex(char *sc, DWORD i) { DWORD v[1] = { i }; return run_lifted(lift_461490, (DWORD)sc, 1, v); }
static THISCALL DWORD armc_setBoosterIndex(char *sc, DWORD i) { DWORD v[1] = { i }; return run_lifted(lift_4614d0, (DWORD)sc, 1, v); }
/* 0x461510 (thiscall) armc_461510(slot, item): the same for an item slot (+0x234245e + slot * 4) */
static THISCALL DWORD armc_461510(char *sc, DWORD slot, DWORD item) { DWORD v[2] = { slot, item }; return run_lifted(lift_461510, (DWORD)sc, 2, v); }
/* 0x46fed0 (thiscall) actor_46fed0(): bind the textures of every shape in an object list (count +0x10, 100-byte
   entries at +0x14, shape first; FUN_00466650) */
static THISCALL DWORD actor_46fed0(char *list) { return run_lifted(lift_46fed0, (DWORD)list, 0, NULL); }
/* 0x474210 (thiscall) match_474210(player, name, v, team, head, chest, arm, leg, booster, item0..5) /
   0x4742f0 load_4742f0(player, record): set up a player completely (name, +0x44 value, team, the five part types,
   the six item slots) and mark it used (FUN_00474390); load_4742f0 takes them from a record (+4 value, +8 name,
   +0x28 team, +0x2c.. parts, +0x40.. items) */
static THISCALL DWORD match_474210(char *eng, DWORD p, DWORD name, DWORD v, DWORD team, DWORD head, DWORD chest, DWORD arm,
                                   DWORD leg, DWORD booster, DWORD i0, DWORD i1, DWORD i2, DWORD i3, DWORD i4, DWORD i5)
{
	DWORD a[15] = { p, name, v, team, head, chest, arm, leg, booster, i0, i1, i2, i3, i4, i5 };   /* the hook's real arguments */
	return run_lifted(lift_474210, (DWORD)eng, 15, a);
}
static THISCALL DWORD load_4742f0(char *eng, DWORD p, DWORD rec) { DWORD v[2] = { p, rec }; return run_lifted(lift_4742f0, (DWORD)eng, 2, v); }
